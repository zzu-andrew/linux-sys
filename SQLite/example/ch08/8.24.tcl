db transaction {
puts "\nUpdating all rows."
db eval { update foods set type_id=0 }
puts "Changes             : [db changes]"

puts "\nDeleting all rows."

# Delete all rows
db eval { delete from foods }

puts "\nInserting a row."

# Insert a row
db eval { insert into foods (type_id, name) values (9, 'Junior Mints') }

puts "Changes             : [db changes]"
puts "last_insert_rowid() : [db last_insert_rowid]"
}
