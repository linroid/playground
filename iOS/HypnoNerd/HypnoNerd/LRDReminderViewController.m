//
//  LRDReminderViewController.m
//  HypnoNerd
//
//  Created by 张林 on 15/6/23.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDReminderViewController.h"

@interface LRDReminderViewController ()

@property (nonatomic, weak) IBOutlet UIDatePicker *datePicker;
@property (nonatomic, weak) IBOutlet UIButton *button;

@end

@implementation LRDReminderViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSLog(@"LRDReminderViewController viewDidLoad");
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (instancetype) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self) {
        self.tabBarItem.title = @"Remminder";
        UIImage *icon = [UIImage imageNamed:@"Time.png"];
        self.tabBarItem.image = icon;
    }
    return self;
}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (void) viewWillAppear:(BOOL)animated{
    self.datePicker.minimumDate = [NSDate dateWithTimeIntervalSinceNow:60];
}
- (IBAction)addReminder:(id) sender{
    
    NSDate *date = self.datePicker.date;
    NSLog(@"button clicked, addReminder, %@", date);
    UILocalNotification *notification = [[UILocalNotification alloc] init];
    notification.alertBody = @"Hypnotize me!";
    notification.fireDate = [[NSDate alloc] init];
    [[UIApplication sharedApplication] scheduleLocalNotification:notification];
}

@end
