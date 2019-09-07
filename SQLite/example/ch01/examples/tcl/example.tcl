#!/usr/bin/env tclsh

package require sqlite3

puts "\nConnecting."
sqlite3 db ./seinfeld.db

puts "\nSelecting 5 records."
db eval {SELECT * FROM foods LIMIT 5} {
    puts "$id $name"
}

db eval {SELECT * FROM foods LIMIT 5} values {
    puts "$values(id) $values(name)"
}

db eval BEGIN

puts "\nUpdating all rows."
db eval { UPDATE foods set type_id=0 }
puts "Changes             : [db changes]"

puts "\nDeleting all rows."
# Delete all rows
db eval { DELETE FROM foods }

puts "\nInserting a row."
# Insert a row
db eval { INSERT INTO foods (type_id, name) VALUES (9, 'Junior Mints') }

puts "Changes             : [db changes]"
puts "last_insert_rowid() : [db last_insert_rowid]"

puts "\nRolling back transaction."
db eval ROLLBACK

set name [db eval {SELECT count(*) FROM foods} ]
puts "Total records       : $name"

# User defined function
proc hello_newman {args} {
    set l [llength $args]
    if {$l == 0} {
        return "Hello Jerry"
    } else {
        return "Hello [join $args {, } ]"
    }
}

db function hello_newman hello_newman
puts [db onecolumn {select hello_newman()}]
puts [db onecolumn {select hello_newman('Elaine')}]
puts [db onecolumn {select hello_newman('Elaine', 'Jerry')}]
puts [db onecolumn {select hello_newman('Elaine', 'Jerry', 'George')}]

db close
