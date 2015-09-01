
/*
 *  CLLocationManager.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <CoreLocation/CLAvailability.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLRegion.h>

/*
 *  CLDeviceOrientation
 *  
 *  Discussion:
 *      Specifies a physical device orientation, equivalent to UIDeviceOrientation.
 *      
 */
typedef NS_ENUM(int, CLDeviceOrientation) {
	CLDeviceOrientationUnknown = 0,
	CLDeviceOrientationPortrait,
	CLDeviceOrientationPortraitUpsideDown,
	CLDeviceOrientationLandscapeLeft,
	CLDeviceOrientationLandscapeRight,
	CLDeviceOrientationFaceUp,
	CLDeviceOrientationFaceDown
};

//应用授权状态
typedef NS_ENUM(int, CLAuthorizationStatus) {
 // 用户尚未做出决定是否启用定位服务
 	kCLAuthorizationStatusNotDetermined = 0,

 // 没有获得用户授权使用定位服务,可能用户没有自己禁止访问授权
	kCLAuthorizationStatusRestricted,

// 用户已经明确禁止应用使用定位服务或者当前系统定位服务处于关闭状态
	kCLAuthorizationStatusDenied,

 // 应用获得授权可以一直使用定位服务，即使应用不在使用状态
	kCLAuthorizationStatusAuthorizedAlways NS_ENUM_AVAILABLE(NA, 8_0),

	 // 使用此应用过程中允许访问定位服务
	kCLAuthorizationStatusAuthorizedWhenInUse NS_ENUM_AVAILABLE(NA, 8_0),

	//用户已经授权，在IOS8.0之后 就等于 kCLAuthorizationStatusAuthorizedAlways
	kCLAuthorizationStatusAuthorized NS_ENUM_DEPRECATED(10_6, NA, 2_0, 8_0, "Use kCLAuthorizationStatusAuthorizedAlways") = kCLAuthorizationStatusAuthorizedAlways
};


typedef NS_ENUM(NSInteger, CLActivityType) {//指示的活动类型与位置更新
    CLActivityTypeOther = 1,//位置管理器正在使用的一个未知的活动。
    CLActivityTypeAutomotiveNavigation,	//正在使用的位置经理专门在车辆导航汽车跟踪定位变化。此活动可能导致被暂停
    CLActivityTypeFitness,				//位置管理器被用来跟踪任何行人有关的活动。这种活动可能导致被暂停的位置更新，仅当用户没有移动过了一段时间的一个显着的距离。
    CLActivityTypeOtherNavigation 		//位置管理器被用来跟踪运动不是汽车相关的其他类型的车辆导航。例如，您可以使用它来跟踪船，火车或飞机的导航。不要使用这种类型的行人导航跟踪。被暂停的位置更新，只有当该车辆不移动一个显着的距离超过了一段时间，这可能会导致活性。
};

@class CLLocation;
@class CLHeading;
@class CLBeaconRegion;
@protocol CLLocationManagerDelegate;

// 位置管理器，用来接入定位服务。可以参照CLLocationManager Class Reference来了解该类的功能定义。
@interface CLLocationManager : NSObject
{
@private
	id _internal;
}

/* 判断用户是否启动位置服务。 * 在启动位置更新操作之前，用户应当检查该方法的返回值来查看设备的位置服务是否启动。
如果位置服务没有启动，而用户又启动了位置更新操作，
那么Core Location 框架将会弹出一个让用户确认是否启动位置服务的对话框。
*/
+ (BOOL)locationServicesEnabled __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

// 如果设备支持方位服务(即设备能否返回方位数据)则返回YES，否则返回NO。
+ (BOOL)headingAvailable __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
/*
表明设备能否报告基于significant location changges的更新(significant location change监控，
	只是基于设备所链接的蜂窝塔的位置改变诊断，在精度要求不高的情况下，可以节省很多电量。)
*/
+ (BOOL)significantLocationChangeMonitoringAvailable __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  isMonitoringAvailableForClass:
 *
 *  Discussion:
 *      Determines whether the device supports monitoring for the specified type of region.
 *      If NO, all attempts to monitor the specified type of region will fail.
 */
+ (BOOL)isMonitoringAvailableForClass:(Class)regionClass __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

