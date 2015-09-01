//
//  MKPlacemark.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>
#import <CoreLocation/CLLocation.h>
#import <CoreLocation/CLPlacemark.h>

/*
 对象存储兴趣点数据给点的经度和维度。兴趣点数据包含了与指定坐标关联的省份，城市和街道等信息。
 兴趣点对象 一般由 MBReverseGeocoder 生成，你也可以自己创建。
 兴趣点也是一个标注并遵从 MBAnnotation 协议，标注的属性及方法包含了兴趣点的坐标及其它信息。
 因为它们是标注，你可 以把它们直接加到地图视图中。
 */
@interface MKPlacemark : CLPlacemark <MKAnnotation>


//用指定的坐标和地址字典初始化并返回兴趣点对象。address:ABRecordCopyValue(person, kABPersonAddressProperty).
- (instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate
                 addressDictionary:(NSDictionary *)addressDictionary;

//国家编码 CLGeocoder 中[MKPlacemark initWithPlacemark:]
@property (nonatomic, readonly) NSString *countryCode;

@end

/*
 NSDictionary * 	addressDictionary
 包含兴趣点key及value的地址数据字典。
 NSString * 	province
 兴趣点所在省份
 NSString * 	city
 兴趣点所在城市
 NSString * 	district
 兴趣点所在区
 NSString * 	POIDirection
 兴趣点所在方向
 NSString * 	distance
 兴趣点距离
 NSString * 	POIType
 兴趣点类型
 NSString * 	POIStreet
 兴趣点道路名称
 NSString * 	POICity
 兴趣点城市
 NSString * 	POIName
 兴趣点名字
 */