//
//  UIButton.h
//  UIKit
//
//  Copyright (c) 2005-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIKitDefines.h>

@class UIImage, UIFont, UIColor, UIImageView, UILabel;

typedef NS_ENUM(NSInteger, UIButtonType) {
    UIButtonTypeCustom = 0,                         // 没有风格
    UIButtonTypeSystem NS_ENUM_AVAILABLE_IOS(7_0),  // 圆角风格按钮

    UIButtonTypeDetailDisclosure,
    UIButtonTypeInfoLight, // 明亮背景的信息按钮
    UIButtonTypeInfoDark,// 黑暗背景的信息按钮
    UIButtonTypeContactAdd,
    
    UIButtonTypeRoundedRect = UIButtonTypeSystem,  
};
/*
	UIButton的类是一个UIControl子类，它实现了在触摸屏上的按钮。
	触摸一个按钮拦截事件和动作消息发送到目标对象时，它的挖掘。
	设定的目标和行动方法都继承自UIControl。
	这个类提供了方法来设置标题，图像，按钮等外观属性。通过使用set方法，你可以指定一个不同的外观为每个按钮状态。
*/
NS_CLASS_AVAILABLE_IOS(2_0) @interface UIButton : UIControl <NSCoding>

+ (id)buttonWithType:(UIButtonType)buttonType;
// 按钮content内外线边缘绘制区域.content包含按钮图片和标题,默认：UIEdgeInsetsZero
@property(nonatomic)          UIEdgeInsets contentEdgeInsets UI_APPEARANCE_SELECTOR; 
// 按钮标题绘制区域控制.默认：UIEdgeInsetsZero
@property(nonatomic)          UIEdgeInsets titleEdgeInsets;                
// 按钮图片绘制区域控制.默认：UIEdgeInsetsZero
@property(nonatomic)          UIEdgeInsets imageEdgeInsets;                

//确定按钮高亮时是否改变阴影的Bool值.默认时NO,当为YES时,阴影在雕刻与浮雕感之间变化(差不多就是去正常offset的相反数作为新的offset)
@property(nonatomic)          BOOL         reversesTitleShadowWhenHighlighted;
//// 确定当按钮高亮时图片是否改变的BOOL值,为真时图片随按钮高亮而高亮
@property(nonatomic)          BOOL         adjustsImageWhenHighlighted;
//// 确定当按钮高亮时图片是否改变的BOOL值,为真时图片随按钮失效而变暗
@property(nonatomic)          BOOL         adjustsImageWhenDisabled;
// 控制当按钮按下时是否闪光的BOOL值.默认NO,YES时按下会有白色光点.图片和按钮事件的不会因闪光改变.
@property(nonatomic)          BOOL         showsTouchWhenHighlighted;      // default is NO. if YES, show a simple feedback (currently a glow) while highlighted
@property(nonatomic,retain)   UIColor     *tintColor NS_AVAILABLE_IOS(5_0); // The tintColor is inherited through the superview hierarchy. See UIView for more information.
//按钮类型
@property(nonatomic,readonly) UIButtonType buttonType;

// you can set the image, title color, title shadow color, and background image to use for each state. you can specify data
// for a combined state by using the flags added together. in general, you should specify a value for the normal state to be used
// by other states which don't have a custom value set

- (void)setTitle:(NSString *)title forState:(UIControlState)state;                     // default is nil. title is assumed to be single line
- (void)setTitleColor:(UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default if nil. use opaque white
// 设置不同状态时的标题阴影颜色.不同状态默认的标题阴影颜色是UIControlStateNormal时的值.若normal状态的值没有设定,默认是个系统值,所以你只要要设置normal状态
- (void)setTitleShadowColor:(UIColor *)color forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil. use 50% black
- (void)setImage:(UIImage *)image forState:(UIControlState)state;                      // default is nil. should be same size if different for different states
- (void)setBackgroundImage:(UIImage *)image forState:(UIControlState)state UI_APPEARANCE_SELECTOR; // default is nil
- (void)setAttributedTitle:(NSAttributedString *)title forState:(UIControlState)state NS_AVAILABLE_IOS(6_0); // default is nil. title is assumed to be single line

- (NSString *)titleForState:(UIControlState)state;          // these getters only take a single state value
- (UIColor *)titleColorForState:(UIControlState)state;
- (UIColor *)titleShadowColorForState:(UIControlState)state;
- (UIImage *)imageForState:(UIControlState)state;
- (UIImage *)backgroundImageForState:(UIControlState)state;
- (NSAttributedString *)attributedTitleForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

// these are the values that will be used for the current state. you can also use these for overrides. a heuristic will be used to
// determine what image to choose based on the explict states set. For example, the 'normal' state value will be used for all states
// that don't have their own image defined.

//当时的标题
@property(nonatomic,readonly,retain) NSString *currentTitle;             // normal/highlighted/selected/disabled. can return nil
//当时的标题颜色
@property(nonatomic,readonly,retain) UIColor  *currentTitleColor;        // normal/highlighted/selected/disabled. always returns non-nil. default is white(1,1)
//当时标题的阴影
@property(nonatomic,readonly,retain) UIColor  *currentTitleShadowColor;  // normal/highlighted/selected/disabled. default is white(0,0.5).
//当时照片
@property(nonatomic,readonly,retain) UIImage  *currentImage;             // normal/highlighted/selected/disabled. can return nil
//当时的背景图
@property(nonatomic,readonly,retain) UIImage  *currentBackgroundImage;   // normal/highlighted/selected/disabled. can return nil
//当时的富文本
@property(nonatomic,readonly,retain) NSAttributedString *currentAttributedTitle NS_AVAILABLE_IOS(6_0);  // normal/highlighted/selected/disabled. can return nil

// return title and image views. will always create them if necessary. always returns nil for system buttons
//当时的文本视图
@property(nonatomic,readonly,retain) UILabel     *titleLabel NS_AVAILABLE_IOS(3_0);
//当时的图片视图
@property(nonatomic,readonly,retain) UIImageView *imageView  NS_AVAILABLE_IOS(3_0);

// 返回背景绘制区域.
- (CGRect)backgroundRectForBounds:(CGRect)bounds;
// 返回内容绘制区域.内容区域是显示图片和标题及他们特定对齐缩放等的范围.
- (CGRect)contentRectForBounds:(CGRect)bounds;
// 返回标题的绘制区域.
- (CGRect)titleRectForContentRect:(CGRect)contentRect;
 // 返回图片的绘制区域.
- (CGRect)imageRectForContentRect:(CGRect)contentRect;
@end

@interface UIButton(UIButtonDeprecated)

@property(nonatomic,retain) UIFont         *font              NS_DEPRECATED_IOS(2_0, 3_0); //字体大小
@property(nonatomic)        NSLineBreakMode lineBreakMode     NS_DEPRECATED_IOS(2_0, 3_0); //绘制文本时使用的换行模式
@property(nonatomic)        CGSize          titleShadowOffset NS_DEPRECATED_IOS(2_0, 3_0); //用于显示接收的标题阴影的偏移。

@end
