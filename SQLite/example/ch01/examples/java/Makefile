
all:
	javac -classpath sqlite.jar SQLiteJNIExample.java
	java -classpath '.:sqlite.jar' -Djava.library.path=/usr/local/lib/ SQLiteJNIExample seinfeld.db

	#javac -classpath sqlite.jar SQLiteJDBCExample.java
	#java -classpath '.:sqlite.jar' -Djava.library.path=/usr/local/lib/ SQLiteJDBCExample seinfeld.db

clean:
	rm *.class
	rm *~
