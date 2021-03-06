//
//  UIApplication.h
//  UIKit
//
//  Copyright (c) 2005-2013, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIAlert.h>

typedef NS_ENUM(NSInteger, UIStatusBarStyle) {
    UIStatusBarStyleDefault                                     = 0, // Dark content, for use on light backgrounds
    UIStatusBarStyleLightContent     NS_ENUM_AVAILABLE_IOS(7_0) = 1, // Light content, for use on dark backgrounds
    
    UIStatusBarStyleBlackTranslucent NS_ENUM_DEPRECATED_IOS(2_0, 7_0, "Use UIStatusBarStyleLightContent") = 1,
    UIStatusBarStyleBlackOpaque      NS_ENUM_DEPRECATED_IOS(2_0, 7_0, "Use UIStatusBarStyleLightContent") = 2,
};

typedef NS_ENUM(NSInteger, UIStatusBarAnimation) {
    UIStatusBarAnimationNone,
#if __IPHONE_3_2 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    UIStatusBarAnimationFade,
    UIStatusBarAnimationSlide,
#endif
};

// Note that UIInterfaceOrientationLandscapeLeft is equal to UIDeviceOrientationLandscapeRight (and vice versa).
// This is because rotating the device to the left requires rotating the content to the right.
typedef NS_ENUM(NSInteger, UIInterfaceOrientation) {
    UIInterfaceOrientationPortrait           = UIDeviceOrientationPortrait,
    UIInterfaceOrientationPortraitUpsideDown = UIDeviceOrientationPortraitUpsideDown,
    UIInterfaceOrientationLandscapeLeft      = UIDeviceOrientationLandscapeRight,
    UIInterfaceOrientationLandscapeRight     = UIDeviceOrientationLandscapeLeft
};

/* This exception is raised if supportedInterfaceOrientations returns 0, or if preferredInterfaceOrientationForPresentation
   returns an orientation that is not supported.
*/
UIKIT_EXTERN NSString *const UIApplicationInvalidInterfaceOrientationException NS_AVAILABLE_IOS(6_0);

typedef NS_OPTIONS(NSUInteger, UIInterfaceOrientationMask) {
    UIInterfaceOrientationMaskPortrait = (1 << UIInterfaceOrientationPortrait),
    UIInterfaceOrientationMaskLandscapeLeft = (1 << UIInterfaceOrientationLandscapeLeft),
    UIInterfaceOrientationMaskLandscapeRight = (1 << UIInterfaceOrientationLandscapeRight),
    UIInterfaceOrientationMaskPortraitUpsideDown = (1 << UIInterfaceOrientationPortraitUpsideDown),
    UIInterfaceOrientationMaskLandscape = (UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight),
    UIInterfaceOrientationMaskAll = (UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight | UIInterfaceOrientationMaskPortraitUpsideDown),
    UIInterfaceOrientationMaskAllButUpsideDown = (UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight),
};

#define UIDeviceOrientationIsValidInterfaceOrientation(orientation) ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown || (orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight)
#define UIInterfaceOrientationIsPortrait(orientation)  ((orientation) == UIInterfaceOrientationPortrait || (orientation) == UIInterfaceOrientationPortraitUpsideDown)
#define UIInterfaceOrientationIsLandscape(orientation) ((orientation) == UIInterfaceOrientationLandscapeLeft || (orientation) == UIInterfaceOrientationLandscapeRight)

typedef NS_OPTIONS(NSUInteger, UIRemoteNotificationType) {
    UIRemoteNotificationTypeNone    = 0,
    UIRemoteNotificationTypeBadge   = 1 << 0,
    UIRemoteNotificationTypeSound   = 1 << 1,
    UIRemoteNotificationTypeAlert   = 1 << 2,
    UIRemoteNotificationTypeNewsstandContentAvailability = 1 << 3,
} NS_ENUM_AVAILABLE_IOS(3_0);

typedef NS_ENUM(NSUInteger, UIBackgroundFetchResult) {
    UIBackgroundFetchResultNewData,
    UIBackgroundFetchResultNoData,
    UIBackgroundFetchResultFailed
} NS_ENUM_AVAILABLE_IOS(7_0);

