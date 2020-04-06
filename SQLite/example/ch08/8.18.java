public static void query(SQLite.Database db)
  throws SQLite.Exception
{
  System.out.println("\nQuery Processing:\n");

  Row row = new Row();
  db.set_authorizer(new AuthorizeFilter());

  Vm vm = db.compile( "select * from foods limit 5;" +
                      "delete from foods where id = 5;" +
                      "insert into foods (type_id, name) values (5, 'Java');" +
                      "select * from foods limit 5" );
  do
  {
    while (vm.step(row))
    {
      System.err.println(row.print());
    }
  }
  while (vm.compile());
}
