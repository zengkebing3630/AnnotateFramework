//
//  MKUserLocation.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>

@class CLLocation;
@class MKUserLocationInternal;

//义了一种特殊类型的标注用于表示用户当前位置。你不需要直接创建本类的实例。相反，你可以从地图视图中的 userLocation 属性获取一个现有的MBUserLocation对象。
@interface MKUserLocation : NSObject <MKAnnotation>

//指示用户位置当前是否更新的布尔值。
@property (readonly, nonatomic, getter=isUpdating) BOOL updating;

//用户的地理位置，知道当 showsUserLocation = NO或者用户的location还没有确定
@property (readonly, nonatomic) CLLocation *location;

//只有在MKUserTrackingModeFollowWithHeading，heading ==nil; 方位
@property (readonly, nonatomic) CLHeading *heading NS_AVAILABLE(10_9, 5_0);

//用户位置 annotation 的标题
@property (nonatomic, copy) NSString *title;

//用户位置 annotation 副标题
@property (nonatomic, copy) NSString *subtitle;

@end