typedef NS_ENUM(NSInteger, UIBackgroundRefreshStatus) {
    UIBackgroundRefreshStatusRestricted, //< unavailable on this system due to device configuration; the user cannot enable the feature
    UIBackgroundRefreshStatusDenied,     //< explicitly disabled by the user for this application
    UIBackgroundRefreshStatusAvailable   //< enabled for this application
} NS_ENUM_AVAILABLE_IOS(7_0);
    
typedef NS_ENUM(NSInteger, UIApplicationState) {
    UIApplicationStateActive,
    UIApplicationStateInactive,
    UIApplicationStateBackground
} NS_ENUM_AVAILABLE_IOS(4_0);

typedef NSUInteger UIBackgroundTaskIdentifier;
UIKIT_EXTERN const UIBackgroundTaskIdentifier UIBackgroundTaskInvalid  NS_AVAILABLE_IOS(4_0);
UIKIT_EXTERN const NSTimeInterval UIMinimumKeepAliveTimeout  NS_AVAILABLE_IOS(4_0);
UIKIT_EXTERN const NSTimeInterval UIApplicationBackgroundFetchIntervalMinimum NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN const NSTimeInterval UIApplicationBackgroundFetchIntervalNever NS_AVAILABLE_IOS(7_0);

typedef NS_ENUM(NSInteger, UIUserInterfaceLayoutDirection) {
    UIUserInterfaceLayoutDirectionLeftToRight,
    UIUserInterfaceLayoutDirectionRightToLeft,
} NS_ENUM_AVAILABLE_IOS(5_0);
    
