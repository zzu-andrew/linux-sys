from pysqlite2 import dbapi2 as sqlite3

con = sqlite3.connect("foods.db")
cur = con.cursor()

episodes = ['Soup Nazi', 'The Fusilli Jerry']
cur.executemany('insert into episodes (name) values (?)', episodes)
cur.close()
con.commit()
