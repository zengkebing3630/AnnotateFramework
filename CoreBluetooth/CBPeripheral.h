//CBPeripheral.h
//外设

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBPeer.h>

#import <Foundation/Foundation.h>

/*!
 *  @enum CBPeripheralState
 *
 *  @discussion Represents the current connection state of a CBPeripheral.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralState) { //外设连接状态
	CBPeripheralStateDisconnected = 0, //未连接
	CBPeripheralStateConnecting, //正在连接
	CBPeripheralStateConnected,//已连接
} NS_AVAILABLE(NA, 7_0);

/*!
 *  @enum CBCharacteristicWriteType
 *
 *  @discussion Specifies which type of write is to be performed on a CBCharacteristic.
 *
 */
typedef NS_ENUM(NSInteger, CBCharacteristicWriteType) { //写入数据类型
	CBCharacteristicWriteWithResponse = 0, //有回应
	CBCharacteristicWriteWithoutResponse, //无回应
};

@protocol CBPeripheralDelegate;
@class CBService, CBCharacteristic, CBDescriptor, CBUUID;

/*!
 *  @class CBPeripheral
 *
 *  @discussion Represents a peripheral.
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBPeripheral : CBPeer  //外设

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive peripheral events.
 */
@property(weak, nonatomic) id<CBPeripheralDelegate> delegate;

/*!
 *  @property name
 *
 *  @discussion The name of the peripheral.
 */
@property(retain, readonly) NSString *name;  //外设名称

/*!
 *  @property RSSI
 *
 *  @discussion The most recently read RSSI, in decibels.
 *
 *  @deprecated Use {@link peripheral:didReadRSSI:error:} instead.
 */
@property(retain, readonly) NSNumber *RSSI NS_DEPRECATED(NA, NA, 5_0, 8_0); //以信号强弱来定位距离的长短，基站侧指标

/*!
 *  @property isConnected
 *
 *  @discussion Whether or not the peripheral is currently connected.
 *              
 *	@deprecated Use the {@link state} property instead.
 */
@property(readonly) BOOL isConnected NS_DEPRECATED(NA, NA, 5_0, 7_0);//是否已经连接

/*!
 *  @property state
 *
 *  @discussion The current connection state of the peripheral.
 */
@property(readonly) CBPeripheralState state;//连接状态

/*!
 *  @property services
 *
 *  @discussion A list of <code>CBService</code> objects that have been discovered on the peripheral.
 */
@property(retain, readonly) NSArray *services;//发现的服务列表

/*!
 *  @method readRSSI
 *
 *  @discussion While connected, retrieves the current RSSI of the link.
 *
 *  @see        peripheral:didReadRSSI:error:
 */
- (void)readRSSI;//更新RSSI

/*!
 *  @method discoverServices:
 *
 *  @param serviceUUIDs A list of <code>CBUUID</code> objects representing the service types to be discovered. If <i>nil</i>,
 *						all services will be discovered, which is considerably slower and not recommended.
 *
 *  @discussion			Discovers available service(s) on the peripheral.
 *
 *  @see				peripheral:didDiscoverServices:
 */
- (void)discoverServices:(NSArray *)serviceUUIDs;//发现UUIDS服务

/*!
 *  @method discoverIncludedServices:forService:
 *
 *  @param includedServiceUUIDs A list of <code>CBUUID</code> objects representing the included service types to be discovered. If <i>nil</i>,
 *								all of <i>service</i>s included services will be discovered, which is considerably slower and not recommended.
 *  @param service				A GATT service.
 *
 *  @discussion					Discovers the specified included service(s) of <i>service</i>.
 *
 *  @see						peripheral:didDiscoverIncludedServicesForService:error:
 */
- (void)discoverIncludedServices:(NSArray *)includedServiceUUIDs forService:(CBService *)service;//服务中匹配服务设备

/*!
 *  @method discoverCharacteristics:forService:
 *
 *  @param characteristicUUIDs	A list of <code>CBUUID</code> objects representing the characteristic types to be discovered. If <i>nil</i>,
 *								all characteristics of <i>service</i> will be discovered, which is considerably slower and not recommended.
 *  @param service				A GATT service.
 *
 *  @discussion					Discovers the specified characteristic(s) of <i>service</i>.
 *
 *  @see						peripheral:didDiscoverCharacteristicsForService:error:
 */
- (void)discoverCharacteristics:(NSArray *)characteristicUUIDs forService:(CBService *)service; //发现服务匹配特征

