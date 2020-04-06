#!/usr/bin/env ruby

<<LYRICS
Driving faster in my car,
Falling farther from just what we are
Smoke a cigarette and lie some more
These conversations kill - Falling faster in my car

Time to take her home, her dizzy head is conscience laden
Time to take a ride, it leaves today no conversation
Time to take her home, her dizzy head is conscience laden
Time to wait to long to wait to long to wait to long

Too much walkin' shoes worn thin
Too much trippin' and my soul's worn thin
Time to catch a ride it leaves today
Her name is what it means
Too much walkin' shoes worn thin

Time to take her home...

Conversations kill
LYRICS

require 'sqlite3'

db = SQLite3::Database.new("seinfeld.db")
db.results_as_hash = true

result = db.query('SELECT * FROM foods limit 10')
result.each do |row|
  puts row['name']
end

result.close()
