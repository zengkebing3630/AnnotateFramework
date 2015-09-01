//
//  MKMapSnapshotter.h
//  MapKit
//
//  Copyright (c) 2013-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>

@class MKMapSnapshotOptions;
@class MKMapSnapshot;

typedef void (^MKMapSnapshotCompletionHandler)(MKMapSnapshot *snapshot, NSError *error);

//捕捉基于地图的图片
@interface MKMapSnapshotter : NSObject

- (instancetype)initWithOptions:(MKMapSnapshotOptions *)options NS_DESIGNATED_INITIALIZER;

//开始加载截图，默认主线程，在[MKMapSnapshotter loading]返回NO才可以调用
- (void)startWithCompletionHandler:(MKMapSnapshotCompletionHandler)completionHandler;
//开始加载截图，在线程queue，在[MKMapSnapshotter loading]返回NO才可以调用
- (void)startWithQueue:(dispatch_queue_t)queue completionHandler:(MKMapSnapshotCompletionHandler)completionHandler;
//取消加载
- (void)cancel;

//是否正在加载
@property (nonatomic, readonly, getter=isLoading) BOOL loading;

@end
