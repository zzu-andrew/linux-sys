#!/usr/bin/env python

import apsw, string

connection=apsw.Connection("seinfeld.db")

def step(context, *args):
    context['value'] += args[0]
        
def finalize(context):
    return context['value']

def pysum():
    
    return ({'value' : 0}, step, finalize)

connection.createaggregatefunction("pysum", pysum)

c = connection.cursor()
print c.execute("select pysum(id) from foods").next()[0]

