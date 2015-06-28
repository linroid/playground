//
//  LRDImageStore.m
//  Homepwner
//
//  Created by 张林 on 15/6/25.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDImageStore.h"

@implementation LRDImageStore

+ (instancetype)sharedStore {
    static LRDImageStore *sharedStore;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedStore = [[LRDImageStore alloc] initPrivate];
    });
    return sharedStore;
}

- (instancetype) initPrivate {
    self = [super init];
    if(self){
        self.dictionary = [[NSMutableDictionary alloc] init];
    }
    return self;
}
- (instancetype)init {
    @throw [NSException exceptionWithName:@"Singleton" reason:@"Use [LRDImageStore sharedStore]" userInfo:nil];
}

- (void)setImage: (UIImage*)image forKey:(NSString *) key {
    self.dictionary[key] = image;
}

- (void)deleteImageForKey:(NSString *) key {
    [self.dictionary removeObjectForKey:key];
}

- (UIImage *)imageForKey:(NSString *)key {
    return self.dictionary[key];
}
@end
