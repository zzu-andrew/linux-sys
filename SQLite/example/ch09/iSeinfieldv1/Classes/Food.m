//
//  Food.m
//  iSeinfieldv1
//
//  Created by Grant Allen on 9/19/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "Food.h"


@implementation Food
@synthesize food_id, type_id, name;

-(id)initWithName:(NSString *)n food_id:(NSString *)f type_id:(NSString *)t {
	self.name = n;
	self.food_id = f;
	self.type_id = t;

	return self;
}

@end
