//
//  MKDirectionsResponse.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKDirectionsTypes.h>
#import <CoreLocation/CoreLocation.h>

@class MKMapItem;
@class MKPolyline;

//线路信息结果类
@interface MKDirectionsResponse : NSObject

//起点
@property (nonatomic, readonly) MKMapItem *source;
//终点
@property (nonatomic, readonly) MKMapItem *destination;
//线路规划数组，MKRoute元素
@property (nonatomic, readonly) NSArray *routes;

@end

//线路信息类，导航的线路结果是这个类型的对象
@interface MKRoute : NSObject
//线路名称
@property (nonatomic, readonly) NSString *name; // localized description of the route's significant feature, e.g. "US-101"
//注意事项
@property (nonatomic, readonly) NSArray *advisoryNotices; // localized notices of route conditions as NSStrings. e.g. "Avoid during winter storms"
//距离
@property (nonatomic, readonly) CLLocationDistance distance; // overall route distance in meters
//耗时
@property (nonatomic, readonly) NSTimeInterval expectedTravelTime;
//检索的类型
@property (nonatomic, readonly) MKDirectionsTransportType transportType; // overall route transport type
// 线路覆盖物
@property (nonatomic, readonly) MKPolyline *polyline; // detailed route geometry
// 线路详情数组 ,MKRouteStep 元素
@property (nonatomic, readonly) NSArray *steps; // array of MKRouteStep objects

@end

//线路详情信息类，线路中每一步的信息都是这个类的对象
@interface MKRouteStep : NSObject
// 节点信息
@property (nonatomic, readonly) NSString *instructions; // localized written instructions
// 注意事项
@property (nonatomic, readonly) NSString *notice; // additional localized legal or warning notice related to this step (e.g. "Do not cross tracks when lights flash")
//线路覆盖物
@property (nonatomic, readonly) MKPolyline *polyline; // detailed step geometry
// 距离
@property (nonatomic, readonly) CLLocationDistance distance; // step distance in meters
// 导航类型
@property (nonatomic, readonly) MKDirectionsTransportType transportType; // step transport type (may differ from overall route transport type)

@end

//时间信息结果类
@interface MKETAResponse : NSObject

// Source and destination may be filled with additional details compared to the request object.
//起点
@property (nonatomic, readonly) MKMapItem *source;
//终点
@property (nonatomic, readonly) MKMapItem *destination;
////耗时
@property (nonatomic, readonly) NSTimeInterval expectedTravelTime;

@end
