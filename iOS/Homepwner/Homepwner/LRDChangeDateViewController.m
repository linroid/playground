//
//  ChangeDateViewController.m
//  Homepwner
//
//  Created by 张林 on 15/6/25.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDChangeDateViewController.h"

@interface LRDChangeDateViewController ()

@property (weak, nonatomic) IBOutlet UIDatePicker *datePicker;

@end

@implementation LRDChangeDateViewController



- (void)viewDidLoad {
    [super viewDidLoad];
    UIBarButtonItem *completeBar = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemSave
                                                                                 target:self
                                                                                 action:@selector(saveDate:)];
    self.navigationItem.rightBarButtonItem = completeBar;

    [self.datePicker setDate:self.item.dateCreated];
}

-(void) saveDate:(id) sender{
    self.item.dateCreated = self.datePicker.date;
    [self.navigationController popViewControllerAnimated:YES];
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
