/*
 *  CLLocationManager+CLVisitExtensions.h
 *  CoreLocation
 *
 *  Copyright (c) 2014 Apple Inc. All rights reserved.
 *
 */

#import <CoreLocation/CLLocationManager.h>

/*
	假设用户同意授权你的应用程序“始终”的使用权限。
	一旦启动，你的应用程序将在有位置更新的时候在后台被唤醒，
	不像基本的定位监控，如果系统有个访问更新的队列（通常可以使更新延迟），
	你的 delegate 方法将被调用多次，每个单一的访问调用一次，
	而不是一个包含 CLLocation 对象的数组调用 locationManager:didReceiveUpdates:。
*/
@interface CLLocationManager (CLVisitExtensions)

 // 将启用后台访问跟踪，
- (void)startMonitoringVisits NS_AVAILABLE(NA, 8_0);

// 停止后台访问跟踪，
- (void)stopMonitoringVisits NS_AVAILABLE(NA, 8_0);

@end
