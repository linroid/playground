//
//  LRDItemTableViewController.m
//  Homepwner
//
//  Created by 张林 on 15/6/24.
//  Copyright (c) 2015年 张林. All rights reserved.
//

#import "LRDItemTableViewController.h"
#import "LRDDetailViewController.h"

@interface LRDItemTableViewController () <UITableViewDelegate>

@end

@implementation LRDItemTableViewController

- (void) loadView {
    [super loadView];
//    self.navigationController
}
- (instancetype) init{
    self = [super initWithStyle:UITableViewStylePlain];
    if (self) {
        for (int i=0; i<8; i++) {
            [[LRDItemStore sharedStore] createItem];
        }
    }
    
    self.navigationItem.title = @"Homepwner";
    
    UIBarButtonItem *addBarButton = [[UIBarButtonItem alloc]
                                      initWithBarButtonSystemItem:UIBarButtonSystemItemAdd
                                      target:self action:@selector(addNewItem:)];
    self.navigationItem.rightBarButtonItem = addBarButton;
    self.navigationItem.leftBarButtonItem = self.editButtonItem;
    return self;
}

- (instancetype) initWithStyle:(UITableViewStyle)style {
    return [self init];
}
- (void)viewDidLoad {
    [super viewDidLoad];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier: @"tableCell"];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier: @"endCell"];
    self.tableView.delegate = self;
    
    UILabel *footer = [[UILabel alloc] init];
    footer.text = @"No mode items";
    [self.tableView setTableFooterView: footer];
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}
- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath {
    return @"Remove";
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction) addNewItem: (id) sender {
//    [[LRDItemStore sharedStore] createItem];
//    NSInteger lastRow = [self.tableView numberOfRowsInSection: 0];
//    NSIndexPath *lastIndexPath = [NSIndexPath indexPathForRow: lastRow inSection:0];
//    
//    [self.tableView insertRowsAtIndexPaths: @[lastIndexPath] withRowAnimation:UITableViewRowAnimationTop];
    
    LRDDetailViewController *detailController = [[LRDDetailViewController alloc] initForNewItem:YES];
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:detailController];
    navController.modalPresentationStyle = UIModalPresentationPageSheet;
    [self presentViewController:navController animated:YES completion:nil];
}
- (IBAction)toggleEditingMode:(id)sender {
//    if(self.tableView.isEditing) {
//        [sender setTitle: @"Edit" forState: UIControlStateNormal];
//        [self setEditing:NO animated:YES];
//    } else {
//        [sender setTitle: @"Done" forState:UIControlStateNormal];
//        [self setEditing:YES animated:YES];
//    }
}

- (void) tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        NSArray * items = [[LRDItemStore sharedStore] allItems];
        [[LRDItemStore sharedStore] removeItem: items[indexPath.row]];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation: UITableViewRowAnimationBottom];
    }
}

- (void) tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)sourceIndexPath toIndexPath:(NSIndexPath *)destinationIndexPath {
    [[LRDItemStore sharedStore] moveItemAtIndex:sourceIndexPath.row toIndex:destinationIndexPath.row];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if(section == 0) {
        return [[[LRDItemStore sharedStore] allItems] count];
    }else {
        return 1;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell;
    NSInteger position = 0;
    if(indexPath.section == 0){
        cell = [tableView dequeueReusableCellWithIdentifier: @"tableCell"
                                               forIndexPath: indexPath];
        position = indexPath.row;
    }else {
        cell = [tableView dequeueReusableCellWithIdentifier: @"endCell"
                                               forIndexPath:indexPath];
    }
    
    if(indexPath.section == 0) {
        cell.backgroundColor = [UIColor whiteColor];
    }else {
        cell.backgroundColor = [UIColor clearColor];
    }
    if(indexPath.section == 0){
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

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    LRDDetailViewController *detailController = [[LRDDetailViewController alloc] initForNewItem:NO];
    NSArray *items = [[LRDItemStore sharedStore] allItems];
    detailController.item = items[indexPath.row];
    [self.navigationController pushViewController:detailController animated:YES];
}

- (CGFloat) tableView: (UITableView *) tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    if(indexPath.section == 0){
        return 66.0;
    }else {
        return 44.0;
    }
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    if(indexPath.section != 0){
        return NO;
    }
    return YES;
}

- (BOOL) tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    if(indexPath.section != 0){
        return NO;
    }
    return YES;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.tableView reloadData];
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
