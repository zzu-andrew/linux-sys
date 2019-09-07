use DBI;
my $dbh = DBI->connect("dbi:SQLite:dbname=:memory:", "", "", { RaiseError => 1 });
$dbh->do("create table cast (name)");
$dbh->do("insert into cast values ('Elaine')");
$dbh->do("insert into cast values ('Jerry')");
$dbh->do("insert into cast values ('Kramer')");
$dbh->do("insert into cast values ('George')");
$dbh->do("insert into cast values ('Newman')");

my $sth = $dbh->prepare("select * from cast");
$sth->execute;

while($row = $sth->fetch) {
    print join(", ", @$row), "\n";
}
$sth->finish;
$dbh->disconnect;
