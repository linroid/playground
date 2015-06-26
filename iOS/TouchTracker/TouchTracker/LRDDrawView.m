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

@property(nonatomic, strong) LRDLine *currentLine;
@property(nonatomic, strong) NSMutableArray *finishedLines;

@end

@implementation LRDDrawView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.finishedLines = [[NSMutableArray alloc] init];
        self.backgroundColor = [UIColor grayColor];
        
    }
    return self;
}
- (void)strokeLine:(LRDLine *)line {
    UIBezierPath *path = [UIBezierPath bezierPath];
    path.lineWidth = 5;
    path.lineCapStyle = kCGLineCapRound;
    [path moveToPoint:line.begin];
    [path addLineToPoint:line.end];
    [path stroke];
}

- (void)drawRect:(CGRect)rect {
    [[UIColor blackColor] set];
        for (LRDLine *line in self.finishedLines) {
        [self strokeLine:line];
    }

    if (self.currentLine) {
        [[UIColor blueColor] set];
        [self strokeLine:self.currentLine];
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInView:self];
    self.currentLine = [[LRDLine alloc] init];
    self.currentLine.begin = location;
    self.currentLine.end = location;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInView:self];
    self.currentLine.end = location;
    [self setNeedsDisplay];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    [self.finishedLines addObject:self.currentLine];
    self.currentLine = nil;
    [self setNeedsDisplay];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    self.currentLine = nil;
    [self setNeedsDisplay];
}

@end
