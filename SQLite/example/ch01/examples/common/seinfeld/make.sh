#!/bin/zsh

# Build base schema
cat schema.sql > seinfeld.sql
cat episodes.sql >> seinfeld.sql

echo 'Making database'
rm seinfeld.db
sqlite3 seinfeld.db < seinfeld.sql

# Generate food SQL and add
./make_foods_sql.rb > foods.sql

# Construct database
echo 'Adding foods'
sqlite3 seinfeld.db < foods.sql
