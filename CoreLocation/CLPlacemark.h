/*
 *  CLPlacemark.h
 *  CoreLocation
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 */

#if TARGET_OS_IPHONE

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>

@class CLLocation;
@class CLRegion;
@class CLPlacemarkInternal;

// 代表了一个地理位置上的地方信息，这些地区信息，可以是国家，州，城市和街道名称
@interface CLPlacemark : NSObject <NSCopying, NSSecureCoding>
{
@private
    CLPlacemarkInternal *_internal;
}

// 使用一个地区信息来初始化
- (instancetype)initWithPlacemark:(CLPlacemark *)placemark;

// 返回这个地区信息的位置信息。
@property (nonatomic, readonly, copy) CLLocation *location;

// 返回一个地区信息的区域位置
@property (nonatomic, readonly, copy) CLRegion *region;

// 返回一个ABCreateStringWithAddressDictionary表示的地址字典类型。
@property (nonatomic, readonly, copy) NSDictionary *addressDictionary;

// 以上为地址信息
@property (nonatomic, readonly, copy) NSString *name; // 地名
@property (nonatomic, readonly, copy) NSString *thoroughfare; // 街道
@property (nonatomic, readonly, copy) NSString *subThoroughfare; //街道相关信息，例如门牌等
@property (nonatomic, readonly, copy) NSString *locality; //城市
@property (nonatomic, readonly, copy) NSString *subLocality; // 城市相关信息，例如标志性建筑
@property (nonatomic, readonly, copy) NSString *administrativeArea; // 州
@property (nonatomic, readonly, copy) NSString *subAdministrativeArea; // 其他行政区域信息
@property (nonatomic, readonly, copy) NSString *postalCode; // 邮编
@property (nonatomic, readonly, copy) NSString *ISOcountryCode; // 国家编码 US
@property (nonatomic, readonly, copy) NSString *country; // 国家
@property (nonatomic, readonly, copy) NSString *inlandWater; // 水源、湖泊
@property (nonatomic, readonly, copy) NSString *ocean; //海洋
@property (nonatomic, readonly, copy) NSArray *areasOfInterest; ///关联的或利益相关的地标 Golden Gate Park
@end

#endif //TARGET_OS_IPHONE
