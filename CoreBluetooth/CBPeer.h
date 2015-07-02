//CBPeer.h
// 蓝牙设备基础信息

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE(N_A, 8_0)
CB_EXTERN_CLASS @interface CBPeer : NSObject <NSCopying>

@property(readonly, nonatomic) CFUUIDRef UUID NS_DEPRECATED(NA, NA, 5_0, 7_0);
// 设备唯一ID
/*!
 *  @property identifier
 *
 *  @discussion The unique, persistent identifier associated with the peer.
 */
@property(readonly, nonatomic) NSUUID *identifier NS_AVAILABLE(NA, 7_0);
//设备注册标示
@end
