//CBATTRequest.h
 

#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>

#import <Foundation/Foundation.h>

@class CBCentral, CBCharacteristic;

/*!
 *  @class CBATTRequest
 *
 *  @discussion Represents a read or write request from a central.
 *
 */
NS_CLASS_AVAILABLE(NA, 6_0)
CB_EXTERN_CLASS @interface CBATTRequest : NSObject  //蓝牙请求 ,一个中央发出的读或者写请求

/*!
 *  @property central
 *
 *  @discussion The central that originated the request.
 *
 */
@property(readonly, retain, nonatomic) CBCentral *central;// 发送请求的中央

/*!
 *  @property characteristic
 *
 *  @discussion The characteristic whose value will be read or written.
 *
 */
@property(readonly, retain, nonatomic) CBCharacteristic *characteristic; // 将被读或者写的对应的characteristic

/*!
 *  @property offset
 *
 *  @discussion The zero-based index of the first byte for the read or write.
 *
 */
 // 正在被读写的数据，这个属性的值取决于不用的请求类型，对于读请求它的值在 respondToRequest：withResult：方法被调用之前被设置。
@property(readonly, nonatomic) NSUInteger offset;

/*!
 *  @property value
 *
 *  @discussion The data being read or written.
 *				For read requests, <i>value</i> will be nil and should be set before responding via @link respondToRequest:withResult: @/link.
 *				For write requests, <i>value</i> will contain the data to be written.
 *
 */
@property(readwrite, copy) NSData *value;//写入数据

@end
