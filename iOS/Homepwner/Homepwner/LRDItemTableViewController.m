//
//  LRDItemTableViewController.m
//  Homepwner
//
//  Created by 张林 on 15/6/24.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDItemTableViewController.h"

@interface LRDItemTableViewController () <UITableViewDelegate>

@end

@implementation LRDItemTableViewController

- (instancetype) init{
    self = [super initWithStyle:UITableViewStylePlain];
    if (self) {
        for (int i=0; i<50; i++) {
            [[LRDItemStore sharedStore] createItem];
        }
    }
    return self;
}

- (instancetype) initWithStyle:(UITableViewStyle)style {
    return [self init];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier: @"cheapCell"];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier: @"expensiveCell"];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier: @"endCell"];
    self.tableView.delegate = self;
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 3;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if(section == 0) {
        return 20;
    }else if(section == 1) {
        return [[[LRDItemStore sharedStore] allItems] count] - 20;
    }else {
        return 1;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell;
    NSInteger position;
    if(indexPath.section == 0){
        cell = [tableView dequeueReusableCellWithIdentifier: @"expensiveCell"
                                               forIndexPath: indexPath];
        position = indexPath.row;
    }else if(indexPath.section == 1){
        cell = [tableView dequeueReusableCellWithIdentifier: @"cheapCell"
                                               forIndexPath: indexPath];
        position = indexPath.row + 20;
    }else {
        cell = [tableView dequeueReusableCellWithIdentifier: @"endCell"
                                               forIndexPath:indexPath];
    }
    
    if(indexPath.section == 0) {
        cell.backgroundColor = [UIColor redColor];
    }else if(indexPath.section == 1){
        cell.backgroundColor = [UIColor clearColor];
    }else {
        cell.backgroundColor = [UIColor clearColor];
    }
    if(indexPath.section != 2){
        NSArray *items = [[LRDItemStore sharedStore] allItems];
        LRDItem *item = items[indexPath.row];
        cell.textLabel.text = [NSString stringWithFormat: @"%d) [%d %d] %@", position, indexPath.section, indexPath.row, item.itemName ];
        UIImage *image = [UIImage imageNamed:@"AppIcon"];
        cell.imageView.image = image;
    } else {
        cell.textLabel.text = @"No mode items";
    }
    
    return cell;
}
- (CGFloat) tableView: (UITableView *) tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    if(indexPath.section != 2){
        return 66.0;
    }else {
        return 44.0;
    }
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
