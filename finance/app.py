import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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

    this_user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    total_balance = user_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    portfolio = db.execute(
        "SELECT stock_name, stock_symbol, SUM(number_shares) FROM transactions WHERE username = ? GROUP BY stock_symbol", this_user[0]["username"])
    prices = []

    for i, item in enumerate(portfolio):
        item_price = lookup(item["stock_symbol"])["price"]
        prices.append(item_price)
        total_balance += portfolio[i]["SUM(number_shares)"] * prices[i]

    return render_template("index.html", portfolio=portfolio, prices=prices, user_cash=user_cash, total_balance=total_balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure stock symbol was submitted
        if not symbol:
            return apology("must provide stock symbol")

        # Lookup quote for stock symbol
        quotes = lookup(symbol)

        # Ensure quote for symbol was retrieved
        if quotes == None:
            return apology("quote symbol doesn't exist")

        # Ensure number of shares is a positive integer
        # Check if shares entered is an integer
        try:
            shares = int(shares)
        except:
            return apology("number of shares must be a positive integer")
        # Check if shares entered > 0
        if shares <= 0:
            return apology("shares must be greater than 0", 400)

        # Retrieve username and associated cash
        this_user_id = session["user_id"]
        this_user_data = db.execute("SELECT * FROM users WHERE id = ?", this_user_id)
        this_username = this_user_data[0]["username"]
        cash = this_user_data[0]["cash"]

        # Check if cash is sufficient
        price = quotes["price"]
        total = price * shares
        if cash - total < 0:
            return apology("available cash is insufficient")

        # Update user cash in users database
        updated_cash = cash - total
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            updated_cash,
            this_user_id
        )

        # Log transaction into transactions database
        db.execute(
            "INSERT INTO transactions (username, action, stock_name, stock_symbol, price, number_shares, date) VALUES(?, ?, ?, ?, ?, ?, ?)",
            this_username,
            "buy",
            quotes["name"],
            quotes["symbol"],
            quotes["price"],
            shares,
            datetime.datetime.now()
        )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    this_user_id = session["user_id"]
    this_user_data = db.execute("SELECT * FROM users WHERE id = ?", this_user_id)
    this_username = this_user_data[0]["username"]
    portfolio = db.execute(
        "SELECT * FROM transactions WHERE username = ?", this_username
    )

    return render_template("history.html", portfolio=portfolio)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Ensure stock symbol was submitted
        if not symbol:
            return apology("must provide stock symbol")

        # Lookup quote for stock symbol
        quotes = lookup(symbol)

        # Ensure quote for symbol was retrieved
        if quotes == None:
            return apology("quote symbol doesn't exist")

        # Prettify price in dollar with helper function
        quotes["price"] = usd(quotes["price"])

        # Redirect user to list of quotes
        return render_template("quoted.html", quotes=quotes)

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        this_username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not this_username:
            return apology("must provide username")

        # Ensure password was submitted
        elif not password:
            return apology("must provide password")

        # Ensure password was confirmed
        elif not password == confirmation:
            return apology("password and confirmation must be identical")

        # Add the user's entry into the database
        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        try:
            create_user = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", this_username, hash)
        except:
            return apology("username already exists")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/update", methods=["GET", "POST"])
@login_required
def update():
    """Update user password"""

    if request.method == "POST":

        this_user_id = session["user_id"]
        this_user_data = db.execute("SELECT * FROM users WHERE id = ?", this_user_id)
        current_username = this_user_data[0]["username"]

        this_username = request.form.get("username")
        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        new_password_confirmation = request.form.get("new_password_confirmation")

        # Retrieve current password for user
        user_current_password_hashed = db.execute("SELECT hash FROM users WHERE username = ?", this_username)

        # Ensure username was submitted
        if not this_username:
            return apology("must provide username")

        # Ensure username is the one of the currently logged user
        elif current_username != this_username:
            return apology("wrong username")

        # Ensure password was submitted
        elif not current_password or not new_password:
            return apology("must provide password")

        # Check that current password is correct
        # returns False/True contrary to my expectations based on the man page?
        elif check_password_hash(user_current_password_hashed, current_password):
            return apology("wrong current password")

        # Ensure password was confirmed
        elif not new_password == new_password_confirmation:
            return apology("new password and confirmation must be identical")

        # Update the user's entry into the database
        hash = generate_password_hash(new_password, method='pbkdf2:sha256', salt_length=8)
        db.execute(
            "UPDATE users SET hash = ? WHERE username = ?",
            hash,
            this_username
        )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("update.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    this_user_id = session["user_id"]
    this_user_data = db.execute("SELECT * FROM users WHERE id = ?", this_user_id)
    this_username = this_user_data[0]["username"]
    portfolio = db.execute(
        "SELECT stock_symbol, SUM(number_shares) FROM transactions WHERE username = ? GROUP BY stock_symbol", this_username
    )

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        this_user_id = session["user_id"]
        this_user = db.execute(
            "SELECT * FROM users WHERE id = ?", this_user_id
        )

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        shares = int(shares)

        # Ensure stock symbol was submitted
        if not symbol:
            return apology("must provide stock symbol")

        # Ensure number of shares is a positive integer
        if shares <= 0:
            return apology("number of shares must be a positive integer")

        # Ensure number of shares is currently in portfolio
        number_shares_for_symbol = db.execute(
            "SELECT SUM(number_shares) FROM transactions WHERE username = ? AND stock_symbol = ?", this_user[0]["username"], symbol
        )
        if shares > number_shares_for_symbol[0]["SUM(number_shares)"]:
            return apology("number of shares must currently be in portfolio")

        # Lookup quote for stock symbol
        quotes = lookup(symbol)

        # Ensure quote for symbol was retrieved
        if quotes == None:
            return apology("quote symbol doesn't exist")

        # Retrieve username and associated cash
        this_user_data = db.execute("SELECT * FROM users WHERE id = ?", this_user_id)
        cash = this_user_data[0]["cash"]
        this_username = this_user_data[0]["username"]

        # Calculate total price of sold shares
        price = quotes["price"]
        total = price * shares

        # Update user cash in users database
        updated_cash = cash + total
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            updated_cash,
            this_user_id
        )

        # Log transaction into transactions database
        db.execute(
            "INSERT INTO transactions (username, action, stock_name, stock_symbol, price, number_shares, date) VALUES(?, ?, ?, ?, ?, ?, ?)",
            this_username,
            "sell",
            quotes["name"],
            quotes["symbol"],
            quotes["price"],
            -shares,
            datetime.datetime.now()
        )

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        return render_template("sell.html", portfolio=portfolio)