@class UIView, UIWindow, UIStatusBar, UIStatusBarWindow, UILocalNotification;
@protocol UIApplicationDelegate;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIApplication : UIResponder <UIActionSheetDelegate>
{
  @package
    id <UIApplicationDelegate>  _delegate;
    NSMutableSet               *_exclusiveTouchWindows;
    UIEvent                    *_event;
    UIEvent                    *_touchesEvent;
    UIEvent                    *_motionEvent;
    UIEvent                    *_remoteControlEvent;
    NSInteger                   _remoteControlEventObservers;
    NSArray                    *_topLevelNibObjects;
    NSInteger                   _networkResourcesCurrentlyLoadingCount;
    NSTimer                    *_hideNetworkActivityIndicatorTimer;
    UIAlertView                *_editAlertView;
    UIStatusBar                *_statusBar;
    UIStatusBarStyle            _statusBarRequestedStyle;
    UIStatusBarWindow          *_statusBarWindow;
    NSMutableArray             *_observerBlocks;
    NSMutableArray             *_postCommitActions;    
    NSString                   *_mainStoryboardName;
    NSMutableArray             *_tintViewDurationStack;
    NSMutableArray             *_statusBarTintColorLockingControllers;
    NSInteger                   _statusBarTintColorLockingCount;
    NSString                   *_preferredContentSizeCategory;
    struct {
        unsigned int deactivatingReasonFlags:8;
        unsigned int isSuspended:1;
        unsigned int isSuspendedEventsOnly:1;
        unsigned int isLaunchedSuspended:1;
        unsigned int calledNonSuspendedLaunchDelegate:1;
        unsigned int isHandlingURL:1;
        unsigned int isHandlingRemoteNotification:1;
        unsigned int isHandlingLocalNotification:1;
        unsigned int isHandlingBackgroundContentFetch:1;
        unsigned int statusBarShowsProgress:1;
        unsigned int statusBarHidden:1;
        unsigned int blockInteractionEvents:4;
        unsigned int receivesMemoryWarnings:1;
        unsigned int showingProgress:1;
        unsigned int receivesPowerMessages:1;
        unsigned int launchEventReceived:1;
        unsigned int systemIsAnimatingApplicationLifecycleEvent:1; // suspension, resumption, or system gesture
        unsigned int isResuming:1;
        unsigned int isSuspendedUnderLock:1;
        unsigned int shouldExitAfterSendSuspend:1;
        unsigned int terminating:1;
        unsigned int isHandlingShortCutURL:1;
        unsigned int idleTimerDisabled:1;
        unsigned int deviceOrientation:3;
        unsigned int delegateShouldBeReleasedUponSet:1;
        unsigned int delegateHandleOpenURL:1;
        unsigned int delegateOpenURL:1;
        unsigned int delegateDidReceiveMemoryWarning:1;
        unsigned int delegateWillTerminate:1;
        unsigned int delegateSignificantTimeChange:1;
        unsigned int delegateWillChangeInterfaceOrientation:1;
        unsigned int delegateDidChangeInterfaceOrientation:1;
        unsigned int delegateWillChangeStatusBarFrame:1;
        unsigned int delegateDidChangeStatusBarFrame:1;
        unsigned int delegateDeviceAccelerated:1;
        unsigned int delegateDeviceChangedOrientation:1;
        unsigned int delegateDidBecomeActive:1;
        unsigned int delegateWillResignActive:1;
        unsigned int delegateDidEnterBackground:1;
        unsigned int delegateDidEnterBackgroundWasSent:1;
        unsigned int delegateWillEnterForeground:1;
        unsigned int delegateWillSuspend:1;
        unsigned int delegateDidResume:1;
        unsigned int delegateSupportsStateRestoration:1;
        unsigned int delegateSupportedInterfaceOrientations:1;        
        unsigned int userDefaultsSyncDisabled:1;
        unsigned int headsetButtonClickCount:4;
        unsigned int isHeadsetButtonDown:1;
        unsigned int isFastForwardActive:1;
        unsigned int isRewindActive:1;
        unsigned int shakeToEdit:1;
        unsigned int isClassic:1;
        unsigned int zoomInClassicMode:1;
        unsigned int ignoreHeadsetClicks:1;
        unsigned int touchRotationDisabled:1;
        unsigned int taskSuspendingUnsupported:1;
        unsigned int taskSuspendingOnLockUnsupported:1;
        unsigned int isUnitTests:1;
        unsigned int requiresHighResolution:1;
        unsigned int disableViewContentScaling:1;
        unsigned int singleUseLaunchOrientation:3;
        unsigned int defaultInterfaceOrientation:3;
        unsigned int supportedInterfaceOrientationsMask:5;
        unsigned int delegateWantsNextResponder:1;
        unsigned int isRunningInApplicationSwitcher:1;
        unsigned int isSendingEventForProgrammaticTouchCancellation:1;
        unsigned int delegateWantsStatusBarTouchesEnded:1;
        unsigned int interfaceLayoutDirectionIsValid:1;
        unsigned int interfaceLayoutDirection:3;
        unsigned int restorationExtended:1;
        unsigned int normalRestorationInProgress:1;
        unsigned int normalRestorationCompleted:1;                        
        unsigned int isDelayingTintViewChange:1;
        unsigned int isUpdatingTintViewColor:1;
        unsigned int isHandlingMemoryWarning:1;
        unsigned int forceStatusBarTintColorChanges:1;
        unsigned int disableLegacyAutorotation:1;
        unsigned int isFakingForegroundTransitionForBackgroundFetch:1;
        unsigned int couldNotRestoreStateWhenLocked:1;
        unsigned int disableStyleOverrides:1;
        unsigned int legibilityAccessibilitySettingEnabled:1;
        unsigned int viewControllerBasedStatusBarAppearance:1;
        unsigned int fakingRequiresHighResolution:1;
        unsigned int isStatusBarFading:1;
    } _applicationFlags;
}
//获取当前程序的UIApplication实例
+ (UIApplication *)sharedApplication;
//获取UIApplicationDelegate实现类的实例
@property(nonatomic,assign) id<UIApplicationDelegate> delegate;
//开始忽略接受交换消息
- (void)beginIgnoringInteractionEvents;               // nested. set should be set during animations & transitions to ignore touch and other events
//结束忽略接受交换信息
- (void)endIgnoringInteractionEvents;
//是否忽略接受交换信息
- (BOOL)isIgnoringInteractionEvents;                  // returns YES if we are at least one deep in ignoring events
//阻止屏幕变暗进入休眠状态,慎重使用本功能，因为非常耗电。
@property(nonatomic,getter=isIdleTimerDisabled)       BOOL idleTimerDisabled;	  // default is NO
//打开URL，成功返回YES，失败返回NO
- (BOOL)openURL:(NSURL*)url;
// 判断能打开URL 
- (BOOL)canOpenURL:(NSURL *)url NS_AVAILABLE_IOS(3_0);

