import SQLite.*;

public class SQLiteJNIExample
{
  public static void main(String args[])
  {
    SQLite.Database db = new SQLite.Database();

    try
      {
        db.open("foods.db", 700);

        // Trace SQL statements
        db.trace(new SQLTrace());

        // Query example
        query(db);

        // Function example
        user_defined_function(db);

        // Aggregate example
        user_defined_aggregate(db);

        db.close();
      }
      catch (java.lang.Exception e)
      {
        System.err.println("error: " + e);
      }
  }

  ...
}
