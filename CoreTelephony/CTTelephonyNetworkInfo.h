/*
 *  CTTelephonyNetworkInfo.h
 *  CoreTelephony
 *
 *  Copyright 2009 Apple, Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyDidChangeNotification;

/*
 * Radio Access Technology values
 */
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyGPRS         //GPRS;
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyEdge          __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyWCDMA         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyHSDPA         //3G;
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyHSUPA         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMA1x        __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORev0  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORevA  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyCDMAEVDORevB  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyeHRPD         __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
CORETELEPHONY_EXTERN NSString * const CTRadioAccessTechnologyLTE           __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

@class CTCarrier;


//主要用于更换SIM卡时电信运营商信息的获取

@interface CTTelephonyNetworkInfo : NSObject

// 一个CTCarrier对象，具体包含内容参考CTCarrier Class
@property(readonly, retain) CTCarrier *subscriberCellularProvider;

//当电信运营商改变时进行回调的接口。
@property(nonatomic, copy) void (^subscriberCellularProviderDidUpdateNotifier)(CTCarrier*);

 /*
	用来判断手机当前的网络类型，是edge还是LTE或其他,以下三种情况为nil
	1、设备处于飞行模式

	2、检测不到SIM卡

	3、无电信信号
 */
@property (nonatomic, readonly, retain) NSString* currentRadioAccessTechnology;

@end
