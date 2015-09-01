/*
 *  CTCallCenter.h
 *  CFTelephony
 *
 *  Copyright 2010 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

@class CTCall;

//作用于通话状态改变时，此时他将回调指定的事件
@interface CTCallCenter : NSObject
{
@private
    void *_server;

    NSSet *_currentCalls;
    void (^_callEventHandler)(CTCall *);
}

// 一个当前进程中所有通话的容器。
@property(readonly, retain) NSSet *currentCalls;

/*
	通话事件状态转变时进行回调的函数。
	当我们的程序处于激活状态，则通话状态转变时直接回调我们指定的函数。
	但是当程序处于挂起状态时（后台），程序 不会立即接到状态转变的回调，直到重新变为激活状态。
	当又挂起转为激活时，程序只能收到每个通话事件最后的转变状态。
	例如，我们的程序在通话创建后（并未 连接）就由激活转变为挂起状态了，而之后此通话先后转变为通话、挂断。
	当我们的程序重新激活后，我们将收到此电话的挂断消息回调。这个就是官方文档中所谓 的Single call event。
*/
@property(nonatomic, copy) void (^callEventHandler)(CTCall*);

@end
