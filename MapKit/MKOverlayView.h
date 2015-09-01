//
//  MKOverlayView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKFoundation.h>


// Prefer MKOverlayRenderer
/*
 所有与覆盖层视图相关的基本行为。一个覆盖层视图提供了覆盖层对象的视觉显示。
 本类定义了在地图视 图使用的绘制结构但不执行任何实际的绘制。
 子类需要重写 drawMapRect:zoomScale:inContext: 方法来绘制图覆盖层视图的 内容。
 MBMapKit 框架提供了一些具体的覆盖层视图实例。它给每个具体的覆盖层对象提供覆盖层视图。
 如果你希望以别的方式绘制覆盖层 的内容你可以使用一个现有的覆盖层视图来定义自己的子类
 */
@interface MKOverlayView : UIView

//初始化并返回与指定覆盖层对象关联的覆盖层视图。 
- (instancetype)initWithOverlay:(id <MKOverlay>)overlay NS_DESIGNATED_INITIALIZER NS_DEPRECATED_IOS(4_0, 7_0);

@property (nonatomic, readonly) id <MKOverlay> overlay NS_DEPRECATED_IOS(4_0, 7_0);

// Convert screen points relative to this view to absolute MKMapPoints
//返回指定地图点在覆盖层视图中对应的点
- (CGPoint)pointForMapPoint:(MKMapPoint)mapPoint NS_DEPRECATED_IOS(4_0, 7_0);
//返回指定覆盖层视图中的点对应的地图点。
- (MKMapPoint)mapPointForPoint:(CGPoint)point NS_DEPRECATED_IOS(4_0, 7_0);

//指定地图点在覆盖层视图中对应的矩形
- (CGRect)rectForMapRect:(MKMapRect)mapRect NS_DEPRECATED_IOS(4_0, 7_0);
//返回指定覆盖层视图坐标系中矩形对应的地图矩形。 
- (MKMapRect)mapRectForRect:(CGRect)rect NS_DEPRECATED_IOS(4_0, 7_0);

// Return YES if the view is currently ready to draw in the specified rect.
// Return NO if the view will not draw in the specified rect or if the
// data necessary to draw in the specified rect is not available.  In the 
// case where the view may want to draw in the specified rect but the data is
// not available, use setNeedsDisplayInMapRect:zoomLevel: to signal when the
// data does become available.
//返回布尔值表示覆盖层视图是否准备好绘制它的内容。 
- (BOOL)canDrawMapRect:(MKMapRect)mapRect
             zoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);

//绘制覆盖层视图的内容。
- (void)drawMapRect:(MKMapRect)mapRect
          zoomScale:(MKZoomScale)zoomScale
          inContext:(CGContextRef)context NS_DEPRECATED_IOS(4_0, 7_0);

//在所有缩放等级下使给定地图矩形中的视图无效。 
- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect NS_DEPRECATED_IOS(4_0, 7_0);
//只在指定的缩放等级下使给定地图矩形中的视图无效。 
- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect
                       zoomScale:(MKZoomScale)zoomScale NS_DEPRECATED_IOS(4_0, 7_0);

@end

// Road widths are typically not drawn to scale on the map.  This function
// returns the approximate width in points of roads at the specified zoomScale.
// The result of this function is suitable for use with CGContextSetLineWidth.
MK_EXTERN CGFloat MKRoadWidthAtZoomScale(MKZoomScale zoomScale) NS_AVAILABLE(10_9, 4_0);
