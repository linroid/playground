//
//  ToDoItem.m
//  ToDoList
//
//  Created by 张林 on 6/19/15.
//  Copyright (c) 2015 张林. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ToDoItem.h"

@interface ToDoItem()
@property NSDate *completionDate;

@end

@implementation ToDoItem

- (void) markAsCompiled:(BOOL)isComplete {
    self.completed = isComplete;
    [self setCompletionDate ];
}
- (void) setCompletionDate {
    if(self.completed){
        self.completionDate = [NSDate date];
    } else {
        self.completionDate = nil;
    }
}
@end