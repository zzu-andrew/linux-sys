#!/usr/bin/env ruby

require 'sqlite3'

db = SQLite3::Database.new('foods.db')

stmt = db.prepare('select name from episodes')

stmt.execute do | result |
  result.each do | row |
    puts row[0]
  end
end

result = stmt.execute()
result.each do | row |
  puts row[0]
end

stmt.close()