/*
    调度程序的适当的响应对象的事件。
    子类可以重写此方法以拦截来袭事件。
    任何截获事件应该派出通过调用 [super sendEvent:event] 检查后，
    截获事件。
*/
- (void)sendEvent:(UIEvent *)event;
//获取当前程序关键窗口
@property(nonatomic,readonly) UIWindow *keyWindow;
////获取当前程序涉及到窗口类数组
@property(nonatomic,readonly) NSArray  *windows;
//把消息发送到指定的目标。
/*
    通常情况下，这种方法是通过一个参考UIControl对象获取用户点击事件
    默认实现调度行动方法，给定的目标对象或，如果未指定目标，默认给第一响应者
    子类可以重写此方法以执行特定的操作的消息调度
    默认情况下，该方法调用的目标的时候需要两个参数
    最后这两个参数是可选的接收器，因为它是由调用者控制添加删除的
    这种设计使得动作选择器是下列之一：
    - (void)action
    - (void)action:(id)sender
    - (void)action:(id)sender forEvent:(UIEvent *)event
*/
- (BOOL)sendAction:(SEL)action to:(id)target from:(id)sender forEvent:(UIEvent *)event;
// 显示联网状态
@property(nonatomic,getter=isNetworkActivityIndicatorVisible) BOOL networkActivityIndicatorVisible; // showing network spinning gear in status bar. default is NO

// Setting the statusBarStyle does nothing if your application is using the default UIViewController-based status bar system.
//状态栏风格
@property(nonatomic) UIStatusBarStyle statusBarStyle; // default is UIStatusBarStyleDefault
//设置状态栏风格，是否支持动画
- (void)setStatusBarStyle:(UIStatusBarStyle)statusBarStyle animated:(BOOL)animated;

// Setting statusBarHidden does nothing if your application is using the default UIViewController-based status bar system.
//状态栏是否隐藏
@property(nonatomic,getter=isStatusBarHidden) BOOL statusBarHidden;
//设置状态栏隐藏，是否支持动画
- (void)setStatusBarHidden:(BOOL)hidden withAnimation:(UIStatusBarAnimation)animation NS_AVAILABLE_IOS(3_2);

// Rotate to a specific orientation.  This only rotates the status bar and updates the statusBarOrientation property.
// This does not change automatically if the device changes orientation.
// Explicit setting of the status bar orientation is more limited in iOS 6.0 and later.
//状态栏方向
@property(nonatomic) UIInterfaceOrientation statusBarOrientation;
//设置状态栏方向，是否支持动画
- (void)setStatusBarOrientation:(UIInterfaceOrientation)interfaceOrientation animated:(BOOL)animated;

// The system only calls this method if the application delegate has not
// implemented the delegate equivalent. It returns the orientations specified by
// the application's info.plist. If no supported interface orientations were
// specified it will return UIInterfaceOrientationMaskAll on an iPad and
// UIInterfaceOrientationMaskAllButUpsideDown on a phone.  The return value
// should be one of the UIInterfaceOrientationMask values which indicates the
// orientations supported by this application.
//返回window支持的方向
- (NSUInteger)supportedInterfaceOrientationsForWindow:(UIWindow *)window NS_AVAILABLE_IOS(6_0);
//状态栏动画时间
@property(nonatomic,readonly) NSTimeInterval statusBarOrientationAnimationDuration; // Returns the animation duration for the status bar during a 90 degree orientation change.  It should be doubled for a 180 degree orientation change.
//状态栏Frame
@property(nonatomic,readonly) CGRect statusBarFrame; // returns CGRectZero if the status bar is hidden
//设置icon上的数字图标
@property(nonatomic) NSInteger applicationIconBadgeNumber;  // set to 0 to hide. default is 0
//设置摇动手势的时候，是否支持redo,undo操作
@property(nonatomic) BOOL applicationSupportsShakeToEdit NS_AVAILABLE_IOS(3_0);
//程序运行状态
@property(nonatomic,readonly) UIApplicationState applicationState NS_AVAILABLE_IOS(4_0);
// 应用程序进行后台运行的大概时间
@property(nonatomic,readonly) NSTimeInterval backgroundTimeRemaining NS_AVAILABLE_IOS(4_0);

