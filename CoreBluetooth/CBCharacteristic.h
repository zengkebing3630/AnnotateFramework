//CBCharacteristic.h

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBAttribute.h>

/*!
 *  @enum CBCharacteristicProperties
 *
 *	@discussion Characteristic properties determine how the characteristic value can be	used, or how the descriptor(s) can be accessed. Can be combined. Unless
 *				otherwise specified, properties are valid for local characteristics published via @link CBPeripheralManager @/link.
 *
 *	@constant CBCharacteristicPropertyBroadcast						Permits broadcasts of the characteristic value using a characteristic configuration descriptor. Not allowed for local characteristics.
 *	@constant CBCharacteristicPropertyRead							Permits reads of the characteristic value.
 *	@constant CBCharacteristicPropertyWriteWithoutResponse			Permits writes of the characteristic value, without a response.
 *	@constant CBCharacteristicPropertyWrite							Permits writes of the characteristic value.
 *	@constant CBCharacteristicPropertyNotify						Permits notifications of the characteristic value, without a response.
 *	@constant CBCharacteristicPropertyIndicate						Permits indications of the characteristic value.
 *	@constant CBCharacteristicPropertyAuthenticatedSignedWrites		Permits signed writes of the characteristic value
 *	@constant CBCharacteristicPropertyExtendedProperties			If set, additional characteristic properties are defined in the characteristic extended properties descriptor. Not allowed for local characteristics.
 *	@constant CBCharacteristicPropertyNotifyEncryptionRequired		If set, only trusted devices can enable notifications of the characteristic value.
 *	@constant CBCharacteristicPropertyIndicateEncryptionRequired	If set, only trusted devices can enable indications of the characteristic value.
 *
 */
typedef NS_OPTIONS(NSUInteger, CBCharacteristicProperties) { //特征属性
	CBCharacteristicPropertyBroadcast												= 0x01,// 标识这个characteristic的属性是广播
	CBCharacteristicPropertyRead													= 0x02,// 标识这个characteristic的属性是读
	CBCharacteristicPropertyWriteWithoutResponse									= 0x04,// 标识这个characteristic的属性是写-没有响应
	CBCharacteristicPropertyWrite													= 0x08,// 标识这个characteristic的属性是写
	CBCharacteristicPropertyNotify													= 0x10,// 标识这个characteristic的属性是通知
	CBCharacteristicPropertyIndicate												= 0x20,// 标识这个characteristic的属性是声明
	CBCharacteristicPropertyAuthenticatedSignedWrites							    = 0x40,// 标识这个characteristic的属性是通过验证的	
	CBCharacteristicPropertyExtendedProperties										= 0x80,// 标识这个characteristic的属性是拓展
	CBCharacteristicPropertyNotifyEncryptionRequired NS_ENUM_AVAILABLE(NA, 6_0)		= 0x100,// 标识这个characteristic的属性是需要加密的通知
	CBCharacteristicPropertyIndicateEncryptionRequired NS_ENUM_AVAILABLE(NA, 6_0)	= 0x200 // 标识这个characteristic的属性是需要加密的申明
};



@class CBService, CBUUID;

/*!
 *  @class CBCharacteristic
 *
 *  @discussion
 *      Represents a service's characteristic.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBCharacteristic : CBAttribute

/*!
 * @property service
 *
 *  @discussion
 *      A back-pointer to the service this characteristic belongs to.
 *
 */

@property(weak, readonly, nonatomic) CBService *service; //服务,表明这个属于哪个service

/*!
 * @property properties
 *
 *  @discussion
 *      The properties of the characteristic.
 *
 */
@property(readonly, nonatomic) CBCharacteristicProperties properties; //属性

/*!
 * @property value
 *
 *  @discussion
 *      The value of the characteristic.
 *
 */
@property(retain, readonly) NSData *value; //特征值

/*!
 * @property descriptors
 *
 *  @discussion
 *      A list of the CBDescriptors that have so far been discovered in this characteristic.
 *
 */
