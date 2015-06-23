//
//  LRDHypnosisView.m
//  Hypnosister
//
//  Created by 张林 on 15/6/23.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDHypnosisView.h"

@implementation LRDHypnosisView

- (void)drawRect:(CGRect)rect {
    CGRect bounds = self.bounds;
    CGPoint center;
    center.x = (bounds.origin.x + bounds.size.width) / 2;
    center.y = (bounds.origin.y + bounds.size.height) / 2;
    
    float maxRadius = hypot(bounds.size.width, bounds.size.height);
    
    UIBezierPath *path = [[UIBezierPath alloc] init];
    
    for (int currentRadius=maxRadius; currentRadius>0; currentRadius-=20) {
        [path moveToPoint:CGPointMake(center.x+currentRadius, center.y)];
        [path addArcWithCenter:center
                        radius:currentRadius
                    startAngle:0.0
                      endAngle:M_PI * 2.0
                     clockwise:YES];

    }
    
    path.lineWidth = 10;
    [[UIColor lightGrayColor] setStroke];
    //绘制路径
    [path stroke];
    
}
- (instancetype) initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if(self) {
        self.backgroundColor = [UIColor clearColor];
    }
    return self;
}

@end
