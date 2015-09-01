
/*
 *  CLLocationManagerDelegate.h
 *  CoreLocation
 *
 *  Copyright (c) 2008-2010 Apple Inc. All rights reserved.
 *
 */

#import <Availability.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CLLocationManager.h>
#import <CoreLocation/CLRegion.h>
#import <CoreLocation/CLVisit.h>

@class CLLocation;
@class CLHeading;

/*
 *  CLLocationManagerDelegate
 *  
 *  Discussion:
 *    Delegate for CLLocationManager.
 */
@protocol CLLocationManagerDelegate<NSObject>

@optional

/*
 *  locationManager:didUpdateToLocation:fromLocation:
 *  
 *  Discussion:
 *    Invoked when a new location is available. oldLocation may be nil if there is no previous location
 *    available.
 *
 *    This method is deprecated. If locationManager:didUpdateLocations: is
 *    implemented, this method will not be called.
 */
- (void)locationManager:(CLLocationManager *)manager
	didUpdateToLocation:(CLLocation *)newLocation
		   fromLocation:(CLLocation *)oldLocation __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_6, __MAC_NA, __IPHONE_2_0, __IPHONE_6_0);

// 位置发生改变后执行（第一次定位到某个位置之后也会执行）,根据distanceFilter 级别
- (void)locationManager:(CLLocationManager *)manager
	 didUpdateLocations:(NSArray *)locations;

// *告知代理，方位信息已经被位置管理器更新，如果位置管理器有使用startUpdateingHeading这个方法，则应当实现本方法。导航方向发生变化后执行
- (void)locationManager:(CLLocationManager *)manager
       didUpdateHeading:(CLHeading *)newHeading;

// 询问代理是否方位校准警告是否需要显示，当有新的Heading信息时调用该方法，如否有需要显示Heading校准信息，则返回YES
- (BOOL)locationManagerShouldDisplayHeadingCalibration:(CLLocationManager *)manager  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

// 告知代理，以下事件有发生，以便做相应处理。
- (void)locationManager:(CLLocationManager *)manager
	didDetermineState:(CLRegionState)state forRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
 *  locationManager:didRangeBeacons:inRegion:
 *
 *  Discussion:
 *    Invoked when a new set of beacons are available in the specified region.
 *    beacons is an array of CLBeacon objects.
 *    If beacons is empty, it may be assumed no beacons that match the specified region are nearby.
 *    Similarly if a specific beacon no longer appears in beacons, it may be assumed the beacon is no longer received
 *    by the device.
 */
- (void)locationManager:(CLLocationManager *)manager
	didRangeBeacons:(NSArray *)beacons inRegion:(CLBeaconRegion *)region __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/*
 *  locationManager:rangingBeaconsDidFailForRegion:withError:
 *
 *  Discussion:
 *    Invoked when an error has occurred ranging beacons in a region. Error types are defined in "CLError.h".
 */
- (void)locationManager:(CLLocationManager *)manager
	rangingBeaconsDidFailForRegion:(CLBeaconRegion *)region
	withError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

// 开始对某个区域进行定位追踪，开始对某个区域进行定位后。如果用户进入某个区域会调用
- (void)locationManager:(CLLocationManager *)manager
	didEnterRegion:(CLRegion *)region;

// 开始对某个区域进行定位追踪，开始对某个区域进行定位后。如果用户走出某个区域会调用
- (void)locationManager:(CLLocationManager *)manager
	didExitRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
 *  locationManager:didFailWithError:
 *  
 *  Discussion:
 *    Invoked when an error has occurred. Error types are defined in "CLError.h".
 */
- (void)locationManager:(CLLocationManager *)manager
	didFailWithError:(NSError *)error;

/*
 *  locationManager:monitoringDidFailForRegion:withError:
 *  
 *  Discussion:
 *    Invoked when a region monitoring error has occurred. Error types are defined in "CLError.h".
 */
- (void)locationManager:(CLLocationManager *)manager
	monitoringDidFailForRegion:(CLRegion *)region
	withError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*
	如果用户之前已经授权了位置服务，那么在每次位置管理器被初始化，
	并且 delegate 被设置了相应的权限状态的情况下这个代理方法仍然会被调用。
	这使得一个单一的代码路径使用定位服务更为方便。
*/
 // 这个方法会在用户改变权限状态的时候调用
- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_2);

/*
 *  locationManager:didStartMonitoringForRegion:
 *  
 *  Discussion:
 *    Invoked when a monitoring for a region started successfully.
 */
- (void)locationManager:(CLLocationManager *)manager
	didStartMonitoringForRegion:(CLRegion *)region __OSX_AVAILABLE_STARTING(__MAC_TBD,__IPHONE_5_0);

/*
 *  Discussion:
 *    Invoked when location updates are automatically paused.
 */
- (void)locationManagerDidPauseLocationUpdates:(CLLocationManager *)manager __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

/*
 *  Discussion:
 *    Invoked when location updates are automatically resumed.
 *
 *    In the event that your application is terminated while suspended, you will
 *	  not receive this notification.
 */
- (void)locationManagerDidResumeLocationUpdates:(CLLocationManager *)manager __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

/*
 *  locationManager:didFinishDeferredUpdatesWithError:
 *
 *  Discussion:
 *    Invoked when deferred updates will no longer be delivered. Stopping
 *    location, disallowing deferred updates, and meeting a specified criterion
 *    are all possible reasons for finishing deferred updates.
 *
 *    An error will be returned if deferred updates end before the specified
 *    criteria are met (see CLError).
 */
- (void)locationManager:(CLLocationManager *)manager
	didFinishDeferredUpdatesWithError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

/*
	每次一个访问被追踪到，CLLocationManagerDelegate 可能会被告知两次：
	一次是在用户刚抵达一个新的地方的时候，以及当用户离开的时候。
	你可以通过检查 departureDate 属性来分辨它们;
	 NSDate.distantFuture() 的离开时间意味着用户还在那儿。


	 至少到 iOS 8.1，CLVisit 还不是那么精确。
	 开始和结束时间一般有一两分钟的误差，
	 是否访问某个地方的线路边际有点模糊。
	 在咖啡店的角落躲一分钟可能不会触发访问，
	 但在等一个特别长的红绿灯的时候却有可能触发。
	 很可能 Apple 将在操作系统的后续升级的时候提升访问检测的质量，
	 但现在如果你的应用程序对访问检测的精度要求很高的话，
	 你最好不要依赖 CLVisit
*/
- (void)locationManager:(CLLocationManager *)manager didVisit:(CLVisit *)visit;

@end
