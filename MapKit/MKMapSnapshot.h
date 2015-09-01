//
//  MKMapSnapshot.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/AppKit.h>
#endif

MK_CLASS_AVAILABLE(10_9, 7_0)

//快照的结果
@interface MKMapSnapshot : NSObject

#if TARGET_OS_IPHONE
@property (nonatomic, readonly) UIImage *image;//截图
- (CGPoint)pointForCoordinate:(CLLocationCoordinate2D)coordinate;//地图上的点转换成 图片上的点
#else
@property (nonatomic, readonly) NSImage *image;
- (NSPoint)pointForCoordinate:(CLLocationCoordinate2D)coordinate;
#endif

@end
