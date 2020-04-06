class HelloNewman implements SQLite.Function
{
  public void function(FunctionContext fc, String args[])
  {
    if (args.length > 0)
    {
      fc.set_result("Hello " + StringUtil.join(args, ", "));
    }
    else
    {
      fc.set_result("Hello Jerry");
    }
  }

  public void step(FunctionContext fc, String args[]){}
  public void last_step(FunctionContext fc)
  {
    fc.set_result(0);
  }

}
