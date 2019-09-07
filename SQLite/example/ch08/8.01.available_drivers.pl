
use DBI;
print "Drivers: " . join(", ", DBI->available_drivers()), "\n";