/*!
 *  @method readValueForCharacteristic:
 *
 *  @param characteristic	A GATT characteristic.
 *
 *  @discussion				Reads the characteristic value for <i>characteristic</i>.
 *
 *  @see					peripheral:didUpdateValueForCharacteristic:error:
 */
- (void)readValueForCharacteristic:(CBCharacteristic *)characteristic;//读取服务的特征值

/*!
 *  @method writeValue:forCharacteristic:type:
 *
 *  @param data				The value to write.
 *  @param characteristic	The characteristic whose characteristic value will be written.
 *  @param type				The type of write to be executed.
 *
 *  @discussion				Writes <i>value</i> to <i>characteristic</i>'s characteristic value.
 *							If the <code>CBCharacteristicWriteWithResponse</code> type is specified, {@link peripheral:didWriteValueForCharacteristic:error:}
 *							is called with the result of the write request.
 *							If the <code>CBCharacteristicWriteWithoutResponse</code> type is specified, the delivery of the data is best-effort and not
 *							guaranteed.
 *
 *  @see					peripheral:didWriteValueForCharacteristic:error:
 *	@see					CBCharacteristicWriteType
 */
- (void)writeValue:(NSData *)data forCharacteristic:(CBCharacteristic *)characteristic type:(CBCharacteristicWriteType)type;//向特征写入数据，写入类型

/*!
 *  @method setNotifyValue:forCharacteristic:
 *
 *  @param enabled			Whether or not notifications/indications should be enabled.
 *  @param characteristic	The characteristic containing the client characteristic configuration descriptor.
 *
 *  @discussion				Enables or disables notifications/indications for the characteristic value of <i>characteristic</i>. If <i>characteristic</i>
 *							allows both, notifications will be used.
 *                          When notifications/indications are enabled, updates to the characteristic value will be received via delegate method 
 *                          @link peripheral:didUpdateValueForCharacteristic:error: @/link. Since it is the peripheral that chooses when to send an update,
 *                          the application should be prepared to handle them as long as notifications/indications remain enabled.
 *
 *  @see					peripheral:didUpdateNotificationStateForCharacteristic:error:
 *  @seealso                CBConnectPeripheralOptionNotifyOnNotificationKey
 */
- (void)setNotifyValue:(BOOL)enabled forCharacteristic:(CBCharacteristic *)characteristic; //开启/关闭特征的通知

/*!
 *  @method discoverDescriptorsForCharacteristic:
 *
 *  @param characteristic	A GATT characteristic.
 *
 *  @discussion				Discovers the characteristic descriptor(s) of <i>characteristic</i>.
 *
 *  @see					peripheral:didDiscoverDescriptorsForCharacteristic:error:
 */
- (void)discoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic;//匹配特征的描述符

/*!
 *  @method readValueForDescriptor:
 *
 *  @param descriptor	A GATT characteristic descriptor.
 *
 *  @discussion			Reads the value of <i>descriptor</i>.
 *
 *  @see				peripheral:didUpdateValueForDescriptor:error:
 */
- (void)readValueForDescriptor:(CBDescriptor *)descriptor;//读取描述符

/*!
 *  @method writeValue:forDescriptor:
 *
 *  @param data			The value to write.
 *  @param descriptor	A GATT characteristic descriptor.
 *
 *  @discussion			Writes <i>data</i> to <i>descriptor</i>'s value. Client characteristic configuration descriptors cannot be written using
 *						this method, and should instead use @link setNotifyValue:forCharacteristic: @/link.
 *
 *  @see				peripheral:didWriteValueForCharacteristic:error:
 */
- (void)writeValue:(NSData *)data forDescriptor:(CBDescriptor *)descriptor;//向描述符写入数据

@end



/*!
 *  @protocol CBPeripheralDelegate
 *
 *  @discussion Delegate for CBPeripheral.
 *
 */
@protocol CBPeripheralDelegate <NSObject>

@optional

/*!
 *  @method peripheralDidUpdateName:
 *
 *  @param peripheral	The peripheral providing this update.
 *
 *  @discussion			This method is invoked when the @link name @/link of <i>peripheral</i> changes.
 */
- (void)peripheralDidUpdateName:(CBPeripheral *)peripheral NS_AVAILABLE(NA, 6_0);//已经更新外设名称

/*!
 *  @method peripheralDidInvalidateServices:
 *
 *  @param peripheral	The peripheral providing this update.
 *
 *  @discussion			This method is invoked when the @link services @/link of <i>peripheral</i> have been changed. At this point, 
 *						all existing <code>CBService</code> objects are invalidated. Services can be re-discovered via @link discoverServices: @/link.
 *
 *	@deprecated			Use {@link peripheral:didModifyServices:} instead.
 */
