#define	PATH_SQRT_DOOR	"/tmp/sqrtproc_door"

typedef struct {		/* input to sqrtproc() */
  long	arg1;
} sqrtproc_in_t;

typedef struct {		/* output from sqrtproc() */
  double	res1;
} sqrtproc_out_t;
