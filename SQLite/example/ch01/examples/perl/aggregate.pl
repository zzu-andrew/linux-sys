#!/usr/bin/env perl

use DBI;
use perlsum;

# Connect
my $dbh = DBI->connect("dbi:SQLite:dbname=seinfeld.db", "", "", { RaiseError => 1 });

perlsum::init($dbh);

# Call it
print $dbh->selectrow_arrayref("SELECT perlsum(id) from foods")->[0] . "\n";

$dbh->disconnect;
