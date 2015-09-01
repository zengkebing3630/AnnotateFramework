/*
 *  CTCarrier.h
 *  CoreTelephony
 *
 *  Copyright 2009 Apple, Inc.. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreTelephony/CoreTelephonyDefines.h>

//是对电信运营商信息的一个封装
@interface CTCarrier : NSObject

 /*
	电信运营商的名字，除非没有插入过SIM卡，否则这个值将是当前SIM卡或上一SIM卡（当前设备内无SIM卡）电信运营商的名字。
 */
@property (nonatomic, readonly, retain) NSString *carrierName;

 /*
	记录移动国家码（MMC），由三位数字组成，
	唯一地识别移动用户所属的国家，我国为460。值得注意的是这个属性的类型是NSString而非数值。
 */
@property (nonatomic, readonly, retain) NSString *mobileCountryCode;

 /*
	记录移动网络码（MNC）由两位数字组成，用于识别移动用户所归属的移动网。
	中国移动TD系统使用00，
	中国联通GSM系统使用01，
	中国移动GSM系统使用02，
	中国电信CDMA系统使用03
 */
@property (nonatomic, readonly, retain) NSString *mobileNetworkCode;

/*
	使用ISO 3166-1标准的国家码标识电信运营商的所属国家。处于nil值状态的情况同allowsVOIP。
*/
@property (nonatomic, readonly, retain) NSString* isoCountryCode;


/*
 用以标识电信运营商是否支持网络电话（VOIP），而在以下三种情况下这个值将为NO。

1、设备处于飞行模式

2、检测不到SIM卡

3、无电信信号
*/
@property (nonatomic, readonly, assign) BOOL allowsVOIP;

@end

