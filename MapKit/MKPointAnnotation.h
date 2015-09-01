//
//  MKPointAnnotation.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKShape.h>
#import <MapKit/MKFoundation.h>
#import <CoreLocation/CLLocation.h>

//定义了一个位于指定点的具体标注对象。当你只需要在地图中添加一个带标题的点时，你可以使用本类而不需要自己定义
@interface MKPointAnnotation : MKShape
//标注的坐标点，由经度和维度定义。 
@property (nonatomic, assign) CLLocationCoordinate2D coordinate;

@end
