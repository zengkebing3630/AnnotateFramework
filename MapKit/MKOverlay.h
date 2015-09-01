//
//  MKOverlay.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKGeometry.h>

/*
 定义了一种在地图中表示点和区域的特定标注。
 覆盖层对象本质上是包含需要在地图区域中显示的地理数据的数据对象。
 例如，覆盖层可能是诸如矩形和圆形的常见形状。
 也可能是多边形或者其它复杂的形状。
 你可以使用覆盖层在地图视图上显示更加复杂的内容。
 例如，你可以使用覆盖层来显示一个国家公园的边界或者是城市街道中的公交线路。
 Map Kit框架定义了一些具体的遵守本协议的具有标准形状的类。
 因为覆盖层同时也是标注。它们的使用方式和标注相似。
 当调用addOverlay方法向地图视图中添加覆盖层视图时，视图会随时检测覆盖层的范围是否和地图的可视部分相交。
 如果相交,地图视图请求自己的委托提供特殊的覆盖层视图用于绘制覆盖层。
 如果你以标注的方式向地图添加了一个覆盖层，地图视图将把它视为一个只有一个独立点的标注
 */
@protocol MKOverlay <MKAnnotation>
@required

//覆盖层范围的适当中心点。
//这个点一般是地图边框的中心。它作为显示标注弹出气泡的固定点。对于一块区域将返回这个区域的质心。
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

// boundingMapRect应包含的最小矩形完全覆盖。
//当然overlay跨度超过180th，boundingMapRect的MinX|MaxX 大于MKMapSizeWorld.width.
//包含覆盖层的投影矩形。
//本属性是完全包含覆盖层范围的最小矩形。在实现覆盖层类的时候必须完成本协议来设置覆盖层的范围。矩形应该使用投影的坐标系 来指定，通过把地球投影到一个二维的平面来取得这个坐标系。
@property (nonatomic, readonly) MKMapRect boundingMapRect;

@optional
//实现intersectsMapRect提供对覆盖物更精确的控制
//如果省略,会自动调用MKMapRectIntersectsRect([overlay boundingRect], mapRect)
//返回一个布尔值表示指定的矩形是否和接收者的形状相交。
//mapRect	和接收者范围判断相交的矩形
- (BOOL)intersectsMapRect:(MKMapRect)mapRect;

//返回YES,Map跳过加载或绘制所建的地图内容覆盖在该地区覆盖。
- (BOOL)canReplaceMapContent NS_AVAILABLE(10_9, 7_0);

@end
