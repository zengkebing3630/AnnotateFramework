
/*
 *  CLHeading.h
 *  CoreLocation
 *
 *  Copyright 2008 Apple, Inc. All rights reserved.
 *
 */

#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLLocation.h>
#import <Foundation/Foundation.h>

// 代表一个地理磁场数据类型，以微特斯拉为单位，在三维空间确定设备的坐标。
typedef double CLHeadingComponentValue;

// CLLocationManager用作为方位信息的过滤标志，表明不需要过滤最小移动量，用户的任何移动都会被通知。
extern const CLLocationDegrees kCLHeadingFilterNone;

//代表了一个可以通过(x,y,z)三维空间坐标确定磁北极位置的向量。精确的Heading(方位)定位，同时也需要时间信息(即通过空间加时间四维坐标来确定位置)
@interface CLHeading : NSObject <NSCopying, NSSecureCoding>
{
@private
    id _internal;
}

/*
以度数来代表方向，0度代表磁北极方位，方向是参照设备的上部方向，不考虑设备的摆放方向，也不考虑用户的面对方向。
度数的范围为0~359.9
*/
@property(readonly, nonatomic) CLLocationDirection magneticHeading;

/*
	以度数来代表方向，0度表示真正的北极方向，方向是参照设备的上部方向，不考虑设备的摆放方向，也不考虑用户的面对方向。
度数的范围是0~359.9
众所周知，磁北极方向和地球北极方向是不重合的，所以，这里有必要区分magnetHeading和trueHeading.
*/
@property(readonly, nonatomic) CLLocationDirection trueHeading;

// 代表了magnetHeading(磁北极方向)和真正的trueHeading(地理北极)在以度为度量单位上的最大偏差。不能取负值。
@property(readonly, nonatomic) CLLocationDirection headingAccuracy;

/*
 分别代表了三维空间位置坐标和时间坐标。
 */
@property(readonly, nonatomic) CLHeadingComponentValue x;

@property(readonly, nonatomic) CLHeadingComponentValue y;

@property(readonly, nonatomic) CLHeadingComponentValue z;

@property(readonly, nonatomic, copy) NSDate *timestamp;

// CLHeading描述
@property (nonatomic, readonly, copy) NSString *description;

@end
