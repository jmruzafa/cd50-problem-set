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

# Configure SQLite database
# You need to create a database called finance.db and a table called users
# Columns: id (INTEGER PRIMARY KEY), username (TEXT NOT NULL), hash (TEXT NOT NULL)
# Another table for purchases is also needed
# Columns: id (INTEGER PRIMARY KEY), user_id (INTEGER NOT NULL), symbol (TEXT NOT NULL), shares (INTEGER NOT NULL), price (NUMERIC NOT NULL), timestamp (DATETIME NOT NULL)
# Ensure UNIQUE indexes on appropriate fields
# Define indexes on fields for searching
# Use appropriate SQLite types

db = SQL("sqlite:///finance.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get user's stocks and cash balance from database
    user_id = session["user_id"]
    stocks = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM purchases WHERE user_id = ? GROUP BY symbol having total_shares > 0",
                        user_id)

    rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = 0
    if (len(rows) == 1 ):
        # Initialize total value of portfolio
        cash = rows[0]["cash"]

        total_portfolio_value = cash

    # Calculate total value of each holding and update total portfolio value
    if(len(stocks) > 0):
        for stock in stocks:
            quote_info = lookup(stock["symbol"])
            if quote_info:
                stock["price"] = quote_info["price"]
                stock["total_value"] = stock["total_shares"] * stock["price"]
                total_portfolio_value += stock["total_value"]

    return render_template("index.html", stocks=stocks, cash_balance=cash, total_portfolio_value=total_portfolio_value)


@app.route("/history")
@login_required
def history():
    """Show transaction history"""
    # Get user's transaction history from purchases table
    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM purchases WHERE user_id = ? ORDER BY timestamp DESC", user_id)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Get symbol from form
        symbol = request.form.get("symbol")

        # Check if symbol was submitted
        if not symbol:
            return apology("Please provide a stock symbol", 400)

        # Lookup stock quote
        quote_info = lookup(symbol)

        # Check if quote was found
        if not quote_info:
            return apology("Invalid stock symbol", 400)

        # Render quoted template with stock information
        return render_template("quoted.html", quote=quote_info)

    else:
        # Display form for getting stock symbol
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Get form data
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate input
        if not username or not password or not confirmation:
            return apology("Please provide username and password", 400)
        elif password != confirmation:
            return apology("Passwords do not match", 400)

         # Hash password
        hashed_password = generate_password_hash(password)

        # Insert new user into database
        try:
            new_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)
        except:
                #username already exists
                return apology("Username already exists", 400)

        # Remember which user has logged in
        session["user_id"] = new_user
        # Redirect to login page
        return redirect("/")

    else:
        # Display registration form
        return render_template("register.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get symbol and shares from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate symbol and shares
        if not symbol:
            return apology("Please provide a stock symbol", 400)
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Shares must be a positive integer")
        else:
            shares = int(shares)

        # Fetch current price of the stock
        quote_info = lookup(symbol)
        if not quote_info:
            return apology("Invalid stock symbol", 400)

        price_per_share = quote_info["price"]
        total_cost = price_per_share * shares

        # Get user's cash balance
        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        if len(user) > 0:

            cash = user[0]["cash"]  # Assuming cash balance is the fourth column (index 3) in the users table

            # Check if user has enough cash
            if cash < total_cost:
                return apology("You don't have enough cash to make this purchase", 400)

            # Deduct cost from user's cash balance
            new_cash_balance = cash - total_cost
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash_balance, user_id)

            # Record purchase in database
            db.execute("INSERT INTO purchases (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, 'buy')",
                    user_id, symbol, shares, price_per_share)

            return redirect("/")
        else:
            return apology("The user does not exist. Please, contact support team", 404)

    else:
        return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Get symbol and shares from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # Validate symbol and shares
        if not symbol:
            return apology("Please provide a stock symbol", 400)
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Shares must be a positive integer")
        else:
            shares = int(shares)

        # Continue with the rest of the buy logic

        # Get user's stocks from database
        user_id = session["user_id"]
        stocks = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM purchases WHERE user_id = ? AND symbol = ? GROUP BY symbol HAVING total_shares > 0",
                            user_id, symbol)

        # Calculate total shares owned
        total_shares_owned = stocks[0]["total_shares"]

        # Validate shares to sell
        if total_shares_owned < shares:
            return apology("You don't have enough shares to sell", 400)


        # Determine total value of shares to sell
        price_per_share = lookup(symbol)["price"]
        total_value = price_per_share * shares

        # Update user's cash balance
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        new_cash_balance = user_cash[0]["cash"] + total_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   new_cash_balance, user_id)

        # Record sell transaction in database
        db.execute("INSERT INTO purchases (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, 'sell')",
                   user_id, symbol,-shares, price_per_share)

        return redirect("/")

    else:
        # Fetch user's stocks for dropdown
        user_id = session["user_id"]
        stocks = db.execute("SELECT DISTINCT symbol, SUM(shares) AS total_shares FROM purchases WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id)

        return render_template("sell.html", stocks=stocks)


if __name__ == "__main__":
    app.run(debug=True)
