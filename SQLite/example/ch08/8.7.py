from pysqlite2 import dbapi2 as sqlite3

con = sqlite3.connect("foods.db")
cur = con.cursor()
cur.execute('select * from foods limit 10')

for row in cur:
    print row[2]
