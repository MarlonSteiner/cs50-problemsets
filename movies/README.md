# Movies

CS50 Week 7 - SQL

## What it is

SQL queries on an IMDb database of movies, actors, directors, and ratings.

## What it does

13 SQL queries that answer questions about movies, such as:
- Finding movies from specific years
- Searching for actors/directors
- Analyzing ratings
- Finding connections between movies and people

## Database

The `movies.db` database contains tables:
- `movies` - Movie titles and years
- `people` - Actors and directors
- `stars` - Which actors starred in which movies
- `directors` - Which directors directed which movies
- `ratings` - IMDb ratings for movies

## Setup

Download the database from [CS50's website](https://cdn.cs50.net/2024/fall/psets/7/movies.zip).

## Usage
```bash
sqlite3 movies.db < 1.sql
```

Or interactively:
```bash
sqlite3 movies.db
sqlite> .read 1.sql
```

## Files

- `1.sql` through `13.sql` - My query solutions

## Problem Description

[CS50 Movies Problem](https://cs50.harvard.edu/x/2024/psets/7/movies/)
