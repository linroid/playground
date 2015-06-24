//
//  LRDItemStore.h
//  Homepwner
//
//  Created by 张林 on 15/6/24.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LRDItem.h"

@interface LRDItemStore : NSObject

@property (nonatomic) NSMutableArray * privateItems;

+ (instancetype) sharedStore;
- (NSArray *) allItems;
- (LRDItem *) createItem;
@end
