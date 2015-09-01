//
//  MKMapSnapshotOptions.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKMapView.h>

//截图的设置
@interface MKMapSnapshotOptions : NSObject <NSCopying>

@property (nonatomic, copy) MKMapCamera *camera;//视角
@property (nonatomic, assign) MKMapRect mapRect;//地图矩形位置
@property (nonatomic, assign) MKCoordinateRegion region;//区域
@property (nonatomic, assign) MKMapType mapType;//地图类型

@property (nonatomic) BOOL showsPointsOfInterest; // Affects MKMapTypeStandard and MKMapTypeHybrid，是否包含兴趣点
@property (nonatomic) BOOL showsBuildings; // Affects MKMapTypeStandard ,是否包含建筑物

// The size of the image to create. Defaults to 256x256
#if TARGET_OS_IPHONE
@property (nonatomic, assign) CGSize size; //截图尺寸默认 256 * 256
#else
@property (nonatomic, assign) NSSize size;
#endif

#if TARGET_OS_IPHONE
// Defaults to the device's screen scale
@property (nonatomic, assign) CGFloat scale;//截图的倍数，默认是设备[UIScreen mainScreen].scale
#endif

@end
