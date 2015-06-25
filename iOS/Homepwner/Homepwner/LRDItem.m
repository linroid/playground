//
//  LRDItem.m
//  Homepwner
//
//  Created by 张林 on 15/6/24.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDItem.h"

@implementation LRDItem

- (void) setItemName:(NSString *)itemName {
    _itemName = itemName;
    _dateCreated = [[NSDate alloc] init];
}
@end
