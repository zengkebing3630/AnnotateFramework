//
//  UIBezierPath.h
//  UIKit
//
//  Copyright (c) 2009-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>


#define pi 3.14159265359  
#define DEGREES_TO_RADIANS(degrees)  ((pi * degrees)/ 180)  

typedef NS_OPTIONS(NSUInteger, UIRectCorner) {
    UIRectCornerTopLeft     = 1 << 0,
    UIRectCornerTopRight    = 1 << 1,
    UIRectCornerBottomLeft  = 1 << 2,
    UIRectCornerBottomRight = 1 << 3,
    UIRectCornerAllCorners  = ~0UL
};

NS_CLASS_AVAILABLE_IOS(3_2) @interface UIBezierPath : NSObject<NSCopying, NSCoding> {
@private
    CGPathRef _path;
    CGFloat *_lineDashPattern;
    NSUInteger _lineDashPatternCount;
    CGFloat _lineWidth, _miterLimit, _flatness, _lineDashPhase;
    CGLineCap _lineCapStyle;
    CGLineJoin _lineJoinStyle;
    BOOL _usesEvenOddFillRule;
    CGPathRef _immutablePath;
    BOOL _immutablePathIsValid;
}

+ (UIBezierPath *)bezierPath;
//根据一个矩形画曲线
+ (UIBezierPath *)bezierPathWithRect:(CGRect)rect;
//根据矩形框的内切圆画曲线，椭圆
+ (UIBezierPath *)bezierPathWithOvalInRect:(CGRect)rect;

//根据矩形画带圆角的曲线
+ (UIBezierPath *)bezierPathWithRoundedRect:(CGRect)rect cornerRadius:(CGFloat)cornerRadius; // rounds all corners with the same horizontal and vertical radius

/*
在矩形中，可以针对四角中的某个角加圆角
corners:枚举值，可以选择某个角
cornerRadii:圆角的大小
*/
+ (UIBezierPath *)bezierPathWithRoundedRect:(CGRect)rect byRoundingCorners:(UIRectCorner)corners cornerRadii:(CGSize)cornerRadii;
/*
可以画出一段弧线
center：圆心的坐标    
radius：半径
startAngle：起始的弧度
endAngle：圆弧结束的弧度
clockwise：YES为顺时针，No为逆时针
*/
+ (UIBezierPath *)bezierPathWithArcCenter:(CGPoint)center radius:(CGFloat)radius startAngle:(CGFloat)startAngle endAngle:(CGFloat)endAngle clockwise:(BOOL)clockwise;
//以CGPath 初始化 
+ (UIBezierPath *)bezierPathWithCGPath:(CGPathRef)CGPath;

// Returns an immutable CGPathRef which is only valid until the UIBezierPath is further mutated.
// Setting the path will create an immutable copy of the provided CGPathRef, so any further mutations on a provided CGMutablePathRef will be ignored.
@property(nonatomic) CGPathRef CGPath;
- (CGPathRef)CGPath NS_RETURNS_INNER_POINTER CF_RETURNS_NOT_RETAINED;

// Path construction

//移动起点 point
- (void)moveToPoint:(CGPoint)point;

//添加一条线，point终点
- (void)addLineToPoint:(CGPoint)point;
/*
    二次贝塞尔曲线
endPoint:结束的Point
controlPoint1:第一个控制点
controlPoint2：第二个控制点
*/ 
- (void)addCurveToPoint:(CGPoint)endPoint controlPoint1:(CGPoint)controlPoint1 controlPoint2:(CGPoint)controlPoint2;


/*
    立方曲线
    endPoint:结束的Point
    controlPoint:控制点
*/
- (void)addQuadCurveToPoint:(CGPoint)endPoint controlPoint:(CGPoint)controlPoint;
/*
可以画出一段弧线
center：圆心的坐标    
radius：半径
startAngle：起始的弧度
endAngle：圆弧结束的弧度
clockwise：YES为顺时针，No为逆时针
*/
- (void)addArcWithCenter:(CGPoint)center radius:(CGFloat)radius startAngle:(CGFloat)startAngle endAngle:(CGFloat)endAngle clockwise:(BOOL)clockwise NS_AVAILABLE_IOS(4_0);
/*
    结束绘画,也在最后一个点和第一个点之间画一条线段
*/
- (void)closePath;

/*
 清除所有的Points
*/
- (void)removeAllPoints;

// Appending paths

- (void)appendPath:(UIBezierPath *)bezierPath;

// Modified paths

- (UIBezierPath *)bezierPathByReversingPath NS_AVAILABLE_IOS(6_0);

// Transforming paths

- (void)applyTransform:(CGAffineTransform)transform;

// Path info

//Path 是不是空的
@property(readonly,getter=isEmpty) BOOL empty;
//矩形大小
@property(nonatomic,readonly) CGRect bounds;
//当然点
@property(nonatomic,readonly) CGPoint currentPoint;
//判断是否包含某点
- (BOOL)containsPoint:(CGPoint)point;


 //线条宽度
@property(nonatomic) CGFloat lineWidth;
 //线条拐角
@property(nonatomic) CGLineCap lineCapStyle;
//终点处理 
@property(nonatomic) CGLineJoin lineJoinStyle;
/*最大斜接长度
只有lineJoin属性为kCALineJoinMiter时miterLimit才有效

边角的角度越小，斜接长度就会越大。

为了避免斜接长度过长，我们可以使用 miterLimit 属性。

如果斜接长度超过 miterLimit 的值，边角会以 lineJoin的 "bevel"即kCALineJoinBevel类型来显示
*/
@property(nonatomic) CGFloat miterLimit; // Used when lineJoinStyle is kCGLineJoinMiter
@property(nonatomic) CGFloat flatness;
@property(nonatomic) BOOL usesEvenOddFillRule; // Default is NO. When YES, the even-odd fill rule is used for drawing, clipping, and hit testing.

/*
    设置线型
    pattern：C类型的线型数据。如：CGFloat dashStyle[] = { 1.0f, 2.0f };
    count：pattern中的数据个数
    phase: 开始画线型的起始位置
*/
- (void)setLineDash:(const CGFloat *)pattern count:(NSInteger)count phase:(CGFloat)phase;
- (void)getLineDash:(CGFloat *)pattern count:(NSInteger *)count phase:(CGFloat *)phase;

// Path operations on the current graphics context

//填充颜色
- (void)fill;
//根据坐标点连线  
- (void)stroke;

// These methods do not affect the blend mode or alpha of the current graphics context
- (void)fillWithBlendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;
- (void)strokeWithBlendMode:(CGBlendMode)blendMode alpha:(CGFloat)alpha;

// 除了使用贝塞尔路径对象来绘制形状，你也可以用它来定义一个新的裁剪区域。的addClip方法相交的形状与当前的图形上下文的裁剪区域所代表的路径对象
- (void)addClip;

@end
