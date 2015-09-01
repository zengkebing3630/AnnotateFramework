//
//  MKDirectionsTypes.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

typedef NS_OPTIONS(NSUInteger, MKDirectionsTransportType) {
    MKDirectionsTransportTypeAutomobile     = 1 << 0,//适合驾车时导航
    MKDirectionsTransportTypeWalking        = 1 << 1,//适合步行时导航
    MKDirectionsTransportTypeAny            = 0x0FFFFFFF//任何情况
} NS_ENUM_AVAILABLE(10_9, 7_0);
