/*  UIWindow.h
Author  曾克兵（keven）
Date    2014/6/14
*/

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIApplication.h>
#import <UIKit/UIKitDefines.h>

typedef CGFloat UIWindowLevel;

@class UIEvent, UIScreen, NSUndoManager, UIViewController;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIWindow : UIView {
  @package
    id                       _delegate;
    CGFloat                  _windowLevel;
    CGFloat                  _windowSublevel;
    id                       _layerContext;
    UIView                  *_lastMouseDownView;
    UIView                  *_lastMouseEnteredView;
    UIResponder             *_firstResponder;
    id                       _fingerInfo;
    id                       _touchData;
    UIInterfaceOrientation   _viewOrientation;
    UIView                  *_exclusiveTouchView;
    NSUndoManager           *_undoManager;
    UIScreen                *_screen;
    CALayer                 *_transformLayer;
    NSMutableArray          *_rotationViewControllers;
    UIViewController        *_rootViewController;
    UIColor                 *_savedBackgroundColor;
    NSMutableSet            *_subtreeMonitoringViews;
    NSMutableSet            *_tintViews;
    id                      _currentTintView;
    struct {
	unsigned int delegateWillRotate:1;
        unsigned int delegateDidRotate:1;
        unsigned int delegateWillAnimateFirstHalf:1;
        unsigned int delegateDidAnimationFirstHalf:1;
        unsigned int delegateWillAnimateSecondHalf:1;
        unsigned int autorotatesToPortrait:1;
        unsigned int autorotatesToPortraitUpsideDown:1;
        unsigned int autorotatesToLandscapeLeft:1;
        unsigned int autorotatesToLandscapeRight:1;
        unsigned int dontBecomeKeyOnOrderFront:1;
        unsigned int output:1;
        unsigned int inGesture:1;
        unsigned int bitsPerComponent:4;
        unsigned int autorotates:1;
        unsigned int isRotating:1;
        unsigned int isUsingOnePartRotationAnimation:1;
        unsigned int isHandlingContentRotation:1;
        unsigned int disableAutorotationCount:4;
        unsigned int needsAutorotationWhenReenabled:1;
        unsigned int forceTwoPartRotationAnimation:1;
        unsigned int orderKeyboardInAfterRotating:1;
        unsigned int roundedCorners:4;
        unsigned int resizesToFullScreen:1;
        unsigned int keepContextInBackground:1;
        unsigned int ignoreSetHidden:1;
        unsigned int forceVisibleOnInit:1;
        unsigned int settingFirstResponder:1;
        unsigned int legacyOrientationChecks:1;
        unsigned int windowResizedToFullScreen:1;
        unsigned int statusBarFollowsOrientation:1;
    } _windowFlags;
    
    id _windowController;
}

@property(nonatomic,retain) UIScreen *screen NS_AVAILABLE_IOS(3_2);  // default is [UIScreen mainScreen]. changing the screen may be an expensive operation and should not be done in performance-sensitive code
/*
    UIWindow在显示的时候会根据UIWindowLevel进行排序的，即Level高的将排在所有Level比他低的层级的前面
    IOS系统中定义了三个window层级，其中每一个层级又可以分好多子层级(从UIWindow的头文件中可以看到成员变量CGFloat _windowSublevel;)，
    不过系统并没有把则个属性开出来。UIWindow的默认级别是UIWindowLevelNormal，我们打印输出这三个level的值分别如下：
 */
@property(nonatomic) UIWindowLevel windowLevel;                   // default = 0.0
@property(nonatomic,readonly,getter=isKeyWindow) BOOL keyWindow;
//调用窗口，使之变成关键窗口
- (void)becomeKeyWindow;                               // override point for subclass. Do not call directly
//调用窗口，使之取消关键窗口
- (void)resignKeyWindow;                               // override point for subclass. Do not call directly

// 使之成为主窗口
- (void)makeKeyWindow;
/*
将当前 UIWindow 设置成应用的 key window，并使得 UIWindow 可见；
 也可以使用 UIView 的 hidden 属性来显示或者隐藏一个 UIWindow。
 */
- (void)makeKeyAndVisible;                             // convenience. most apps call this to show the main window and also make it key. otherwise use view hidden property

@property(nonatomic,retain) UIViewController *rootViewController NS_AVAILABLE_IOS(4_0);  // default is nil
/*
 事件拦截分发到指定视图对象
 当用户发起一个事件，比如触摸屏幕或者晃动设备，系统产生一个事件，同时投递给UIApplication，
 而UIApplication则将这个事件传递给特定的UIWindow进行处理(正常情况都一个程序都只有一个UIWindow)，
 然后由UIWindow将这个事件传递给 特定的对象(即first responder)
 并通过响应链进行处理。虽然都是通过响应链对事件进行处理，但是触摸事件和运动事件在处理上有着明显的不同(主要体现在确定哪个对象才是他们的first responder)：
 */
