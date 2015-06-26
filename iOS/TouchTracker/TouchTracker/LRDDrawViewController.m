//
//  LRDDrawViewController.m
//  TouchTracker
//
//  Created by 张林 on 15/6/26.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDDrawViewController.h"
#import "LRDDrawView.h"
@interface LRDDrawViewController ()

@end

@implementation LRDDrawViewController

- (void)loadView {
    self.view = [[LRDDrawView alloc] initWithFrame:CGRectZero];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
