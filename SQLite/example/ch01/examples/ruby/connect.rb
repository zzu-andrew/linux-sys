#!/usr/bin/env ruby

require 'sqlite3'

db = SQLite3::Database.new("seinfeld.db")
db.results_as_hash = true

result = db.query('SELECT * FROM foods limit 10')
result.each do |row|
  puts row['name']
end
