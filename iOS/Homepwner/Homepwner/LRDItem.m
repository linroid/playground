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

- (void) encodeWithCoder:(NSCoder *)aCoder {
    [aCoder encodeObject:self.itemName forKey: @"itemName"];
    [aCoder encodeObject:self.serialNumber forKey:@"serialNumber"];
    [aCoder encodeObject:self.dateCreated forKey:@"dateCreated"];
    [aCoder encodeObject:self.imageKey forKey:@"imageKey"];
    [aCoder encodeInt:self.valueInDollars forKey: @"valueInDollars"];
}
-(instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super init];
    if(self) {
        _itemName = [aDecoder decodeObjectForKey:@"itemName"];
        _serialNumber = [aDecoder decodeObjectForKey:@"serialNumber"];
        _dateCreated = [aDecoder decodeObjectForKey:@"dateCreated"];
        _imageKey = [aDecoder decodeObjectForKey:@"imageKey"];
        _valueInDollars = [aDecoder decodeIntForKey:@"valueInDollars"];
    }
    return self;
}
@end
