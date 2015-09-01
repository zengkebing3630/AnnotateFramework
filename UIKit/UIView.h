/*  UIView.h
Author  曾克兵（keven）
Date    2014/6/14
*/

/*
     UIView基本概念
UIView是组成画面的基本元素。拥有位置属性及一定尺寸的四方形，背景色。可以包含字符串或者图片等内容（信息）。例如UILabel就是包含字符串的UIView，而UIImageView是包含图片的UIView。最重要的一点是UIView可以拥有UIView类型的子元素。可以轻易地在UIView上追加UIView，创建各种各样的画面。在iPhone应用程序中，应用程序的UIWindow也是UIView的子类。也就是说，所有的画面都是在UIWindow中追加各种UIView而组成的。

二、坐标大小
1、bounds是指这个view在它自己坐标系的坐标和大小,绝对坐标，以屏幕为原点的坐标系，以用来帮助它的subview来定位的 ，layoutSubviews。
2、frame指的是这个view在它superview的坐标系的坐标和大小,相对坐标

三、功能介绍

1、创建一个视图对象
2、动画
3、管理视图层次结构
4、子视图的布局(layout)
5、绘制/重绘视图
6、以块展现动画的方式
7、视图和坐标系统之间转换
8、跟踪视图相关的变化
*/

#import <Foundation/Foundation.h> //基础框架入口
#import <UIKit/UIResponder.h>//触摸事件响应处理
#import <UIKit/UIInterface.h>//界面UIcolor, UIFont 定义
#import <UIKit/UIKitDefines.h>//一些宏定义
#import <UIKit/UIAppearance.h>//外观代理
#import <UIKit/UIDynamicBehavior.h>
#import <UIKit/NSLayoutConstraint.h>//布局对象约束

typedef NS_ENUM(NSInteger, UIViewAnimationCurve) {//动画速度变化设定
    UIViewAnimationCurveEaseInOut,         // slow at beginning and end  缓慢开始，中间加速，然后减速到结束
    UIViewAnimationCurveEaseIn,            // slow at beginning  缓慢开始，加速到结束
    UIViewAnimationCurveEaseOut,           // slow at end 加速开始，加速到结束
    UIViewAnimationCurveLinear //正常速度
};

typedef NS_ENUM(NSInteger, UIViewContentMode) {//UIView自身的设定
    UIViewContentModeScaleToFill,//缩放内容到合适比例大小
    //缩放内容到合适的大小，边界多余部分透明
    UIViewContentModeScaleAspectFit,      // contents scaled to fit with fixed aspect. remainder is transparent
    // 缩放内容填充到指定大小，边界多余的部分省略
    UIViewContentModeScaleAspectFill,     // contents scaled to fill with fixed aspect. some portion of content may be clipped.
    //重绘视图边界
    UIViewContentModeRedraw,              // redraw on bounds change (calls -setNeedsDisplay)
    //视图保持等比缩放
    UIViewContentModeCenter,              // contents remain same size. positioned adjusted.
    // 视图顶部对齐
    UIViewContentModeTop,
    // 视图底部对齐
    UIViewContentModeBottom,
    //视图左侧对齐
    UIViewContentModeLeft,
    // 视图右侧对齐
    UIViewContentModeRight,
    // 视图左上角对齐
    UIViewContentModeTopLeft,
    // 视图右上角对齐
    UIViewContentModeTopRight,
    // 视图左下角对齐
    UIViewContentModeBottomLeft,
    // 视图右下角对齐
    UIViewContentModeBottomRight,
};

typedef NS_ENUM(NSInteger, UIViewAnimationTransition) { //翻转
    UIViewAnimationTransitionNone,//没有过渡
    UIViewAnimationTransitionFlipFromLeft,//翻转视图从左到右
    UIViewAnimationTransitionFlipFromRight,//翻转视图从右到左
    UIViewAnimationTransitionCurlUp,//从上卷动
    UIViewAnimationTransitionCurlDown,//从下卷动
};

typedef NS_OPTIONS(NSUInteger, UIViewAutoresizing) {//自适应设定
    UIViewAutoresizingNone                 = 0,//父视图变化，自己不变化
    UIViewAutoresizingFlexibleLeftMargin   = 1 << 0,//视图的左边界和父视图的宽度等比例变化
    UIViewAutoresizingFlexibleWidth        = 1 << 1,//视图的宽度和父视图的宽度成比例变化
    UIViewAutoresizingFlexibleRightMargin  = 1 << 2,//视图的右边界和父视图的宽度等比例变化
    UIViewAutoresizingFlexibleTopMargin    = 1 << 3,//视图的上边界和父视图的高度成等比例变化
    UIViewAutoresizingFlexibleHeight       = 1 << 4,//视图的高度和父视图的高度成比例变化
    UIViewAutoresizingFlexibleBottomMargin = 1 << 5//视图的下边界和父视图的高度成等比例变化
};

typedef NS_OPTIONS(NSUInteger, UIViewAnimationOptions) { //动画效果显著
    UIViewAnimationOptionLayoutSubviews            = 1 <<  0,
    UIViewAnimationOptionAllowUserInteraction      = 1 <<  1, // turn on user interaction while animating
    UIViewAnimationOptionBeginFromCurrentState     = 1 <<  2, // start all views from current value, not initial value
    UIViewAnimationOptionRepeat                    = 1 <<  3, // repeat animation indefinitely
    UIViewAnimationOptionAutoreverse               = 1 <<  4, // if repeat, run animation back and forth
    UIViewAnimationOptionOverrideInheritedDuration = 1 <<  5, // ignore nested duration
    UIViewAnimationOptionOverrideInheritedCurve    = 1 <<  6, // ignore nested curve
    UIViewAnimationOptionAllowAnimatedContent      = 1 <<  7, // animate contents (applies to transitions only)
    UIViewAnimationOptionShowHideTransitionViews   = 1 <<  8, // flip to/from hidden state instead of adding/removing
    UIViewAnimationOptionOverrideInheritedOptions  = 1 <<  9, // do not inherit any options or animation type
    
    UIViewAnimationOptionCurveEaseInOut            = 0 << 16, // default
    UIViewAnimationOptionCurveEaseIn               = 1 << 16,
    UIViewAnimationOptionCurveEaseOut              = 2 << 16,
    UIViewAnimationOptionCurveLinear               = 3 << 16,
    
    UIViewAnimationOptionTransitionNone            = 0 << 20, // default
    UIViewAnimationOptionTransitionFlipFromLeft    = 1 << 20,
    UIViewAnimationOptionTransitionFlipFromRight   = 2 << 20,
    UIViewAnimationOptionTransitionCurlUp          = 3 << 20,
    UIViewAnimationOptionTransitionCurlDown        = 4 << 20,
    UIViewAnimationOptionTransitionCrossDissolve   = 5 << 20,
    UIViewAnimationOptionTransitionFlipFromTop     = 6 << 20,
    UIViewAnimationOptionTransitionFlipFromBottom  = 7 << 20,
} NS_ENUM_AVAILABLE_IOS(4_0);

