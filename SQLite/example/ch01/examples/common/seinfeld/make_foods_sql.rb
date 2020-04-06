#!/usr/bin/env ruby

require 'sqlite3'

db = SQLite3::Database.new( "seinfeld.db" )

food_id = 1
File.open('foods.txt') do |f|
  f.each do |line|
    items = line.split('|')

    food_type = items[0]
    food_name = items[1]
    eps = items[2].split(',')

    # Get the food type id
    sql = "select id from food_types where name='%s'" % food_type
    food_type_id = db.query(sql).next[0]

    # Create the food record
    print "insert into foods values(%i, %i, '%s');\n" % [food_id,food_type_id,food_name]

    eps.each do |e| 
      e = e.strip

      sql = "select id from episodes where name='%s'" % e
      result = db.query(sql)

      rows = 0
      result.each do |row|
        # Create the food-episode record
        print "insert into foods_episodes values(%i, %i);\n" % [food_id, row[0]]
        rows += 1
      end

      if rows == 0
        print "NONE #{food_name}, #{sql}\n"
      end

    end

    food_id += 1

  end
end
