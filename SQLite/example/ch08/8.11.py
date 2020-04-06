from pysqlite2 import dbapi2 as sqlite3

# The Python function
def hello_newman():
    return 'Hello Jerry'

con = sqlite3.connect(":memory:")
con.create_function("hello_newman", 0, hello_newman)
cur = con.cursor()

cur.execute("select hello_newman()")
print cur.fetchone()[0]
