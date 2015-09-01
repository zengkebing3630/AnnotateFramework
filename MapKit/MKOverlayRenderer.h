//
//  MKOverlayRenderer.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKOverlay.h>

//覆盖物渲染器
@interface MKOverlayRenderer : NSObject
//初始化并返回与指定覆盖层对象关联的覆盖层视图。
- (instancetype)initWithOverlay:(id <MKOverlay>)overlay NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) id <MKOverlay> overlay;

//返回指定地图点在覆盖层视图中对应的点。
- (CGPoint)pointForMapPoint:(MKMapPoint)mapPoint;
//返回指定覆盖层视图中的点对应的地图点。 
- (MKMapPoint)mapPointForPoint:(CGPoint)point;

//指定地图矩形在覆盖层视图中对应的视图坐标
- (CGRect)rectForMapRect:(MKMapRect)mapRect;
//返回指定覆盖层视图坐标系中矩形对应的地图矩形。 
- (MKMapRect)mapRectForRect:(CGRect)rect;

//返回布尔值表示覆盖层视图是否准备好绘制它的内容。
//mapRect:地图矩形
//zoomScale:缩放级别
- (BOOL)canDrawMapRect:(MKMapRect)mapRect
             zoomScale:(MKZoomScale)zoomScale;
//绘制覆盖层视图的内容。
//mapRect:地图矩形
//zoomScale:缩放级别
//context:上下文
- (void)drawMapRect:(MKMapRect)mapRect
          zoomScale:(MKZoomScale)zoomScale
          inContext:(CGContextRef)context;

//重新渲染地图
- (void)setNeedsDisplay;
//重新渲染MapRect范围的视图
- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect;
//重新渲染MapRect范围的视图，zoomScale:缩放级别
- (void)setNeedsDisplayInMapRect:(MKMapRect)mapRect
                       zoomScale:(MKZoomScale)zoomScale;

//透明度
@property CGFloat alpha;

//缩放比例
@property (readonly) CGFloat contentScaleFactor;

@end

// Road widths are typically not drawn to scale on the map.  This function
// returns the approximate width in points of roads at the specified zoomScale.
// The result of this function is suitable for use with CGContextSetLineWidth.
MK_EXTERN CGFloat MKRoadWidthAtZoomScale(MKZoomScale zoomScale) NS_AVAILABLE(10_9, 4_0);
