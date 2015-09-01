/*
 *  CTSubscriberInfo.h
 *  CFTelephony
 *
 *  Copyright 2012 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

#import "CTSubscriber.h"

//授权信息
@interface CTSubscriberInfo : NSObject

+ (CTSubscriber*) subscriber;

@end
