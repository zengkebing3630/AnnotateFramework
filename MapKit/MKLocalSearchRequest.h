//
//  MKLocalSearchRequest.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>

//地理区域内附近的兴趣点 请求
@interface MKLocalSearchRequest : NSObject <NSCopying>

@property (nonatomic, copy) NSString *naturalLanguageQuery; //兴趣点关键词
@property (nonatomic, assign) MKCoordinateRegion region;//边界地域

@end
