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

@end

@implementation LRDHypnosisViewController

- (void)loadView {
    
    CGRect frame = [[UIScreen mainScreen] bounds];
    LRDHypnosisView *backgroundView = [[LRDHypnosisView alloc] initWithFrame:frame];
    
    //    UIView *containerView = [[UIView alloc] init];
    
    //    CGRect controlRect = CGRectMake(20.0f, 10.0f, 300.0f, 30.0f);    NSArray *segmentItems = @[@"红", @"绿", @"蓝"];
    //    UISegmentedControl *control = [[UISegmentedControl alloc] initWithItems:segmentItems];
    //    control.selectedSegmentIndex = 0;
    //    control.frame = controlRect;
    //    [control addTarget:self
    //                action:@selector(whichColor:)
    //      forControlEvents:UIControlEventValueChanged];
    //
    //    [containerView addSubview:control];
    //    [containerView addSubview:self.hypnosisView];
    //    self.view = containerView;
    UIScrollView scrollView = []
    CGRect textFieldRect = CGRectMake(40, 70, 240, 30);
    UITextField *textField = [[UITextField alloc] initWithFrame:textFieldRect];
    textField.borderStyle = UITextBorderStyleRoundedRect;
    textField.placeholder = @"What?";
    textField.returnKeyType = UIReturnKeyDone;
    textField.keyboardType = UIKeyboardTypeDefault;
    textField.delegate = self;
    
    [backgroundView addSubview:textField];
    self.view = backgroundView;
    NSLog(@"LRDHypnosisViewController loadView");
}
- (BOOL)textFieldShouldReturn: (UITextField *) textField {
    NSLog(@"textFieldShouldReturn %@", textField);
    [self drawHypnoticMessage:textField.text];
    textField.text = @"";
    [textField resignFirstResponder];
    return YES;
}
- (void) drawHypnoticMessage:(NSString *) message {
    for(int i=0; i<20; i++) {
        UILabel *messageLabel = [[UILabel alloc] init];
        messageLabel.textColor = [UIColor whiteColor];
        messageLabel.backgroundColor = [UIColor clearColor];
        messageLabel.text = message;
        [messageLabel sizeToFit];
        
        int width = (int) (self.view.bounds.size.width - messageLabel.bounds.size.width);
        int x = arc4random() % width;
        
        int height = (int) (self.view.bounds.size.height - messageLabel.bounds.size.height);
        int y = arc4random() % height;
        
        CGRect frame = messageLabel.frame;
        frame.origin = CGPointMake(x, y);
        messageLabel.frame = frame;
        [self.view addSubview:messageLabel];
        
        UIInterpolatingMotionEffect *motionEffect = [[UIInterpolatingMotionEffect alloc]
                                                     initWithKeyPath:@"center.x"
                                                     type:UIInterpolatingMotionEffectTypeTiltAlongHorizontalAxis];
        motionEffect.minimumRelativeValue = @(-25);
        motionEffect.maximumRelativeValue = @(25);
        [messageLabel addMotionEffect:motionEffect];
        motionEffect = [[UIInterpolatingMotionEffect alloc]
                        initWithKeyPath:@"center.y"
                        type:UIInterpolatingMotionEffectTypeTiltAlongVerticalAxis];
        motionEffect.minimumRelativeValue = @(-25);
        motionEffect.maximumRelativeValue = @(25);
        [messageLabel addMotionEffect:motionEffect];
    }
}


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}
- (void) whichColor:(UISegmentedControl *) sender {
//    switch ([sender selectedSegmentIndex]) {
//        case 0:
//            self.hypnosisView.circleColor = [UIColor redColor];
//            break;
//        case 1:
//            self.hypnosisView.circleColor = [UIColor greenColor];
//        default:
//            self.hypnosisView.circleColor = [UIColor blueColor];
//            break;
//    }
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
