//
//  JitPush.h
//  JitPush
//
//  Created by Yuttana Kungwon on 8/9/2559 BE.
//  Copyright © 2559 Jitta.com. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, JitPushUpdateType)
{
    // Sementic Version
    JitPushMajorUpdate = 1,
    JitPushMinorUpdate,
    JitPushPatchUpdate,
};

@class JitPush;

@protocol JitPushDelegate<NSObject>
- (void)JitPushDidUpdateBundleWithURL: (NSURL *)url;
@end

@interface JitPush : NSObject

@property (weak) id<JitPushDelegate> delegate;

+ (id)sharedManager;

/* DEFAULT PAYLOAD
 {
     version: "1.2.0",
     minContainerVersion: "1.0",
     url: {
         url: "/s/jiexqbo37ud4cov/main.jsbundle?raw=1",
         isRelative: true
     }
 }
*/
- (void)initWithUpdatePayloadURL:(NSURL *)url defaultBundle:(NSURL *)bundleURL defaultPayload:(NSURL *)payloadURL;

- (NSURL *)lastestBundleURL;

- (void)checkUpdate;
- (void)showProgress:(BOOL)progress;
- (void)allowCellularDataUse:(BOOL)cellular;
- (void)downloadUpdateWithType:(JitPushUpdateType)type;
- (void)setHostName:(NSString *)hostName;

@end
