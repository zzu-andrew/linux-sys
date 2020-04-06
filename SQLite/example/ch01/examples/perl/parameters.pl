#!/usr/bin/env perl

use DBI;

print "Drivers: " . join(", ", DBI->available_drivers()), "\n";

my $dbh = DBI->connect("dbi:SQLite:dbname=seinfeld.db", "", "", { RaiseError => 1 });

my $sth = $dbh->prepare("SELECT * FROM foods where name like :1");

$sth->execute('C%');

while($row = $sth->fetchrow_hashref) {
    print @$row{'name'} . "\n";
}

$sth->finish;
$dbh->disconnect;