typedef NS_OPTIONS(NSUInteger, UIViewKeyframeAnimationOptions) {
    UIViewKeyframeAnimationOptionLayoutSubviews            = UIViewAnimationOptionLayoutSubviews,
    UIViewKeyframeAnimationOptionAllowUserInteraction      = UIViewAnimationOptionAllowUserInteraction, // turn on user interaction while animating
    UIViewKeyframeAnimationOptionBeginFromCurrentState     = UIViewAnimationOptionBeginFromCurrentState, // start all views from current value, not initial value
    UIViewKeyframeAnimationOptionRepeat                    = UIViewAnimationOptionRepeat, // repeat animation indefinitely
    UIViewKeyframeAnimationOptionAutoreverse               = UIViewAnimationOptionAutoreverse, // if repeat, run animation back and forth
    UIViewKeyframeAnimationOptionOverrideInheritedDuration = UIViewAnimationOptionOverrideInheritedDuration, // ignore nested duration
    UIViewKeyframeAnimationOptionOverrideInheritedOptions  = UIViewAnimationOptionOverrideInheritedOptions, // do not inherit any options or animation type
    
    UIViewKeyframeAnimationOptionCalculationModeLinear     = 0 << 10, // default
    UIViewKeyframeAnimationOptionCalculationModeDiscrete   = 1 << 10,
    UIViewKeyframeAnimationOptionCalculationModePaced      = 2 << 10,
    UIViewKeyframeAnimationOptionCalculationModeCubic      = 3 << 10,
    UIViewKeyframeAnimationOptionCalculationModeCubicPaced = 4 << 10
} NS_ENUM_AVAILABLE_IOS(7_0);
    
typedef NS_ENUM(NSUInteger, UISystemAnimation) {
    UISystemAnimationDelete,    // removes the views from the hierarchy when complete
} NS_ENUM_AVAILABLE_IOS(7_0);

typedef NS_ENUM(NSInteger, UIViewTintAdjustmentMode) {
    UIViewTintAdjustmentModeAutomatic,
    
    UIViewTintAdjustmentModeNormal,
    UIViewTintAdjustmentModeDimmed,
} NS_ENUM_AVAILABLE_IOS(7_0);

@class UIBezierPath, UIEvent, UIWindow, UIViewController, UIColor, UIGestureRecognizer, UIMotionEffect, CALayer;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIView : UIResponder<NSCoding, UIAppearance, UIAppearanceContainer, UIDynamicItem> {
  @package
    CALayer        *_layer;
    id              _gestureInfo;
    NSMutableArray *_gestureRecognizers;
    NSArray        *_subviewCache;
    float           _charge;
    NSInteger       _tag;
    UIViewController *_viewDelegate;
    NSString         *_backgroundColorSystemColorName;
    NSUInteger      _countOfMotionEffectsInSubtree;
    struct {
        unsigned int userInteractionDisabled:1;
        unsigned int implementsDrawRect:1;
        unsigned int implementsDidScroll:1;
        unsigned int implementsMouseTracking:1;
        unsigned int hasBackgroundColor:1;
        unsigned int isOpaque:1;
        unsigned int becomeFirstResponderWhenCapable:1;
        unsigned int interceptMouseEvent:1;
        unsigned int deallocating:1;
        unsigned int debugFlash:1;
        unsigned int debugSkippedSetNeedsDisplay:1;
        unsigned int debugScheduledDisplayIsRequired:1;
        unsigned int isInAWindow:1;
        unsigned int isAncestorOfFirstResponder:1;
        unsigned int dontAutoresizeSubviews:1;
        unsigned int autoresizeMask:6;
        unsigned int patternBackground:1;
        unsigned int fixedBackgroundPattern:1;
        unsigned int dontAnimate:1;
        unsigned int superLayerIsView:1;
        unsigned int layerKitPatternDrawing:1;
        unsigned int multipleTouchEnabled:1;
        unsigned int exclusiveTouch:1;
        unsigned int hasViewController:1;
        unsigned int needsDidAppearOrDisappear:1;
        unsigned int gesturesEnabled:1;
        unsigned int deliversTouchesForGesturesToSuperview:1;
        unsigned int chargeEnabled:1;
        unsigned int skipsSubviewEnumeration:1;
        unsigned int needsDisplayOnBoundsChange:1;
        unsigned int hasTiledLayer:1;
        unsigned int hasLargeContent:1;
        unsigned int unused:1;
        unsigned int traversalMark:1;
        unsigned int appearanceIsInvalid:1;
        unsigned int monitorsSubtree:1;
        unsigned int hostsAutolayoutEngine:1;
        unsigned int constraintsAreClean:1;
        unsigned int subviewLayoutConstraintsAreClean:1;
        unsigned int intrinsicContentSizeConstraintsAreClean:1;
        unsigned int potentiallyHasDanglyConstraints:1;
        unsigned int doesNotTranslateAutoresizingMaskIntoConstraints:1;
        unsigned int autolayoutIsClean:1;
        unsigned int subviewsAutolayoutIsClean:1;
        unsigned int layoutFlushingDisabled:1;
        unsigned int layingOutFromConstraints:1;
        unsigned int wantsAutolayout:1;
        unsigned int subviewWantsAutolayout:1;
        unsigned int isApplyingValuesFromEngine:1;
        unsigned int isInAutolayout:1;
        unsigned int isUpdatingAutoresizingConstraints:1;
        unsigned int isUpdatingConstraints:1;
        unsigned int stayHiddenAwaitingReuse:1;
        unsigned int stayHiddenAfterReuse:1;
        unsigned int skippedLayoutWhileHiddenForReuse:1;
        unsigned int hasMaskView:1;
        unsigned int hasVisualAltitude:1;
        unsigned int hasBackdropMaskViews:1;
        unsigned int backdropMaskViewFlags:3;
        unsigned int delaysTouchesForSystemGestures:1;
        unsigned int subclassShouldDelayTouchForSystemGestures:1;
        unsigned int hasMotionEffects:1;
        unsigned int backdropOverlayMode:2;
        unsigned int tintAdjustmentMode:2;
        unsigned int isReferenceView:1;
        unsigned int focusState:2;
        unsigned int hasUserInterfaceIdiom:1;
        unsigned int userInterfaceIdiom:3;
        unsigned int ancestorDefinesTintColor:1;
        unsigned int ancestorDefinesTintAdjustmentMode:1;
    } _viewFlags;
}
//绘图布局
+ (Class)layerClass;                        // default is [CALayer class]. Used when creating the underlying layer for the view.
//初始化视图布局
- (id)initWithFrame:(CGRect)frame;          // default initializer
//确定是否接受用户事件
@property(nonatomic,getter=isUserInteractionEnabled) BOOL userInteractionEnabled;  // default is YES. if set to NO, user events (touch, keys) are ignored and removed from the event queue.
//标记视图对象
@property(nonatomic)                                 NSInteger tag;                // default is 0
// 返回一个只读的视图层
@property(nonatomic,readonly,retain)                 CALayer  *layer;              // returns view's layer. Will always return a non-nil value. view is layer's delegate

