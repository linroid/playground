//
//  LRDItemStore.m
//  Homepwner
//
//  Created by 张林 on 15/6/24.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDItemStore.h"

@implementation LRDItemStore

+ (instancetype) sharedStore {
    static LRDItemStore *shareStore = nil;
    if(shareStore == nil) {
        shareStore = [[self alloc] initPrivate];
    }
    return shareStore;
}
- (instancetype) init {
    @throw [NSException exceptionWithName:@"Singleton"
                                   reason:@"Use +[LRDItemStore sharedStore]"
                                 userInfo: nil];
}
- (instancetype) initPrivate {
    self = [super init];
    if (self) {
        _privateItems = [[NSMutableArray alloc] init];
    }
    return self;
}

- (NSArray *) allItems {
    return self.privateItems;
}

- (LRDItem *) createItem{
    LRDItem *item = [[LRDItem alloc] init];
    item.itemName = [NSString stringWithFormat: @"hello %d", arc4random()];

    [_privateItems addObject:item];
    return item;
}
@end