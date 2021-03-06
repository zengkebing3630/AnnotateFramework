//CBUUID.h

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

/*!
 *  @const CBUUIDCharacteristicExtendedPropertiesString
 *  @discussion The string representation of the UUID for the extended properties descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicExtendedPropertiesString;
/*!
 *  @const CBUUIDCharacteristicUserDescriptionString
 *  @discussion The string representation of the UUID for the user description descriptor.
 *				The corresponding value for this descriptor is an <code>NSString</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicUserDescriptionString;
/*!
 *  @const CBUUIDClientCharacteristicConfigurationString
 *  @discussion The string representation of the UUID for the client configuration descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDClientCharacteristicConfigurationString;
/*!
 *  @const CBUUIDServerCharacteristicConfigurationString
 *  @discussion The string representation of the UUID for the server configuration descriptor.
 *				The corresponding value for this descriptor is an <code>NSNumber</code> object.
 */
CB_EXTERN NSString * const CBUUIDServerCharacteristicConfigurationString;
/*!
 *  @const CBUUIDCharacteristicFormatString
 *  @discussion The string representation of the UUID for the presentation format descriptor.
 *				The corresponding value for this descriptor is an <code>NSData</code> object.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicFormatString;
/*!
 *  @const CBUUIDCharacteristicAggregateFormatString
 *  @discussion The string representation of the UUID for the aggregate descriptor.
 */
CB_EXTERN NSString * const CBUUIDCharacteristicAggregateFormatString;



/*!
 *  @const CBUUIDGenericAccessProfileString
 *  @discussion The string representation of the GAP UUID.
 */
CB_EXTERN NSString * const CBUUIDGenericAccessProfileString NS_DEPRECATED(NA, NA, 5_0, 7_0);
/*!
 *  @const CBUUIDGenericAttributeProfileString
 *  @discussion The string representation of the GATT UUID.
 */
CB_EXTERN NSString * const CBUUIDGenericAttributeProfileString NS_DEPRECATED(NA, NA, 5_0, 7_0);

/*!
 *  @const CBUUIDDeviceNameString
 *  @discussion The string representation of the GAP device name UUID.
 */
CB_EXTERN NSString * const CBUUIDDeviceNameString NS_DEPRECATED(NA, NA, 5_0, 7_0);
/*!
 *  @const CBUUIDAppearanceString
 *  @discussion The string representation of the GAP appearance UUID.
 */
CB_EXTERN NSString * const CBUUIDAppearanceString NS_DEPRECATED(NA, NA, 5_0, 7_0);
/*!
 *  @const CBUUIDPeripheralPrivacyFlagString
 *  @discussion The string representation of the GAP privacy flag UUID.
 */
CB_EXTERN NSString * const CBUUIDPeripheralPrivacyFlagString NS_DEPRECATED(NA, NA, 5_0, 7_0);
/*!
 *  @const CBUUIDReconnectionAddressString
 *  @discussion The string representation of the GAP reconnection address UUID.
 */
CB_EXTERN NSString * const CBUUIDReconnectionAddressString NS_DEPRECATED(NA, NA, 5_0, 7_0);
/*!
 *  @const CBUUIDPeripheralPreferredConnectionParametersString
 *  @discussion The string representation of the GAP preferred connection parameter UUID.
 */
CB_EXTERN NSString * const CBUUIDPeripheralPreferredConnectionParametersString NS_DEPRECATED(NA, NA, 5_0, 7_0);
/*!
 *  @const CBUUIDServiceChangedString
 *  @discussion The string representation of the GATT service changed UUID.
 */
CB_EXTERN NSString * const CBUUIDServiceChangedString NS_DEPRECATED(NA, NA, 5_0, 7_0);



/*!
 * @class CBUUID
 *
 * @discussion
 *      A 16-bit, 32-bit, or 128-bit Bluetooth UUID.
 *      16-bit and 32-bit UUIDs are implicitly pre-filled with the Bluetooth Base UUID.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBUUID : NSObject <NSCopying> //设备UUID

/*!
 * @property data
 *
 *  @discussion
 *      The UUID as NSData.
 *
 */
@property(nonatomic, readonly) NSData *data; //UUID二进制数据

/*!
 * @property UUIDString
 *
 *  @discussion
 *      The UUID as NSString.
 *
 */
@property(nonatomic, readonly) NSString *UUIDString NS_AVAILABLE(NA, 7_1); //UUID字符串

/*!
 * @method UUIDWithString:
 *
 *  @discussion
 *      Creates a CBUUID with a 16-bit, 32-bit, or 128-bit UUID string representation.
 *      The expected format for 128-bit UUIDs is a string punctuated by hyphens, for example 68753A44-4D6F-1226-9C60-0050E4C00067.
 *
 */
+ (CBUUID *)UUIDWithString:(NSString *)theString; //以16-bit，32-bit，128-bit UUID 字符串创建 CBUUID

/*!
 * @method UUIDWithData:
 *
 *  @discussion
 *      Creates a CBUUID with a 16-bit, 32-bit, or 128-bit UUID data container.
 *
 */
+ (CBUUID *)UUIDWithData:(NSData *)theData;//以16-bit，32-bit，128-bit UUID 二进制数据创建 CBUUID

/*!
 * @method UUIDWithCFUUID:
 *
 *  @discussion
 *      Creates a CBUUID with a CFUUIDRef.
 *
 */
+ (CBUUID *)UUIDWithCFUUID:(CFUUIDRef)theUUID;//以CFUUIDRef创建 CBUUID

/*!
 * @method UUIDWithNSUUID:
 *
 *  @discussion
 *      Creates a CBUUID with a NSUUID.
 *
 */
+ (CBUUID *)UUIDWithNSUUID:(NSUUID *)theUUID NS_AVAILABLE(NA, 7_0);//以NSUUID创建 CBUUID

@end
