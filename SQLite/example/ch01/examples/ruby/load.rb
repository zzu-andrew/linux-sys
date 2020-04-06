#!/usr/bin/env ruby

require 'sqlite3'

db = SQLite3::Database.new( "seinfeld.db" )
db.results_as_hash = true

food_id = 1
File.open('foods.txt') do |f|
  f.each do |line|
    items = line.split('|')

    type = items[0]
    food = items[1]
    eps = items[2].split(',')

    print "insert into foods values(%i, '%s', '%s');\n" % [food_id,type,food]

    eps.each do |e| 
      e = e.strip

      sql = "select id from episodes where name='%s'" % e
      result = db.query(sql)

      rows = 0
      result.each do |row|
        print "insert into foods_episodes(%i, %i);\n" % [food_id, row['id']]
        rows += 1
      end

      if rows == 0
        print "NONE #{food}, #{sql}\n"
      end

    end

    food_id += 1

  end
end




#db.query(sql)

