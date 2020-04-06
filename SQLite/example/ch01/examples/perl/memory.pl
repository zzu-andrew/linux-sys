#!/usr/bin/env perl

use DBI;

my $dbh = DBI->connect("dbi:SQLite:dbname=:memory:", "", "", { RaiseError => 1 });
$dbh->do("CREATE TABLE cast (name)");
$dbh->do("INSERT INTO cast VALUES ('Elaine')");
$dbh->do("INSERT INTO cast VALUES ('Jerry')");
$dbh->do("INSERT INTO cast VALUES ('Kramer')");
$dbh->do("INSERT INTO cast VALUES ('George')");
$dbh->do("INSERT INTO cast VALUES ('Newman')");

my $sth = $dbh->prepare("SELECT * FROM cast");
$sth->execute;

while($row = $sth->fetch) {
    print join(", ", @$row), "\n";
}

$sth->finish;
$dbh->disconnect;
