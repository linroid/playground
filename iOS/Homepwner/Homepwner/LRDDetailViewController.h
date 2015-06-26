//
//  LRDDetailViewController.h
//  Homepwner
//
//  Created by 张林 on 15/6/25.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import <UIKit/UIKit.h>
@class LRDItem;

@interface LRDDetailViewController : UIViewController

@property (nonatomic, strong) LRDItem *item;
-(instancetype) initForNewItem:(BOOL) isNew;
@end
