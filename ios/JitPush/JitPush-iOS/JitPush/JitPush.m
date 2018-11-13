//
//  JitPush.m
//  JitPush
//
//  Created by Yuttana Kungwon on 8/9/2559 BE.
//  Copyright © 2559 Jitta.com. All rights reserved.
//

#import "JitPush.h"
#import "RCTBridge.h"
//#import "CWStatusBarNotification.h"

NSString *const kBundlePayload = @"CurrentPayload";


@interface JitPush() <NSURLSessionDownloadDelegate, RCTBridgeModule>

@property NSURL *defaultBundleURL;
@property NSURL *defaultPayloadURL;
@property NSURL *_latestBundleURL;
@property NSURL *payloadURL;
@property BOOL showProgress;
@property BOOL allowCellularDataUse;
@property NSString *hostName;
@property JitPushUpdateType updateType;
@property NSDictionary *updatedPayloadData;
@property BOOL isInitialize;

@end

@implementation JitPush

RCT_EXPORT_MODULE()

+ (id)sharedManager
{
    static JitPush *_sharedManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedManager = [[self alloc] init];
        [_sharedManager defaults];
    });
    
    return _sharedManager;
}
- (instancetype)init
{
    self = [super init];
    return self;
}

- (void)defaults
{
    self.showProgress = YES;
    self.allowCellularDataUse = NO;
    self.updateType = JitPushMinorUpdate;
    //    self.statusBarNotification = [CWStatusBarNotification new];
}

#pragma mark - JS methods // Export constants

- (NSDictionary *)constantsToExport {
    NSDictionary *payload = [[NSUserDefaults standardUserDefaults] objectForKey:kBundlePayload];
    NSString *version = @"";
    if (payload) {
        version = [payload objectForKey:@"version"];
    }
    return @{ @"jsCodeVersion": version };
}

#pragma mark - initialize Singleton

- (void)initWithUpdatePayloadURL:(NSURL *)url defaultBundle:(NSURL *)bundleURL defaultPayload:(NSURL *)payloadURL
{
    self.payloadURL = url;
    self.defaultBundleURL = bundleURL;
    self.defaultPayloadURL = payloadURL;
    
    // compare payload data
    NSData *defaultPayloadData = [NSData dataWithContentsOfURL:self.defaultPayloadURL];
    [self compareStoredPayloadDataWithDefaultPayloadData:defaultPayloadData];
}

- (void)compareStoredPayloadDataWithDefaultPayloadData:(NSData *)defaultPayloadData
{
    NSUserDefaults *defaults = [[NSUserDefaults alloc] init];
    
    if (!defaultPayloadData) {
        NSLog(@"Don't have your default payload. plz check initialize default payload url");
        self.isInitialize = NO;
        return;
    }
    
    NSError *error;
    NSDictionary *localPayload = [NSJSONSerialization JSONObjectWithData:defaultPayloadData
                                                                 options:NSJSONReadingAllowFragments
                                                                   error:&error];
    if (error) {
        NSLog(@"Wrong JSON file.");
        self.isInitialize = NO;
        return;
    }
    
    NSDictionary *storedPayload = [defaults objectForKey:kBundlePayload];
    if (!storedPayload) {
        // store it to UserDefault.
        [defaults setObject:localPayload forKey:kBundlePayload];
    } else {
        // check compare version between old version (stored in USERDEFAULT) and new version (local default payload file)
        id storedPayloadVersion = [storedPayload objectForKey:@"version"];
        id localPayloadVersion = [localPayload objectForKey:@"version"];
        
        // compare if stored version < local payload version
        if ([storedPayloadVersion compare:localPayloadVersion options:NSNumericSearch] == NSOrderedAscending) {
            NSData *defaultJSBundleData = [NSData dataWithContentsOfURL:self.defaultBundleURL];
            NSString *fileName = [NSString stringWithFormat:@"%@/%@", [self JSCodeDirectory], @"main.jsbundle"];
            
            if ([defaultJSBundleData writeToFile:fileName atomically:YES]) {
                [defaults setObject:localPayloadVersion forKey:kBundlePayload];
            }
        }
    }
    
    self.isInitialize = YES;
}

- (void)showProgress:(BOOL)progress
{
    self.showProgress = progress;
}

- (NSURL *)lastestBundleURL
{
    NSString *latestJSCodeURLString = [[[self libraryDirectory] stringByAppendingPathComponent:@"JSCode"] stringByAppendingPathComponent:@"main.jsbundle"];
    
    if (latestJSCodeURLString && [[NSFileManager defaultManager] fileExistsAtPath:latestJSCodeURLString]) {
        self._latestBundleURL = [NSURL URLWithString:[NSString stringWithFormat:@"file://%@", latestJSCodeURLString]];
        NSLog(@"last bundle %@", self._latestBundleURL);
    }
    
    if (self._latestBundleURL) {
        return self._latestBundleURL;
    } else {
        return self.defaultBundleURL;
    }
    
}