- (void)sendEvent:(UIEvent *)event;                    // called by UIApplication to dispatch events to views inside the window
//转化当前窗口一个坐标相对另外一个窗口的坐标
- (CGPoint)convertPoint:(CGPoint)point toWindow:(UIWindow *)window;    // can be used to convert to another window
//转化另外窗口一个坐标相对于当前窗口的坐标
- (CGPoint)convertPoint:(CGPoint)point fromWindow:(UIWindow *)window;  // pass in nil to mean screen
//转化当前窗口一个矩形坐标相对另外一个窗口的坐标
- (CGRect)convertRect:(CGRect)rect toWindow:(UIWindow *)window;
//转化另外窗口一个矩形坐标相对于当前窗口的坐标
- (CGRect)convertRect:(CGRect)rect fromWindow:(UIWindow *)window;

@end
/*
 级别的高低顺序从小到大为Normal 0.000000 < StatusBar 1000.000000 < Alert 2000.000000
 */
//默认等级
UIKIT_EXTERN const UIWindowLevel UIWindowLevelNormal;
//UIAlert等级
UIKIT_EXTERN const UIWindowLevel UIWindowLevelAlert;
//状态栏等级
UIKIT_EXTERN const UIWindowLevel UIWindowLevelStatusBar;

//通知对象窗口为可见
UIKIT_EXTERN NSString *const UIWindowDidBecomeVisibleNotification; // nil
//通知对象窗口为隐藏
UIKIT_EXTERN NSString *const UIWindowDidBecomeHiddenNotification;  // nil
//通知对象窗口为重要,关键
UIKIT_EXTERN NSString *const UIWindowDidBecomeKeyNotification;     // nil
//通知对象窗口取消主窗口状态
UIKIT_EXTERN NSString *const UIWindowDidResignKeyNotification;     // nil

// Each notification includes a nil object and a userInfo dictionary containing the
// begining and ending keyboard frame in screen coordinates. Use the various UIView and
// UIWindow convertRect facilities to get the frame in the desired coordinate system.
// Animation key/value pairs are only available for the "will" family of notification.
//通知键盘对象视图即将加载
UIKIT_EXTERN NSString *const UIKeyboardWillShowNotification;
//通知键盘对象视图完全加载
UIKIT_EXTERN NSString *const UIKeyboardDidShowNotification;
//通知键盘对象视图即将隐藏
UIKIT_EXTERN NSString *const UIKeyboardWillHideNotification;
//通知键盘对象视图完全隐藏
UIKIT_EXTERN NSString *const UIKeyboardDidHideNotification;
/*
    指明键盘动画之前的框架，键盘将要显示时，显示之前把框架传递给这个动画;
    键盘已经显示即将隐藏时，键盘消失之前将这个框架传递给一个隐藏动画。包含一个CGRct类型值。
 */
UIKIT_EXTERN NSString *const UIKeyboardFrameBeginUserInfoKey        NS_AVAILABLE_IOS(3_2); // NSValue of CGRect
/*
    指明动画完成后的键盘框架，键盘将要显示时，键盘完全显示后把框架传递给键盘;
    键盘已经显示即将隐藏时，键盘隐藏后将这个框架传递给一个键盘。包含一个CGRct类型值。
 */
UIKIT_EXTERN NSString *const UIKeyboardFrameEndUserInfoKey          NS_AVAILABLE_IOS(3_2); // NSValue of CGRect
/*
    指明键盘显示和隐藏动画所用时间，包好一个NSNumber类型值（double）
 */
UIKIT_EXTERN NSString *const UIKeyboardAnimationDurationUserInfoKey NS_AVAILABLE_IOS(3_0); // NSNumber of double
/*
 指明动画类型，用来显示和隐藏键盘，包含了一个NSnumber类型值（NSUInteger）
 */
UIKIT_EXTERN NSString *const UIKeyboardAnimationCurveUserInfoKey    NS_AVAILABLE_IOS(3_0); // NSNumber of NSUInteger (UIViewAnimationCurve)

// Like the standard keyboard notifications above, these additional notifications include
// a nil object and begin/end frames of the keyboard in screen coordinates in the userInfo dictionary.
//键盘即将改变布局发出通知
UIKIT_EXTERN NSString *const UIKeyboardWillChangeFrameNotification  NS_AVAILABLE_IOS(5_0);
//键盘已经改变布局后发出通知
UIKIT_EXTERN NSString *const UIKeyboardDidChangeFrameNotification   NS_AVAILABLE_IOS(5_0);

// These keys are superseded by UIKeyboardFrameBeginUserInfoKey and UIKeyboardFrameEndUserInfoKey.
//键盘开始动画之前的起始坐标
UIKIT_EXTERN NSString *const UIKeyboardCenterBeginUserInfoKey   NS_DEPRECATED_IOS(2_0, 3_2);
//键盘动画后的坐标
UIKIT_EXTERN NSString *const UIKeyboardCenterEndUserInfoKey     NS_DEPRECATED_IOS(2_0, 3_2);
//包含的矩形只能用于取得尺寸信息
UIKIT_EXTERN NSString *const UIKeyboardBoundsUserInfoKey        NS_DEPRECATED_IOS(2_0, 3_2);
