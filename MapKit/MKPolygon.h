//
//  MKPolygon.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKOverlay.h>

/*表示由一个或多个点组成的形状，它用于定义封闭多边形。端点的按点数组中的顺序点对点连结。
第一个点和最后一个点 互相连结以创建这个封闭形状。
创建多边形时，你可以指定一个或多个内嵌多边形来遮盖这个多边形的部分区域。
被内嵌矩形遮盖的部 分将不被视为这个多边形的一部分。
*/
@interface MKPolygon : MKMultiPoint <MKOverlay>
//使用指定的地图点集合创建并返回MBPolygon对象。

//coords	定义这个形状的坐标点数组。这个数值的数据将被拷贝到新的对象中。
//count	coords 数组中项目的数量。
+ (instancetype)polygonWithPoints:(MKMapPoint *)points count:(NSUInteger)count;

//使用指定的地图点集合创建并返回MBPolygon对象。

//coords	定义这个形状的地图点数组。这个数值的数据将被拷贝到新的对象中。
//count	points 数组中项目的数量。
//interiorPolygons	定义了接收者多边形一个或多个裁剪区域的MBPolygon对象数组。
+ (instancetype)polygonWithPoints:(MKMapPoint *)points count:(NSUInteger)count interiorPolygons:(NSArray *)interiorPolygons;

//使用指定的地图点集合创建并返回MBPolygon对象。
//points	定义这个形状的地图点数组。这个数值的数据将被拷贝到新的对象中。
//count	points 数组中项目的数量。
+ (instancetype)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

//使用指定的地图点集合创建并返回MBPolygon对象。
//points	定义这个形状的地图点数组。这个数值的数据将被拷贝到新的对象中。
//count	points 数组中项目的数量。
//interiorPolygons	定义了接收者多边形一个或多个裁剪区域的MBPolygon对象数组。
+ (instancetype)polygonWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count interiorPolygons:(NSArray *)interiorPolygons;

//嵌在接收者中的一组多边形。
//当多边形在屏幕中时，被内嵌多边形标记的区域将不被视为多边形的一部分。
@property (readonly) NSArray *interiorPolygons;

@end