- (void)checkUpdate
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        if (self.payloadURL) {
            [self performUpdateCheck];
        }
        else {
            NSLog(@"Please make sure you have set the Update payload URL");
        }
    });
}

- (void)allowCellularDataUse:(BOOL)cellular
{
    self.allowCellularDataUse = cellular;
}

- (void)downloadUpdateWithType:(JitPushUpdateType)type
{
    self.updateType = type;
}

#pragma mark - private

- (void)startDownloadingUpdateFromURL:(NSString *)urlString
{
    NSURL *url = [NSURL URLWithString:urlString];
    
    NSURLSessionConfiguration *sessionConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
    sessionConfig.allowsCellularAccess = self.allowCellularDataUse;
    sessionConfig.timeoutIntervalForRequest = 60.0;
    sessionConfig.timeoutIntervalForResource = 60.0;
    sessionConfig.HTTPMaximumConnectionsPerHost = 1;
    
    NSURLSession *session = [NSURLSession sessionWithConfiguration:sessionConfig
                                                          delegate:self
                                                     delegateQueue:nil];
    
    NSURLSessionDownloadTask* task = [session downloadTaskWithURL:url];
    [task resume];
}

- (NSString*)containerVersion {
    return [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
}

- (NSString*)libraryDirectory
{
    // Application sandbox library directory.
    // eg. /data/Containers/Data/Application/AEB82194-E958-4BD3-8C90-3F3B70157D75/Library
    return [NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES) firstObject];
}

- (NSString *)JSCodeDirectory
{
    NSString* libraryDirectory = [self libraryDirectory];
    NSString *filePathAndDirectory = [libraryDirectory stringByAppendingPathComponent:@"JSCode"];
    NSError *error;
    
    NSFileManager* fileManager = [NSFileManager defaultManager];
    
    BOOL isDir;
    if ([fileManager fileExistsAtPath:filePathAndDirectory isDirectory:&isDir]) {
        if (isDir) {
            NSLog(@"file path and directory: %@", filePathAndDirectory);
            return filePathAndDirectory;
        }
    }
    
    if (![fileManager createDirectoryAtPath:filePathAndDirectory
                withIntermediateDirectories:YES
                                 attributes:nil
                                      error:&error])
    {
        NSLog(@"Create directory error: %@", error);
        return nil;
    }
    return filePathAndDirectory;
}

#pragma mark - check update

- (void)performUpdateCheck
{
    if (!self.isInitialize) {
        return;
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        if (self.showProgress) {
            //            CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
            //            [statusBarNotification displayNotificationWithMessage:@"Checking for update." forDuration:0.5];
            NSLog(@"Checking update");
        }
    });
    
    NSData *data = [NSData dataWithContentsOfURL:self.payloadURL];
    if (!data) {
        if (self.showProgress) {
            //            CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
            //            [statusBarNotification displayNotificationWithMessage:@"Received no Update payload data." forDuration:1];
            NSLog(@"no update payload data");
        }
        return;
    }
    
    NSError* error;
    self.updatedPayloadData = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingAllowFragments error:&error];
    if (error) {
        if (self.showProgress) {
            //            CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
            //            [statusBarNotification displayNotificationWithMessage:@"Error reading json payload!" forDuration:1];
            NSLog(@"Error json payload");
        }
        return;
    }
    
    // json parser
    NSString *versionToDownload = [self.updatedPayloadData objectForKey:@"version"];
    NSString *urlToDownload = [[self.updatedPayloadData objectForKey:@"url"] objectForKey:@"url"];
    NSString *minContainerVersion = [self.updatedPayloadData objectForKey:@"minContainerVersion"];
    BOOL isRelative = [[[self.updatedPayloadData objectForKey:@"url"] objectForKey:@"isRelative"] boolValue];
    
    if ([self shouldDownloadUpdateWithVersion:versionToDownload forMinContainerVersion:minContainerVersion]) {
        if (self.showProgress) {
            //            CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
            //            [statusBarNotification displayNotificationWithMessage:@"You have a new update!" forDuration:1];
            NSLog(@"You have a new update.");
        }
        if (isRelative) {
            urlToDownload = [self.hostName stringByAppendingString:urlToDownload];
        }
        [self startDownloadingUpdateFromURL:urlToDownload];
    }
    else {
        if (self.showProgress) {
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                //                CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
                //                [statusBarNotification setNotificationLabelBackgroundColor:[UIColor greenColor]];
                //                [statusBarNotification displayNotificationWithMessage:@"Already up to date." forDuration:0.5];
                NSLog(@"Already up to date");
            });
            
            //TODO: test call delegate
            // [self.delegate JitPushDidUpdateBundleWithURL:nil];
        }
    }
}