@end

@interface UIView(UIViewGeometry)

// animatable. do not use frame if view is transformed since it will not correctly reflect the actual location of the view. use bounds + center instead.
// 描述view在其父view坐标系中的定位和大小
@property(nonatomic) CGRect            frame;

// use bounds/center and not frame if non-identity transform. if bounds dimension is odd, center may be have fractional part
// 描述view自身的本地坐标系统的定位和大小
@property(nonatomic) CGRect            bounds;      // default bounds is zero origin, frame size. animatable
// 描述view的frame属性的中心点
@property(nonatomic) CGPoint           center;      // center is center of frame. animatable
// 描述view相对bounds的平移量
@property(nonatomic) CGAffineTransform transform;   // default is CGAffineTransformIdentity. animatable
 // 改变视图比例，主要用于修改分辨率，来支持高，低分辨率转化绘图
@property(nonatomic) CGFloat           contentScaleFactor NS_AVAILABLE_IOS(4_0);
//设置是否接受多点触摸。YES 是接受多点，NO 接受单点。
@property(nonatomic,getter=isMultipleTouchEnabled) BOOL multipleTouchEnabled;   // default is NO
// 当前视图独占触摸事件
@property(nonatomic,getter=isExclusiveTouch) BOOL       exclusiveTouch;         // default is NO
// 接收视图触摸事件，遍历视图，确定最终接受视图层
/*
 hitTest:withEvent:调用过程

iOS系统检测到手指触摸(Touch)操作时会将其放入当前活动Application的事件队列，
UIApplication会从事件队列中取出触摸事件并传递给key window(当前接收用户事件的窗口)处理,
window对象首先会使用hitTest:withEvent:方法寻找此次Touch操作初始点所在的视图(View),
即需要将触摸事件传递给其处理的视图,称之为hit-test view。
window对象会在首先在view hierarchy的顶级view上调用hitTest:withEvent:，
此方法会在视图层级结构中的每个视图上调用pointInside:withEvent:,如果pointInside:withEvent:返回YES,
则继续逐级调用，直到找到touch操作发生的位置，这个视图也就是hit-test view。
hitTest:withEvent:方法的处理流程如下:
1、首先调用当前视图的pointInside:withEvent:方法判断触摸点是否在当前视图内；
2、若返回NO,则hitTest:withEvent:返回nil;
3、若返回YES,则向当前视图的所有子视图(subviews)发送hitTest:withEvent:消息，
所有子视图的遍历顺序是从top到bottom，即从subviews数组的末尾向前遍历,
直到有子视图返回非空对象或者全部子视图遍历完毕；
4、若第一次有子视图返回非空对象,则hitTest:withEvent:方法返回此对象，处理结束；
5、如所有子视图都返回非，则hitTest:withEvent:方法返回自身(self)。
hitTest:withEvent:方法忽略隐藏(hidden=YES)的视图,禁止用户操作(userInteractionEnabled=YES)的视图，
以及alpha级别小于0.01(alpha<0.01)的视图。如果一个子视图的区域超过父视图的bound区域(父视图的clipsToBounds 属性为NO,
这样超过父视图bound区域的子视图内容也会显示)，那么正常情况下对子视图在父视图之外区域的触摸操作不会被识别,
因为父视图的pointInside:withEvent:方法会返回NO,这样就不会继续向下遍历子视图了。
当然，也可以重写pointInside:withEvent:方法来处理这种情况。
对于每个触摸操作都会有一个UITouch对象,UITouch对象用来表示一个触摸操作，
即一个手指在屏幕上按下、移动、离开的整个过程。UITouch对象在触摸操作的过程中在不断变化，
所以在使用UITouch对象时，不能直接retain,而需要使用其他手段存储UITouch的内部信息。
UITouch对象有一个view属性，表示此触摸操作初始发生所在的视图，
即上面检测到的hit-test view,此属性在UITouch的生命周期不再改变，即使触摸操作后续移动到其他视图之上。
*/
- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event;   // recursively calls -pointInside:withEvent:. point is in the receiver's coordinate system
// 判断触摸事件是否在当前视图
- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event;   // default returns YES if point is in bounds
// 转化当前视图的坐标相对于另外一个视图的坐标
- (CGPoint)convertPoint:(CGPoint)point toView:(UIView *)view;
// 转化另外视图坐标相对于当前视图的坐标
- (CGPoint)convertPoint:(CGPoint)point fromView:(UIView *)view;
// 转化当前视图的矩形坐标相对于另外一个视图的矩形
- (CGRect)convertRect:(CGRect)rect toView:(UIView *)view;
// 转化另外视图的矩形坐标相对于当前视图矩形
- (CGRect)convertRect:(CGRect)rect fromView:(UIView *)view;

