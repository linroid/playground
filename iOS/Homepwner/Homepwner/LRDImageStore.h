//
//  LRDImageStore.h
//  Homepwner
//
//  Created by 张林 on 15/6/25.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@interface LRDImageStore : NSObject

@property (nonatomic, strong) NSMutableDictionary *dictionary;

+ (instancetype)sharedStore;
- (void)setImage: (UIImage*)image forKey:(NSString *) key;
- (UIImage *)imageForKey:(NSString *)key;
- (void)deleteImageForKey:(NSString *) key;
- (NSString *)imagePathForKey: (NSString *)key;
@end
