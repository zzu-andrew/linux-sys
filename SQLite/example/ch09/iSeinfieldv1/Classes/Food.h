//
//  Food.h
//  iSeinfieldv1
//
//  Created by Grant Allen on 9/19/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface Food : NSObject {
	NSString *food_id;
	NSString *type_id;
	NSString *name;
}

@property (nonatomic, retain) NSString *food_id;
@property (nonatomic, retain) NSString *type_id;
@property (nonatomic, retain) NSString *name;

-(id)initWithName:(NSString *)n food_id:(NSString *)f type_id:(NSString *)t;

@end