//申请一个新的长期运行的后台任务开始。延长程序在后台运行的时间
- (UIBackgroundTaskIdentifier)beginBackgroundTaskWithExpirationHandler:(void(^)(void))handler  NS_AVAILABLE_IOS(4_0);
//申请着一个新的长期运行的后台任务开始时使用指定的名称标识。
- (UIBackgroundTaskIdentifier)beginBackgroundTaskWithName:(NSString *)taskName expirationHandler:(void(^)(void))handler NS_AVAILABLE_IOS(7_0);
// 标志着一个特定的长期运行的后台任务结束。
- (void)endBackgroundTask:(UIBackgroundTaskIdentifier)identifier NS_AVAILABLE_IOS(4_0);

/*! The system guarantees that it will not wake up your application for a background fetch more
    frequently than the interval provided. Set to UIApplicationBackgroundFetchIntervalMinimum to be
    woken as frequently as the system desires, or to UIApplicationBackgroundFetchIntervalNever (the
    default) to never be woken for a background fetch.
 
    This setter will have no effect unless your application has the "fetch" 
    UIBackgroundMode. See the UIApplicationDelegate method
    `application:performFetchWithCompletionHandler:` for more. */
    //设置程序在后台读取操作的时间量最小
- (void)setMinimumBackgroundFetchInterval:(NSTimeInterval)minimumBackgroundFetchInterval NS_AVAILABLE_IOS(7_0);

/*! When background refresh is available for an application, it may launched or resumed in the background to handle significant
    location changes, remote notifications, background fetches, etc. Observe UIApplicationBackgroundRefreshStatusDidChangeNotification to
    be notified of changes. */
/*
    当程序的后台更新有用时
    它可以启动或恢复在后台处理重大事件，比如
    位置的变化，远程通知，后台提取等
    观察uiapplicationbackgroundrefreshstatusdidchangenotification 会收到backgroundRefreshStatus变化的通知
*/
@property (nonatomic, readonly) UIBackgroundRefreshStatus backgroundRefreshStatus NS_AVAILABLE_IOS(7_0);
//为VoIP应用 配置周期性处理程序 Voip：将模拟信号（Voice）数字化
- (BOOL)setKeepAliveTimeout:(NSTimeInterval)timeout handler:(void(^)(void))keepAliveHandler NS_AVAILABLE_IOS(4_0);
//移除以前安装的周期性处理程序块。
- (void)clearKeepAliveTimeout NS_AVAILABLE_IOS(4_0);
//内容保护是否有效,是否加密有效
@property(nonatomic,readonly,getter=isProtectedDataAvailable) BOOL protectedDataAvailable NS_AVAILABLE_IOS(4_0);
//返回用户界面的布局方向
@property(nonatomic,readonly) UIUserInterfaceLayoutDirection userInterfaceLayoutDirection NS_AVAILABLE_IOS(5_0);

// Return the size category
//用户首选字体大小的选项,取到用户设置的字体大小
@property(nonatomic,readonly) NSString *preferredContentSizeCategory NS_AVAILABLE_IOS(7_0);

@end

@interface UIApplication (UIRemoteNotifications)
//注册一个接收指定类型的通知，从一个供应商通过苹果推送服务。
- (void)registerForRemoteNotificationTypes:(UIRemoteNotificationType)types NS_AVAILABLE_IOS(3_0);
//取消注册通知，接受供应商通过苹果的推送服务
- (void)unregisterForRemoteNotifications NS_AVAILABLE_IOS(3_0);       // calls -registerForRemoteNotificationTypes with UIRemoteNotificationTypeNone

// returns the enabled types, also taking into account any systemwide settings; doesn't relate to connectivity
//返回应用程序支持接受推送服务 通知类型。
- (UIRemoteNotificationType)enabledRemoteNotificationTypes NS_AVAILABLE_IOS(3_0);

@end

@interface UIApplication (UILocalNotifications)

- (void)presentLocalNotificationNow:(UILocalNotification *)notification NS_AVAILABLE_IOS(4_0);

