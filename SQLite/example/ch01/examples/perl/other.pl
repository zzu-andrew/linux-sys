#!/usr/bin/perl

use DBI;
use perlsum;

# Connect
my $dbh = DBI->connect("dbi:SQLite:dbname=seinfeld.db", "", "", { RaiseError => 1 });

# Set timeout to 5 seconds
print $dbh->func(5, 'busy_timeout') . "\n";
print $dbh->func('busy_timeout') . "\n";

$dbh->do("INSERT INTO foods (type_id, name) values (9, 'Junior Mints')");

# Print the last generated autoincrement key value
print $dbh->func('last_insert_rowid') . "\n";

$dbh->disconnect;
