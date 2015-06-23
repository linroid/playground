//
//  QuizViewController.m
//  Quiz
//
//  Created by 张林 on 6/21/15.
//  Copyright (c) 2015 linroid. All rights reserved.
//

#import "QuizViewController.h"

@interface QuizViewController ()

@property (nonatomic) int currentQuestionIndex;
@property (nonatomic, weak) IBOutlet UILabel *questionLabel;
@property (nonatomic, weak) IBOutlet UILabel *answerLabel;

@property (nonatomic, copy) NSArray *questions;
@property (nonatomic, copy) NSArray *answers;

@end

@implementation QuizViewController

-(IBAction)showQuestion:(id)sender {
    self.currentQuestionIndex++;
    if (self.currentQuestionIndex >= [self.questions count]) {
        self.currentQuestionIndex = 0;
    }
    NSString *question = [self.questions objectAtIndex:self.currentQuestionIndex];
    self.questionLabel.text = question;
    self.answerLabel.text = @"???";
}
-(IBAction)showAnswer:(id)sender {
    NSString *answer = self.answers[self.currentQuestionIndex];
    self.answerLabel.text = answer;
}

-(instancetype) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self){
        self.questions = @[@"Form what is cognac made?",
                       @"What is 7+7",
                       @"What is the capital of Vermont"];
        self.answers = @[@"Grapes",
                     @"14",
                     @"Montpelier"];
        self.tabBarItem.title = @"Quiz";
    }
    return self;
}


@end