@property(retain, readonly) NSArray *descriptors; //描述符列表

/*!
 * @property isBroadcasted
 *
 *  @discussion
 *      Whether the characteristic is currently broadcasted or not.
 *
 */
@property(readonly) BOOL isBroadcasted NS_DEPRECATED(NA, NA, 5_0, 8_0);//此刻是否正在广播

/*!
 * @property isNotifying
 *
 *  @discussion
 *      Whether the characteristic is currently notifying or not.
 *
 */
@property(readonly) BOOL isNotifying;//是否正在通知

@end

/*!
 *  @enum CBAttributePermissions
 *
 *	@discussion Read, write, and encryption permissions for an ATT attribute. Can be combined.
 *
 *	@constant CBAttributePermissionsReadable					Read-only.
 *	@constant CBAttributePermissionsWriteable					Write-only.
 *	@constant CBAttributePermissionsReadEncryptionRequired		Readable by trusted devices.
 *	@constant CBAttributePermissionsWriteEncryptionRequired		Writeable by trusted devices.
 *
 */
typedef NS_OPTIONS(NSUInteger, CBAttributePermissions) {//特征输入接受数据  权限
	CBAttributePermissionsReadable					= 0x01,// 可读的
	CBAttributePermissionsWriteable					= 0x02,// 可写的
	CBAttributePermissionsReadEncryptionRequired	= 0x04, // 需读验证
	CBAttributePermissionsWriteEncryptionRequired	= 0x08 // 需写验证
} NS_ENUM_AVAILABLE(NA, 6_0);


/*!
 *	@class CBMutableCharacteristic
 *
 *	@discussion Used to create a local characteristic, which can be added to the local database via <code>CBPeripheralManager</code>. Once a characteristic
 *				is published, it is cached and can no longer be changed. 
 *				If a characteristic value is specified, it will be cached and marked <code>CBCharacteristicPropertyRead</code> and 
 *				<code>CBAttributePermissionsReadable</code>. If a characteristic value needs to be writeable, or may change during the lifetime of the
 *				published <code>CBService</code>, it is considered a dynamic value and will be requested on-demand. Dynamic values are identified by a
 *				<i>value</i> of <i>nil</i>.
 *
 */
NS_CLASS_AVAILABLE(NA, 6_0)
CB_EXTERN_CLASS @interface CBMutableCharacteristic : CBCharacteristic //可变特征

/*!
 *	@property permissions
 *
 *	@discussion The permissions of the characteristic value.
 *
 *	@see		CBAttributePermissions
 */
@property(assign, readwrite, nonatomic) CBAttributePermissions permissions; // 权限

/*!
 *  @property subscribedCentrals
 *
 *  @discussion For notifying characteristics, the set of currently subscribed centrals.
 */
@property(retain, readonly) NSArray *subscribedCentrals NS_AVAILABLE(NA, 7_0);//订阅这个characteristic的central

@property(retain, readwrite, nonatomic) CBUUID *UUID; //characteristic的UUID标识

@property(assign, readwrite, nonatomic) CBCharacteristicProperties properties; //属性
@property(retain, readwrite) NSData *value; //特征值
@property(retain, readwrite) NSArray *descriptors;//描述符

/*!
 *  @method initWithType:properties:value:permissions
 *
 *  @param UUID			The Bluetooth UUID of the characteristic.
 *  @param properties	The properties of the characteristic.
 *  @param value		The characteristic value to be cached. If <i>nil</i>, the value will be dynamic and requested on-demand.
 *	@param permissions	The permissions of the characteristic value.
 *
 *  @discussion			Returns an initialized characteristic.
 *
 */
 //初始化
- (instancetype)initWithType:(CBUUID *)UUID properties:(CBCharacteristicProperties)properties value:(NSData *)value permissions:(CBAttributePermissions)permissions NS_DESIGNATED_INITIALIZER;

@end
