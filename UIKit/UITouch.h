//
//  UITouch.h
//  UIKit
//
//  Copyright (c) 2007-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

@class UIWindow, UIView;

typedef NS_ENUM(NSInteger, UITouchPhase) {
    UITouchPhaseBegan,             // 触摸开始
    UITouchPhaseMoved,             // 接触点移动
    UITouchPhaseStationary,        // 接触点无移动
    UITouchPhaseEnded,             // 触摸结束
    UITouchPhaseCancelled,         //触摸取消
};
/*
当手指接触到屏幕，不管是单点触摸还是多点触摸，事件都会开始，直到用户所有的手指都离开屏幕。
期间所有的UITouch对象都被包含在UIEvent事件对象中，由程序分发给处理者。事件记录了这个周期中所有触摸对象状态的变化。
只要屏幕被触摸，系统就会报若干个触摸的信息封装到UIEvent对象中发送给程序，由管理程序UIApplication对象将事件分发。
一般来说，事件将被发给主窗口，然后传给第一响应者对象(FirstResponder)处理。
*/
NS_CLASS_AVAILABLE_IOS(2_0) @interface UITouch : NSObject

@property(nonatomic,readonly) NSTimeInterval      timestamp; //时间戳记录了触摸事件产生或变化时的时间。单位是秒
@property(nonatomic,readonly) UITouchPhase        phase;//触摸事件在屏幕上有一个周期，即触摸开始、触摸点移动、触摸结束，还有中途取消。而通过phase可以查看当前触摸事件在一个周期中所处的状态
@property(nonatomic,readonly) NSUInteger          tapCount;   // 轻击（Tap）操作和鼠标的单击操作类似，tapCount表示短时间内轻击屏幕的次数。因此可以根据tapCount判断单击、双击或更多的轻击。

// majorRadius and majorRadiusTolerance are in points
// The majorRadius will be accurate +/- the majorRadiusTolerance
//点击的主要半径
@property(nonatomic,readonly) CGFloat majorRadius NS_AVAILABLE_IOS(8_0);
//点击的主要半径公差
@property(nonatomic,readonly) CGFloat majorRadiusTolerance NS_AVAILABLE_IOS(8_0);

@property(nonatomic,readonly,retain) UIWindow    *window;//触摸产生时所处的窗口。由于窗口可能发生变化，当前所在的窗口不一定是最开始的窗口
@property(nonatomic,readonly,retain) UIView      *view;//触摸产生时所处的视图。由于视图可能发生变化，当前视图也不一定时最初的视图。
@property(nonatomic,readonly,copy)   NSArray     *gestureRecognizers NS_AVAILABLE_IOS(3_2);//触摸产生时所处的视图。所具有的手势

//函数返回一个CGPoint类型的值，表示触摸在view这个视图上的位置，这里返回的位置是针对view的坐标系的。调用时传入的view参数为空的话，返回的时触摸点在整个窗口的位置。
- (CGPoint)locationInView:(UIView *)view;
//该方法记录了前一个坐标值，函数返回也是一个CGPoint类型的值， 表示触摸在view这个视图上的位置，这里返回的位置是针对view的坐标系的。调用时传入的view参数为空的话，返回的时触摸点在整个窗口的位置。
- (CGPoint)previousLocationInView:(UIView *)view;

@end
