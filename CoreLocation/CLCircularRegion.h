/*
 *  CLCircularRegion.h
 *  CoreLocation
 *
 *  Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLRegion.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLAvailability.h>

// 圆形区域
 // 定义了区域类型，但在现在的版本中，只支持圆形区域(是通过区域中心坐标和区域半径实现)。区域半径以米为单位。
@interface CLCircularRegion : CLRegion

使用区域原点，区域半径 和区域标志来初始化一个区域实例。
- (instancetype)initWithCenter:(CLLocationCoordinate2D)center
                            radius:(CLLocationDistance)radius
                        identifier:(NSString *)identifier;

// 区域原点
@property (readonly, nonatomic) CLLocationCoordinate2D center;

//区域半径
@property (readonly, nonatomic) CLLocationDistance radius;

/*
 *  containsCoordinate:
 *
 *  Discussion:
 *    Returns YES if the coordinate lies inside the region, and NO otherwise.
 */
 //圆形区域是否包含位置coordinate，是返回 YES，
- (BOOL)containsCoordinate:(CLLocationCoordinate2D)coordinate;

@end