- (BOOL)shouldDownloadUpdateWithVersion:(NSString*)version forMinContainerVersion:(NSString*)minContainerVersion
{
    BOOL shouldDownload = NO;
    
    /*
     * First check for the version match. If we have the update version, then don't download.
     * Also, check what kind of updates the user wants.
     */
    NSDictionary *currentPayload = [[NSUserDefaults standardUserDefaults] objectForKey:kBundlePayload];
    if (!currentPayload) {
        shouldDownload = YES;
    }
    else {
        NSString *currentVersion = [currentPayload objectForKey:@"version"];
        
        int currentMajor, currentMinor, currentPatch, updateMajor, updateMinor, updatePatch;
        
        NSArray *currentComponents = [currentVersion componentsSeparatedByString:@"."];
        if (currentComponents.count == 0) {
            return NO;
        }
        currentMajor = [currentComponents[0] intValue];
        if (currentComponents.count >= 2) {
            currentMinor = [currentComponents[1] intValue];
        }
        else {
            currentMinor = 0;
        }
        if (currentComponents.count >= 3) {
            currentPatch = [currentComponents[2] intValue];
        }
        else {
            currentPatch = 0;
        }
        NSArray *updateComponents = [version componentsSeparatedByString:@"."];
        updateMajor = [updateComponents[0] intValue];
        if (updateComponents.count >= 2) {
            updateMinor = [updateComponents[1] intValue];
        }
        else {
            updateMinor = 0;
        }
        if (updateComponents.count >= 3) {
            updatePatch = [updateComponents[2] intValue];
        }
        else {
            updatePatch = 0;
        }
        
        switch (self.updateType) {
            case JitPushMajorUpdate: {
                if (currentMajor < updateMajor) {
                    shouldDownload = YES;
                }
                break;
            }
            case JitPushMinorUpdate: {
                if (currentMajor < updateMajor || (currentMajor == updateMajor && currentMinor < updateMinor)) {
                    shouldDownload = YES;
                }
                
                break;
            }
            case JitPushPatchUpdate: {
                if (currentMajor < updateMajor || (currentMajor == updateMajor && currentMinor < updateMinor)
                    || (currentMajor == updateMajor && currentMinor == updateMinor && currentPatch < updatePatch)) {
                    shouldDownload = YES;
                }
                break;
            }
            default: {
                shouldDownload = YES;
                break;
            }
        }
    }
    
    /*
     * Then check if the update is good for our container version.
     */
    NSString* containerVersion = [self containerVersion];
    if (shouldDownload && [containerVersion compare:minContainerVersion options:NSNumericSearch] != NSOrderedAscending) {
        shouldDownload = YES;
    }
    else {
        shouldDownload = NO;
    }
    
    return shouldDownload;
}


#pragma mark - NSURLSessionDownloadDelegate

- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didWriteData:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite
{
    if (totalBytesExpectedToWrite == NSURLSessionTransferSizeUnknown) {
        if (self.showProgress) {
            NSString *progress = [NSString stringWithFormat:@"Downloading Update - %@", [NSByteCountFormatter stringFromByteCount:totalBytesWritten
                                                                                                                       countStyle:NSByteCountFormatterCountStyleFile]];
            //            CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
            //            [statusBarNotification setNotificationLabelBackgroundColor: [UIColor colorWithRed:102.0/255.0 green:178.0/255.0 blue:255.0/255.0 alpha:1.0]];
            //            [statusBarNotification displayNotificationWithMessage:progress completion:nil];
            
            NSLog(@"%@", progress);
        }
    }
    else {
        if (self.showProgress) {
            NSString *progress = [NSString stringWithFormat:@"Downloading Update - %d%%", (int)(totalBytesWritten/totalBytesExpectedToWrite) * 100];
            //            CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
            //            [statusBarNotification displayNotificationWithMessage:progress completion:nil];
            NSLog(@"%@", progress);
        }
    }
    
}

- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didFinishDownloadingToURL:(NSURL *)location
{
    if (self.showProgress) {
        //        CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
        //        [statusBarNotification displayNotificationWithMessage:@"Download Complete." forDuration:1];
        NSLog(@"Download complete");
    }
    
    NSError *error;
    NSData *data = [NSData dataWithContentsOfURL:location];
    NSString *filename = [NSString stringWithFormat:@"%@/%@", [self JSCodeDirectory], @"main.jsbundle"];
    
    if ([data writeToFile:filename atomically:YES]) {
        [[NSUserDefaults standardUserDefaults] setObject:self.updatedPayloadData forKey:kBundlePayload];
        if ([self.delegate respondsToSelector:@selector(JitPushDidUpdateBundleWithURL:)]) {
            NSURL *updatedBundleURL = [NSURL URLWithString:[NSString stringWithFormat:@"file://%@", filename]];
            [self.delegate JitPushDidUpdateBundleWithURL:updatedBundleURL];
        }
    }
    else {
        //        CWStatusBarNotification *statusBarNotification = [CWStatusBarNotification new];
        //        [statusBarNotification displayNotificationWithMessage:@"Update Failed." forDuration:1];
        NSLog(@"Update failed - %@.", error.localizedDescription);
    }
    
}

- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task didCompleteWithError:(NSError *)error
{
    if (error) {
        NSLog(@"%@", error.localizedDescription);
    }
}

@end
