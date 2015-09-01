//
//  MKCircle.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKShape.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKFoundation.h>

//是一个具体的覆盖层对象，它用于在地图中展示一个圆形区域。
//本类管理定义这个区域的数据，同时在处理地图中的圆形 绘制时它一般配合 MBCircleView 对象使用
@interface MKCircle : MKShape <MKOverlay>
//以中心坐标 ，半径初始化 一个圆区域
+ (instancetype)circleWithCenterCoordinate:(CLLocationCoordinate2D)coord
                                  radius:(CLLocationDistance)radius;
//一个mapRect矩形区域初始化，中心坐标在矩形中心，半径是MAX(width, height)
//mapRect	决定圆形区域的地图矩形。矩形的中心点用作圆形的中心点。如果矩形不是正方形，矩形的长边用来决定圆形的半径。
+ (instancetype)circleWithMapRect:(MKMapRect)mapRect;

//地理坐标
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
//半径
@property (nonatomic, readonly) CLLocationDistance radius;
//圆形区域的边界矩形
//当维度从赤道像极地移动时，地图点的物理距离逐渐变小。
//这就意味着需要更多的地图点来表示同样的距离。结果圆形覆盖层的边界 矩形随着圆形中心点从赤道像极地移动而越来越大
@property (nonatomic, readonly) MKMapRect boundingMapRect;

@end
