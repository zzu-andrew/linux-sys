public static void exec_query(SQLite.Database db)
  throws SQLite.Exception
{
  System.out.println("\nExec Query:\n");

  String sql = "insert into foods (type_id, name) values (5, '%q')";
  ResultSet result = new ResultSet();

  String params[] = {"Java"};
  db.exec(sql, result, params);

  System.out.println("Result: last_insert_id(): " + db.last_insert_rowid());
  System.out.println("Result:        changes(): " + db.changes());
}
