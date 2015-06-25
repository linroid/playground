//
//  LRDDetailViewController.m
//  Homepwner
//
//  Created by 张林 on 15/6/25.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDDetailViewController.h"
#import "LRDItem.h"

@interface LRDDetailViewController ()

@property (weak, nonatomic) IBOutlet UITextField *nameField;
@property (weak, nonatomic) IBOutlet UITextField *serialField;
@property (weak, nonatomic) IBOutlet UITextField *valueField;
@property (weak, nonatomic) IBOutlet UILabel *dateLabel;


@end

@implementation LRDDetailViewController

- (void)setItem:(LRDItem *)item {
    _item = item;
    self.navigationItem.title = item.itemName;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    NSLog(@"viewDidLoad");
}

- (void)loadView {
    [super loadView];
    NSLog(@"loadView");
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated {
    NSLog(@"viewWillAppear");
    [super viewWillAppear:animated];
    self.nameField.text = self.item.itemName;
    self.serialField.text=  self.item.serialNumber;
    self.valueField.text =  [NSString stringWithFormat:@"%d", self.item.valueInDollars];
    self.dateLabel.text = [self.item.dateCreated description];
}
- (void)viewWillDisappear:(BOOL)animated {
    NSLog(@"viewWillDisappear");
    [self.view endEditing:NO];
    
    LRDItem *item = self.item;
    item.itemName = self.nameField.text;
    item.serialNumber = self.nameField.text;
    item.valueInDollars = [self.nameField.text intValue];
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
