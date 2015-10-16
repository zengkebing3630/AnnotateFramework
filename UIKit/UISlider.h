//
//  UISlider.h
//  UIKit
//
//  Copyright (c) 2006-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIControl.h>
#import <UIKit/UIKitDefines.h>
#import <QuartzCore/QuartzCore.h>

@class UIImageView, UIImage;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UISlider : UIControl <NSCoding>

@property(nonatomic) float value;                                // 当前值, minimumValue<= value <=maximumValue
@property(nonatomic) float minimumValue;                         // 最小值，默认0.0 
@property(nonatomic) float maximumValue;                         // 最大值，默认1.0 

@property(nonatomic,retain) UIImage *minimumValueImage;          // 最小值一侧图标 ，设置滑块最左端显示的图片
@property(nonatomic,retain) UIImage *maximumValueImage;          // 最大值一侧图标 ，设置滑块最右端显示的图片

/*
	[slider addTarget:self action:@selector(updateValue:) forControlEvents:UIControlEventValueChanged];／／设置响应事件
*/
//这个属性设置为YES则在滑动时，其value就会随时变化，设置为NO，则当滑动结束时，value才会改变
@property(nonatomic,getter=isContinuous) BOOL continuous;        // 移动过程中是否触发值变化事件,默认YES ，移动时，value时刻改变

/*
	注意这个属性：如果你没有设置滑块的图片，那个这个属性将只会改变已划过一段线条的颜色，
	不会改变滑块的颜色，如果你设置了滑块的图片，又设置了这个属性，那么滑块的图片将不显示，滑块的颜色会改变（IOS7）
*/
//设置滑块左边（小于部分）线条的颜色
@property(nonatomic,retain) UIColor *minimumTrackTintColor NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
//设置滑块右边（大于部分）线条的颜色
@property(nonatomic,retain) UIColor *maximumTrackTintColor NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
//设置滑块颜色（影响已划过一端的颜色）
@property(nonatomic,retain) UIColor *thumbTintColor NS_AVAILABLE_IOS(5_0) UI_APPEARANCE_SELECTOR;
//手动设置滑块的值：
- (void)setValue:(float)value animated:(BOOL)animated; 

// set the images for the slider. there are 3, the thumb which is centered by default and the track. You can specify different left and right track
// e.g blue on the left as you increase and white to the right of the thumb. The track images should be 3 part resizable (via UIImage's resizableImage methods) along the direction that is longer

- (void)setThumbImage:(UIImage *)image forState:(UIControlState)state;// 自定义滑块图标
- (void)setMinimumTrackImage:(UIImage *)image forState:(UIControlState)state;// 自定义最小值一侧轨道图标
- (void)setMaximumTrackImage:(UIImage *)image forState:(UIControlState)state;// 自定义最大值一侧轨道图标

//对应的几个get方法
- (UIImage *)thumbImageForState:(UIControlState)state;
- (UIImage *)minimumTrackImageForState:(UIControlState)state;
- (UIImage *)maximumTrackImageForState:(UIControlState)state;

//对应的设置当前状态的响应属性的方法
@property(nonatomic,readonly) UIImage* currentThumbImage;
@property(nonatomic,readonly) UIImage* currentMinimumTrackImage;
@property(nonatomic,readonly) UIImage* currentMaximumTrackImage;

// lets a subclass lay out the track and thumb as needed
- (CGRect)minimumValueImageRectForBounds:(CGRect)bounds;
- (CGRect)maximumValueImageRectForBounds:(CGRect)bounds;
- (CGRect)trackRectForBounds:(CGRect)bounds;
- (CGRect)thumbRectForBounds:(CGRect)bounds trackRect:(CGRect)rect value:(float)value;

@end
