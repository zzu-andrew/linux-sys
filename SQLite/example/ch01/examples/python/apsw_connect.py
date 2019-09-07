#!/usr/bin/env python

import apsw

connection=apsw.Connection("seinfeld.db")
cursor=connection.cursor()

for row in cursor.execute("SELECT * FROM foods LIMIT 10"):
    print row[2], type(row[1])


