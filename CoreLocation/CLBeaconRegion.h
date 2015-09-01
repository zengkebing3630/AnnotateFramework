/*
 *  CLBeaconRegion.h
 *  CoreLocation
 *
 *  Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLRegion.h>
#import <CoreLocation/CLAvailability.h>

/*
 *  CLBeaconMajorValue
 *
 *  Discussion:
 *    Type represents the most significant value in a beacon.
 *
 */
typedef uint16_t CLBeaconMajorValue;

/*
 *  CLBeaconMinorValue
 *
 *  Discussion:
 *    Type represents the least significant value in a beacon.
 *
 */
typedef uint16_t CLBeaconMinorValue;

/*
 *  CLBeaconRegion
 *
 *  Discussion:
 *    A region containing similar beacons.
 *
 *    Such a region can be defined by proximityUUID, major and minor values.
 *    proximityUUID must be specified. If proximityUUID is only specified, the major and
 *    minor values will be wildcarded and the region will match any beacons with the same
 *    proximityUUID. Similarly if only proximityUUID and major value are specified, the minor value will be
 *    wildcarded and the region will match against any beacons with the same proximityUUID and major
 *    value.
 *
 */
NS_CLASS_AVAILABLE(NA, 7_0)
@interface CLBeaconRegion : CLRegion

/*
 *  initWithProximityUUID:identifier:
 *
 *  Discussion:
 *    Initialize a beacon region with a proximityUUID. Major and minor values will be wildcarded.
 *
 */
- (instancetype)initWithProximityUUID:(NSUUID *)proximityUUID identifier:(NSString *)identifier;

/*
 *  initWithProximityUUID:major:identifier:
 *
 *  Discussion:
 *    Initialize a beacon region with an proximityUUID and major value. Minor value will be wildcarded.
 *
 */
- (instancetype)initWithProximityUUID:(NSUUID *)proximityUUID major:(CLBeaconMajorValue)major identifier:(NSString *)identifier;

/*
 *  initWithProximityUUID:major:minor:identifier:
 *
 *  Discussion:
 *    Initialize a beacon region identified by an proximityUUID, major and minor values.
 *
 */
- (instancetype)initWithProximityUUID:(NSUUID *)proximityUUID major:(CLBeaconMajorValue)major minor:(CLBeaconMinorValue)minor identifier:(NSString *)identifier;

/*
 *  peripheralDataWithMeasuredPower:
 *
 *  Discussion:
 *    This dictionary can be used to advertise the current device as a beacon when
 *    used in conjunction with CoreBluetooth's CBPeripheralManager startAdvertising: method.
 *    The dictionary will contain data that represents the current region in addition to a measured power value.
 *
 *    measuredPower is the RSSI of the device observed from one meter in its intended environment.
 *    This value is optional, but should be specified to achieve the best ranging performance.
 *    If not specified, it will default to a pre-determined value for the device.
 *
 */
- (NSMutableDictionary *)peripheralDataWithMeasuredPower:(NSNumber *)measuredPower;

/*
 *  proximityUUID
 *
 *  Discussion:
 *    Proximity identifier associated with the region.
 *
 */
 // 对于每个公司这个是唯一的。对于该公司的所有的ibeacons都有相同的UUID。
@property (readonly, nonatomic, strong) NSUUID *proximityUUID;

/*
 *  major
 *
 *  Discussion:
 *    Most significant value associated with the region. If a major value wasn't specified, this will be nil.
 *
 */
@property (readonly, nonatomic, strong) NSNumber *major;

/*
 *  minor
 *
 *  Discussion:
 *    Least significant value associated with the region. If a minor value wasn't specified, this will be nil.
 *
 */
@property (readonly, nonatomic, strong) NSNumber *minor;

/*
 *  notifyEntryStateOnDisplay
 *
 *  Discussion:
 *    App will be launched and the delegate will be notified via locationManager:didDetermineState:forRegion:
 *    when the device's screen is turned on and the user is in the region. By default, this is NO.
 */
 // 标记是否在用户手机屏幕点亮时调用代理方法
@property (nonatomic, assign) BOOL notifyEntryStateOnDisplay;

@end

/*
 *  CLBeacon
 *
 *  Discussion:
 *    A single beacon within a CLBeaconRegion.
 *
 */
NS_CLASS_AVAILABLE(NA, 7_0)
@interface CLBeacon : NSObject <NSCopying, NSSecureCoding>

/*
 *  proximityUUID
 *
 *  Discussion:
 *    Proximity identifier associated with the beacon.
 *
 */
@property (readonly, nonatomic, strong) NSUUID *proximityUUID;

/*
 *  major
 *
 *  Discussion:
 *    Most significant value associated with the beacon.
 *
 */
@property (readonly, nonatomic, strong) NSNumber *major;

/*
 *  minor
 *
 *  Discussion:
 *    Least significant value associated with the beacon.
 *
 */
@property (readonly, nonatomic, strong) NSNumber *minor;

/*
 *  proximity
 *
 *  Discussion:
 *    Proximity of the beacon from the device.
 *
 */
 // proximity远近范围的，有Near（在几米内），Immediate（在几厘米内），Far（超过 10 米以外，不过在测试中超不过10米就是far），Unknown（无效）
@property (readonly, nonatomic) CLProximity proximity;

/*
 *  accuracy
 *
 *  Discussion:
 *    Represents an one sigma horizontal accuracy in meters where the measuring device's location is
 *    referenced at the beaconing device. This value is heavily subject to variations in an RF environment.
 *    A negative accuracy value indicates the proximity is unknown.
 *
 */
 // 和iBeacon的距离
@property (readonly, nonatomic) CLLocationAccuracy accuracy;

 // rssi信号轻度为负值，越接近0信号越强，等于0时无法获取信号强度
@property (readonly, nonatomic) NSInteger rssi;

@end
