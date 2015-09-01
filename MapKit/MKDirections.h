//
//  MKDirections.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKDirectionsRequest;
@class MKDirectionsResponse;
@class MKETAResponse;

typedef void (^MKDirectionsHandler)(MKDirectionsResponse *response, NSError *error);
typedef void (^MKETAHandler)(MKETAResponse *response, NSError *error);

// MKDirections用于计算方向
//从apple服务器获取数据的连接类
@interface MKDirections : NSObject

//初始化方法
- (instancetype)initWithRequest:(MKDirectionsRequest *)request NS_DESIGNATED_INITIALIZER;

//开始计算线路信息,completionHandler必须运行在主线程，在[MKDirections isCalculating] 返回NO时才可以调用
- (void)calculateDirectionsWithCompletionHandler:(MKDirectionsHandler)completionHandler;
//开始计算时间信息，在[MKDirections isCalculating] 返回NO时才可以调用，completionHandler必须运行在主线程
- (void)calculateETAWithCompletionHandler:(MKETAHandler)completionHandler;
//取消
- (void)cancel;
//是否正在计算
@property (nonatomic, readonly, getter=isCalculating) BOOL calculating;

@end
