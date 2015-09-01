//  UIResponder.h


#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIEvent.h>

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIResponder : NSObject {
  @private
}

//返回接收者的下一个相应，如果没有就返回nil
- (UIResponder*)nextResponder;

//判断一个对象是否可以成为第一响应者。默认返回NO。
- (BOOL)canBecomeFirstResponder;    // default is NO
//如果接收者接受了第一响应者的状态就返回YES，拒绝了这个状态就返回NO。默认返回YES。
- (BOOL)becomeFirstResponder;

//如果一个对象可以放弃对象响应者就返回YES。默认返回YES。
- (BOOL)canResignFirstResponder;    // default is YES
//默认实现返回YES，放弃第一响应状态。子类可以override这个方法来更新状态或者执行一些行为，比如取消高亮选中项。如果返回NO，拒绝放弃第一响应状态。如果你override这个方法，必须调用父类的实现[super resignFirstResponder].
- (BOOL)resignFirstResponder;

//判断一个对象是否是第一响应者。
- (BOOL)isFirstResponder;

/*
 通知接收者当一个或多个手指在UIView或UIWindow上点下了。
 将消息转发给下一个响应者，将消息发送给父类，不要将消息直接传递给下一个响应者。
 如果你override这个方法而没有调用super..，你必须同样override其它响应触摸事件的方法，你要是空实现就好。
 默认是不支持多点触摸的，如果想要响应多点触摸，你只要吧UIView的 multipleTouchEnabled  属性设置为YES即可。
 */
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
//手指移动
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
//手指抬起
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
/*
 当收到一个系统干扰需要取消触摸事件时才会调用该方法，这种系统干扰往往会引起应用程序长时间没有响应或者一个View从window上移除了。
 当收到touchesCancelled:withEvent:消息的时候需要清除所有通过touchesBegan:withEvent:创建的内容。
 */
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

/*
 通知接收者一个动作开始了。
 当一个动作开始了和结束了的时候iOS才会通知接收者。it doesn’t report individual shakes. 接收者必须是接收动作事件的第一响应者。
 */
- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event NS_AVAILABLE_IOS(3_0);

//通知接收者一个动作结束了
- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event NS_AVAILABLE_IOS(3_0);
//一个动作被取消了。雷同 - (void)touchesCancelled:( NSSet *) touches withEvent:( UIEvent *) event
- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event NS_AVAILABLE_IOS(3_0);

/*
 接收到一个远程控制事件。比如耳机控制。
 允许传递远程控制事件，必须调用UIApplication的beginReceivingRemoteControlEvents方法；关闭远程控制，调用endReceivingRemoteControlEvents。
 */
- (void)remoteControlReceivedWithEvent:(UIEvent *)event NS_AVAILABLE_IOS(4_0);

/*
    是否能响应一个操作事件，如果能返回YES，不能返回NO
 */
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender NS_AVAILABLE_IOS(3_0);

/*
    canPerformAction:(SEL)action withSender:(id)sender 返回YES，能响应事件，那用 action，sender从UIResponder可以响应事件的target
 */
- (id)targetForAction:(SEL)action withSender:(id)sender NS_AVAILABLE_IOS(7_0);

/*
 返回在响应链中最近的共享undo manager。
 默认的，每个应用程序的window都有一个undo manager：a shared object for managing undo and redo operations.
 然而，在响应链中任何对象的类都有它们自己的undo manager
 */
@property(nonatomic,readonly) NSUndoManager *undoManager NS_AVAILABLE_IOS(3_0);

@end

typedef NS_OPTIONS(NSInteger, UIKeyModifierFlags) {
    UIKeyModifierAlphaShift     = 1 << 16,  // 大写锁定键 == vspds lock 键
    UIKeyModifierShift          = 1 << 17,  //Shift键
    UIKeyModifierControl        = 1 << 18, //CTRL键
    UIKeyModifierAlternate      = 1 << 19, //Alt键 == option键
    UIKeyModifierCommand        = 1 << 20, //Command 键
    UIKeyModifierNumericPad     = 1 << 21, //位于数字键盘上
} NS_ENUM_AVAILABLE_IOS(7_0);

/*
    可用于捕获蓝牙键盘的按键事件
 */
NS_CLASS_AVAILABLE_IOS(7_0) @interface UIKeyCommand : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic,readonly) NSString *input;//输入文本
@property (nonatomic,readonly) UIKeyModifierFlags modifierFlags; //按键

// the action for UIKeyCommands should accept a single (id)sender, as do the UIResponderStandardEditActions below
//初始化  UIKeyCommands,按键的响应事件 ， 按键的Text，及响应事件
+ (UIKeyCommand *)keyCommandWithInput:(NSString *)input modifierFlags:(UIKeyModifierFlags)modifierFlags action:(SEL)action;

