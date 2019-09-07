from pysqlite2 import dbapi2 as sqlite3

con = sqlite3.connect("foods.db")
cur = con.cursor()
cur.execute('insert into episodes (name) values (?)', ('Soup Nazi'))
cur.close()

cur = con.cursor()
cur.execute('insert into episodes (name) values (:name)', {'name':'Soup Nazi'})
cur.close()
