/*
 *  CLVisit.h
 *  CoreLocation
 *
 *  Copyright (c) 2014 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>

// 表示该用户已经处于某个位置的时间长度，包括一个坐标和开始/结束的时间戳。
NS_CLASS_AVAILABLE(NA, 8_0)
@interface CLVisit : NSObject <NSSecureCoding, NSCopying>

//visti监控开始，监控开始日期 ,当然arriveDate不可用,arrivalDate ==  [NSDate distantPast]
@property (nonatomic, readonly, copy) NSDate *arrivalDate;

//visti监控结束日期 ,当然device没有离开,arrivalDate ==  [NSDate distantFuture]
@property (nonatomic, readonly, copy) NSDate *departureDate;

// 平均坐标
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

 //水平精度 （单位 米）
@property (nonatomic, readonly) CLLocationAccuracy horizontalAccuracy;
@end
