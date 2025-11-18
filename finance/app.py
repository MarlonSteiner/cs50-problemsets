import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    # Ensure responses aren't cached
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    # Show portfolio of stocks
    user_id = session["user_id"]

    # Get user's current cash balance
    user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]["cash"]

    # Get user stocks and shares
    stocks = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = :user_id
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id=user_id)

    # Get current prices and calculate totals
    grand_total = user_cash
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["total"] = stock["price"] * stock["total_shares"]
        grand_total += stock["total"]

    # Format currency values
    for stock in stocks:
        stock["price"] = usd(stock["price"])
        stock["total"] = usd(stock["total"])

    return render_template("index.html", stocks=stocks, cash=usd(user_cash), total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Buy shares of stok
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Stock not provided")

        symbol = symbol.upper()

        # Validate shares input
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("Invalid number of shares")
        except ValueError:
            return apology("Invalid number of shares")

        quote = lookup(symbol)
        if quote is None:
            return apology("Stock not found")

        price = quote["price"]
        total_cost = price * shares

        # Get user cash
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]["cash"]

        if cash < total_cost:
            return apology("Not enough cash")

        db.execute("UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
                   total_cost=total_cost, user_id=user_id)

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=user_id, symbol=symbol, shares=shares, price=price)

        # Include raw price numbers in flash message
        flash(
            f"Bought {shares} shares of {symbol} at {price:.2f} per share for a total of {total_cost:.2f}!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    # Show history of transactions
    user_id = session["user_id"]

    try:
        # Get only the current user's transactions
        history = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id=user_id)
    except Exception as e:
        print("Error querying transactions:", e)
        history = []

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    # Log user in

    # Forget user_id
    session.clear()

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        # Ensure username submittion
        if not username:
            return apology("must provide username", 400)

        # Ensure password submittion
        elif not password:
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return apology("invalid username and/or password", 400)

        # Rememberr which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    # Log user out

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    # Get stock quote.
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("Stock not found.", 400)
        return render_template("quote.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    # Register user
    session.clear()

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Checkusername
        if not username:
            return apology("must provide username", 400)

        # Check password
        elif not password:
            return apology("must provide password", 400)

        # Check confirmation
        elif not confirmation:
            return apology("must confirm confirmation", 400)

        # Confirm Password
        elif password != confirmation:
            return apology("must confirm password", 400)

        # Check duplicate name
        existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(existing_user) > 0:
            return apology("username already exists", 400)

         # Hash the password before storing
        hashed_password = generate_password_hash(password)

        # Insert user into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)

        # Go to login
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session["user_id"]
    stocks = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = :user_id
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id=user_id)

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Error handling
        if not symbol:
            return apology("provide symbol")
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("provide positive integer")

        symbol = symbol.upper()
        shares = int(shares)

        # Stock search
        for stock in stocks:
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("not enough shares")

                quote = lookup(symbol)
                if not quote:
                    return apology("stock not found")

                price = quote["price"]
                total_sale = shares * price

                # Update amount
                db.execute("UPDATE users SET cash = cash + :total_sale WHERE id = :user_id",
                           total_sale=total_sale, user_id=user_id)

                # Insert transaction as negative shres
                db.execute("""
                    INSERT INTO transactions (user_id, symbol, shares, price)
                    VALUES (:user_id, :symbol, :shares, :price)
                """, user_id=user_id, symbol=symbol, shares=-shares, price=price)

                flash(f"Sold {shares} shares of {symbol} for {usd(total_sale)}!")
                return redirect("/")

        return apology("symbol not found")

    else:
        return render_template("sell.html", stocks=stocks)
