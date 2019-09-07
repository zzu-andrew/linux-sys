class Row implements SQLite.Callback
{
  private String row[];

  public void columns(String col[]) {}
  public void types(String types[]) {}

  public boolean newrow(String data[])
  {
    // Copy to internal array
    row = data;
    return false;
  }

  public String print()
  {
    return "Row:    [" + StringUtil.join(row, ", ") + "]";
  }
}