// 判断是否接收边界的改变，YES：接收  NO：不接收
@property(nonatomic) BOOL               autoresizesSubviews; // default is YES. if set, subviews are adjusted according to their autoresizingMask if self.bounds changes
// 视图边界大小调整参数
@property(nonatomic) UIViewAutoresizing autoresizingMask;    // simple resize. default is UIViewAutoresizingNone
// 计算并返回一个最适应接收子视图的大小
- (CGSize)sizeThatFits:(CGSize)size;     // return 'best' size to fit given size. does not actually resize view. Default is return existing view size
// 移动并调整子视图的大小
- (void)sizeToFit;                       // calls sizeThatFits: with current view bounds and changes bounds size.

@end

@interface UIView(UIViewHierarchy)
// 父视图
@property(nonatomic,readonly) UIView       *superview;
// 子视图
@property(nonatomic,readonly,copy) NSArray *subviews;
// 窗口
@property(nonatomic,readonly) UIWindow     *window;

// 将当前视图从父视图和窗口移除，并且把它的响应事件的响应链移除。
/*
    在ios当中，视图的设计模式可以看做是组件模式，即以树作为存储的数据结构，这种数据结构具有明确的两个特点：
【1】.父子关系分明，从根节点出发，通过叶节点向下扩展，同一枝的上一个节点就是下一个节点的superview，
下一个节点就是上一个节点的subview；不同枝如果同层，则为兄弟节点。
【2】.layer关系分明，layer在ios中对事件响应具有举足轻重的作用，通常两个重叠的控件，处在上层的会优先响应；
view在操作时候的核心，即一个view的操作关系到两个方面，视图结构和响应者链。
removeFromSuperview，类似一个剪枝，执行此函数，就等于在树形结构中找到该节点，剪去该节点及其子节点，
而并非只是剪去该节点自己。同时，另一个操作就是把该对象从响应者链中移除。
【3】、如果当前view对象的父视图不为空，则父视图会release一次当前视图对象。如果你还想重用当前view，
你应该在调用removeFromSuperview之前，retain一次当前view对象，但不要忘记，在恰当的时候要release它，以确保没有内存泄露。
【4】、永远不要在view的drawRect方法中调用removeFromSuperview；
*/
- (void)removeFromSuperview;
// 指定索引插入视图
- (void)insertSubview:(UIView *)view atIndex:(NSInteger)index;
// 指定索引交换子视图
- (void)exchangeSubviewAtIndex:(NSInteger)index1 withSubviewAtIndex:(NSInteger)index2;
/*
视图的添加都是以栈的方式，即后进先出。
*/
// 添加视图到最后
- (void)addSubview:(UIView *)view;
// 添加视图到底层
- (void)insertSubview:(UIView *)view belowSubview:(UIView *)siblingSubview;
// 添加视图到顶层
- (void)insertSubview:(UIView *)view aboveSubview:(UIView *)siblingSubview;
// 将指定子视图推送到前台（顶层）
- (void)bringSubviewToFront:(UIView *)view;
// 将指定子视图推送到后台
- (void)sendSubviewToBack:(UIView *)view;
//通知某个子视图已经添加,通知视图已经添加子视图, 默认不执行任何操作，子类可以重写
- (void)didAddSubview:(UIView *)subview;
// 通知视图某个子视图即将移除,通知视图某个子视图即将移除, 默认不执行任何操作，子类可以重写
- (void)willRemoveSubview:(UIView *)subview;
//通知即将移动到新的父视图中
- (void)willMoveToSuperview:(UIView *)newSuperview;
// 通知已经到新父视图
- (void)didMoveToSuperview;
// 通知即将已移动到新的窗口
- (void)willMoveToWindow:(UIWindow *)newWindow;
// 通知已经移动新的窗口,
- (void)didMoveToWindow;
 // 判断一个视图是否在父视图层中
- (BOOL)isDescendantOfView:(UIView *)view;  // returns YES for self.
// 获取标记的子视图
- (UIView *)viewWithTag:(NSInteger)tag;     // recursive search. includes self

// Allows you to perform layout before the drawing cycle happens. -layoutIfNeeded forces layout early
 // 标记为需要重新布局，异步调用layoutIfNeeded刷新布局，不立即刷新，但layoutSubviews一定会被调用
- (void)setNeedsLayout;
// 如果，有需要刷新的标记，立即调用layoutSubviews进行布局（如果没有标记，不会调用layoutSubviews）
- (void)layoutIfNeeded;
//重新布局
/*
layoutSubviews在以下情况下会被调用：
1、init初始化不会触发layoutSubviews ,  但 initWithFrame 进行初始化时，当rect的值不为CGRectZero时,也会触发.
2、addSubview会触发layoutSubviews.
3、设置view的Frame会触发layoutSubviews，当然前提是frame的值设置前后发生了变化.
4、滚动一个UIScrollView会触发layoutSubviews.
5、旋转Screen会触发父UIView上的layoutSubviews事件.
6、改变一个UIView大小的时候也会触发父UIView上的layoutSubviews事件.
[1]、layoutSubviews对subviews重新布局
[2]、layoutSubviews方法调用先于drawRect
[3]、setNeedsLayout在receiver标上一个需要被重新布局的标记，在系统runloop的下一个周期自动调用layoutSubviews
[4]、layoutIfNeeded方法如其名，UIKit会判断该receiver是否需要layout
[5]、layoutIfNeeded遍历的不是superview链，应该是subviews链
*/
- (void)layoutSubviews;    // override point. called by layoutIfNeeded automatically. As of iOS 6.0, when constraints-based layout is used the base implementation applies the constraints-based layout, otherwise it does nothing.

@end

