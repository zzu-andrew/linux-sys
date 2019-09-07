//
//  iSeinfieldv1AppDelegate.h
//  iSeinfieldv1
//
//  Created by Grant Allen on 9/19/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

@interface iSeinfieldv1AppDelegate : NSObject <UIApplicationDelegate> {
    
    UIWindow *window;
    UINavigationController *navigationController;
	
	// Details of your database
	NSString *databaseName;
	NSString *databasePath;
	
	// Our iSeinfeld food array, for storing our foods
	NSMutableArray *foods;
	
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;
@property (nonatomic, retain) NSMutableArray *foods;

@end

