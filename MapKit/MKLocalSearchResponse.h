//
//  MKLocalSearchResponse.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

//地理区域内附近的兴趣点查询结果
@interface MKLocalSearchResponse : NSObject

//兴趣节点，MKMapItems
@property (nonatomic, readonly) NSArray *mapItems;
//兴趣节点区域
@property (nonatomic, readonly) MKCoordinateRegion boundingRegion;

@end