@interface UIView(UIViewRendering)
//子类重写方法，重绘
/*
drawRect是对receiver的重绘
setNeedDisplay在receiver标上一个需要被重新绘图的标记，
在下一个draw周期自动重绘，iphone device的刷新频率是60hz，也就是1/60秒后重绘
*/
- (void)drawRect:(CGRect)rect;
//标记为需要重绘，异步调用drawRect
- (void)setNeedsDisplay;
// 标记为需要局部重绘
- (void)setNeedsDisplayInRect:(CGRect)rect;
//决定子视图边界是否可以超过父视图范围
@property(nonatomic)                 BOOL              clipsToBounds;              // When YES, content and subviews are clipped to the bounds of the view. Default is NO.
// 背景颜色
@property(nonatomic,copy)            UIColor          *backgroundColor UI_APPEARANCE_SELECTOR; // default is nil. Can be useful with the appearance proxy on custom UIView subclasses.
// 透明度， 取值范围为0.0 --- 1.0 
@property(nonatomic)                 CGFloat           alpha;                      // animatable. default is 1.0
// 决定该消息接收者(UIView instance)是否让其视图不透明,用处在于给绘图系统提供一个性能优化开关。
/*
该值为YES, 那么绘图在绘制该视图的时候把整个视图当作不透明对待。优化绘图过程并提升系统性能；为了性能方面的考量，默认被置为YES。
该值为NO,，不去做优化操作。 
一个不透明视图需要整个边界里面的内容都是不透明。基于这个原因，opaque设置为YES，要求对应的alpha必须为1.0。
如果一个UIView实例opaque被设置为YES, 而同时它又没有完全填充它的边界(bounds),或者它包含了整个或部分的透明的内容视图，那么将会导致未知的结果。 
因此，如果视图部分或全部支持透明，那么你必须把opaque这个值设置为NO.
*/
@property(nonatomic,getter=isOpaque) BOOL              opaque;                     // default is YES. opaque views must fill their entire bounds or the results are undefined. the active CGContext in drawRect: will not have been cleared and may have non-zeroed pixels
// 决定绘制前是否清屏，默认为YES
/*
提高描画性能（特别是在滚动过程）的另一个方法是将视图的clearsContextBeforeDrawing属性设置为NO。
当这个属性被设置为YES时，UIKIt会在调用drawRect:方法之前，把即将被该方法更新的区域填充为透明的黑色。
将这个属性设置为NO可以取消相应的填充操作，而由应用程序负责完全重画传给drawRect:方法的更新矩形中的部。
这样的优化在滚动过程中通常是一个好的折衷。
*/
@property(nonatomic)                 BOOL              clearsContextBeforeDrawing; // default is YES. ignored for opaque views. for non-opaque views causes the active CGContext in drawRect: to be pre-filled with transparent pixels
 // 视图是否隐藏，默认为NO(显示),YES为隐藏
@property(nonatomic,getter=isHidden) BOOL              hidden;                     // default is NO. doesn't check superviews
// 视图边界填充
@property(nonatomic)                 UIViewContentMode contentMode;                // default is UIViewContentModeScaleToFill
 // 视图拉伸和缩略
@property(nonatomic)                 CGRect            contentStretch NS_DEPRECATED_IOS(3_0,6_0); // animatable. default is unit rectangle {{0,0} {1,1}}. Now deprecated: please use -[UIImage resizableImageWithCapInsets:] to achieve the same effect.

/*
 -tintColor always returns a color. The color returned is the first non-default value in the receiver's superview chain (starting with itself).
 If no non-default value is found, a system-defined color is returned.
 If this view's -tintAdjustmentMode returns Dimmed, then the color that is returned for -tintColor will automatically be dimmed.
 If your view subclass uses tintColor in its rendering, override -tintColorDidChange in order to refresh the rendering if the color changes.
 */
@property(nonatomic,retain) UIColor *tintColor NS_AVAILABLE_IOS(7_0);

/*
 -tintAdjustmentMode always returns either UIViewTintAdjustmentModeNormal or UIViewTintAdjustmentModeDimmed. The value returned is the first non-default value in the receiver's superview chain (starting with itself).
 If no non-default value is found, UIViewTintAdjustmentModeNormal is returned.
 When tintAdjustmentMode has a value of UIViewTintAdjustmentModeDimmed for a view, the color it returns from tintColor will be modified to give a dimmed appearance.
 When the tintAdjustmentMode of a view changes (either the view's value changing or by one of its superview's values changing), -tintColorDidChange will be called to allow the view to refresh its rendering.
 */
@property(nonatomic) UIViewTintAdjustmentMode tintAdjustmentMode NS_AVAILABLE_IOS(7_0);

/*
 The -tintColorDidChange message is sent to appropriate subviews of a view when its tintColor is changed by client code or to subviews in the view hierarchy of a view whose tintColor is implicitly changed when its superview or tintAdjustmentMode changes.
 */
- (void)tintColorDidChange NS_AVAILABLE_IOS(7_0);

@end

@interface UIView(UIViewAnimation)
// 开始一个动画
+ (void)beginAnimations:(NSString *)animationID context:(void *)context;  // additional context info passed to will start/did stop selectors. begin/commit can be nested
// 结束一个动画，类似数据库的事务处理
+ (void)commitAnimations;                                                 // starts up any animations when the top level animation is commited

// no getters. if called outside animation block, these setters have no effect.
// 设置动画委托
+ (void)setAnimationDelegate:(id)delegate;                          // default = nil
// 当动画执行开始时，执行selector方法
+ (void)setAnimationWillStartSelector:(SEL)selector;                // default = NULL. -animationWillStart:(NSString *)animationID context:(void *)context
//当动画执行结束时，执行selector方法
+ (void)setAnimationDidStopSelector:(SEL)selector;                  // default = NULL. -animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context
// 设置动画时间， 时间参数为double类型
+ (void)setAnimationDuration:(NSTimeInterval)duration;              // default = 0.2
// 设置动画延迟时间，单位秒
+ (void)setAnimationDelay:(NSTimeInterval)delay;                    // default = 0.0
// 设置在动画块内部动画属性改变的开始时间
+ (void)setAnimationStartDate:(NSDate *)startDate;                  // default = now ([NSDate date])
// 设置动画的旋转曲度变化
+ (void)setAnimationCurve:(UIViewAnimationCurve)curve;              // default = UIViewAnimationCurveEaseInOut
// 设置动画在动画模块中的重复次数 
+ (void)setAnimationRepeatCount:(float)repeatCount;                 // default = 0.0.  May be fractional
// 设置动画块中的动画效果是否自动重复播放
+ (void)setAnimationRepeatAutoreverses:(BOOL)repeatAutoreverses;    // default = NO. used if repeat count is non-zero
// 设置动画是否从当前状态开始播放。
+ (void)setAnimationBeginsFromCurrentState:(BOOL)fromCurrentState;  // default = NO. If YES, the current view position is always used for new animations -- allowing animations to "pile up" on each other. Otherwise, the last end state is used for the animation (the default).
// 在动画块设置过渡效果
+ (void)setAnimationTransition:(UIViewAnimationTransition)transition forView:(UIView *)view cache:(BOOL)cache;  // current limitation - only one per begin/commit block
// 设置是否开启动画，默认YES，开启
+ (void)setAnimationsEnabled:(BOOL)enabled;                         // ignore any attribute changes while set.
// 验证动画是否开启，YES:开启 NO：关闭
+ (BOOL)areAnimationsEnabled;
+ (void)performWithoutAnimation:(void (^)(void))actionsWithoutAnimation NS_AVAILABLE_IOS(7_0);

