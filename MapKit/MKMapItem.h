//
//  MKMapItem.h
//  MapKit
//
//  Copyright 2011-2012, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKPlacemark.h>

//地点节点类，包含此节点的许多地点信息
@interface MKMapItem : NSObject
//当前节点的地点信息对象,MKMapItem代表设备当前位置，isCurrentLocation == YES时placemark = nil;
@property (nonatomic, readonly) MKPlacemark *placemark;
//是否是当前位置
@property (nonatomic, readonly) BOOL isCurrentLocation;
//节点名称
@property (nonatomic, copy) NSString *name;
//电话号码
@property (nonatomic, copy) NSString *phoneNumber;
//网址
@property (nonatomic, strong) NSURL *url;
//将当前位置创建为节点
+ (MKMapItem *)mapItemForCurrentLocation;
//由一个位置信息创建节点
- (instancetype)initWithPlacemark:(MKPlacemark *)placemark;

//用于在地图上标注一个位置，打开苹果地图应用
- (BOOL)openInMapsWithLaunchOptions:(NSDictionary *)launchOptions;
// 可以标注多个位置外还可以进行多个位置之间的驾驶导航，打开苹果地图应用
+ (BOOL)openMapsWithItems:(NSArray *)mapItems launchOptions:(NSDictionary *)launchOptions;

@end
/*
	路线模式，常量
		MKLaunchOptionsDirectionsModeDriving  驾车模式
		MKLaunchOptionsDirectionsModeWalking 步行模式
*/
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeKey;
/*
	地图类型，枚举
		MKMapTypeStandard ：标准模式
		MKMapTypeSatellite ：卫星模式
		MKMapTypeHybrid  ：混合模式
*/
MK_EXTERN NSString * const MKLaunchOptionsMapTypeKey;
// 是否 显示交通状况，布尔型
MK_EXTERN NSString * const MKLaunchOptionsShowsTrafficKey;

  // 驾车模式
 MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeDriving;
 // 步行模式
MK_EXTERN NSString * const MKLaunchOptionsDirectionsModeWalking;

// 中心点坐标，CLLocationCoordinate2D类型
MK_EXTERN NSString * const MKLaunchOptionsMapCenterKey;
// 地图显示跨度，MKCoordinateSpan 类型
MK_EXTERN NSString * const MKLaunchOptionsMapSpanKey;
/*
3D地图效果，MKMapCamera类型
注意：此属性从iOS7及以后可用，前面的属性从iOS6开始可用
*/
MK_EXTERN NSString * const MKLaunchOptionsCameraKey;
