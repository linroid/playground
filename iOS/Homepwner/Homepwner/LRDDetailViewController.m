//
//  LRDDetailViewController.m
//  Homepwner
//
//  Created by 张林 on 15/6/25.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDDetailViewController.h"
#import "LRDItem.h"
#import "LRDChangeDateViewController.h"
#import "LRDImageStore.h"
#import "LRDItemStore.h"

@interface LRDDetailViewController () <UITextFieldDelegate, UIPopoverControllerDelegate, UINavigationControllerDelegate, UIImagePickerControllerDelegate>

@property (weak, nonatomic) IBOutlet UITextField *nameField;
@property (weak, nonatomic) IBOutlet UITextField *serialField;
@property (weak, nonatomic) IBOutlet UITextField *valueField;
@property (weak, nonatomic) IBOutlet UIButton *changeDateButton;
@property (weak, nonatomic) UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UIToolbar *toolbar;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *cameraButton;
@property (weak, nonatomic) IBOutlet UIButton *dateButton;


@property (strong, nonatomic) UIPopoverController *imagePickerPopover;

@end

@implementation LRDDetailViewController

#pragma mark - init
-(instancetype) initForNewItem:(BOOL) isNew {
    self = [super initWithNibName:@"LRDDetailViewController" bundle: nil];
    if(self) {
        if(isNew) {
            UIBarButtonItem *doneItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                                                      target:self
                                                                                      action:@selector(done:)];
            self.navigationItem.rightBarButtonItem = doneItem;
            UIBarButtonItem *cancelItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel
                                                                                        target:self
                                                                                        action:@selector(cancel:)];
            self.navigationItem.leftBarButtonItem = cancelItem;
            self.item = [[LRDItemStore sharedStore] createItem];
        } else {
            
            UIBarButtonItem *saveItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemSave target:self action: @selector(saveChange:)];
            self.navigationItem.rightBarButtonItem = saveItem;
        }
    }
    return self;
}
-(instancetype) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    @throw [[NSException alloc] initWithName:@"@Wrong Initializer"
                                      reason:@"Use initForNewItem"
                                    userInfo:nil];
}

- (void)setItem:(LRDItem *)item {
    _item = item;
    self.navigationItem.title = item.itemName;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    NSLog(@"viewDidLoad");
    self.nameField.delegate = self;
    self.serialField.delegate = self;
    self.valueField.delegate = self;
    
    UIImageView *iv = [[UIImageView alloc] initWithImage:nil];
    iv.contentMode = UIViewContentModeScaleAspectFit;
    iv.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view addSubview:iv];
    self.imageView = iv;
    
    NSDictionary *nameMap = @{@"imageView": self.imageView,
                              @"dateButton": self.dateButton,
                              @"toolbar": self.toolbar
                              };
    
    NSArray *horizontalConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[imageView]-0-|"
                                                                             options:0
                                                                             metrics:nil
                                                                               views:nameMap];
    NSArray *verticalConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"V:[dateButton]-[imageView]-[toolbar]"
                                                                           options:0
                                                                           metrics:nil
                                                                             views:nameMap];
    [self.imageView setContentHuggingPriority:100
                                      forAxis:UILayoutConstraintAxisVertical];
    [self.imageView setContentHuggingPriority:100
                                      forAxis:UILayoutConstraintAxisHorizontal];
    NSLayoutConstraint *aspectConstraint = [NSLayoutConstraint constraintWithItem:self.imageView
                                                                        attribute:NSLayoutAttributeHeight
                                                                        relatedBy:NSLayoutRelationEqual
                                                                           toItem:self.imageView
                                                                        attribute:NSLayoutAttributeWidth
                                                                       multiplier:1.0
                                                                         constant:0.0];
    
    [self.view addConstraints:horizontalConstraints];
    [self.view addConstraints:verticalConstraints];
    [self.imageView addConstraint:aspectConstraint];
}
-(BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}
- (void)loadView {
    [super loadView];
    NSLog(@"loadView");
}

