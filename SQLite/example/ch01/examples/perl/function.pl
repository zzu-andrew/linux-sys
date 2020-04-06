#!/usr/bin/env perl

use DBI;

sub hello_newman {
    if (@_ == 0) {
        return "Hello Jerry";
    } 

    return "Hello " . join ", ", @_;
}

# Connect
my $dbh = DBI->connect("dbi:SQLite:dbname=seinfeld.db", "", "", { RaiseError => 1 });

# Register function
$dbh->func('hello_newman', -1, \&hello_newman, 'create_function');

# Call it
print $dbh->selectrow_arrayref("SELECT hello_newman()")->[0] . "\n";
print $dbh->selectrow_arrayref("SELECT hello_newman('Elaine', 'Jerry')")->[0] . "\n";
print $dbh->selectrow_arrayref("SELECT hello_newman('Elaine', 'Jerry', 'George')")->[0] . "\n";

$dbh->disconnect;
