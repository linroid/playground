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
        NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
        [notificationCenter addObserver:self
                               selector:@selector(clearCache:)
                                   name:UIApplicationDidReceiveMemoryWarningNotification
                                 object:nil];
    }
    return self;
}
- (void) clearCache: (NSNotification * ) notification {
    NSLog(@"clearCache: %@", notification);
    [self.dictionary removeAllObjects];
}
- (instancetype)init {
    @throw [NSException exceptionWithName:@"Singleton" reason:@"Use [LRDImageStore sharedStore]" userInfo:nil];
}

- (void)setImage: (UIImage*)image forKey:(NSString *) key {
    self.dictionary[key] = image;
    NSString *imagePath = [self imagePathForKey:key];
    NSData *data = UIImagePNGRepresentation(image);
    [data writeToFile:imagePath atomically:YES];
}

- (void)deleteImageForKey:(NSString *) key {
    [self.dictionary removeObjectForKey:key];
    NSString *imagePath = [self imagePathForKey:key];
    [[NSFileManager defaultManager] removeItemAtPath:imagePath error:nil];
}

- (UIImage *)imageForKey:(NSString *)key {
    UIImage *result = self.dictionary[key];
    if(!result) {
        NSString *imagePath = [self imagePathForKey:key];
        result = [UIImage imageWithContentsOfFile:imagePath];
        if( result ){
            self.dictionary[key] = result;
        }else {
            NSLog(@"Could not retrieve image");
        }
    }
    return result;
}

- (NSString *)imagePathForKey: (NSString *)key {
    NSArray *documentDirectories = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [documentDirectories firstObject];
    return [documentDirectory stringByAppendingPathComponent:key];
}
@end
