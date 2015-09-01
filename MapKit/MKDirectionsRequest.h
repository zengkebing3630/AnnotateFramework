//
//  MKDirectionsRequest.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKMapItem.h>
#import <MapKit/MKDirectionsTypes.h>

// MKDirectionRequest对象用于计算路线
//导航请求类
@interface MKDirectionsRequest : NSObject
//起点节点
- (MKMapItem *)source NS_AVAILABLE(10_9, 6_0);
- (void)setSource:(MKMapItem *)source NS_AVAILABLE(10_9, 7_0);
//目的地节点
- (MKMapItem *)destination NS_AVAILABLE(10_9, 6_0);
- (void)setDestination:(MKMapItem *)destination NS_AVAILABLE(10_9, 7_0);

@end

@interface MKDirectionsRequest (MKRequestOptions)
//设置路线检索类型,默认MKDirectionsTransportTypeAny
@property (nonatomic) MKDirectionsTransportType transportType NS_AVAILABLE(10_9, 7_0);
//设置是否搜索多条线路，默认NO
@property (nonatomic) BOOL requestsAlternateRoutes NS_AVAILABLE(10_9, 7_0);

//设置出发日期
@property (nonatomic, copy) NSDate *departureDate NS_AVAILABLE(10_9, 7_0);
//设置到达日期
@property (nonatomic, copy) NSDate *arrivalDate NS_AVAILABLE(10_9, 7_0);

@end

@interface MKDirectionsRequest (MKDirectionsURL)

- (instancetype)initWithContentsOfURL:(NSURL *)url NS_AVAILABLE(10_9, 6_0);
+ (BOOL)isDirectionsRequestURL:(NSURL *)url NS_AVAILABLE(10_9, 6_0);

@end
