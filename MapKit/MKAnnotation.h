//
//  MKAnnotation.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MKFoundation.h>

//用于给地图视图提供标注相关的信息
@protocol MKAnnotation <NSObject>

// 显示标注中心点(经纬度)
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

@optional

// 标注的标题
@property (nonatomic, readonly, copy) NSString *title;
//标注的子标题(字符串将显示在关联标注视图的弹出气泡中)
@property (nonatomic, readonly, copy) NSString *subtitle;

//设置标注新的中心点(经纬度)
- (void)setCoordinate:(CLLocationCoordinate2D)newCoordinate;

@end
