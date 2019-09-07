#!/usr/bin/env python

import apsw, string

connection=apsw.Connection(":memory:")

def hello_newman(*args):
    if len(args) > 0:
        return 'Hello %s' % string.join(args, ', ')
    return 'Hello Jerry'

connection.createscalarfunction("hello_newman", hello_newman)

c = connection.cursor()
print c.execute("select hello_newman()").next()[0]
print c.execute("select hello_newman('Elaine')").next()[0]
print c.execute("select hello_newman('Elaine', 'Jerry')").next()[0]
print c.execute("select hello_newman('Elaine', 'Jerry', 'George')").next()[0]

