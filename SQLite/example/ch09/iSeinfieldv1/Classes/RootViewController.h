//
//  RootViewController.h
//  iSeinfieldv1
//
//  Created by Grant Allen on 9/19/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "FoodViewController.h"

@interface RootViewController : UITableViewController {
	FoodViewController *foodView;

}

@property(nonatomic, retain) FoodViewController *foodView;

@end