// 表明设备是否支持区域监测，即使设备支持区域监测，用户也可能把当前应用设置为区域监测不可用，在启动或者初始化区域监测时应当检查。
+ (BOOL)regionMonitoringAvailable __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0);

/*
 *  regionMonitoringEnabled
 *  
 *  Discussion:
 *      Deprecated. Use +isMonitoringAvailableForClass: and +authorizationStatus instead.
 */
+ (BOOL)regionMonitoringEnabled __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA,__IPHONE_4_0, __IPHONE_6_0);

/*
 *  isRangingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports ranging.
 *      If NO, all attempts to range beacons will fail.
 */
+ (BOOL)isRangingAvailable __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

// 检查应用的授权状态，应用在第一次启动时，会自动请求授权，应用应当明确被授权使用位置服务，并且位置服务当前出于运行状态，应用才能使用位置服务
+ (CLAuthorizationStatus)authorizationStatus __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_2);

// 把位置管理的一些活动代理出去
@property(assign, nonatomic) id<CLLocationManagerDelegate> delegate;

/*
 *  locationServicesEnabled
 *  
 *  Discussion:
 *      Deprecated. Use +locationServicesEnabled instead.
 */
@property(readonly, nonatomic) BOOL locationServicesEnabled __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_4_0);

/*
 *  purpose
 *  
 *  Discussion:
 *      Allows the application to specify what location will be used for in their app. This
 *      will be displayed along with the standard Location permissions dialogs. This property will need to be
 *      set prior to calling startUpdatingLocation.
 *
 *      Deprecated.  Set the purpose string in Info.plist using key NSLocationUsageDescription.
 */
@property(copy, nonatomic) NSString *purpose __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_7, __MAC_NA, __IPHONE_3_2, __IPHONE_6_0);

// 活动类型指明框架是否可以自动停止位置更新，这样当用户的位置很长时间没有改变时，系统可以暂停位置更新，来节省电能
@property(assign, nonatomic) CLActivityType activityType __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

// 每隔多少米定位一次，位置信息更新最小距离，只有移动大于这个距离才更新位置信息，默认为kCLDistanceFilterNone：不进行距离限制
@property(assign, nonatomic) CLLocationDistance distanceFilter; 

/* 所需要的精度，应当根据应用场景来设置当前的最佳定位精度，更高的精度意味着在定位时将会消耗更多的能量和时间。
定位服务可能不支持所设定的精度，但定位服务将会最大可能的满足所设定的精度。
*/
@property(assign, nonatomic) CLLocationAccuracy desiredAccuracy;

// 是否可以自动暂停位置更新操作。
@property(assign, nonatomic) BOOL pausesLocationUpdatesAutomatically __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

// 上次接收到的位置信息。
@property(readonly, nonatomic, copy) CLLocation *location;

/*
 *  headingAvailable
 *
 *  Discussion:
 *      Deprecated. Use +headingAvailable instead.
 */
@property(readonly, nonatomic) BOOL headingAvailable __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_3_0,__IPHONE_4_0);

// 指定产生heading事件时的最小角度改变量。默认的最小headingFilter值为1度。

@property(assign, nonatomic) CLLocationDegrees headingFilter __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

/*
指定设备的方位朝向参照方向，默认是参照设备的向上方向，
但如果应用的布局方向在其他方向上，那么通过设置headingOrientation可以指定heading的参照方向。
*/
@property(assign, nonatomic) CLDeviceOrientation headingOrientation __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

// 返回最近一次的方位信息。
@property(readonly, nonatomic, copy) CLHeading *heading __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

// 检测区域的最大范围。这个值可能依赖于设备的硬件特性，当给出比该值更大的区域范围时，将会产生kCLErrorRegionMonitoringFailure
@property (readonly, nonatomic) CLLocationDistance maximumRegionMonitoringDistance __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
当前正在监测的区域集合。不能直接把监测区域添加到该集合中，
应当使用startMonitoringForRegion:desiredAccuracy:方法来增加想要监测的区域。
*/
@property (readonly, nonatomic, copy) NSSet *monitoredRegions __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  rangedRegions
 *
 *  Discussion:
 *       Retrieve a set of objects representing the regions for which this location manager is actively providing ranging.
 */
@property (readonly, nonatomic, copy) NSSet *rangedRegions __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

