/*
 *  CLGeocoder.h
 *  CoreLocation
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 */

#if TARGET_OS_IPHONE

#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLAvailability.h>

@class CLRegion;
@class CLPlacemark;
@class CLGeocoderInternal;

// 定义地理编码处理器
typedef void (^CLGeocodeCompletionHandler)(NSArray *placemarks, NSError *error);

// 地理位置编码器。
@interface CLGeocoder : NSObject
{
@private
    CLGeocoderInternal *_internal;
}
// 判断是否在进行位置编码。
@property (nonatomic, readonly, getter=isGeocoding) BOOL geocoding;

// 翻转解码请求。地理解码是通过地址信息，解析出定位坐标，而这里是通过定位坐标解析出placemark。
- (void)reverseGeocodeLocation:(CLLocation *)location completionHandler:(CLGeocodeCompletionHandler)completionHandler;

// 通过地址信息，和区域位置解析出定位坐标。
- (void)geocodeAddressDictionary:(NSDictionary *)addressDictionary completionHandler:(CLGeocodeCompletionHandler)completionHandler;
- (void)geocodeAddressString:(NSString *)addressString completionHandler:(CLGeocodeCompletionHandler)completionHandler;
- (void)geocodeAddressString:(NSString *)addressString inRegion:(CLRegion *)region completionHandler:(CLGeocodeCompletionHandler)completionHandler;

// 取消当前解码请求
- (void)cancelGeocode;

@end
#endif //TARGET_OS_IPHONE
