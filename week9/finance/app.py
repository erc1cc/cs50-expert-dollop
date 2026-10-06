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
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
    list = [float(stock["value"]) for stock in stocks]
    total = sum(list)

    # we need the [0] after everything so we can index into the first dictionary of the list
    users = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]
    # valuation = db.execute("SELECT * FROM users )
    valuation = float(users["cash"]) + total
    return render_template("index.html", stocks=stocks, users=users, valuation=valuation)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # when requested via GET, display form to buy a stock
    if request.method == "GET":
        return render_template("buy.html")

    # When form is submitted via POST, purchase the stock so long as the user can afford it
    if request.method == "POST":
        symbol = request.form.get("symbol")

        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                raise ValueError
        except:
            return apology("invalid number of shares", 400)

        # check for valid input
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid stock", 400)

        # check if can afford
        user_id = session["user_id"]
        # cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]
        # ^^^ this is still a dictionary [{"cash": 10000.00}]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        cost = stock["price"] * shares
        if cash < cost:
            return apology("insufficient cash", 400)
        # update money
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, user_id)

        # update database
        # CREATE TABLE transactions (
        #   id INTEGER PRIMARY KEY AUTOINCREMENT,
        #   user_id INTEGER NOT NULL,
        #   symbol TEXT NOT NULL,
        #   shares INTEGER NOT NULL,
        #   price REAL NOT NULL,
        #   value REAL NOT NULL,
        #   type TEXT NOT NULL,
        #   timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);

        # CREATE TABLE stocks (
        #     id INTEGER PRIMARY KEY AUTOINCREMENT,
        #     user_id INTEGER NOT NULL,
        #     symbol TEXT NOT NULL,
        #     price REAL NOT NULL,
        #     shares INTEGER NOT NULL,
        #     value REAL NOT NULL);
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, value, type) VALUES(?, ?, ?, ?, ?, ?)",
                   user_id, symbol, shares, stock["price"], cost, "buy")

        # check for existing stocks
        rows = db.execute("SELECT * FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol)

        if len(rows) == 0:
            # user does not have stock yet
            db.execute("INSERT INTO stocks (user_id, symbol, price, shares, value) VALUES(?, ?, ?, ?, ?)",
                       user_id, symbol, stock["price"], shares, cost)
        else:
            # user does have stock
            # we [0] to access the dictionary inside the list
            total_shares = rows[0]["shares"] + shares
            # we recalculate to avoid errors
            total_value = stock["price"] * total_shares

            db.execute("UPDATE stocks SET shares = ?, value = ? WHERE user_id = ? AND symbol = ?",
                       total_shares, total_value, user_id, symbol)

        # redirect to homepage
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    # all transactions
    stocks = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    # user
    users = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]

    return render_template("history.html", stocks=stocks, users=users)


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
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    symbol = request.form.get("symbol")
    if not symbol:
        return apology("must provide stock name", 400)

    stock = lookup(symbol)
    # lookup() function returns python object None instead of a string "None"
    if stock is None:
        return apology("invalid stock symbol", 400)

    # stock(on the right hand side) is the name of the python dictionary returned to you from lookup()
    # result is the variable from your jinja template
    return render_template("quoted.html", result=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        elif not password == confirmation:
            return apology("confirmed password does not match", 400)

        # Query database for username
        users = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Checks if username has already been registered
        # if request.form.get("username") == users:
        # ^^^ users is a list, which can never be true
        if len(users) != 0:
            return apology("username already taken", 400)

        hashed_password = generate_password_hash(password)

        # Inserts username into database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashed_password)

        # Remember which user has logged in
        user = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = user[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # when requested via GET, display the form to sell a stock
    if request.method == "GET":
        user_id = session["user_id"]
        stocks = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", user_id)
        return render_template("sell.html", stocks=stocks)

    # When the form is submitted via POST, check for errors and sell the specified
    # number of shares of stock and update the user's cash
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # check for valid input
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid stock", 400)

        user_id = session["user_id"]
        # check how many of that stock the user has
        result = db.execute(
            "SELECT * FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol)

        # check for owning the stock
        if len(result) == 0:
            return apology("you do not own any of that stock", 400)

        numberofsharesowned = result[0]["shares"]

        if shares > numberofsharesowned:
            return apology("insufficient shares", 400)

        money_from_selling = stock["price"] * shares
        remaining_shares = int(numberofsharesowned) - shares
        remaining_value = stock["price"] * remaining_shares

        # update money
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", money_from_selling, user_id)
        # log transaction
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, value, type) VALUES(?, ?, ?, ?, ?, ?)",
                   user_id, symbol, shares, stock["price"], money_from_selling, "sell")
        # update portfolio
        if remaining_shares > 0:
            db.execute("UPDATE stocks SET shares = ?, value = ? WHERE user_id = ? AND symbol = ?",
                       remaining_shares, remaining_value, user_id, symbol)
        else:
            db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol = ?", user_id, symbol)

        # redirect to homepage
        return redirect("/")


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """ Deposit Cash """
    if request.method == "GET":
        return render_template("deposit.html")

    else:
        user_id = session["user_id"]

        deposit_money = float(request.form.get("depositamt"))
        current_cash = float(db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"])
        updated_cash = deposit_money + current_cash

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, value, type)  VALUES(?, ?, ?, ?, ?, ?)",
                   user_id, "CASH", 0, deposit_money, deposit_money, "deposit")

        return redirect("/")
