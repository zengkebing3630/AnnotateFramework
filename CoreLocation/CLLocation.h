/*
 *  CLLocation.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

/*
	以WGS84(World Geodetic System一1984 Coordinate System)坐标系统为基础，以度为单位，代表了经度或者纬度的类型。
度数可以是正的，代表了北方和东方；或者为负值，代表了南方和西方。
*/
typedef double CLLocationDegrees;

// 用来代表以米为单位的位置精度类型，越低的值，代表越精确的位置信息，不允许负值。
typedef double CLLocationAccuracy;

// 代表了设备以m/s为单位的移动速度类型。
typedef double CLLocationSpeed;

// 定义了以度为单位的方向类型，取值范围为0~359.9，不允许负值。
typedef double CLLocationDirection;

// 定义了二位的平面坐标系，以经度和纬度为坐标方向。
typedef struct {
	CLLocationDegrees latitude;
	CLLocationDegrees longitude;
} CLLocationCoordinate2D;

// 定义了以米为单位的距离类型。
typedef double CLLocationDistance;

// 定义CLLocationManager中使用的距离过滤器，表明定位服务是否过滤最小移动距离，如果不过滤，用户的任何移动都会被通知。
extern const CLLocationDistance kCLDistanceFilterNone;//不进行距离限制

// 定义定位精度枚举，更精确级别的定位对移动设备意味着更多的能耗和时间，所以对于应用需要的精度，选择合适的定位精度。
extern const CLLocationAccuracy kCLLocationAccuracyBestForNavigation;//导航最精确定位
extern const CLLocationAccuracy kCLLocationAccuracyBest;//最精确定位
extern const CLLocationAccuracy kCLLocationAccuracyNearestTenMeters;//十米误差范围
extern const CLLocationAccuracy kCLLocationAccuracyHundredMeters;//百米误差范围
extern const CLLocationAccuracy kCLLocationAccuracyKilometer;//千米误差范围
extern const CLLocationAccuracy kCLLocationAccuracyThreeKilometers;//三千米误差范围

// 用来指定设备支持的最长距离。
extern const CLLocationDistance CLLocationDistanceMax;

// 用来指定设备支持的最大时间跨度。
extern const NSTimeInterval CLTimeIntervalMax;

// 用来指定非法的二维坐标。
extern const CLLocationCoordinate2D kCLLocationCoordinate2DInvalid;

#ifdef __cplusplus
extern "C" {
#endif    

// 用来判断一个二维坐标是否合法。
BOOL CLLocationCoordinate2DIsValid(CLLocationCoordinate2D coord);

// 使用经度和纬度值来创建一个二维坐标。
CLLocationCoordinate2D CLLocationCoordinate2DMake(CLLocationDegrees latitude, CLLocationDegrees longitude);

#ifdef __cplusplus
}
#endif

// 室内定位技术
NS_CLASS_AVAILABLE(NA, 8_0)
@interface CLFloor : NSObject <NSCopying, NSSecureCoding>

/*
	level = 0;表示地面、
	level < 0 ,表示地下
	level > 0 ,表示地面以上的楼层
	不能作为高度的估计值,楼层信息
	一个整形值来表示当前位置处于建筑物的第几层楼。
*/
@property(readonly, nonatomic) NSInteger level;

@end

// 代表带有精度和时间信息的地理坐标。
@interface CLLocation : NSObject <NSCopying, NSSecureCoding>
{
@private
	id _internal;
}

// 使用经度和纬度来初始化一个CLLocation类型。
- (instancetype)initWithLatitude:(CLLocationDegrees)latitude
	longitude:(CLLocationDegrees)longitude;

// 使用经度纬度，当前的距离,及在水平和竖直方向的精度、时间戳来初始化 一个CLLocation实例
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate
	altitude:(CLLocationDistance)altitude
	horizontalAccuracy:(CLLocationAccuracy)hAccuracy
	verticalAccuracy:(CLLocationAccuracy)vAccuracy
	timestamp:(NSDate *)timestamp;

// 使用经度纬度，当前的距离,及在水平和竖直方向的精度、时间戳,相对地理北极的偏度,速度来初始化 一个CLLocation实例
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate
    altitude:(CLLocationDistance)altitude
    horizontalAccuracy:(CLLocationAccuracy)hAccuracy
    verticalAccuracy:(CLLocationAccuracy)vAccuracy
    course:(CLLocationDirection)course
    speed:(CLLocationSpeed)speed
    timestamp:(NSDate *)timestamp;

// 返回当前的二维位置信息，即经度和纬度。
@property(readonly, nonatomic) CLLocationCoordinate2D coordinate;

// 返回当前的距离，正值表示海平面以上的距离，负值表示海平面以下的距离
@property(readonly, nonatomic) CLLocationDistance altitude;

// 返回当前的水平精度，负值表示当前纬度非法
@property(readonly, nonatomic) CLLocationAccuracy horizontalAccuracy;

// 返回当前的垂直精度，负值表示经度非法。
@property(readonly, nonatomic) CLLocationAccuracy verticalAccuracy;

// 返回相对地理北极的偏度，取值范围在0~359.9，负值非法。
@property(readonly, nonatomic) CLLocationDirection course;

// 返回当前设备的移动速度。
@property(readonly, nonatomic) CLLocationSpeed speed;

// 返回当前位置点的定位时间。
@property(readonly, nonatomic, copy) NSDate *timestamp;

//如果floor不支持，floor == nil、室内定位信息
@property(readonly, nonatomic, copy) CLFloor *floor __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);

//location 描述
@property (nonatomic, readonly, copy) NSString *description;

// 返回两个位置间的横向位置(应当是欧氏距离吧)。
- (CLLocationDistance)getDistanceFrom:(const CLLocation *)location;

// 返回两个位置间的横向位置(应当是欧氏距离吧)。
- (CLLocationDistance)distanceFromLocation:(const CLLocation *)location;

@end