- (void)scheduleLocalNotification:(UILocalNotification *)notification NS_AVAILABLE_IOS(4_0);  // copies notification
- (void)cancelLocalNotification:(UILocalNotification *)notification NS_AVAILABLE_IOS(4_0);
- (void)cancelAllLocalNotifications NS_AVAILABLE_IOS(4_0);
@property(nonatomic,copy) NSArray *scheduledLocalNotifications NS_AVAILABLE_IOS(4_0);         // setter added in iOS 4.2

@end

@interface UIApplication (UIRemoteControlEvents)

- (void)beginReceivingRemoteControlEvents NS_AVAILABLE_IOS(4_0);
- (void)endReceivingRemoteControlEvents NS_AVAILABLE_IOS(4_0);

@end

@interface UIApplication (UINewsstand)
- (void)setNewsstandIconImage:(UIImage *)image;
@end

@protocol UIStateRestoring;
@interface UIApplication (UIStateRestoration)
// These methods are used to inform the system that state restoration is occuring asynchronously after the application
// has processed its restoration archive on launch. In the even of a crash, the system will be able to detect that it may
// have been caused by a bad restoration archive and arrange to ignore it on a subsequent application launch.
- (void)extendStateRestoration  NS_AVAILABLE_IOS(6_0);
- (void)completeStateRestoration  NS_AVAILABLE_IOS(6_0);

// Indicate the application should not use the snapshot on next launch, even if there is a valid state restoration archive.
// This should only be called from methods invoked from State Preservation, else it is ignored.
- (void)ignoreSnapshotOnNextApplicationLaunch NS_AVAILABLE_IOS(7_0);

// Register non-View/ViewController objects for state restoration so other objects can reference them within state restoration archives.
// If the object implements encode/decode, those methods will be called during save/restore.
// Obj and identifier must not be nil, or will raise UIRestorationObjectRegistrationException.
// Objects do not need to be unregistered when they are deleted, the State Restoration system will notice and stop tracking the object.
+ (void) registerObjectForStateRestoration:(id<UIStateRestoring>)object restorationIdentifier:(NSString *)restorationIdentifier NS_AVAILABLE_IOS(7_0);
@end


@protocol UIApplicationDelegate<NSObject>

@optional
//应用程序启动完毕。
- (void)applicationDidFinishLaunching:(UIApplication *)application;
//
- (BOOL)application:(UIApplication *)application willFinishLaunchingWithOptions:(NSDictionary *)launchOptions NS_AVAILABLE_IOS(6_0);
// 当由于其它方法打开应用程序（如URL指定或者连接），通知委托启动完毕
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions NS_AVAILABLE_IOS(3_0);

//通知委托应用程序进入活动状态，请恢复数据 
- (void)applicationDidBecomeActive:(UIApplication *)application;
// 通知委托应用程序将进入非活动状态，在此期间，应用程序不接收消息或事件。
- (void)applicationWillResignActive:(UIApplication *)application;

// 打开指定的URL 
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url;  // Will be deprecated at some point, please replace with application:openURL:sourceApplication:annotation:
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation NS_AVAILABLE_IOS(4_2); // no equiv. notification. return NO if the application can't open for some reason
 // 通知委托，应用程序收到了为来自系统的内存不足警告。
- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application;      // try to clean up as much memory as possible. next step is to terminate app
//  通知委托，应用程序将在关闭 退出，请做一些清理工作。
- (void)applicationWillTerminate:(UIApplication *)application;
// 通知委托系统时间发生改变（主要是指时间属性，而不是具体的时间值）
- (void)applicationSignificantTimeChange:(UIApplication *)application;        // midnight, carrier time update, daylight savings time change
//控制状态栏方位变化 
- (void)application:(UIApplication *)application willChangeStatusBarOrientation:(UIInterfaceOrientation)newStatusBarOrientation duration:(NSTimeInterval)duration;
// 设备方向将要发生改变 
- (void)application:(UIApplication *)application didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation;

- (void)application:(UIApplication *)application willChangeStatusBarFrame:(CGRect)newStatusBarFrame;   // in screen coordinates
- (void)application:(UIApplication *)application didChangeStatusBarFrame:(CGRect)oldStatusBarFrame;