@end

@interface UIView(UIViewAnimationWithBlocks)
//动画效果处理块
+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion NS_AVAILABLE_IOS(4_0);
//动画效果处理块，无延迟
+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion NS_AVAILABLE_IOS(4_0); // delay = 0.0, options = 0
// 动画效果处理块。无延迟，简单版
+ (void)animateWithDuration:(NSTimeInterval)duration animations:(void (^)(void))animations NS_AVAILABLE_IOS(4_0); // delay = 0.0, options = 0, completion = NULL

/* Performs `animations` using a timing curve described by the motion of a spring. When `dampingRatio` is 1, the animation will smoothly decelerate to its final model values without oscillating. Damping ratios less than 1 will oscillate more and more before coming to a complete stop. You can use the initial spring velocity to specify how fast the object at the end of the simulated spring was moving before it was attached. It's a unit coordinate system, where 1 is defined as travelling the total animation distance in a second. So if you're changing an object's position by 200pt in this animation, and you want the animation to behave as if the object was moving at 100pt/s before the animation started, you'd pass 0.5. You'll typically want to pass 0 for the velocity. */ 
// 过渡动画处理块
+ (void)animateWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay usingSpringWithDamping:(CGFloat)dampingRatio initialSpringVelocity:(CGFloat)velocity options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);
 // 视图之间切换过渡动画处理块
+ (void)transitionWithView:(UIView *)view duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion NS_AVAILABLE_IOS(4_0);

+ (void)transitionFromView:(UIView *)fromView toView:(UIView *)toView duration:(NSTimeInterval)duration options:(UIViewAnimationOptions)options completion:(void (^)(BOOL finished))completion NS_AVAILABLE_IOS(4_0); // toView added to fromView.superview, fromView removed from its superview

/* Performs the requested system-provided animation on one or more views. Specify addtional animations in the parallelAnimations block. These additional animations will run alongside the system animation with the same timing and duration that the system animation defines/inherits. Additional animations should not modify properties of the view on which the system animation is being performed. Not all system animations honor all available options.
 */
+ (void)performSystemAnimation:(UISystemAnimation)animation onViews:(NSArray *)views options:(UIViewAnimationOptions)options animations:(void (^)(void))parallelAnimations completion:(void (^)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);

@end

@interface UIView (UIViewKeyframeAnimations)

+ (void)animateKeyframesWithDuration:(NSTimeInterval)duration delay:(NSTimeInterval)delay options:(UIViewKeyframeAnimationOptions)options animations:(void (^)(void))animations completion:(void (^)(BOOL finished))completion NS_AVAILABLE_IOS(7_0);
+ (void)addKeyframeWithRelativeStartTime:(double)frameStartTime relativeDuration:(double)frameDuration animations:(void (^)(void))animations NS_AVAILABLE_IOS(7_0); // start time and duration are values between 0.0 and 1.0 specifying time and duration relative to the overall time of the keyframe animation

@end

@interface UIView (UIViewGestureRecognizers)
/*
UIKit 中UIGestureRecognizer类的子类系列如下：
UITapGestureRecognizer – “轻击”手势。可以配置为“单击”和“连击”的识别。
UIPinchGestureRecognizer –“捏合”手势。该手势通常用于缩放视图或改变可视组件的大小。
UIPanGestureRecognizer – “平移”手势。识别拖拽或移动动作。
UISwipeGestureRecognizer – “轻扫”手势。当用户从屏幕上划过时识别为该手势。可以指定该动作的方向（上、下、左、右）。
UIRotationGestureRecognizer – “转动”手势。用户两指在屏幕上做相对环形运动。
UILongPressGestureRecognizer – “长按”手势。使用1指或多指触摸屏幕并保持一定时间。
*/
// 手势识别器
@property(nonatomic,copy) NSArray *gestureRecognizers NS_AVAILABLE_IOS(3_2);
// 绑定手势到视图
- (void)addGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer NS_AVAILABLE_IOS(3_2);
// 从视图中分离手势
- (void)removeGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer NS_AVAILABLE_IOS(3_2);

// called when the recognizer attempts to transition out of UIGestureRecognizerStatePossible if a touch hit-tested to this view will be cancelled as a result of gesture recognition
// returns YES by default. return NO to cause the gesture recognizer to transition to UIGestureRecognizerStateFailed
// subclasses may override to prevent recognition of particular gestures. for example, UISlider prevents swipes parallel to the slider that start in the thumb
// 手势识别处理方式
/*
手势识别处理方式在gesture recognizer视图转出《UIGestureRecognizerStatePossible》状态时调用，
如果返回NO,则转换到《UIGestureRecognizerStateFailed》;
如果返回YES,则继续识别触摸序列.(默认情况下为YES)。
*/
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer NS_AVAILABLE_IOS(6_0);

@end
    
@interface UIView (UIViewMotionEffects)

/*! Begins applying `effect` to the receiver. The effect's emitted keyPath/value pairs will be
    applied to the view's presentation layer.
 
    Animates the transition to the motion effect's values using the present UIView animation
    context. */
- (void)addMotionEffect:(UIMotionEffect *)effect NS_AVAILABLE_IOS(7_0);

/*! Stops applying `effect` to the receiver. Any affected presentation values will animate to
    their post-removal values using the present UIView animation context. */
- (void)removeMotionEffect:(UIMotionEffect *)effect NS_AVAILABLE_IOS(7_0);

@property (copy, nonatomic) NSArray *motionEffects NS_AVAILABLE_IOS(7_0);

@end


//
// UIView Constraint-based Layout Support
//

typedef NS_ENUM(NSInteger, UILayoutConstraintAxis) {
    UILayoutConstraintAxisHorizontal = 0,
    UILayoutConstraintAxisVertical = 1
};

// Installing Constraints

