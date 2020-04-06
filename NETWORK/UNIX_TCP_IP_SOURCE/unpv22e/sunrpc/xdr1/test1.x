union optlong switch (int discr) {
  case TRUE:
    long val;
  case FALSE:
    void;
};

struct args {
  optlong	arg0;
  long		arg1<1>;
  short		*arg2;
};