- (void) saveChange:(id) sender{
    [self.view endEditing:NO];
    
    LRDItem *item = self.item;
    item.itemName = self.nameField.text;
    item.serialNumber = self.nameField.text;
    item.valueInDollars = [self.nameField.text intValue];
  
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
    self.dateButton.titleLabel.text = [self.item.dateCreated description];
    UIImage *image = [[LRDImageStore sharedStore] imageForKey:self.item.imageKey];
    if(image) {
        self.imageView.image = image;
    }
}

- (void)viewWillDisappear:(BOOL)animated {
    NSLog(@"viewWillDisappear");
    [self saveChange:nil];
    
}

//- (void)viewDidLayoutSubviews {
//    for (UIView *subView in self.view.subviews) {
//        if([subView hasAmbiguousLayout]) {
//            NSLog(@"Ambigous:%@", subView);
//        } else {
//            NSLog(@"No ambigous view");
//        }
//    }
//}


#pragma mark - Delegate

-(void) popoverControllerDidDismissPopover:(UIPopoverController *)popoverController {
    NSLog(@"popoverControllerDidDismissPopover");
    self.imagePickerPopover = nil;
}
-(void) popoverController:(UIPopoverController *)popoverController willRepositionPopoverToRect:(inout CGRect *)rect inView:(inout UIView *__autoreleasing *)view {
    NSLog(@"popoverController");
}
-(void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info {
    if(self.imagePickerPopover){
        [self.imagePickerPopover dismissPopoverAnimated:YES];
        self.imagePickerPopover = nil;
    } else {
        [self dismissViewControllerAnimated:YES completion:nil];
    }
    UIImage *image = info[UIImagePickerControllerOriginalImage];
    self.imageView.image = image;
    [self dismissViewControllerAnimated:YES completion:nil];
    [[LRDImageStore sharedStore] setImage:image forKey:self.item.imageKey];
}



#pragma mark - Actions

-(void) cancel:(id)sender {
    [[LRDItemStore sharedStore] removeItem: self.item];
    [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
}
-(void) done:(id) sender {
    [self saveChange:sender];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void) changeDate:(id) sender {
    LRDChangeDateViewController *changeDateController = [[LRDChangeDateViewController alloc] init];
    changeDateController.item = self.item;
    [self.navigationController pushViewController:changeDateController animated:YES];
}

- (IBAction)takePicture:(id)sender {
    CGRect rootFrame =  self.view.bounds;
    CGRect frame = CGRectMake(rootFrame.origin.x+rootFrame.size.width/2 - 60,
                              rootFrame.origin.y+rootFrame.size.height/2 - 60,
                              60.0,
                              60.0);
    
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    if([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
        imagePicker.sourceType = UIImagePickerControllerSourceTypeCamera;
        NSLog(@"有相机📷");
        UILabel *label = [[UILabel alloc] initWithFrame:frame];
        label.text = @"+";
        imagePicker.allowsEditing = YES;
        imagePicker.cameraOverlayView = label;
    }else {
        imagePicker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    }
    imagePicker.delegate = self;
    //    [self presentViewController:imagePicker animated:YES completion: nil];
    if ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) {
        if(self.imagePickerPopover!=nil && [self.imagePickerPopover isPopoverVisible]) {
            [self.imagePickerPopover dismissPopoverAnimated:YES];
            self.imagePickerPopover = nil;
            return;
        }
        self.imagePickerPopover = [[UIPopoverController alloc] initWithContentViewController:imagePicker];
        self.imagePickerPopover.delegate = self;
        [self.imagePickerPopover presentPopoverFromBarButtonItem:sender
                                        permittedArrowDirections:UIPopoverArrowDirectionAny
                                                        animated:YES];
    } else {
        [self presentViewController:imagePicker animated:YES completion:nil];
    }
    
}

- (IBAction)deletePicture:(id)sender {
    
    self.imageView.image = nil;
    [[LRDImageStore sharedStore] deleteImageForKey:self.item.imageKey];
}

- (IBAction)backgroundTapped:(id)sender {
    [self.view endEditing:NO];
    for(UIView *subView in self.view.subviews) {
        if ([subView hasAmbiguousLayout]) {
            [subView exerciseAmbiguityInLayout];
        }
    }
    NSLog(@"backgroundTapped");
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