/* A constraint is typically installed on the closest common ancestor of the views involved in the constraint. 
 It is required that a constraint be installed on _a_ common ancestor of every view involved.  The numbers in a constraint are interpreted in the coordinate system of the view it is installed on.  A view is considered to be an ancestor of itself.
 */
@interface UIView (UIConstraintBasedLayoutInstallingConstraints)
// 视图布局约束
- (NSArray *)constraints NS_AVAILABLE_IOS(6_0);
// 视图布局上添加一个约束
- (void)addConstraint:(NSLayoutConstraint *)constraint NS_AVAILABLE_IOS(6_0);
// 视图布局上添加多个约束
- (void)addConstraints:(NSArray *)constraints NS_AVAILABLE_IOS(6_0);
// 移除视图布局上的一个约束
- (void)removeConstraint:(NSLayoutConstraint *)constraint NS_AVAILABLE_IOS(6_0);
// 移除视图布局上的多个约束
- (void)removeConstraints:(NSArray *)constraints NS_AVAILABLE_IOS(6_0);
@end

// Core Layout Methods

/* To render a window, the following passes will occur, if necessary.  
 
 update constraints
 layout
 display
 
 Please see the conceptual documentation for a discussion of these methods.
 */

@interface UIView (UIConstraintBasedLayoutCoreMethods) 
 //调用新的视图布局自动触发，更新视图布局上的约束
- (void)updateConstraintsIfNeeded NS_AVAILABLE_IOS(6_0); // Updates the constraints from the bottom up for the view hierarchy rooted at the receiver. UIWindow's implementation creates a layout engine if necessary first.
// 更新自定义视图布局约束
- (void)updateConstraints NS_AVAILABLE_IOS(6_0); // Override this to adjust your special constraints during a constraints update pass
// 判断视图布局是否需要更新约束
- (BOOL)needsUpdateConstraints NS_AVAILABLE_IOS(6_0);
// 设置视图布局是否需要更新约束
- (void)setNeedsUpdateConstraints NS_AVAILABLE_IOS(6_0);
@end

// Compatibility and Adoption

@interface UIView (UIConstraintBasedCompatibility) 

/* by default, the autoresizing mask on a view gives rise to constraints that fully determine the view's position.  Any constraints you set on the view are likely to conflict with autoresizing constraints, so you must turn off this property first. IB will turn it off for you.
 */
 // 标示是否自动遵循视图布局约束
- (BOOL)translatesAutoresizingMaskIntoConstraints NS_AVAILABLE_IOS(6_0); // Default YES
// 设置是否自动遵循视图布局约束
- (void)setTranslatesAutoresizingMaskIntoConstraints:(BOOL)flag NS_AVAILABLE_IOS(6_0);

/* constraint-based layout engages lazily when someone tries to use it (e.g., adds a constraint to a view).  If you do all of your constraint set up in -updateConstraints, you might never even receive updateConstraints if no one makes a constraint.  To fix this chicken and egg problem, override this method to return YES if your view needs the window to use constraint-based layout.  
 */
// 返回是遵循自定义视图布局约束
+ (BOOL)requiresConstraintBasedLayout NS_AVAILABLE_IOS(6_0);

@end

// Separation of Concerns

@interface UIView (UIConstraintBasedLayoutLayering)

/* Constraints do not actually relate the frames of the views, rather they relate the "alignment rects" of views.  This is the same as the frame unless overridden by a subclass of UIView.  Alignment rects are the same as the "layout rects" shown in Interface Builder 3.  Typically the alignment rect of a view is what the end user would think of as the bounding rect around a control, omitting ornamentation like shadows and engraving lines.  The edges of the alignment rect are what is interesting to align, not the shadows and such.  
 */

/* These two methods should be inverses of each other.  UIKit will call both as part of layout computation.
 They may be overridden to provide arbitrary transforms between frame and alignment rect, though the two methods must be inverses of each other.
 However, the default implementation uses -alignmentRectInsets, so just override that if it's applicable.  It's easier to get right. 
 A view that displayed an image with some ornament would typically override these, because the ornamental part of an image would scale up with the size of the frame.  
 Set the NSUserDefault UIViewShowAlignmentRects to YES to see alignment rects drawn.
 */
 // 返回矩形对于指定视图框架。
- (CGRect)alignmentRectForFrame:(CGRect)frame NS_AVAILABLE_IOS(6_0);
// 返回框架对于指定视图矩形
- (CGRect)frameForAlignmentRect:(CGRect)alignmentRect NS_AVAILABLE_IOS(6_0);

/* override this if the alignment rect is obtained from the frame by insetting each edge by a fixed amount.  This is only called by alignmentRectForFrame: and frameForAlignmentRect:.
 */
// 返回自定义视图框架
- (UIEdgeInsets)alignmentRectInsets NS_AVAILABLE_IOS(6_0);

/* When you make a constraint on the NSLayoutAttributeBaseline of a view, the system aligns with the bottom of the view returned from this method. A nil return is interpreted as the receiver, and a non-nil return must be in the receiver's subtree.  UIView's implementation returns self.
 */
// 如果超出约束范围，自动生成基线限制，以满足视图需求
- (UIView *)viewForBaselineLayout NS_AVAILABLE_IOS(6_0);


/* Override this method to tell the layout system that there is something it doesn't natively understand in this view, and this is how large it intrinsically is.  A typical example would be a single line text field.  The layout system does not understand text - it must just be told that there's something in the view, and that that something will take a certain amount of space if not clipped.  
 
 In response, UIKit will set up constraints that specify (1) that the opaque content should not be compressed or clipped, (2) that the view prefers to hug tightly to its content. 
 
 A user of a view may need to specify the priority of these constraints.  For example, by default, a push button 
 -strongly wants to hug its content in the vertical direction (buttons really ought to be their natural height)
 -weakly hugs its content horizontally (extra side padding between the title and the edge of the bezel is acceptable)
 -strongly resists compressing or clipping content in both directions. 
 
 However, you might have a case where you'd prefer to show all the available buttons with truncated text rather than losing some of the buttons. The truncation might only happen in portrait orientation but not in landscape, for example. In that case you'd want to setContentCompressionResistancePriority:forAxis: to (say) UILayoutPriorityDefaultLow for the horizontal axis.
 
 The default 'strong' and 'weak' priorities referred to above are UILayoutPriorityDefaultHigh and UILayoutPriorityDefaultLow.  
 
 Note that not all views have an intrinsicContentSize.  UIView's default implementation is to return (UIViewNoIntrinsicMetric, UIViewNoIntrinsicMetric).  The _intrinsic_ content size is concerned only with data that is in the view itself, not in other views. Remember that you can also set constant width or height constraints on any view, and you don't need to override instrinsicContentSize if these dimensions won't be changing with changing view content.
 */
