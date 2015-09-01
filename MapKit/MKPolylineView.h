//
//  MKPolylineView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <MapKit/MKPolyline.h>
#import <MapKit/MKOverlayPathView.h>
#import <MapKit/MKFoundation.h>

// Prefer MKPolylineRenderer
//提供了 MBPolygon 标注对象的视觉展示。这个视图填充、描边这个标注表示的区域。
//你可以修改继承自 MBOverlayPathView　 类的属性来更变多边形的颜色或者其它绘制属性。本类通常直接使用而不是子类化。
@interface MKPolylineView : MKOverlayPathView
//使用指定的多边形覆盖层对象初始化并返回一个新的覆盖层视图。
//polygon	包含将要绘制区域信息的多边形覆盖层对象。这个对象必须至少含有三个顶点用于定义多边形，这样才能使视图绘制 对应的路径。
- (instancetype)initWithPolyline:(MKPolyline *)polyline NS_DEPRECATED_IOS(4_0, 7_0);
//包含用于绘制覆盖层信息的多边形覆盖层对象。 
@property (nonatomic, readonly) MKPolyline *polyline NS_DEPRECATED_IOS(4_0, 7_0);

@end
