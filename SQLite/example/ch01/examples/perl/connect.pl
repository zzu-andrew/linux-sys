#!/usr/bin/env perl

use DBI;

print "Drivers: " . join(", ", DBI->available_drivers()), "\n";

my $dbh = DBI->connect("dbi:SQLite:dbname=/tmp/db", "", "", { RaiseError => 1 });
my $sth = $dbh->prepare("SELECT * FROM session");

$sth->execute;

while($row = $sth->fetch) {
    print join(", ", @$row), "\n";
}

$sth->finish;
$dbh->disconnect;
