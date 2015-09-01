/*
 *  CTCall.h
 *  CFTelephony
 *
 *  Copyright 2010 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

CORETELEPHONY_EXTERN NSString * const CTCallStateDialing //呼叫;
CORETELEPHONY_EXTERN NSString * const CTCallStateIncoming //呼入;
CORETELEPHONY_EXTERN NSString * const CTCallStateConnected  //通话;
CORETELEPHONY_EXTERN NSString * const CTCallStateDisconnected  //挂断;

@interface CTCall : NSObject //通话信息的封装
{
@private
    NSString *_callState;
    NSString *_callID;
}

 //通话状态,初始化状态CTCallStateDialing或者CTCallStateIncoming，通话建立状态：CTCallStateConnected，通话挂断
@property(nonatomic, readonly, copy) NSString *callState;

 //通话ID，用来标识一个手机通话（唯一），以区分多个正在激活的通话（例如挂起的通话与正在通话）
@property(nonatomic, readonly, copy) NSString *callID;

@end
