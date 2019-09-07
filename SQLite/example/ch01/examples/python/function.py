#!/usr/bin/env python

import string
from pysqlite2 import dbapi2 as sqlite

def hello_newman(*args):
    if len(args) > 0:
        return 'Hello %s' % string.join(args, ', ')
    return 'Hello Jerry'

con = sqlite.connect(":memory:")
con.create_function("hello_newman", -1, hello_newman)
cur = con.cursor()

cur.execute("select hello_newman()")
print cur.fetchone()[0] 

cur.execute("select hello_newman('Elaine')")
print cur.fetchone()[0] 

cur.execute("select hello_newman('Elaine', 'Jerry')")
print cur.fetchone()[0] 

cur.execute("select hello_newman('Elaine', 'Jerry', 'George')")
print cur.fetchone()[0] 