// one of these will be called after calling -registerForRemoteNotifications
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken NS_AVAILABLE_IOS(3_0);
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error NS_AVAILABLE_IOS(3_0);

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo NS_AVAILABLE_IOS(3_0);
- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification NS_AVAILABLE_IOS(4_0);

/*! This delegate method offers an opportunity for applications with the "remote-notification" background mode to fetch appropriate new data in response to an incoming remote notification. You should call the fetchCompletionHandler as soon as you're finished performing that operation, so the system can accurately estimate its power and data cost.
 
 This method will be invoked even if the application was launched or resumed because of the remote notification. The respective delegate methods will be invoked first. Note that this behavior is in contrast to application:didReceiveRemoteNotification:, which is not called in those cases, and which will not be invoked if this method is implemented. !*/
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler NS_AVAILABLE_IOS(7_0);

/// Applications with the "fetch" background mode may be given opportunities to fetch updated content in the background or when it is convenient for the system. This method will be called in these situations. You should call the fetchCompletionHandler as soon as you're finished performing that operation, so the system can accurately estimate its power and data cost.
- (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler NS_AVAILABLE_IOS(7_0);

// Applications using an NSURLSession with a background configuration may be launched or resumed in the background in order to handle the
// completion of tasks in that session, or to handle authentication. This method will be called with the identifier of the session needing
// attention. Once a session has been created from a configuration object with that identifier, the session's delegate will begin receiving
// callbacks. If such a session has already been created (if the app is being resumed, for instance), then the delegate will start receiving
// callbacks without any action by the application. You should call the completionHandler as soon as you're finished handling the callbacks.
- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler NS_AVAILABLE_IOS(7_0);

- (void)applicationDidEnterBackground:(UIApplication *)application NS_AVAILABLE_IOS(4_0);
- (void)applicationWillEnterForeground:(UIApplication *)application NS_AVAILABLE_IOS(4_0);

- (void)applicationProtectedDataWillBecomeUnavailable:(UIApplication *)application NS_AVAILABLE_IOS(4_0);
- (void)applicationProtectedDataDidBecomeAvailable:(UIApplication *)application    NS_AVAILABLE_IOS(4_0);

@property (nonatomic, retain) UIWindow *window NS_AVAILABLE_IOS(5_0);

- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window  NS_AVAILABLE_IOS(6_0);

#pragma mark -- State Restoration protocol adopted by UIApplication delegate --

- (UIViewController *) application:(UIApplication *)application viewControllerWithRestorationIdentifierPath:(NSArray *)identifierComponents coder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
- (BOOL) application:(UIApplication *)application shouldSaveApplicationState:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
- (BOOL) application:(UIApplication *)application shouldRestoreApplicationState:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
- (void) application:(UIApplication *)application willEncodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
- (void) application:(UIApplication *)application didDecodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
@end

@interface UIApplication(UIApplicationDeprecated)

@property(nonatomic,getter=isProximitySensingEnabled) BOOL proximitySensingEnabled NS_DEPRECATED_IOS(2_0, 3_0); // default is NO. see UIDevice for replacement
- (void)setStatusBarHidden:(BOOL)hidden animated:(BOOL)animated NS_DEPRECATED_IOS(2_0, 3_2); // use -setStatusBarHidden:withAnimation:

@end

// If nil is specified for principalClassName, the value for NSPrincipalClass from the Info.plist is used. If there is no
// NSPrincipalClass key specified, the UIApplication class is used. The delegate class will be instantiated using init.
UIKIT_EXTERN int UIApplicationMain(int argc, char *argv[], NSString *principalClassName, NSString *delegateClassName);

UIKIT_EXTERN NSString *const UITrackingRunLoopMode;

// These notifications are sent out after the equivalent delegate message is called
UIKIT_EXTERN NSString *const UIApplicationDidEnterBackgroundNotification       NS_AVAILABLE_IOS(4_0);
UIKIT_EXTERN NSString *const UIApplicationWillEnterForegroundNotification      NS_AVAILABLE_IOS(4_0);
UIKIT_EXTERN NSString *const UIApplicationDidFinishLaunchingNotification;
UIKIT_EXTERN NSString *const UIApplicationDidBecomeActiveNotification;
UIKIT_EXTERN NSString *const UIApplicationWillResignActiveNotification;
UIKIT_EXTERN NSString *const UIApplicationDidReceiveMemoryWarningNotification;
UIKIT_EXTERN NSString *const UIApplicationWillTerminateNotification;
UIKIT_EXTERN NSString *const UIApplicationSignificantTimeChangeNotification;
UIKIT_EXTERN NSString *const UIApplicationWillChangeStatusBarOrientationNotification; // userInfo contains NSNumber with new orientation
UIKIT_EXTERN NSString *const UIApplicationDidChangeStatusBarOrientationNotification;  // userInfo contains NSNumber with old orientation
UIKIT_EXTERN NSString *const UIApplicationStatusBarOrientationUserInfoKey;            // userInfo dictionary key for status bar orientation
UIKIT_EXTERN NSString *const UIApplicationWillChangeStatusBarFrameNotification;       // userInfo contains NSValue with new frame
UIKIT_EXTERN NSString *const UIApplicationDidChangeStatusBarFrameNotification;        // userInfo contains NSValue with old frame
UIKIT_EXTERN NSString *const UIApplicationStatusBarFrameUserInfoKey;                  // userInfo dictionary key for status bar frame
UIKIT_EXTERN NSString *const UIApplicationBackgroundRefreshStatusDidChangeNotification NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsURLKey                   NS_AVAILABLE_IOS(3_0); // userInfo contains NSURL with launch URL
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsSourceApplicationKey     NS_AVAILABLE_IOS(3_0); // userInfo contains NSString with launch app bundle ID
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsRemoteNotificationKey    NS_AVAILABLE_IOS(3_0); // userInfo contains NSDictionary with payload
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsLocalNotificationKey     NS_AVAILABLE_IOS(4_0); // userInfo contains a UILocalNotification
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsAnnotationKey            NS_AVAILABLE_IOS(3_2); // userInfo contains object with annotation property list
UIKIT_EXTERN NSString *const UIApplicationProtectedDataWillBecomeUnavailable    NS_AVAILABLE_IOS(4_0);
UIKIT_EXTERN NSString *const UIApplicationProtectedDataDidBecomeAvailable       NS_AVAILABLE_IOS(4_0);
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsLocationKey              NS_AVAILABLE_IOS(4_0); // app was launched in response to a CoreLocation event.
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsNewsstandDownloadsKey    NS_AVAILABLE_IOS(5_0); // userInfo contains an NSArray of NKAssetDownload identifiers
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsBluetoothCentralsKey     NS_AVAILABLE_IOS(7_0); // userInfo contains an NSArray of CBCentralManager restore identifiers
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsBluetoothPeripheralsKey  NS_AVAILABLE_IOS(7_0); // userInfo contains an NSArray of CBPeripheralManager restore identifiers

// Content size category constants
UIKIT_EXTERN NSString *const UIContentSizeCategoryExtraSmall NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategorySmall NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryMedium NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryLarge NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryExtraLarge NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryExtraExtraLarge NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryExtraExtraExtraLarge NS_AVAILABLE_IOS(7_0);

// Accessibility sizes
UIKIT_EXTERN NSString *const UIContentSizeCategoryAccessibilityMedium NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryAccessibilityLarge NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryAccessibilityExtraLarge NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryAccessibilityExtraExtraLarge NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIContentSizeCategoryAccessibilityExtraExtraExtraLarge NS_AVAILABLE_IOS(7_0);

// Notification is emitted when the user has changed the preferredContentSizeCategory for the system
UIKIT_EXTERN NSString *const UIContentSizeCategoryDidChangeNotification NS_AVAILABLE_IOS(7_0); // userInfo dictionary will contain new value for UIContentSizeCategoryNewValueKey
UIKIT_EXTERN NSString *const UIContentSizeCategoryNewValueKey NS_AVAILABLE_IOS(7_0); // NSString instance with new content size category in userInfo

// This notification is posted after the user takes a screenshot (for example by pressing both the home and lock screen buttons)
UIKIT_EXTERN NSString *const UIApplicationUserDidTakeScreenshotNotification NS_AVAILABLE_IOS(7_0);
