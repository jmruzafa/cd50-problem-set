from flask import Flask, render_template, json, request, redirect, url_for
import sqlite3
from datetime import date
from flask import g
import codecs

DATABASE = 'database.db'
app = Flask(__name__)

def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
        db.row_factory = sqlite3.Row
    return db

def query_db(query, args=(), one=False):
    cur = get_db().execute(query, args)
    rv = cur.fetchall()
    cur.close()
    return (rv[0] if rv else None) if one else rv

def make_dicts(cursor, row):
    return dict((cursor.description[idx][0], value)
                for idx, value in enumerate(row))

@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()


@app.route('/')
def main():
    notes = query_db('select * from note')
    return render_template('index.html', notes = notes)

@app.route('/edit/<id>', methods=['GET'])
def edit(id):
    note = query_db('select * from note where id= ?', id, one=True)
    if note is None:
        return render_template('index.html')
    else:
        date_now = date.today().strftime('%Y-%m-%d')
        return render_template('edit.html', note = note, date = date_now)

@app.route('/update', methods=['POST'])
def update():
        message = "Note has been updated"
        try:

            noteid = request.form['note_id']
            title = request.form['note_title'].replace("'","''")
            notetext = request.form['note_text'].replace("'","''")
            duedate = request.form['due_date']
            created = date.today().strftime('%Y-%m-%d')
            #_colour = request.form['colour']
            # validate the received values
            if title and notetext and noteid:
                note = query_db('select * from note where id= ?', noteid, one=True)
                conn = get_db()
                c = conn.cursor()
                if note is not None:
                    query = f"update note SET  title = '{title}',  text = '{notetext}', duedate = '{duedate}' where id={noteid}" 
                    c.execute(query)
                    conn.commit()
                else:
                    query = f"insert into note (title, created, text, duedate) values ('{title}','{created}','{note}','{duedate}')"
                return redirect('/')
            else:
                message = "Title and note text are mandatory"
        except Exception as e:
            message = str(e)
        finally:
            return render_template("result.html", message = message)


@app.route('/new')
def new():
    date_now = date.today().strftime('%Y-%m-%d')
    return render_template('new.html', error = None, date = date_now)

@app.route('/add', methods=['POST'])
def add():
        message = "New note added"
        try:
            title = request.form['note_title'].replace("'","''")
            note = request.form['note_text'].replace("'","''")
            duedate = request.form['due_date']
            created = date.today().strftime('%Y-%m-%d')
            #_colour = request.form['colour']
            # validate the received values
            if title and note:
                query = f"insert into note (title, created, text, duedate) values ('{title}','{created}','{note}','{duedate}')"
                conn = get_db()
                c = conn.cursor()
                c.execute(query)
                conn.commit()
            else:
                message =  "Title and note text are mandatory"
        except Exception as e:
                message = str(e)
        finally:
            return render_template("result.html", message = message)

@app.route('/delete/<id>')
def delete(id):
    note = query_db('select * from note where id= ?', id, one=True)
    if note is None:
        message = "No note found"
        return render_template("result.html", message = message)
    else:
        conn = get_db()
        c = conn.cursor()
        c.execute("delete from note where id=?", id)
        conn.commit()
    return redirect('/')


if __name__ == "__main__":
    app.run(port=5002)
