#!/usr/bin/env python

import apsw

connection=apsw.Connection(":memory:")
cursor=connection.cursor()

c = connection.cursor()
c.execute('create table types(i int, f float, t text, b blob, n)')
c.execute("insert into types values (1, 1.1, '1.1', X'01', NULL)")

for row in cursor.execute('SELECT * FROM types'):
    d = cursor.getdescription()
    i = 0
    for field in row:
        print "%s %5s %-6s %-10s" % ( d[i][0],
                                      d[i][1],
                                      str(field),
                                      type(field) )
        i += 1

