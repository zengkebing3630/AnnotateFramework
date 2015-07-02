//CBAttribute.h


#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

@class CBUUID;

NS_CLASS_AVAILABLE(N_A, 8_0)
CB_EXTERN_CLASS @interface CBAttribute : NSObject //蓝牙服务属性

/*!
 * @property UUID
 *
 * @discussion
 *      The Bluetooth UUID of the attribute.
 *
 */
@property(readonly, nonatomic) CBUUID *UUID;//蓝牙UUID

@end
