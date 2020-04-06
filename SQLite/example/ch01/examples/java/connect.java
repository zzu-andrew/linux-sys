import SQLite.*;

public class test implements SQLite.Callback, SQLite.Function,
    SQLite.Authorizer, SQLite.Trace, SQLite.ProgressHandler 
{
    private StringBuffer acc = new StringBuffer();

    public void function(FunctionContext fc, String args[]) {
	System.out.println("function:");
	for (int i = 0; i < args.length; i++) {
	    System.out.println("arg[" + i + "]=" + args[i]);
	}
	if (args.length > 0) {
	    fc.set_result(args[0].toLowerCase());
	}
    }

    public boolean newrow(String data[]) {
	for (int i = 0; i < data.length; i++) {
	    System.out.println("data" + i + ": " + data[i]);
	}
	return false;
    }

    public void step(FunctionContext fc, String args[]) {
	System.out.println("step:");
	for (int i = 0; i < args.length; i++) {
	    acc.append(args[i]);
	    acc.append(" ");
	}
    }

    public void last_step(FunctionContext fc) {
	System.out.println("last_step");
	fc.set_result(acc.toString());
	acc.setLength(0);
    }

    public void trace(String stmt) {
	System.out.println("TRACE: " + stmt);
    }

    public static void main(String args[])
    {
        System.out.println("LIB version: " + SQLite.Database.version());

        SQLite.Database db = new SQLite.Database();

        if (db.is3())
        {
            System.out.println("SQLite 3 database");
        }
        else
        {
            System.out.println("SQLite 2 database");
        }
        
        try {
            db.open("seinfeld.db", 0666);

            System.out.println("DB version: " + db.dbversion());

            db.interrupt();
            db.busy_timeout(1000);
            db.busy_handler(null);
            db.create_function("hello_newman", -1, new test());
            db.function_type("hello_newman", Constants.SQLITE_TEXT);
            db.create_aggregate("myaggfunc", 1, new test());
            db.function_type("myaggfunc", Constants.SQLITE_TEXT);
            db.exec("PRAGMA show_datatypes = on", null);
            System.out.println("==== local callback ====");
            db.exec("select * from sqlite_master", new test());
            System.out.println("==== call regular function ====");
            db.exec("select myregfunc(name) from foods", new test());
            System.out.println("==== call aggregate function ====");
            db.exec("select myaggfunc(name) from foods", new test());
            System.out.println("==== compile/step interface ====");
            test cb = new test();
            db.set_authorizer(cb);
            db.trace(cb);
            Vm vm = db.compile("select * from foods LIMIT 5; " +
                               "delete from foods where id = 5; " +
                               "insert into foods (type_id, name) values (5, 'Java'); " +
                               "select * from foods");
            int stmt = 0;
            do {
                ++stmt;
                if (stmt > 3) {
                    System.out.println("setting progress handler");
                    db.progress_handler(3, cb);
                }
                System.out.println("---- STMT #" + stmt + " ----");
                while (vm.step(cb)) {
                }
            } while (vm.compile());
            db.close();
            System.out.println("An exception is expected from now on.");
            System.out.println("==== local callback ====");
            db.exec("select * from sqlite_master", new test());
        } catch (java.lang.Exception e) {
            System.err.println("error: " + e);
        } finally {
            try {
                System.err.println("cleaning up ...");
                db.close();
            } catch(java.lang.Exception e) {
                System.err.println("error: " + e);
            } finally {
                System.err.println("done.");
            }
        }
    }
}
