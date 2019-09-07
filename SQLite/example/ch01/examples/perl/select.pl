#!/usr/bin/env perl

use DBI;

print "Drivers: " . join(", ", DBI->available_drivers()), "\n";

my $dbh = DBI->connect("dbi:SQLite:dbname=seinfeld.db", "", "", { RaiseError => 1 });

my $sth = $dbh->prepare("SELECT name FROM foods LIMIT 3");

print "\nArray:\n\n";

$sth->execute;
while($row = $sth->fetchrow_arrayref) {
    print @$row[0] . "\n";
}

print "\nHash:\n\n";

$sth->execute;
while($row = $sth->fetchrow_hashref) {
    print @$row{'name'} . "\n";
}

$sth->finish;
$dbh->disconnect;