UIKIT_EXTERN const CGFloat UIViewNoIntrinsicMetric NS_AVAILABLE_IOS(6_0); // -1
// 返回自定义视图大小
- (CGSize)intrinsicContentSize NS_AVAILABLE_IOS(6_0);
// 自定义视图内容大小无效
- (void)invalidateIntrinsicContentSize NS_AVAILABLE_IOS(6_0); // call this when something changes that affects the intrinsicContentSize.  Otherwise UIKit won't notice that it changed.  
//返回放大的视图布局的轴线
- (UILayoutPriority)contentHuggingPriorityForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
// 设置放大的视图布局的轴线
- (void)setContentHuggingPriority:(UILayoutPriority)priority forAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
// 返回缩小的视图布局的轴线
- (UILayoutPriority)contentCompressionResistancePriorityForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
// 设置缩小的视图布局的轴线
- (void)setContentCompressionResistancePriority:(UILayoutPriority)priority forAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);
@end

// Size To Fit

UIKIT_EXTERN const CGSize UILayoutFittingCompressedSize NS_AVAILABLE_IOS(6_0);
UIKIT_EXTERN const CGSize UILayoutFittingExpandedSize NS_AVAILABLE_IOS(6_0);

@interface UIView (UIConstraintBasedLayoutFittingSize)
/* The size fitting most closely to targetSize in which the receiver's subtree can be laid out while optimally satisfying the constraints. If you want the smallest possible size, pass UILayoutFittingCompressedSize; for the largest possible size, pass UILayoutFittingExpandedSize.
 Also see the comment for UILayoutPriorityFittingSizeLevel.
 */
 //满足约束视图布局的大小
- (CGSize)systemLayoutSizeFittingSize:(CGSize)targetSize NS_AVAILABLE_IOS(6_0);
@end

// Debugging

/* Everything in this section should be used in debugging only, never in shipping code.  These methods may not exist in the future - no promises.  
 */
@interface UIView (UIConstraintBasedLayoutDebugging)

/* This returns a list of all the constraints that are affecting the current location of the receiver.  The constraints do not necessarily involve the receiver, they may affect the frame indirectly.
 Pass UILayoutConstraintAxisHorizontal for the constraints affecting [self center].x and CGRectGetWidth([self bounds]), and UILayoutConstraintAxisVertical for the constraints affecting[self center].y and CGRectGetHeight([self bounds]).
 */
 // 返回影响视图布局限制的轴线
- (NSArray *)constraintsAffectingLayoutForAxis:(UILayoutConstraintAxis)axis NS_AVAILABLE_IOS(6_0);

/* If there aren't enough constraints in the system to uniquely determine layout, we say the layout is ambiguous.  For example, if the only constraint in the system was x = y + 100, then there are lots of different possible values for x and y.  This situation is not automatically detected by UIKit, due to performance considerations and details of the algorithm used for layout.  
 The symptom of ambiguity is that views sometimes jump from place to place, or possibly are just in the wrong place.
 -hasAmbiguousLayout runs a check for whether there is another center and bounds the receiver could have that could also satisfy the constraints.
 -exerciseAmbiguousLayout does more.  It randomly changes the view layout to a different valid layout.  Making the UI jump back and forth can be helpful for figuring out where you're missing a constraint.  
 */
 // 返回视图布局约束是否影响指定视图，主要用于调试约束布局，结合exerciseAmbiguityInLayout。
- (BOOL)hasAmbiguousLayout NS_AVAILABLE_IOS(6_0);
// 随机改变不同效值布局视图，主要用于调试基于约束布局的视图
- (void)exerciseAmbiguityInLayout NS_AVAILABLE_IOS(6_0); 
@end

@interface UIView (UIStateRestoration)
// 标示是否支持保存，恢复视图状态信息
@property (nonatomic, copy) NSString *restorationIdentifier NS_AVAILABLE_IOS(6_0);
// 保存视图状态相关信息
- (void) encodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
// 恢复和保持视图状态相关信息
- (void) decodeRestorableStateWithCoder:(NSCoder *)coder NS_AVAILABLE_IOS(6_0);
@end

@interface UIView (UISnapshotting)
/* 
* When requesting a snapshot, 'afterUpdates' defines whether the snapshot is representative of what's currently on screen or if you wish to include any recent changes before taking the snapshot. 
 
 If called during layout from a committing transaction, snapshots occurring after the screen updates will include all changes made, regardless of when the snapshot is taken and the changes are made. For example:
 
     - (void)layoutSubviews {
         UIView *snapshot = [self snapshotViewAfterScreenUpdates:YES];
         self.alpha = 0.0;
     }
 
 The snapshot will appear to be empty since the change in alpha will be captured by the snapshot. If you need to animate the view during layout, animate the snapshot instead.

* Creating snapshots from existing snapshots (as a method to duplicate, crop or create a resizable variant) is supported. In cases where many snapshots are needed, creating a snapshot from a common superview and making subsequent snapshots from it can be more performant. Please keep in mind that if 'afterUpdates' is YES, the original snapshot is committed and any changes made to it, not the view originally snapshotted, will be included.
 */
- (UIView *)snapshotViewAfterScreenUpdates:(BOOL)afterUpdates NS_AVAILABLE_IOS(7_0);
- (UIView *)resizableSnapshotViewFromRect:(CGRect)rect afterScreenUpdates:(BOOL)afterUpdates withCapInsets:(UIEdgeInsets)capInsets NS_AVAILABLE_IOS(7_0);  // Resizable snapshots will default to stretching the center
// Use this method to render a snapshot of the view hierarchy into the current context. Returns NO if the snapshot is missing image data, YES if the snapshot is complete. Calling this method from layoutSubviews while the current transaction is committing will capture what is currently displayed regardless if afterUpdates is YES.
- (BOOL)drawViewHierarchyInRect:(CGRect)rect afterScreenUpdates:(BOOL)afterUpdates NS_AVAILABLE_IOS(7_0);
@end
