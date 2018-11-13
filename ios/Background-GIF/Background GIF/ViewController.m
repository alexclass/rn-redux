//
//  ViewController.m
//  Background GIF
//
//  Created by Yuttana Kungwon on 1/6/2558 BE.
//  Copyright (c) 2558 E-Commerce Solution Co., Ltd. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // Set your gif file path
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"kenblock" ofType:@"gif"];
    NSData *gifImage = [NSData dataWithContentsOfFile:filePath];
    
    // initial webview full frame view and load gif to webview
    UIWebView *webviewBackground = [[UIWebView alloc] initWithFrame:self.view.frame];
    [webviewBackground loadData:gifImage MIMEType:@"image/gif" textEncodingName:nil baseURL:nil];
    [webviewBackground setUserInteractionEnabled:NO];
    [self.view addSubview:webviewBackground];

    // add black color filter
    UIView *filterBlack = [[UIView alloc] initWithFrame:self.view.frame];
    [filterBlack setBackgroundColor:[UIColor blackColor]];
    [filterBlack setAlpha:0.05];
    [self.view addSubview:filterBlack];

    // add label
    UILabel *welcomeLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 60, self.view.bounds.size.width, 100)];
    [welcomeLabel setText:@"KENBLOCK"];
    [welcomeLabel setTextColor:[UIColor whiteColor]];
    [welcomeLabel setFont:[UIFont systemFontOfSize:50]];
    [welcomeLabel setTextAlignment:NSTextAlignmentCenter];
    [self.view addSubview:welcomeLabel];
    
    // add some buttons
    UIButton *loginButton = [[UIButton alloc] initWithFrame:CGRectMake(40, self.view.bounds.size.height-200, 300, 40)];
    [loginButton.layer setBorderColor:[[UIColor whiteColor] CGColor]];
    [loginButton.layer setBorderWidth:2.0];
    [loginButton.titleLabel setFont:[UIFont systemFontOfSize:24]];
    [loginButton setTintColor:[UIColor whiteColor]];
    [loginButton setTitle:@"Login" forState:UIControlStateNormal];
    [self.view addSubview:loginButton];

    UIButton *signupButton = [[UIButton alloc] initWithFrame:CGRectMake(40, self.view.bounds.size.height-140, 300, 40)];
    [signupButton.layer setBorderColor:[[UIColor whiteColor] CGColor]];
    [signupButton.layer setBorderWidth:2.0];
    [signupButton.titleLabel setFont:[UIFont systemFontOfSize:24]];
    [signupButton setTintColor:[UIColor whiteColor]];
    [signupButton setTitle:@"Sign Up" forState:UIControlStateNormal];
    [self.view addSubview:signupButton];
    
    // Awesome!
}

- (UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
