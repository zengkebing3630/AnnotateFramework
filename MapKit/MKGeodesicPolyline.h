//
//  MKGeodesicPolyline.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKPolyline.h>

/*
 一个MKGeodesicPolyline遵循最短路径沿地球表面，
 这可能看起来像一个弯曲的线时，画在投影MKMapView。
 */
MK_CLASS_AVAILABLE(10_9, 7_0)

@interface MKGeodesicPolyline : MKPolyline
//以多点，count显示点的个数 ，最短路径

+ (instancetype)polylineWithPoints:(MKMapPoint *)points count:(NSUInteger)count;
//以坐标数组，count显示点的个数 ，最短路径
+ (instancetype)polylineWithCoordinates:(CLLocationCoordinate2D *)coords count:(NSUInteger)count;

@end