// 请求获得应用使用时的定位服务授权，注意使用此方法前在要在info.plist中配置NSLocationWhenInUseUsageDescription
/*
	“使用期间” 的授权会只允许应用在 - 就跟你猜测的一样 - 使用期间取得你的位置信息。

	“始终” 的授权则跟之前版本的 iOS 那样，会给应用后台权限。
*/
 // 只能让应用在使用的时候有权获取位置数据,“使用期间”获取权限的方法，异步
- (void)requestWhenInUseAuthorization;

// 请求获得应用一直使用定位服务授权，注意使用此方法前要在info.plist中配置NSLocationAlwaysUsageDescription
  // 只能让应用始终有权获取位置数据,“始终”获取权限的方法,异步
- (void)requestAlwaysAuthorization __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_8_0);


// 开始定位追踪，开始定位后将按照用户设置的更新频率执行
- (void)startUpdatingLocation;
// 停止定位追踪
- (void)stopUpdatingLocation;
// 开始导航方向追踪
- (void)startUpdatingHeading;
// 停止导航方向追踪
- (void)stopUpdatingHeading;

- (void)dismissHeadingCalibrationDisplay __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
// 开始对某个区域进行定位追踪，开始对某个区域进行定位后。如果用户进入或者走出某个区域会调用- 
- (void)startMonitoringSignificantLocationChanges;
// 停止对某个区域进行定位追踪
- (void)stopMonitoringSignificantLocationChanges;


/*
	以指定的精度添加需要监测的区域，应用将要自己负责检测这些区域边界是否有重合的部分，
	来防止当用户在使用这些重合区域时而发出的重复的通知
	。如果有相同标记的区域已经出于被监控的状态，则从监控列表中移除该区域。
	操作的异步性可能导致区域不能立即处于被监控状态。
*/
- (void)startMonitoringForRegion:(CLRegion *)region
                 desiredAccuracy:(CLLocationAccuracy)accuracy __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA, __MAC_NA,__IPHONE_4_0, __IPHONE_6_0);
		
/*
 *  stopMonitoringForRegion:
 *
 *  Discussion:
 *      Stop monitoring the specified region.  It is valid to call stopMonitoringForRegion: for a region that was registered
 *      for monitoring with a different location manager object, during this or previous launches of your application.
 *
 *      This is done asynchronously and may not be immediately reflected in monitoredRegions.
 */
- (void)stopMonitoringForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  startMonitoringForRegion:
 *
 *  Discussion:
 *      Start monitoring the specified region.
 *
 *      If a region of the same type with the same identifier is already being monitored for this application,
 *      it will be removed from monitoring. For circular regions, the region monitoring service will prioritize
 *      regions by their size, favoring smaller regions over larger regions.
 *
 *      This is done asynchronously and may not be immediately reflected in monitoredRegions.
 */
- (void)startMonitoringForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_TBD,__IPHONE_5_0);

/*
 *  requestStateForRegion:
 *
 *  Discussion:
 *      Asynchronously retrieve the cached state of the specified region. The state is returned to the delegate via
 *      locationManager:didDetermineState:forRegion:.
 */
- (void)requestStateForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
 *  startRangingBeaconsInRegion:
 *
 *  Discussion:
 *      Start calculating ranges for beacons in the specified region.
 */
- (void)startRangingBeaconsInRegion:(CLBeaconRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
 *  stopRangingBeaconsInRegion:
 *
 *  Discussion:
 *      Stop calculating ranges for the specified region.
 */
- (void)stopRangingBeaconsInRegion:(CLBeaconRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
	设定应用的位置更新处理的延迟时间，这样可以使设备处于低能耗状态。
	如果应用是在前台运行，LocationManagerDelegate仍会持续的接收到位置更新的请求，
	但是应用在后台处理时，则会使用此处设置的延迟时间，以节省设备的电能。
*/
- (void)allowDeferredLocationUpdatesUntilTraveled:(CLLocationDistance)distance
					  timeout:(NSTimeInterval)timeout __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

// 如果之前有设置enabled 那么则取消延迟位置更新的允许。
- (void)disallowDeferredLocationUpdates __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

// 表明设备是否支持延迟更新。
+ (BOOL)deferredLocationUpdatesAvailable __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

@end
