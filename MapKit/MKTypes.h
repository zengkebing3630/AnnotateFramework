//
//  MKTypes.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

typedef NS_ENUM(NSUInteger, MKMapType) {//地图类型
    MKMapTypeStandard = 0,//标准地图，一般情况下使用此地图即可满足
    MKMapTypeSatellite,//卫星地图
    MKMapTypeHybrid//混合地图，加载最慢比较消耗资源
} NS_ENUM_AVAILABLE(10_9, 3_0);

MK_EXTERN NSString *MKErrorDomain;

typedef NS_ENUM(NSUInteger, MKErrorCode) { //错误Code
    MKErrorUnknown = 1,
    MKErrorServerFailure,
    MKErrorLoadingThrottled,
    MKErrorPlacemarkNotFound,
    MKErrorDirectionsNotFound NS_ENUM_AVAILABLE(10_9, 7_0)
} NS_ENUM_AVAILABLE(10_9, 3_0);

