import java.sql.*;
import SQLite.JDBCDriver;

public class SQLiteJDBCExample {

public static void main ( String [ ] args )
{
    try 
    {
        String cnxURL = "jdbc:sqlite://tmp/seinfeld.db";
        Class.forName("SQLite.JDBCDriver");
        Connection con = DriverManager.getConnection(cnxURL, "", "");	  
        
        Statement s = con.createStatement();
        ResultSet rs = s.executeQuery("SELECT * FROM foods LIMIT 10");
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

        rs.close();
        s.close();
        con.close();
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
