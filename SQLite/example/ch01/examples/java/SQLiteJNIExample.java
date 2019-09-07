import SQLite.*;

/*
    waiting on a Sunday afternoon
    for what I read between the lines,
    your lies.
    feelin' like a hand in rusted shame
    so do you laugh or does it cry
    reply

    leavin' on a southern train
    only yesterday you lied,
    promises of what I seemed to be
    only watched the time go by,
    all of these things you said to me.

    breathing is the hardest thing
    to do. with all I've said and
    all that's dead for you,
    you lied - good bye

    leavin' on a southern train
    only yesterday you lied
    promises of what I seemed to be
    only watched the time go by,
    all of these things I said to you.
*/

public class SQLiteJNIExample 
{
    public static void main(String args[])
    {
        SQLite.Database db = new SQLite.Database();

        try
        {
            db.open("seinfeld.db", 700);

            // Trace SQL statements
            db.trace(new SQLTrace());

            // Prepared Query example
            prepared_query(db);

            // One Step Query example
            exec_query(db);
           
            db.set_authorizer(new AuthorizeFilter());

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

    public static void prepared_query(SQLite.Database db) 
        throws SQLite.Exception
    {
        System.out.println("\nPrepared Query:\n");

        Row row = new Row();

        Vm vm = db.compile( "select * from foods LIMIT 5;" +
                            "delete from foods where id > 416;" +
                            "insert into foods (type_id, name) values (5, 'Java');" +
                            "select * from foods LIMIT 5" );
        do
        {
            while (vm.step(row))
            {
                System.err.println(row.print());
            }
        } 
        while (vm.compile());
    }

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

    public static void user_defined_function(SQLite.Database db) 
        throws SQLite.Exception
    {
        System.out.println("\nUser Define Function:\n");

        // Register function
        db.create_function("hello_newman", -1, new HelloNewman());

        // Set return type
        db.function_type("hello_newman", Constants.SQLITE_TEXT);

        // Test
        PrintResult r = new PrintResult();
        db.exec("select hello_newman()", r);
        db.exec("select hello_newman('Elaine', 'Jerry')", r);
        db.exec("select hello_newman('Elaine', 'Jerry', 'George')", r);
    }

    public static void user_defined_aggregate(SQLite.Database db) 
        throws SQLite.Exception
    {
        System.out.println("\nUser Define Aggregate:\n");

        // Register aggregate
        db.create_aggregate("javasum", 1, new JavaSum());

        // Set return type
        db.function_type("javasum", Constants.SQLITE_TEXT);

        db.exec("select javasum(id) from foods", new PrintResult());
    }
}

class SQLTrace implements SQLite.Trace
{
    public void trace(String stmt) 
    {
        System.out.println("SQL:    " + stmt);
    }
}

class Row implements SQLite.Callback
{
    private String row[];

    public void columns(String col[]) {}
    public void types(String types[]) {}

    public boolean newrow(String data[]) 
    {
        row = data;
        return false;
    }

    public String print()
    {
        return "Row:    [" + StringUtil.join(row, ", ") + "]";
    }

    public String field(int i)
    {
        return row[i];
    }
}

class ResultSet implements SQLite.Callback
{
    private String row[];

    public void columns(String col[]) {}
    public void types(String types[]) {}

    public boolean newrow(String data[]) 
    {
        System.out.println("Row:    [" + StringUtil.join(data, ", ") + "]");

        return false;
    }
}

class PrintResult extends Row
{
    public boolean newrow(String data[]) 
    {
        super.newrow(data);
        System.out.println(super.print());
        return false;
    }
}

class HelloNewman implements SQLite.Function
{
    private int acc = 0;

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

class JavaSum implements SQLite.Function
{
    private int sum = 0;

    public void function(FunctionContext fc, String args[])
    {
        fc.set_result(args[0].toLowerCase());
    }

    public void step(FunctionContext fc, String args[])
    {
        for (int i = 0; i < args.length; i++)
        {
            sum += Integer.parseInt(args[i]);
        }
    }

    public void last_step(FunctionContext fc)
    {
        fc.set_result(sum);
    }
}

class AuthorizeFilter implements SQLite.Authorizer
{
    public int authorize( int what, String arg1, String arg2, 
                          String arg3, String arg4)
    {
        return Constants.SQLITE_OK;
    }
}

class StringUtil
{
    static String join( String[] array, String delim ) {
        StringBuffer sb = join(array, delim, new StringBuffer());
        return sb.toString();
    }

    static StringBuffer join( String[] array, String delim, StringBuffer sb ) {
        for ( int i=0; i<array.length; i++ ) {
            if (i!=0) sb.append(delim);
            sb.append(array[i]);
        }
        return sb;		
    }
}
