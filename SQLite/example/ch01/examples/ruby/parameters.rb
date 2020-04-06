#!/usr/bin/env ruby

require 'sqlite3'

db = SQLite3::Database.new("seinfeld.db")
db.results_as_hash = true

# Named paramters

stmt = db.prepare('SELECT * FROM foods where name like :name')
stmt.bind_param(':name', '%Peach%')

stmt.execute() do |result|
  result.each do |row|
    puts row['name']
  end
end

# Positional paramters

stmt = db.prepare('SELECT * FROM foods where name like ?')
stmt.bind_params('%Bobka%')

stmt.execute() do |result|
  result.each do |row|
    puts row['name']
  end
end

# Free read lock
stmt.close()
