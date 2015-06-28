//
//  LRDItemStore.m
//  Homepwner
//
//  Created by 张林 on 15/6/24.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDItemStore.h"
#import "LRDImageStore.h"

@implementation LRDItemStore

+ (instancetype) sharedStore {
    static LRDItemStore *shareStore = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shareStore = [[self alloc] initPrivate];
    });
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
        NSString *path = [self itemArchivePath];
        _privateItems = [NSKeyedUnarchiver unarchiveObjectWithFile: path];
        if(!_privateItems){
            _privateItems = [[NSMutableArray alloc] init];
        }
        
    }
    return self;
}

- (NSArray *) allItems {
    return self.privateItems;
}

- (LRDItem *) createItem{
    LRDItem *item = [[LRDItem alloc] init];
    item.itemName = [NSString stringWithFormat: @"hello %d", arc4random()];
    item.serialNumber = [NSString stringWithFormat: @"%d", arc4random()];
    item.valueInDollars = arc4random() % 1000;
    NSUUID *uuid = [[NSUUID alloc] init];
    item.imageKey = [uuid UUIDString];
    [_privateItems addObject:item];
    [[LRDItemStore sharedStore] saveChanges];
    return item;
}

- (void) removeItem: (LRDItem *) item {
    [[LRDImageStore sharedStore] deleteImageForKey:item.imageKey];
    [self.privateItems removeObjectIdenticalTo: item];
    [[LRDItemStore sharedStore] saveChanges];
}

- (void) moveItemAtIndex: (NSUInteger) fromIndex
                 toIndex: (NSUInteger) toIndex {
    LRDItem *item = self.privateItems[fromIndex];
    [self.privateItems removeObjectIdenticalTo:item];
    [self.privateItems insertObject:item atIndex: toIndex];
    [[LRDItemStore sharedStore] saveChanges];
}

- (BOOL) saveChanges {
    NSString *archivePath = [self itemArchivePath];
    BOOL success =  [NSKeyedArchiver archiveRootObject:self.privateItems toFile: archivePath];
    if(success) {
        NSLog(@"Save items success");
    }else {
        NSLog(@"Could not save items");
    }
    return success;
}

-(NSString *) itemArchivePath {
    NSArray *documentDirectories = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [documentDirectories firstObject];
    return [documentDirectory stringByAppendingPathComponent:@"items.archive"];
}
@end
