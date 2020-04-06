use DBI;
# Connect to database
my $dbh = DBI->connect( "dbi:SQLite:dbname=foods.db", "", "",
                        { RaiseError => 1 });

# Prepare the statment
my $sth = $dbh->prepare("select name from foods limit 3");

# Execute
$sth->execute;

# Print a human-readable header
print "\nArray:\n\n";

# Iterate over results and print
while($row = $sth->fetchrow_arrayref) {
  print @$row[0] . "\n";
}

# Do the same thing, this time using hashref
print "\nHash:\n\n";
$sth->execute;
while($row = $sth->fetchrow_hashref) {
  print @$row{'name'} . "\n";
}

# Finalize the statement
$sth->finish;

#Disconnect
$dbh->disconnect;

