//
//  MKOverlayPathView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <MapKit/MKOverlayView.h>
#import <MapKit/MKFoundation.h>

// Prefer MKOverlayPathRenderer
/*
	使用CGPathRef数据类型用于绘制一般的覆盖层。
	你可以调用本方法来实现简单的基于路径的覆盖层视图， 或者子类化它来定义额外的绘制行为。
	本类默认的绘制行为是应用对象当前的填充属性填充路径，应用当前的描边属性描绘路径。 
	子类化时你需要重写 createPath 方法，使用该方法为覆盖层创建适当的路径。
	当你的子类获得新数据时你可以使当前路径无效 并强制重新创建路径。
*/
@interface MKOverlayPathView : MKOverlayView
// 路径的填充色。 
@property (strong) UIColor *fillColor NS_DEPRECATED_IOS(4_0, 7_0);
// 路径的描边色。
@property (strong) UIColor *strokeColor NS_DEPRECATED_IOS(4_0, 7_0);
	// 路径的描边宽度。 
@property CGFloat lineWidth NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 0, which is MKRoadWidthAtZoomScale(currentZoomScale)
// 应用到路径拐角的线条连结式样。
@property CGLineJoin lineJoin NS_DEPRECATED_IOS(4_0, 7_0); // defaults to kCGLineJoinRound
// 应用到开放路径的线帽式样。
@property CGLineCap lineCap NS_DEPRECATED_IOS(4_0, 7_0); // defaults to kCGLineCapRound
// 限制值用于避免连结线段拐角出现尖峰。 
@property CGFloat miterLimit NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 10
// 指定虚线式样下线条的起点。 
@property CGFloat lineDashPhase NS_DEPRECATED_IOS(4_0, 7_0); // defaults to 0
	// 一组数字用于指定路径的虚线式样。 
@property (copy) NSArray *lineDashPattern NS_DEPRECATED_IOS(4_0, 7_0); // an array of NSNumbers, defaults to nil

// 创建覆盖层的路径。 self.path = newPath;
- (void)createPath NS_DEPRECATED_IOS(4_0, 7_0);
// returns cached path or calls createPath if path has not yet been created
// 用于绘制覆盖层的当前路径。 
@property CGPathRef path NS_DEPRECATED_IOS(4_0, 7_0); // path will be retained
// 释放与接收者关联的路径。 
- (void)invalidatePath NS_DEPRECATED_IOS(4_0, 7_0);

// 应用接收者当前填充相关的绘制属性到指定的图像上下文。 
- (void)applyStrokePropertiesToContext:(CGContextRef)context
                           atZoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);
// 应用接收者当前描边相关的绘制属性到指定的图像上下文。                           
- (void)applyFillPropertiesToContext:(CGContextRef)context
                         atZoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);
// 沿着指定的路径绘制一条线。 
- (void)strokePath:(CGPathRef)path inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);
// 填充指定的路径围成的区域。 
- (void)fillPath:(CGPathRef)path inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);

@end
