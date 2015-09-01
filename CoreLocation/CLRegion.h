/*
 *  CLRegion.h
 *  CoreLocation
 *
 *  Copyright (c) 2009-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLAvailability.h>

/*
 * CLRegionState
 *
 * Discussion:
 *    Represents the current state of the device with reference to a region.
 *
 */
typedef NS_ENUM(NSInteger, CLRegionState) {
	CLRegionStateUnknown,
	CLRegionStateInside,
	CLRegionStateOutside
} NS_ENUM_AVAILABLE_IOS(7_0);

/*
 * CLProximity
 *
 * Discussion:
 *    Represents the current proximity of an entity.
 *
 */
typedef NS_ENUM(NSInteger, CLProximity) {
	CLProximityUnknown,
	CLProximityImmediate,
	CLProximityNear,
	CLProximityFar
} NS_ENUM_AVAILABLE_IOS(7_0);

// 定义了区域类型，但在现在的版本中，只支持圆形区域(是通过区域中心坐标和区域半径实现)。区域半径以米为单位。
@interface CLRegion : NSObject <NSCopying, NSSecureCoding>

// 使用区域原点，区域半径 和区域标志来初始化一个区域实例。
- (instancetype)initCircularRegionWithCenter:(CLLocationCoordinate2D)center
									  radius:(CLLocationDistance)radius
								  identifier:(NSString *)identifier;
// 区域原点
@property (readonly, nonatomic) CLLocationCoordinate2D center;

// 区域半径
@property (readonly, nonatomic) CLLocationDistance radius;

// 区域标志
@property (readonly, nonatomic, copy) NSString *identifier;

/*
 *  notifyOnEntry
 *
 *  Discussion:
 *    App will be launched and the delegate will be notified via locationManager:didEnterRegion:
 *    when the user enters the region. By default, this is YES.
 */
 //用户进入区域通知，locationManager:didEnterRegion:，默认YES
@property (nonatomic, assign) BOOL notifyOnEntry __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

 //用户走出区域通知，locationManager:didExitRegion:，默认YES
@property (nonatomic, assign) BOOL notifyOnExit __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

// 判断一个坐标点是否在该区域内部。
- (BOOL)containsCoordinate:(CLLocationCoordinate2D)coordinate;

@end
