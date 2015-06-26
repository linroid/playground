//
//  LRDDrawView.m
//  TouchTracker
//
//  Created by 张林 on 15/6/26.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDDrawView.h"
#import "LRDLine.h"

@interface LRDDrawView ()

@property(nonatomic, strong) NSMutableArray *finishedLines;
@property(nonatomic, strong) NSMutableDictionary *linesInProgress;

@end

@implementation LRDDrawView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.finishedLines = [[NSMutableArray alloc] init];
        self.backgroundColor = [UIColor grayColor];
        self.multipleTouchEnabled = YES;
        self.linesInProgress = [[NSMutableDictionary alloc]init];
    }
    return self;
}
- (void)strokeLine:(LRDLine *)line {
    UIBezierPath *path = [UIBezierPath bezierPath];
    [self setLineColor:line];
    path.lineWidth = 5;
    path.lineCapStyle = kCGLineCapRound;
    [path moveToPoint:line.begin];
    [path addLineToPoint:line.end];
    [path stroke];
}

- (void)drawRect:(CGRect)rect {
    [[UIColor blackColor] set];
    for (LRDLine *line in self.finishedLines) {
        [self setLineColor:line];
        [self strokeLine:line];
    }
    if ([self.linesInProgress count]>0) {
        
        for(NSValue *key in self.linesInProgress) {
            LRDLine *line = self.linesInProgress[key];
            [self setLineColor:line];
            [self strokeLine:line];
        }
    }

}
- (void) setLineColor:(LRDLine *) line {
    if (line.angle <90){
        [[UIColor yellowColor] set];
    } else if(line.angle < 180) {
        [[UIColor greenColor] set];
    } else if(line.angle <270) {
        [[UIColor blackColor] set];
    } else {
        [[UIColor purpleColor] set];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    NSLog(@"%@", NSStringFromSelector(_cmd));
    for (UITouch *touch in touches) {
        CGPoint location = [touch locationInView:self];
        LRDLine *line = [[LRDLine alloc] init];
        line.begin = location;
        line.end = location;
        NSValue *key = [NSValue valueWithNonretainedObject:touch];
        self.linesInProgress[key] = line;
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    
    NSLog(@"%@", NSStringFromSelector(_cmd));
    for (UITouch *touch in touches) {
        NSValue *key = [NSValue valueWithNonretainedObject:touch];
        LRDLine *line = self.linesInProgress[key];
        
        CGPoint location = [touch locationInView:self];
        line.end = location;
    }
    [self setNeedsDisplay];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    
    NSLog(@"%@", NSStringFromSelector(_cmd));
    for (UITouch *touch in touches) {
        NSValue *key = [NSValue valueWithNonretainedObject:touch];
        LRDLine *line = self.linesInProgress[key];
        [self.finishedLines addObject:line];
        [self.linesInProgress removeObjectForKey:key];
    }
    [self setNeedsDisplay];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    NSLog(@"%@", NSStringFromSelector(_cmd));
    for (UITouch *touch in touches) {
        NSValue *key = [NSValue valueWithNonretainedObject:touch];
        [self.linesInProgress removeObjectForKey:key];
    }

    [self setNeedsDisplay];
}

@end
