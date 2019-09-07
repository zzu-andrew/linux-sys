//
//  FoodsViewController.h
//  iSeinfieldv1
//
//  Created by Grant Allen on 9/19/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface FoodViewController : UIViewController {
	IBOutlet UITextView *foodID;
	IBOutlet UITextView *typeID;
}

@property (nonatomic, retain) IBOutlet UITextView *foodID;
@property (nonatomic, retain) IBOutlet UITextView *typeID;

@end
