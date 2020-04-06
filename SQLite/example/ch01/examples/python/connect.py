#!/usr/bin/env python

from pysqlite2 import dbapi2 as sqlite

con = sqlite.connect("seinfeld.db")
cur = con.cursor()
cur.execute('SELECT * FROM foods LIMIT 10')

row = cur.fetchone()
while row:
    print row[2]
    row = cur.fetchone()
