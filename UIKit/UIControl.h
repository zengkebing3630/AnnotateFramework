//
//  UIControl.h
//  UIKit
//
//  Copyright (c) 2005-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

typedef NS_OPTIONS(NSUInteger, UIControlEvents) {
    UIControlEventTouchDown           = 1 <<  0,     //单点触摸按下事件：用户点触屏幕，或者又有新手指落下的时候
    UIControlEventTouchDownRepeat     = 1 <<  1,      // 多点触摸按下事件，点触计数大于1：用户按下第二、三、或第四根手指的时候。
    UIControlEventTouchDragInside     = 1 <<  2,     //当一次触摸在控件窗口内拖动时。
    UIControlEventTouchDragOutside    = 1 <<  3,     //当一次触摸在控件窗口之外拖动时。
    UIControlEventTouchDragEnter      = 1 <<  4,     //当一次触摸从控件窗口之外拖动到内部时。
    UIControlEventTouchDragExit       = 1 <<  5,     //当一次触摸从控件窗口内部拖动到外部时。
    UIControlEventTouchUpInside       = 1 <<  6,     //所有在控件之内触摸抬起事件。
    UIControlEventTouchUpOutside      = 1 <<  7,     //所有在控件之外触摸抬起事件(点触必须开始与控件内部才会发送通知)。
    UIControlEventTouchCancel         = 1 <<  8,     //所有触摸取消事件，即一次触摸因为放上了太多手指而被取消，或者被上锁或者电话呼叫打断。

    UIControlEventValueChanged        = 1 << 12,     // 当控件的值发生改变时，发送通知。用于滑块、分段控件、以及其他取值的控件。你可以配置滑块控件何时发送通知，在滑块被放下时发送，或者在被拖动时发送。

    UIControlEventEditingDidBegin     = 1 << 16,     // UITextField,当文本控件中开始编辑时发送通知。
    UIControlEventEditingChanged      = 1 << 17,     //当文本控件中的文本被改变时发送通知。
    UIControlEventEditingDidEnd       = 1 << 18,     //当文本控件中编辑结束时发送通知。
    UIControlEventEditingDidEndOnExit = 1 << 19,     // 当文本控件内通过按下回车键（或return）结束编辑时，发送通知。

    UIControlEventAllTouchEvents      = 0x00000FFF,  // 通知所有事件 
    UIControlEventAllEditingEvents    = 0x000F0000,  // 通知所有关于文本编辑的事件。for UITextField
    UIControlEventApplicationReserved = 0x0F000000,  // range available for application use
    UIControlEventSystemReserved      = 0xF0000000,  // range reserved for internal framework use
    UIControlEventAllEvents           = 0xFFFFFFFF
};
// 除了默认事件以外，自定义控件类还可以用0x0F000000到0x0FFFFFFF之间的值，来定义自己的事件。

typedef NS_ENUM(NSInteger, UIControlContentVerticalAlignment) {
    UIControlContentVerticalAlignmentCenter  = 0,//中心
    UIControlContentVerticalAlignmentTop     = 1,//顶部
    UIControlContentVerticalAlignmentBottom  = 2,//底部
    UIControlContentVerticalAlignmentFill    = 3,//充满
};

typedef NS_ENUM(NSInteger, UIControlContentHorizontalAlignment) {
    UIControlContentHorizontalAlignmentCenter = 0,//中心
    UIControlContentHorizontalAlignmentLeft   = 1,//左边
    UIControlContentHorizontalAlignmentRight  = 2,//右边
    UIControlContentHorizontalAlignmentFill   = 3,//充满
};

typedef NS_OPTIONS(NSUInteger, UIControlState) {
    UIControlStateNormal       = 0,   //正常
    UIControlStateHighlighted  = 1 << 0,       //高亮           // used when UIControl isHighlighted is set
    UIControlStateDisabled     = 1 << 1,       //无效
    UIControlStateSelected     = 1 << 2,       //选中           // flag usable by app (see below)
    UIControlStateApplication  = 0x00FF0000,              // additional flags available for application use
    UIControlStateReserved     = 0xFF000000               // flags reserved for internal framework use
};
// 除了默认状态以外，自定义控件类还可以用0x00FF0000到0xFF000000之间的值，来定义他们的状态。

@class UITouch;
@class UIEvent;