@end

@interface UIResponder (UIResponderKeyCommands)
@property (nonatomic,readonly) NSArray *keyCommands NS_AVAILABLE_IOS(7_0); // 响应的键盘按钮数组
@end

@interface NSObject(UIResponderStandardEditActions)   // these methods are not implemented in NSObject

- (void)cut:(id)sender NS_AVAILABLE_IOS(3_0);
- (void)copy:(id)sender NS_AVAILABLE_IOS(3_0);
- (void)paste:(id)sender NS_AVAILABLE_IOS(3_0);
- (void)select:(id)sender NS_AVAILABLE_IOS(3_0);
- (void)selectAll:(id)sender NS_AVAILABLE_IOS(3_0);
- (void)delete:(id)sender NS_AVAILABLE_IOS(3_2);
- (void)makeTextWritingDirectionLeftToRight:(id)sender NS_AVAILABLE_IOS(5_0);
- (void)makeTextWritingDirectionRightToLeft:(id)sender NS_AVAILABLE_IOS(5_0);
- (void)toggleBoldface:(id)sender NS_AVAILABLE_IOS(6_0);
- (void)toggleItalics:(id)sender NS_AVAILABLE_IOS(6_0);
- (void)toggleUnderline:(id)sender NS_AVAILABLE_IOS(6_0);

// cmd+ ,用来放大/缩小内容
- (void)increaseSize:(id)sender NS_AVAILABLE_IOS(7_0);
// cmd- ,用来放大/缩小内容
- (void)decreaseSize:(id)sender NS_AVAILABLE_IOS(7_0);

@end

@class UIInputViewController;
@class UITextInputMode;

@interface UIResponder (UIResponderInputViewAdditions)

//当一个对象变成第一响应者的时候显示的View
/*
    UITextField和UITextView如果设置了inputView那么在 becomeFirstResponder时不会显示键盘，而显示自定义的inputView；
    如果设置了inputAccessoryView那么在 becomeFirstResponder时会在键盘的顶端显示自定义的inputAccessoryView。
 */
@property (nonatomic, readonly, retain) UIView *inputView NS_AVAILABLE_IOS(3_2);
@property (nonatomic, readonly, retain) UIView *inputAccessoryView NS_AVAILABLE_IOS(3_2);

// For viewController equivalents of -inputView and -inputAccessoryView
// Called and presented when object becomes first responder.  Goes up the responder chain.
@property (nonatomic, readonly, retain) UIInputViewController *inputViewController NS_AVAILABLE_IOS(8_0);
@property (nonatomic, readonly, retain) UIInputViewController *inputAccessoryViewController NS_AVAILABLE_IOS(8_0);

/* When queried, returns the current UITextInputMode, from which the keyboard language can be determined.
 * When overridden it should return a previously-queried UITextInputMode object, which will attempt to be
 * set inside that app, but not persistently affect the user's system-wide keyboard settings. */
@property (nonatomic, readonly, retain) UITextInputMode *textInputMode NS_AVAILABLE_IOS(7_0);
/* When the first responder changes and an identifier is queried, the system will establish a context to
 * track the textInputMode automatically. The system will save and restore the state of that context to
 * the user defaults via the app identifier. Use of -textInputMode above will supercede use of -textInputContextIdentifier. */
@property (nonatomic, readonly, retain) NSString *textInputContextIdentifier NS_AVAILABLE_IOS(7_0);
// This call is to remove stored app identifier state that is no longer needed.
+ (void)clearTextInputContextIdentifier:(NSString *)identifier NS_AVAILABLE_IOS(7_0);

//当对象成为第一响应者的时候更新inputView和accessoryView。textInputMode
- (void)reloadInputViews NS_AVAILABLE_IOS(3_2);

@end

// These are pre-defined constants for use with the input property of UIKeyCommand objects.
UIKIT_EXTERN NSString *const UIKeyInputUpArrow         NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIKeyInputDownArrow       NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIKeyInputLeftArrow       NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIKeyInputRightArrow      NS_AVAILABLE_IOS(7_0);
UIKIT_EXTERN NSString *const UIKeyInputEscape          NS_AVAILABLE_IOS(7_0);

@interface UIResponder (ActivityContinuation)
@property (nonatomic, retain) NSUserActivity *userActivity NS_AVAILABLE_IOS(8_0);
- (void)updateUserActivityState:(NSUserActivity *)activity NS_AVAILABLE_IOS(8_0);
- (void)restoreUserActivityState:(NSUserActivity *)activity NS_AVAILABLE_IOS(8_0);
@end

