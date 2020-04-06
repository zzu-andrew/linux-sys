//
//  iSeinfieldv1AppDelegate.m
//  iSeinfieldv1
//
//  Created by Grant Allen on 9/19/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "iSeinfieldv1AppDelegate.h"
#import "RootViewController.h"
#import "Food.h" // import our food object header
#import "sqlite3.h"

@implementation iSeinfieldv1AppDelegate

@synthesize window;
@synthesize navigationController;
@synthesize foods; // use sythesize to automatically create foods getters and setters

#pragma mark -
#pragma mark Application lifecycle

- (void)applicationDidFinishLaunching:(UIApplication *)application {    
    
	// Set up our databaseName
	databaseName = @"foods.db";
	
	// Get the path to the documents directory and append the database name
	NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDir = [documentPaths objectAtIndex:0];
	databasePath = [documentsDir stringByAppendingPathComponent:databaseName];

	// Check for existing database and create if necessary
	[self checkAndCreateDatabase];
	
	// Query the database for all foods and populate the array
	[self readFoodsFromDatabase];
	
    // Override point for customization after app launch    
	
	[window addSubview:[navigationController view]];
    [window makeKeyAndVisible];
}


- (void)applicationWillTerminate:(UIApplication *)application {
	// Save data if appropriate
}


#pragma mark -
#pragma mark Memory management

- (void)dealloc {
	[foods release];
	[navigationController release];
	[window release];
	[super dealloc];
}

-(void) checkAndCreateDatabase{
	// Check if the SQL database has already been saved to the users phone, if not then copy it over
	BOOL success;
	
	// Create a FileManager object, we will use this to check the status
	// of the database and to copy it over if required
	NSFileManager *fileManager = [NSFileManager defaultManager];
	
	// Check if the database has already been created in the users filesystem
	success = [fileManager fileExistsAtPath:databasePath];
	
	// If the database already exists then return without doing anything
	if(success) return;
	
	// If not then proceed to copy the database from the application to the users filesystem
	
	// Get the path to the database in the application package
	NSString *databasePathFromApp = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:databaseName];
	
	// Copy the database from the package to the users filesystem
	[fileManager copyItemAtPath:databasePathFromApp toPath:databasePath error:nil];
	
	[fileManager release];
}

-(void) readFoodsFromDatabase {
	// Setup the database object
	sqlite3 *database;
	
	// Init the foods Array
	foods = [[NSMutableArray alloc] init];
	
	// Open the database from the users filessytem
	if(sqlite3_open([databasePath UTF8String], &database) == SQLITE_OK) {
		// Setup the SQL Statement and compile it for faster access
		const char *sqlStatement = "select * from foods limit 5";
		sqlite3_stmt *compiledStatement;
		if(sqlite3_prepare_v2(database, sqlStatement, -1, &compiledStatement, NULL) == SQLITE_OK) {
			// Loop through the results and add them to the feeds array
			while(sqlite3_step(compiledStatement) == SQLITE_ROW) {
				// Read the data from the result row
				NSString *aFood_ID = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 0)];
				NSString *aType_ID = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 1)];
				NSString *aName = [NSString stringWithUTF8String:(char *)sqlite3_column_text(compiledStatement, 2)];
				
				// Create a new food object with the data from the database
				Food *food = [[Food alloc] initWithName:aName food_id:aFood_ID type_id:aType_ID];
				
				// Add the food object to the foods Array
				[foods addObject:food];
				
				[food release];
			}
		}
		// Release the compiled statement from memory
		sqlite3_finalize(compiledStatement);
		
	}
	sqlite3_close(database);
	
}


@end

