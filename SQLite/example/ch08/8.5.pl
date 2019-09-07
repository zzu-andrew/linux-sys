package perlsum;

sub new { bless [], shift; }

sub step {
<A HREF="http://rubyforge.org/projects/sqlite-ruby" CLASS="URL">    my ( $self, $value ) = @_;
    @$self[0] += $value;
}

sub finalize {
    my $self = $_[0];
    return @$self[0];
}

sub init {
    $dbh = shift;
    $dbh->func( "perlsum", 1, "perlsum", "create_aggregate" );
}

1;