//______________________________________________________

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIControl : UIView {
  @package
    NSMutableArray* _targetActions;
    CGPoint         _previousPoint;
    CFAbsoluteTime  _downTime;
    struct {
        unsigned int disabled:1;
        unsigned int tracking:1;
        unsigned int touchInside:1;
        unsigned int touchDragged:1;
        unsigned int requiresDisplayOnTracking:1;
        unsigned int highlighted:1;
        unsigned int dontHighlightOnTouchDown:1;
        unsigned int delayActions:1;
        unsigned int allowActionsToQueue:1;
        unsigned int pendingUnhighlight:1;
        unsigned int selected:1;
	unsigned int verticalAlignment:2;
	unsigned int horizontalAlignment:2;
        unsigned int wasLastHighlightSuccessful:1;
        unsigned int touchHasHighlighted:1;
    } _controlFlags;
}
/* 控件默认是启用的。要禁用控件，可以将enabled属性设置为NO，这将导致控件忽略任何触摸事件。
被禁用后，控件还可以用不同的方式显示自己，比如变成灰色不可用。
虽然是由控件的子类完成的，这个属性却存在于UIControl中。默认YES
*/
@property(nonatomic,getter=isEnabled) BOOL enabled;                                  
/*
    当用户选中控件时，UIControl类会将其selected属性设置为YES。子类有时使用这个属性来让控件选择自身，或者来表现不同的行为方式,默认：NO
*/
@property(nonatomic,getter=isSelected) BOOL selected;               
/*
    默认：NO

*/                 
@property(nonatomic,getter=isHighlighted) BOOL highlighted;                          // default is NO. this gets set/cleared automatically when touch enters/exits during tracking and cleared on up
/*
    控件如何在垂直方向上布置自身的内容。默认是将内容顶端对其，对于文本字段，默认center
*/
@property(nonatomic) UIControlContentVerticalAlignment contentVerticalAlignment;  
// 控件如何在水平方向上布置自身的内容  ，默认center 
@property(nonatomic) UIControlContentHorizontalAlignment contentHorizontalAlignment; 
//状态
@property(nonatomic,readonly) UIControlState state;                
@property(nonatomic,readonly,getter=isTracking) BOOL tracking;
@property(nonatomic,readonly,getter=isTouchInside) BOOL touchInside; // valid during tracking only

// 当在控件的bound内发生了一个触摸事件，首先会调用控件的beginTrackingWithTouch方法。
// 该函数返回的BOOl值决定着：当触摸事件是dragged时，是否需要响应。在我们这里的自定义控件中，是需要跟踪用户的dragging，所以返回YES
- (BOOL)beginTrackingWithTouch:(UITouch *)touch withEvent:(UIEvent *)event;

//该方法返回的BOOL值标示是否继续跟踪touch事件。通过该方法我们可以根据touch位置对用户的操作进行过滤
- (BOOL)continueTrackingWithTouch:(UITouch *)touch withEvent:(UIEvent *)event;
//当跟踪结束的时候，会调用下面这个方法：
- (void)endTrackingWithTouch:(UITouch *)touch withEvent:(UIEvent *)event;
//当control从window 移除，或者event = nil，结束追踪
- (void)cancelTrackingWithEvent:(UIEvent *)event;   // event may be nil if cancelled for non-event reasons, e.g. removed from window
/*
// 事件可以用逻辑OR合并在一起，因此可以再一次单独的addTarget调用中指定多个事件。
下列事件为基类UIControl所支持，除非另有说明，也适用于所有控件 action ！= nil,target 不能Retained
*/
- (void)addTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

// 要删除一个或多个事件的相应动作，可以使用UIControl类的removeTarget方法。使用nil值就可以将给定事件目标的所有动作删除
- (void)removeTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents;

// 要取得关于一个控件所有指定动作的列表，可以使用allTargets方法。这个方法返回一个NSSet，其中包含事件的完整列表- (NSSet *)allTargets;                                                                     // set may include NSNull to indicate at least one nil target
- (UIControlEvents)allControlEvents;                                                       
// 用actionsForTarget方法，来获取针对某一特定事件目标的全部动作列表, NSString selector names
- (NSArray *)actionsForTarget:(id)target forControlEvent:(UIControlEvents)controlEvent;    

/*
如果设计了一个自定义控件类，可以使用sendActionsForControlEvent方法，为基本的UIControl事件或自己的自定义事件发送通知。
例如，如果你的控件值正在发生变化，就可以
发送相应通知，通过控件的代码可以指定时间目标，这个通知将被传播到这些指定的目标
*/
- (void)sendAction:(SEL)action to:(id)target forEvent:(UIEvent *)event;
- (void)sendActionsForControlEvents:(UIControlEvents)controlEvents;                        // send all actions associated with events

@end
