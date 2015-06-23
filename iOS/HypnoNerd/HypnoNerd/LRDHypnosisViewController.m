//
//  LRDHypnosisViewController.m
//  HypnoNerd
//
//  Created by 张林 on 15/6/23.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDHypnosisViewController.h"
#import "LRDHypnosisView.h"

@interface LRDHypnosisViewController ()

@property (nonatomic, strong) LRDHypnosisView *hypnosisView;
@end

@implementation LRDHypnosisViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.hypnosisView = [[LRDHypnosisView alloc] init];
    
    UIView *containerView = [[UIView alloc] init];
    
    CGRect controlRect = CGRectMake(20.0f, 10.0f, 300.0f, 30.0f);    NSArray *segmentItems = @[@"红", @"绿", @"蓝"];
    UISegmentedControl *control = [[UISegmentedControl alloc] initWithItems:segmentItems];
    control.selectedSegmentIndex = 0;
    control.frame = controlRect;
    [control addTarget:self
                action:@selector(whichColor:)
      forControlEvents:UIControlEventValueChanged];
    
    [containerView addSubview:control];
    [containerView addSubview:self.hypnosisView];
    self.view = containerView;
    NSLog(@"LRDHypnosisViewController viewDidLoad");
    
    // Do any additional setup after loading the view.
}
- (void) whichColor:(UISegmentedControl *) sender {
    switch ([sender selectedSegmentIndex]) {
        case 0:
            self.hypnosisView.circleColor = [UIColor redColor];
            break;
        case 1:
            self.hypnosisView.circleColor = [UIColor greenColor];
        default:
            self.hypnosisView.circleColor = [UIColor blueColor];
            break;
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (instancetype) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self) {
        self.tabBarItem.title = @"Hypnotize";
        UIImage *icon = [UIImage imageNamed:@"Hypno.png"];
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

@end
