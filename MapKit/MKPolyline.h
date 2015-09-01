//
//  MKPolyline.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKMultiPoint.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKFoundation.h>

//表示一个或多个点组成的形状，它用于定义连结的线段。端点的按点数组中的顺序点对点连结。第一个点和最后一个 点没有互相连结。
@interface MKPolyline : MKMultiPoint <MKOverlay>
//使用指定的地图点集合创建并返回MBPolyline对象。
//points	定义这个形状的地图点数组。这个数值的数据将被拷贝到新的对象中。
//count	points 数组中项目的数量。
+ (instancetype)polylineWithPoints:(MKMapPoint *)points count:(NSUInteger)count;
//使用指定的坐标点集合创建并返回MBPolyline对象。
//coords	定义这个形状的坐标点数组。这个数值的数据将被拷贝到新的对象中。
//count	coords 数组中项目的数量。
+ (instancetype)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;
@end
