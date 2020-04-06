package SQLiteEx.utils;

class StringUtil
{
    static String join( String[] array, String delim ) {
        StringBuffer sb = join(array, delim, new StringBuffer());
        return sb.toString();
    }

    static StringBuffer join( String[] array, String delim, StringBuffer sb ) {
        for ( int i=0; i<array.length; i++ ) {
            if (i!=0) sb.append(delim);
            sb.append("'" + array[i] + "'");
        }
        return sb;		
    }
}

