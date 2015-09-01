//
//  MKReverseGeocoder.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKFoundation.h>
#import <MapKit/MKPlacemark.h>

@protocol MKReverseGeocoderDelegate;
/*
    提供服务转化地图坐标点（由经度、维度指定）到那个坐标点信息，例如国家、城市或街道。
  逆地址编码器 对象是一次执行对象连同基于联网的地图服务用于查找指定精度值的兴趣点信息。
 CLGeocoder可以替代
 */
@interface MKReverseGeocoder : NSObject

//使用指定的坐标值初始化逆地址编码器。
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate NS_DEPRECATED_IOS(3_0,5_0);


// A MKReverseGeocoder object should only be started once.
//异步开始逆地址编码进程。 
- (void)start NS_DEPRECATED_IOS(3_0,5_0);
//取消一个即将发生的逆地址编码请求
- (void)cancel NS_DEPRECATED_IOS(3_0,5_0);

//逆地址编码器的委托对象。 
@property (nonatomic, weak) id<MKReverseGeocoderDelegate> delegate    NS_DEPRECATED_IOS(3_0,5_0);
//你想要取得兴趣点信息的坐标。 
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate       NS_DEPRECATED_IOS(3_0,5_0);
//逆地址编码操作的结果
@property (nonatomic, readonly) MKPlacemark *placemark                  NS_DEPRECATED_IOS(3_2,5_0);
//表示接收者是否在逆地址编码坐标的过程中的布尔值。 
@property (nonatomic, readonly, getter=isQuerying) BOOL querying        NS_DEPRECATED_IOS(3_0,5_0);

@end

MK_CLASS_DEPRECATED(NA, NA, 3_0, 5_0)
@protocol MKReverseGeocoderDelegate <NSObject>
@required
//告知委托逆地址编码器对象成功的获取了对应坐标的兴趣点信息。
//geocoder	成功完成请求的逆地址编码器对象。
//placemark	包含兴趣点数据的对象。
- (void)reverseGeocoder:(MKReverseGeocoder *)geocoder didFindPlacemark:(MKPlacemark *)placemark NS_DEPRECATED_IOS(3_0,5_0);
// There are at least two types of errors:
//   - Errors sent up from the underlying connection (temporary condition)
//   - Result not found errors (permanent condition).  The result not found errors
//     will have the domain MKErrorDomain and the code MKErrorPlacemarkNotFound

//告知委托逆地址编码器对象未能获取对应坐标的兴趣点信息。

//geocoder	未能完成请求的逆地址编码器对象。
//error	表示请求未能成功原因的错误对象。
- (void)reverseGeocoder:(MKReverseGeocoder *)geocoder didFailWithError:(NSError *)error NS_DEPRECATED_IOS(3_0,5_0);
@end
