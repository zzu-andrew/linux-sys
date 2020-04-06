#!/usr/bin/env python

from pysqlite2 import dbapi2 as sqlite

class pysum:
    def __init__(self):
        self.sum = 0

    def step(self, value):
        self.sum += value

    def finalize(self):
        return self.sum

con = sqlite.connect("seinfeld.db")
con.create_aggregate("pysum", 1, pysum)
cur = con.cursor()
cur.execute("select pysum(id) from foods")
print cur.fetchone()[0] 
