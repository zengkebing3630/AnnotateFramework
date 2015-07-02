//CBService.h


#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAttribute.h>

@class CBPeripheral, CBUUID;

/*!
 * @class CBService
 *
 * @discussion
 *      Represents a peripheral's service or a service's included service.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBService : CBAttribute  //蓝牙服务

/*!
 * @property peripheral
 *
 * @discussion
 *      A back-pointer to the peripheral this service belongs to.
 *
 */
 //表明服务属于哪个peripheral，一个peripheral可以有多个服务
@property(weak, readonly, nonatomic) CBPeripheral *peripheral;

/*!
 * @property isPrimary
 *
 * @discussion
 *      The type of the service (primary or secondary).
 *
 */
 //标识CBService是主要的服务还是次要的。
//解释：一个周边peripheral的服务可以是主要的也可以是次要的。
 //主要的服务描述了设备的主要功能并且可以包含另外一个服务。
 //次要服务描述了服务唯一相关和另一个服务额应用。
 //如心率检测器的主要服务是显示心率监测数据，而第二个服务可能是显示电池数据，
 //如果属性是Yes那么服务就是主要类型
@property(readonly, nonatomic) BOOL isPrimary;//是否是主要服务

/*!
 * @property includedServices
 *
 * @discussion
 *      A list of included CBServices that have so far been discovered in this service.
 *
 */
 //服务可能包含服务，那么includedServices就是服务所包含的服务（层级关系）
@property(retain, readonly) NSArray *includedServices;//包含服务列表

/*!
 * @property characteristics
 *
 * @discussion
 *      A list of CBCharacteristics that have so far been discovered in this service.
 *
 */
 //包含服务的characteristic
@property(retain, readonly) NSArray *characteristics;//服务特征列表

@end


/*!
 * @class CBMutableService
 *
 * @discussion
 *      Used to create a local service or included service, which can be added to the local database via <code>CBPeripheralManager</code>.
 *		Once a service is published, it is cached and can no longer be changed. This class adds write access to all properties in the
 *		@link CBService @/link class.
 *
 */
NS_CLASS_AVAILABLE(NA, 6_0)
CB_EXTERN_CLASS @interface CBMutableService : CBService //可变服务器

@property(retain, readwrite, nonatomic) CBUUID *UUID;//服务的UUID标识
@property(readwrite, nonatomic) BOOL isPrimary;//是否主要服务
@property(retain, readwrite) NSArray *includedServices;//提供服务
@property(retain, readwrite) NSArray *characteristics;//特征列表

/*!
 *  @method initWithType:primary:
 *
 *  @param UUID			The Bluetooth UUID of the service.
 *  @param isPrimary	The type of the service (primary or secondary).
 *
 *  @discussion			Returns a service, initialized with a service type and UUID.
 *
 */
- (instancetype)initWithType:(CBUUID *)UUID primary:(BOOL)isPrimary NS_DESIGNATED_INITIALIZER; //以UUID，是否主要服务初始化

@end
