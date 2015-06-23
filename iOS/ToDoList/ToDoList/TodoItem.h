//
//  TodoItem.h
//  ToDoList
//
//  Created by 张林 on 6/19/15.
//  Copyright (c) 2015 张林. All rights reserved.
//

#ifndef ToDoList_TodoItem_h
#define ToDoList_TodoItem_h

@interface ToDoItem : NSObject

@property NSString *itemName;
@property BOOL completed;
@property (readonly) NSDate *creationDate;

- (void)markAsCompiled: (BOOL)isComplete;
- (void)setCompletionDate;
@end
#endif
