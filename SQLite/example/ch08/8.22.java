import java.sql.*;
import SQLite.JDBCDriver;

public class SQLiteJDBCExample {

public static void main ( String [ ] args )
{
  try
  {
    Class.forName("SQLite.JDBCDriver");
    Connection c = DriverManager.getConnection( "jdbc:sqlite://tmp/foods.db",
                                                ""  // username (NA),
                                                ""  // password (NA));
       
    Statement s = c.createStatement();
    ResultSet rs = s.executeQuery ("select * from foods limit 10");
    int cols = (rs.getMetaData()).getColumnCount();
       
    while (rs.next())
    {
      String fields[] = new String[cols];

      for(int i=0; i<cols; i++)
      {
        fields[i] = rs.getString(i+1);
      }

      System.out.println("[" + join(fields, ", ") + "]");
    }
  }
  catch( Exception x )
  {
    x.printStackTrace();
  }
}
   
static String join( String[] array, String delim )
{
  StringBuffer sb = join(array, delim, new StringBuffer());
  return sb.toString();
}

static StringBuffer join( String[] array, String delim, StringBuffer sb )
{
  for ( int i=0; i<array.length; i++ )
  {
    if (i!=0) sb.append(delim);
    sb.append("'" + array[i] + "'");
  }

  return sb;
}

}
