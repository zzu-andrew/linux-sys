Definitive Guide to SQLite - Errata

Dear readers,

My apologies for the mix up with the code for chapter 10 - the Android SQLite example.  As some of you have discovered, I mistakenly included a duplicate of the code for chapter 9 (the iPhone code).  I've recreated a working version of the code for chapter 10 which is now available.

There are a few changes to this code, but it is by and large still the same functionality, methods, classes etc. as described in the chapter.  I've mainly changed some of the code to push things down into the MyDatabaseHelper class, and cleaned up the Seinfeld class to just handle the wrapper steps.  I've also used a slightly later version of the Android SDK and developer tools, but there's no explicit version dependency here so you should be able to use the code in any version of the API from 2.2 onwards.

Included in the code are also some commented out steps if you'd like to explore creating the database "fresh" rather than copying it from the project assets.

Once again, thank you for your patience in waiting for this corrected code, and best of luck with your Android SQLite development efforts.

Regards
Grant
