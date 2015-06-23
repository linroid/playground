//
//  LRDHypnosisView.m
//  Hypnosister
//
//  Created by 张林 on 15/6/23.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDHypnosisView.h"
@interface LRDHypnosisView()

@end


@implementation LRDHypnosisView

- (void)drawRect:(CGRect)rect {
    NSLog(@"drawRect");
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
    [self.circleColor setStroke];
    //绘制路径
    [path stroke];
    
    CGContextRef currentContext = UIGraphicsGetCurrentContext();
    
    CGContextSaveGState(currentContext);
    CGContextSetShadow(currentContext, CGSizeMake(4, 8), 3);
    
    UIImage *logoImage = [UIImage imageNamed:@"logo.png"];
    
    [logoImage drawInRect:rect];
    
    CGContextRestoreGState(currentContext);
    
    CGContextSaveGState(currentContext);
    UIBezierPath *trianglePath = [[UIBezierPath alloc] init];
    
    //设置剪切路径
    int size = 190;
    [trianglePath moveToPoint:CGPointMake(center.x, center.y-size)];//top
    [trianglePath addLineToPoint:CGPointMake(center.x+size, center.y+size)];//right
    [trianglePath addLineToPoint:CGPointMake(center.x-size, center.y+size)];//left
    [trianglePath addLineToPoint:CGPointMake(center.x, center.y-size)];//top
    [trianglePath addClip];
    
    //设置渐变色
    CGFloat locations[2] = {0.0, 1.0};
    CGFloat components[8] = {
        1.0, 1.0, 0.0, 1.0, //yellow
        0.0, 1.0, 0.0, 1.0 //green
    };
    CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
    CGGradientRef gradient = CGGradientCreateWithColorComponents(colorspace, components, locations,
                                                                 kCGGradientDrawsBeforeStartLocation|kCGGradientDrawsAfterEndLocation);
    CGPoint startPoint = CGPointMake(center.x, center.y-size);
    CGPoint endPoint = CGPointMake(center.x, center.y+size);
    CGContextDrawLinearGradient(currentContext, gradient
                                , startPoint, endPoint, 0);
    CGGradientRelease(gradient);
    CGColorSpaceRelease(colorspace);
    
    CGContextRestoreGState(currentContext);

}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    NSLog(@"%@ was touched\n", self);
    self.circleColor = [self generateRandomColor];
    NSLog(@"circle color :%@", self.circleColor);
}
- (void) setCircleColor:(UIColor *)circleColor{
    _circleColor = circleColor;
    [self setNeedsDisplay];
}
- (UIColor *) generateRandomColor {
    float red = (arc4random()%255) / 255.0;
    float green = (arc4random()%255) / 255.0;
    float blue = (arc4random()%255) / 255.0;
    return [UIColor colorWithRed:red
                           green:green
                            blue:blue
                           alpha:1.0];
}
- (instancetype) initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if(self) {
        self.backgroundColor = [UIColor clearColor];
        self.circleColor = [UIColor lightGrayColor];
    }
    return self;
}

@end