- (void)peripheralDidInvalidateServices:(CBPeripheral *)peripheral NS_DEPRECATED(NA, NA, 6_0, 7_0);//已经更新外设服务

/*!
 *  @method peripheral:didModifyServices:
 *
 *  @param peripheral			The peripheral providing this update.
 *  @param invalidatedServices	The services that have been invalidated
 *
 *  @discussion			This method is invoked when the @link services @/link of <i>peripheral</i> have been changed.
 *						At this point, the designated <code>CBService</code> objects have been invalidated.
 *						Services can be re-discovered via @link discoverServices: @/link.
 */
- (void)peripheral:(CBPeripheral *)peripheral didModifyServices:(NSArray *)invalidatedServices NS_AVAILABLE(NA, 7_0);//已经更新外设服务列表

/*!
 *  @method peripheralDidUpdateRSSI:error:
 *
 *  @param peripheral	The peripheral providing this update.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link readRSSI: @/link call.
 *
 *  @deprecated			Use {@link peripheral:didReadRSSI:error:} instead.
 */
- (void)peripheralDidUpdateRSSI:(CBPeripheral *)peripheral error:(NSError *)error NS_DEPRECATED(NA, NA, 5_0, 8_0);//已经更新外设信号强度

/*!
 *  @method peripheral:didReadRSSI:error:
 *
 *  @param peripheral	The peripheral providing this update.
 *  @param RSSI			The current RSSI of the link.
 *  @param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link readRSSI: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didReadRSSI:(NSNumber *)RSSI error:(NSError *)error NS_AVAILABLE(NA, 8_0);//已经读取外设信号强度

/*!
 *  @method peripheral:didDiscoverServices:
 *
 *  @param peripheral	The peripheral providing this information.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverServices: @/link call. If the service(s) were read successfully, they can be retrieved via
 *						<i>peripheral</i>'s @link services @/link property.
 *
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error;//已经发现服务

/*!
 *  @method peripheral:didDiscoverIncludedServicesForService:error:
 *
 *  @param peripheral	The peripheral providing this information.
 *  @param service		The <code>CBService</code> object containing the included services.
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverIncludedServices:forService: @/link call. If the included service(s) were read successfully, 
 *						they can be retrieved via <i>service</i>'s <code>includedServices</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverIncludedServicesForService:(CBService *)service error:(NSError *)error;//已经匹配到服务

/*!
 *  @method peripheral:didDiscoverCharacteristicsForService:error:
 *
 *  @param peripheral	The peripheral providing this information.
 *  @param service		The <code>CBService</code> object containing the characteristic(s).
 *	@param error		If an error occurred, the cause of the failure.
 *
 *  @discussion			This method returns the result of a @link discoverCharacteristics:forService: @/link call. If the characteristic(s) were read successfully, 
 *						they can be retrieved via <i>service</i>'s <code>characteristics</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error;//已经匹配到特征

/*!
 *  @method peripheral:didUpdateValueForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method is invoked after a @link readValueForCharacteristic: @/link call, or upon receipt of a notification/indication.
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;//已经更新特征

/*!
 *  @method peripheral:didWriteValueForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a {@link writeValue:forCharacteristic:type:} call, when the <code>CBCharacteristicWriteWithResponse</code> type is used.
 */
 - (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;//完成向特征写入数据

/*!
 *  @method peripheral:didUpdateNotificationStateForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link setNotifyValue:forCharacteristic: @/link call. 
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;//更新特征通知状态

/*!
 *  @method peripheral:didDiscoverDescriptorsForCharacteristic:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param characteristic	A <code>CBCharacteristic</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link discoverDescriptorsForCharacteristic: @/link call. If the descriptors were read successfully, 
 *							they can be retrieved via <i>characteristic</i>'s <code>descriptors</code> property.
 */
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;//已经匹配特征描述符

/*!
 *  @method peripheral:didUpdateValueForDescriptor:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param descriptor		A <code>CBDescriptor</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link readValueForDescriptor: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error;//已经更新描述符

/*!
 *  @method peripheral:didWriteValueForDescriptor:error:
 *
 *  @param peripheral		The peripheral providing this information.
 *  @param descriptor		A <code>CBDescriptor</code> object.
 *	@param error			If an error occurred, the cause of the failure.
 *
 *  @discussion				This method returns the result of a @link writeValue:forDescriptor: @/link call.
 */
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error;//已经向描述写入数据

@end
