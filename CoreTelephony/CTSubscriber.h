/*
 *  CTSubscriber.h
 *  CoreTelephony
 *
 *  Copyright 2012 Apple, Inc.. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

 //授权信息变更通知 KEY
CORETELEPHONY_EXTERN NSString * const CTSubscriberTokenRefreshed;

CORETELEPHONY_CLASS_AVAILABLE(7_0)
@interface CTSubscriber : NSObject

 //用户授权Token
@property (nonatomic, readonly, retain) NSData* carrierToken;

@end
