# Finance

CS50 Week 9 - Flask Web Application

## What it is

A web application that simulates stock trading with real-time stock quotes.

## Features

- **Register/Login** - User authentication
- **Quote** - Look up real-time stock prices
- **Buy** - Purchase shares of stock
- **Sell** - Sell shares you own
- **Portfolio** - View your holdings and total value
- **History** - Transaction history
- **Cash Management** - Add additional cash to account

## How it works

Uses Flask framework, SQLite database, and IEX Cloud API for real-time stock data. Tracks user portfolios and transaction history.

## Usage
```bash
flask run
```

Then visit `http://localhost:5000` in your browser.

## Technologies

- Python/Flask
- SQLite
- Jinja templates
- Bootstrap (CSS)
- IEX Cloud API

## Files

- `app.py` - Main Flask application
- `helpers.py` - Helper functions (login required, API calls)
- `finance.db` - SQLite database
- `templates/` - HTML templates
- `static/` - CSS and images

## Problem Description

[CS50 Finance Problem](https://cs50.harvard.edu/x/2024/psets/9/finance/)
