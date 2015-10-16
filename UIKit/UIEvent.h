//
//  UIEvent.h
//  UIKit
//
//  Copyright (c) 2005-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

@class UIWindow, UIView, UIGestureRecognizer;

typedef NS_ENUM(NSInteger, UIEventType) {
    UIEventTypeTouches,//触摸事件
    UIEventTypeMotion,//摇晃事件
    UIEventTypeRemoteControl,//遥控事件
};

typedef NS_ENUM(NSInteger, UIEventSubtype) {
    // available in iPhone OS 3.0
    UIEventSubtypeNone                              = 0,//// 不包含任何子事件类型
    
    // for UIEventTypeMotion, available in iPhone OS 3.0
    UIEventSubtypeMotionShake                       = 1,//// 摇晃事件（从iOS3.0开始支持此事件）
    
    // for UIEventTypeRemoteControl, available in iOS 4.0
    UIEventSubtypeRemoteControlPlay                 = 100,////远程控制子事件类型（从iOS4.0开始支持远程控制事件）
    //播放事件【操作：停止状态下，按耳机线控中间按钮一下】
    UIEventSubtypeRemoteControlPause                = 101,//暂停事件
    UIEventSubtypeRemoteControlStop                 = 102,  //停止事件
    UIEventSubtypeRemoteControlTogglePlayPause      = 103,// //播放或暂停切换【操作：播放或暂停状态下，按耳机线控中间按钮一下】
    UIEventSubtypeRemoteControlNextTrack            = 104,////下一曲【操作：按耳机线控中间按钮两下】
    UIEventSubtypeRemoteControlPreviousTrack        = 105,//上一曲【操作：按耳机线控中间按钮三下】
    UIEventSubtypeRemoteControlBeginSeekingBackward = 106, //快退开始【操作：按耳机线控中间按钮三下到了快退的位置松开】
    UIEventSubtypeRemoteControlEndSeekingBackward   = 107,//快退停止【操作：按耳机线控中间按钮三下到了快退的位置松开】
    UIEventSubtypeRemoteControlBeginSeekingForward  = 108, //快进开始【操作：按耳机线控中间按钮两下不要松开】
    UIEventSubtypeRemoteControlEndSeekingForward    = 109,//快进停止【操作：按耳机线控中间按钮两下到了快进的位置松开】
};

/*
    一个UIEvent对象（或者，简单的事件对象）在iPhone OS中变现为事件。
    这里有大致上有三种类型的事件：触摸事件，摇晃事件，以及遥控事件。
    遥控事件能够让一个响应者对象从外部配件或者耳机接受命令以便他可以管理音频和视频
    。举个例子，播放视频或者跳到下一个音轨。摇晃事件被引入是在iOS3.0，而遥控事件是在iOS4.0被引进。
    触摸对象的事件类型包括一个或多个触摸（就是，手指触摸在屏幕上），触摸与某一事件联系在一起。
    一个触摸是被一个UITouch对象调用的。
    当一个事件触发了，系统将会把它传递给合适的响应对象并通过UIEvent对象发出一个消息调用UIResponder方法如touchesBegan:withEvent: 。
    响应对象可以分配触摸事件到合适的触摸类型并适当的控制他们。
    UIEvent中的方法可以让你获取全部的触摸事件(allTouches)或者给定的视图或者窗口（touchesForView: 或者 touchesForWindow:）。
    它可以分辨从响应对象传递过来的事件对象发生的时间（timestamp）。

一个UIEvent对象贯穿在多点触摸事件的序列中；
UIKit 重用同一个UIEvent实例来分配每一个事件到应用程序。
你不需要保持一个事件对象或者任何从事件对象返回的对象。
如果你需要保存事件对象然後传递到另外一个对象，你需要从UITouch或者UIEvent中复制信息。

     你可以通过类型属性和子类型属性，获取事件类型和事件的子类型。
     UIEvent定义了事件的类型为触摸，摇晃和遥控事件。
     它也定义了摇晃事件的子类型，以及为遥控事件定义了一系列的子类型；例如“播放”，“上一曲目”。
     在响应链中第一响应者或者任意响应者能够实现关于遥控相应的方法（例如 asmotionBegan:withEvent:）去处理摇动遥控事件。
     一个事件响应者去处理遥控事件，必须实现UIResponder的这个方法：
*/
NS_CLASS_AVAILABLE_IOS(2_0) @interface UIEvent : NSObject
{
  @private
    NSTimeInterval _timestamp;
}

@property(nonatomic,readonly) UIEventType     type NS_AVAILABLE_IOS(3_0); //事件类型
@property(nonatomic,readonly) UIEventSubtype  subtype NS_AVAILABLE_IOS(3_0);

@property(nonatomic,readonly) NSTimeInterval  timestamp;//事件发生的时间

//获取事件中的触摸对象
//返回和接收者有关的所有触摸对象
- (NSSet *)allTouches;
//返回接收者给定的窗口的触摸事件的事件响应对象
- (NSSet *)touchesForWindow:(UIWindow *)window;
// 返回属于接收者给定的视图的事件响应的触摸对象


- (NSSet *)touchesForView:(UIView *)view;
//获取绑定手势识别器的所有触摸,能够查询所有触摸的一个正在处理的一个手势识别器对象
- (NSSet *)touchesForGestureRecognizer:(UIGestureRecognizer *)gesture NS_AVAILABLE_IOS(3_2);

@end
