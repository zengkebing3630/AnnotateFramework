//
//  MKMultiPoint.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKShape.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>

MK_CLASS_AVAILABLE(10_9, 4_0)

//一个抽象超类，用于定义由许多点组成的形状。你不应该直接创建本类的实例。
//相反你应该创建 MBpolyline 或 MBPolygon 类的实例，你可以调用本类的方法和属性来获取与线条或多边形关联的指定点的信息
@interface MKMultiPoint : MKShape
//与形状关联的点数组。
- (MKMapPoint *)points NS_RETURNS_INNER_POINTER;
//与形状关联的点数量。 
@property (nonatomic, readonly) NSUInteger pointCount;

//将一个或多个与形状关联的点转换为地图坐标值。
//coords	输入时你必须提供足够大的C数值结构来容纳请求的坐标点数量。输出时，这个结构包含了请求的坐标数据。
//range	你想要的点的范围。“location”元素表示你请求的第一个点，0表示其一个点，1表示第二个点，依此类推。 “length”元素表示你请求的点的数量。coords 中的数组必须足够大以容纳请求的坐标。
- (void)getCoordinates:(CLLocationCoordinate2D *)coords range:(NSRange)range;

@end
