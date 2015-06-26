//
//  LRDLine.m
//  TouchTracker
//
//  Created by 张林 on 15/6/26.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDLine.h"

@implementation LRDLine


-(void) setAngle {
    double tan = ((self.end.y - self.begin.y)*1.0) / (self.end.x - self.begin.x);
    _angle = atan(tan);
    if (self.end.y-self.begin.y > 0) {
        _angle = 360 - _angle;
    }
}
-(void) setEnd:(CGPoint)end {
    _end = end;
    [self setAngle];
}

-(void) setBegin:(CGPoint)begin {
    _begin = begin;
    [self setAngle];
}
@end
