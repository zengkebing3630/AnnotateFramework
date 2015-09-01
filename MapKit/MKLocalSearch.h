//
//  MKLocalSearch.h
//  MapKit
//
//  Copyright (c) 2012-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKLocalSearchRequest;
@class MKLocalSearchResponse;

typedef void (^MKLocalSearchCompletionHandler)(MKLocalSearchResponse *response, NSError *error);

//允许开发者得到一个地理区域内附近的兴趣点。
@interface MKLocalSearch : NSObject

//以一个地理区域内附近的兴趣点请求 初始化，在调用-startWithCompletionHandler: 去请求
- (instancetype)initWithRequest:(MKLocalSearchRequest *)request NS_DESIGNATED_INITIALIZER;

//开始请求，运行在主线程中，必须在 [MKLocalSearch isSearching] 返回NO调用
- (void)startWithCompletionHandler:(MKLocalSearchCompletionHandler)completionHandler;

//结束请求
- (void)cancel;

//是否正在查询
@property (nonatomic, readonly, getter=isSearching) BOOL searching;

@end
