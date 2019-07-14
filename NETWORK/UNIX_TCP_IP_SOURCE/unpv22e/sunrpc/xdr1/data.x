enum result_t { RESULT_INT = 1, RESULT_DOUBLE = 2 };

union union_arg switch (result_t result) {
  case RESULT_INT:
	int		intval;
  case RESULT_DOUBLE:
	double	doubleval;
  default:
	void;
};

struct data {
  short		short_arg;
  long		long_arg;

  string	vstring_arg<128>;	/* variable-length string */
  opaque	fopaque_arg[3];		/* fixed-length opaque */
  opaque	vopaque_arg<>;		/* variable-length opaque */
  short		fshort_arg[4];		/* fixed-length array */
  long		vlong_arg<>;		/* variable-length array */
  union_arg	uarg;
};
