//
//  MKPinAnnotationView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotationView.h>

typedef NS_ENUM(NSUInteger, MKPinAnnotationColor) { //大头针视图颜色
    MKPinAnnotationColorRed = 0, //默认 红色
    MKPinAnnotationColorGreen, //绿色
    MKPinAnnotationColorPurple //紫色
} NS_ENUM_AVAILABLE(10_9, 3_0);

//提供一个具体的标注视图，在地图中现实一个别针图标。使用本类时，一可以设置别针的类型以及是否 需要动画放置到地图中。
@interface MKPinAnnotationView : MKAnnotationView
// 大头针视图颜色
@property (nonatomic) MKPinAnnotationColor pinColor;
// 添加大头针动画
@property (nonatomic) BOOL animatesDrop;

@end
