const	FOO = 100;
%#include <floatingpoint.h>	/* required under Solaris 2.6 */

enum color { RED = 1, GREEN = 2, BLUE = 3 };

union union_arg switch (int status) {
  case 0:
	int	intval;
  case 1:
	float	floatval;
  default:
	void;
};

struct square_in {
  char		char_arg;		/* signed integers */
  short		short_arg;
  int		int_arg;
  long		long_arg;
  hyper		hyper_arg;

  unsigned char		uchar_arg;	/* unsigned integers */
  unsigned short	ushort_arg;
  unsigned int		uint_arg;
  unsigned long		ulong_arg;
  unsigned hyper	uhyper_arg;

  float		float_arg;		/* floating point */
  double	double_arg;
  quadruple	quad_arg;

  bool		bool_arg;
  color		color_arg;
  string	vstring_arg<5>;		/* variable-length string */
  opaque	fopaque_arg[10];	/* fixed-length opaque */
  opaque	vopaque_arg<>;		/* variable-length opaque */
  short		fshort_arg[4];		/* fixed-length array */
  long		vshort_arg<>;		/* variable-length array */
};
