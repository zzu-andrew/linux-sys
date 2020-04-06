union optlong switch (bool flag) {
  case TRUE:
    long val;
  case FALSE:
    void;
};

struct args {
  optlong	arg1;		/* union with boolean discriminant */
  long		arg2<1>;	/* variable-length array with one element */
  long		*arg3;		/* pointer */
};
