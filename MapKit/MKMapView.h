//
//  MKMapView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKAnnotationView.h>
#import <MapKit/MKFoundation.h>
#import <MapKit/MKGeometry.h>
#import <MapKit/MKTypes.h>
#import <MapKit/MKOverlay.h>
#import <MapKit/MKOverlayRenderer.h>
#if TARGET_OS_IPHONE
#import <MapKit/MKOverlayView.h>
#endif

@class MKUserLocation;
@class MKMapCamera;

@protocol MKMapViewDelegate;

typedef NS_ENUM(NSInteger, MKUserTrackingMode) {//跟踪类型
	MKUserTrackingModeNone = 0, //不进行用户位置跟踪
	MKUserTrackingModeFollow, // 跟踪用户位置
	MKUserTrackingModeFollowWithHeading, //跟踪用户位置并且跟踪用户前进方向
} NS_ENUM_AVAILABLE(NA, 5_0);

/*
 提供可嵌入的地图界面，类似于地图应用提供的界面。
 你直接使用这个类来显示地图信息、在应用中控制地图的 内容。
 你可以给定一个坐标作为地图的中心，指定想要显示的范围的大小，使用自定义的信息标注地图。
 在你初始化地图视图的时候，你需要指定地图显示的初始范围。
 你可以通过设置 region 属性来完成这个操作。
 范围是由中心点 和水平与竖直距离（跨度）定义。
 跨度决定了在给定点的下多少地图可视，同时你可以用它设置缩放等级。
 指定一个大的跨度将导致 用户看见一个大的地理区域对应一个低的缩放等级。
 指定一个小的跨度将导致用户看见一个更狭窄的地理区域对应一个高的缩放等级。
 除了通过编码设置跨度外， MKMapView 类支持许多标准接口用于改变地图的位置和缩放等级。
 地图视图支持双击和双 指手势来滚动、放大和缩小地图。默认启用这些手势，但可以通过设置scrollEnabled和zoomEnabled属性来禁用手势。
 数据类型 MBMapPoint 、 MBMapSize 和 MBMapRect 用来指定地图上的位置和距离。
 你可以使用这些类型的数据来指定 地图的可视范围和指定覆盖层的位置。
 你可以提供一个委托对象来获得地图视图运行的信息。
 地图视图调用你自定义委托的方法让委托知道地图状态的改变同时调整自定 义标注的显示， 下面的“标注地图”中将有更加详细的描述。
 委托的对象可以是你应用中的任何对象只要它遵从 MKMapViewDelegate 协议。参考 MKMapViewDelegate 可以获得更多实现委托对象的信息
 */
@interface MKMapView : UIView <NSCoding>

@property (nonatomic, weak) id <MKMapViewDelegate> delegate;
//地图类型
@property (nonatomic) MKMapType mapType;
//当然地图显示区域, regionThatFits:调整指定范围的长宽比以确保它和地图试图的框架匹配
@property (nonatomic) MKCoordinateRegion region;
//设置地图显示区域，用于控制当前屏幕显示地图范围
- (void)setRegion:(MKCoordinateRegion)region animated:(BOOL)animated;

// 地图中心点位置,不改变zoom level
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;
//设置地图中心点位置
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

//调整指定范围的长宽比以确保它和地图试图的框架匹配。 
- (MKCoordinateRegion)regionThatFits:(MKCoordinateRegion)region;

//改变地图的当前可视部分，同时允许指定边缘额外的间隔。
@property (nonatomic) MKMapRect visibleMapRect;
- (void)setVisibleMapRect:(MKMapRect)mapRect animated:(BOOL)animate;

//加上指定的插值调整指定地图矩形的长宽比。 
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect;

//改变地图的当前可视部分，同时允许指定边缘额外的间隔。
//mapRect	将在地图视图中可视的地图矩形。
//insets	使指定矩形周围额外空间可视的数值（以屏幕点来计算）。
//animate	如果你想地图视图动画过渡到新的地图矩形，指定YES；如果你想地图立即定位到指定的矩形，指定NO。
- (void)setVisibleMapRect:(MKMapRect)mapRect edgePadding:(UIEdgeInsets)insets animated:(BOOL)animate;
- (MKMapRect)mapRectThatFits:(MKMapRect)mapRect edgePadding:(UIEdgeInsets)insets;


@property (nonatomic, copy) MKMapCamera *camera NS_AVAILABLE(10_9, 7_0);//将允许开发者调整3D地图中视角的位置,创造出一种影院级别的镜头切换效果
- (void)setCamera:(MKMapCamera *)camera animated:(BOOL)animated NS_AVAILABLE(10_9, 7_0);

// 将地理坐标（经纬度）转化为数学坐标（UIKit坐标）
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(UIView *)view;
//将数学坐标转换为地理坐标
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(UIView *)view;
//将地理区域转化成数学坐标（UIKit坐标）
- (CGRect)convertRegion:(MKCoordinateRegion)region toRectToView:(UIView *)view;
//将数学坐标转换为地理区域
- (MKCoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(UIView *)view;


//确定用户是否能够通过手势对地图进行缩放的布尔值。
@property (nonatomic, getter=isZoomEnabled) BOOL zoomEnabled;
//确定用户是否能够缩放地图的布尔值。
@property (nonatomic, getter=isScrollEnabled) BOOL scrollEnabled;
// Rotate and pitch are enabled by default on Mac OS X and on iOS 7.0 and later.
//禁用或开启旋转手势
@property (nonatomic, getter=isRotateEnabled) BOOL rotateEnabled NS_AVAILABLE(10_9, 7_0);
//设置是否支持3D效果
@property (nonatomic, getter=isPitchEnabled) BOOL pitchEnabled NS_AVAILABLE(10_9, 7_0);

#if !TARGET_OS_IPHONE
@property (nonatomic) BOOL showsCompass NS_AVAILABLE(10_9, NA);
@property (nonatomic) BOOL showsZoomControls NS_AVAILABLE(10_9, NA);
//指示是否显示比例尺的布尔值。 
@property (nonatomic) BOOL showsScale NS_AVAILABLE(10_10, NA);
#endif

//设置是否显示兴趣点，例如学校，医院等，只在MKMapTypeStandard and MKMapTypeHybrid有效
@property (nonatomic) BOOL showsPointsOfInterest NS_AVAILABLE(10_9, 7_0); // Affects MKMapTypeStandard and MKMapTypeHybrid
//设置是否显示建筑物轮廓，只在标准的地图中有效，MKMapTypeStandard
@property (nonatomic) BOOL showsBuildings NS_AVAILABLE(10_9, 7_0); // Affects MKMapTypeStandard

//显示用户位置
@property (nonatomic) BOOL showsUserLocation;

//用户位置
@property (nonatomic, readonly) MKUserLocation *userLocation;

#if TARGET_OS_IPHONE
//设置更新用户位置的模式,当显示用户位置设置为YES，这个方法也设置了后，地图框架为我们直接集成了定位，地图上就会显示我们的位置
@property (nonatomic) MKUserTrackingMode userTrackingMode NS_AVAILABLE(NA, 5_0);
- (void)setUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated NS_AVAILABLE(NA, 5_0);
#endif

// 判断用户当前位置是否可见（只读属性）
@property (nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;


// 添加大头针
- (void)addAnnotation:(id <MKAnnotation>)annotation;
//添加大头针数组
- (void)addAnnotations:(NSArray *)annotations;
//删除大头针
- (void)removeAnnotation:(id <MKAnnotation>)annotation;
// 删除大头针数组
- (void)removeAnnotations:(NSArray *)annotations;
//已经加载在map上的大头针数组
@property (nonatomic, readonly) NSArray *annotations;
//mapRect矩形区域内所有的大头针聚合
- (NSSet *)annotationsInMapRect:(MKMapRect)mapRect NS_AVAILABLE(10_9, 4_2);

//如果有的话返回和指定标注关联的标注视图
- (MKAnnotationView *)viewForAnnotation:(id <MKAnnotation>)annotation;

// 从缓存池中取出大头针，类似于UITableView中取出UITableViewCell，为了进行性能优化而设计
- (MKAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;

// 选中指定的大头针
- (void)selectAnnotation:(id <MKAnnotation>)annotation animated:(BOOL)animated;
// 取消选中指定的大头针
- (void)deselectAnnotation:(id <MKAnnotation>)annotation animated:(BOOL)animated;
//选择大头针数组
@property (nonatomic, copy) NSArray *selectedAnnotations;

//当前标注视图显示的可视矩形。
//当mapView:didAddAnnotationViews:调用之后才能使用
@property (nonatomic, readonly) CGRect annotationVisibleRect;

// Position the map such that the provided array of annotations are all visible to the fullest extent possible.
- (void)showAnnotations:(NSArray *)annotations animated:(BOOL)animated NS_AVAILABLE(10_9, 7_0);

@end

typedef NS_ENUM(NSInteger, MKOverlayLevel) {
    MKOverlayLevelAboveRoads = 0, // 覆盖物位于道路之上
    MKOverlayLevelAboveLabels    //覆盖物位于标签之上
} NS_ENUM_AVAILABLE(10_9, 7_0);

@interface MKMapView (OverlaysAPI)

// Overlays are models used to represent areas to be drawn on top of the map.
// This is in contrast to annotations, which represent points on the map.
// Implement -mapView:rendererForOverlay: on MKMapViewDelegate to return the renderer for each overlay.
//向地图中添加一个覆盖层。 level：等级
- (void)addOverlay:(id <MKOverlay>)overlay level:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);
//向地图中添加一组覆盖层。 
- (void)addOverlays:(NSArray *)overlays level:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);
//从地图视图中移除一个覆盖层。 
- (void)removeOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 4_0);
//从地图中移除一个或多个覆盖层。 
- (void)removeOverlays:(NSArray *)overlays NS_AVAILABLE(10_9, 4_0);

//插入一个覆盖层到和地图关联的覆盖层对象列表中。
- (void)insertOverlay:(id <MKOverlay>)overlay atIndex:(NSUInteger)index level:(MKOverlayLevel)level;
//插入一个覆盖层到另一个的上面。 
- (void)insertOverlay:(id <MKOverlay>)overlay aboveOverlay:(id <MKOverlay>)sibling;
//插入一个覆盖层到另一个的下面。
- (void)insertOverlay:(id <MKOverlay>)overlay belowOverlay:(id <MKOverlay>)sibling;

//交换两个覆盖层的位置。 
- (void)exchangeOverlay:(id <MKOverlay>)overlay1 withOverlay:(id <MKOverlay>)overlay2;

//当前和地图视图关联的覆盖层。
@property (nonatomic, readonly) NSArray *overlays NS_AVAILABLE(10_9, 4_0);
//level相关的覆盖物
- (NSArray *)overlaysInLevel:(MKOverlayLevel)level NS_AVAILABLE(10_9, 7_0);

// Current renderer for overlay; returns nil if the overlay is not shown.
- (MKOverlayRenderer *)rendererForOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 7_0);

#if TARGET_OS_IPHONE
// Currently displayed view for overlay; returns nil if the view has not been created yet.
// Prefer using MKOverlayRenderer and -rendererForOverlay.
//如果有的话返回和指定覆盖层相关的视图。
- (MKOverlayView *)viewForOverlay:(id <MKOverlay>)overlay NS_DEPRECATED_IOS(4_0, 7_0);
#endif

// These methods operate implicitly on overlays in MKOverlayLevelAboveLabels and may be deprecated in a future release in favor of the methods that specify the level.
//向地图中添加一个覆盖层，level：MKOverlayLevelAboveLabels等级
- (void)addOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 4_0);
//向地图中添加一组覆盖层。 level：MKOverlayLevelAboveLabels等级
- (void)addOverlays:(NSArray *)overlays NS_AVAILABLE(10_9, 4_0);
//插入一个覆盖层到和地图关联的覆盖层对象列表中。level：MKOverlayLevelAboveLabels等级
- (void)insertOverlay:(id <MKOverlay>)overlay atIndex:(NSUInteger)index NS_AVAILABLE(10_9, 4_0);
//交换两个覆盖层的位置 level：MKOverlayLevelAboveLabels等级
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2 NS_AVAILABLE(10_9, 4_0);

@end

@protocol MKMapViewDelegate <NSObject>
@optional

//通知委托地图视图显示的范围将要改变
- (void)mapView:(MKMapView *)mapView regionWillChangeAnimated:(BOOL)animated;
//通知委托地图显示的范围刚改变。
- (void)mapView:(MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

//通知委托指定的地图视图将要请求一些地图数据。
- (void)mapViewWillStartLoadingMap:(MKMapView *)mapView;
//通知委托指定的地图视图成功的加载了需要的地图数据。
- (void)mapViewDidFinishLoadingMap:(MKMapView *)mapView;
// 通知委托指定的地图视图不能加载地图数据。
- (void)mapViewDidFailLoadingMap:(MKMapView *)mapView withError:(NSError *)error;

///开始渲染下载的地图块时调用
- (void)mapViewWillStartRenderingMap:(MKMapView *)mapView NS_AVAILABLE(10_9, 7_0);
//结束渲染下载的地图块时调用，fullyRendered：是否全部渲染
- (void)mapViewDidFinishRenderingMap:(MKMapView *)mapView fullyRendered:(BOOL)fullyRendered NS_AVAILABLE(10_9, 7_0);

// 返回与指定标注对象关联的视图。显示大头针时触发，返回大头针视图，通常自定义大头针可以通过此方法进行
- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation;

//通知委托一个或多个标注视图被添加到地图。
- (void)mapView:(MKMapView *)mapView didAddAnnotationViews:(NSArray *)views;

#if TARGET_OS_IPHONE
// mapView:annotationView:calloutAccessoryControlTapped: is called when the user taps on left & right callout accessory UIControls.
//通知委托用户点击了一个标注视图的附加按钮。
- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;
#endif

// 点击选中某个大头针时触发
- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view NS_AVAILABLE(10_9, 4_0);
//取消选中大头针时触发
- (void)mapView:(MKMapView *)mapView didDeselectAnnotationView:(MKAnnotationView *)view NS_AVAILABLE(10_9, 4_0);
//通知委托地图视图将要开始跟踪用户的位置。
- (void)mapViewWillStartLocatingUser:(MKMapView *)mapView NS_AVAILABLE(10_9, 4_0);
//通知委托地图视图停止跟踪用户的位置。
- (void)mapViewDidStopLocatingUser:(MKMapView *)mapView NS_AVAILABLE(10_9, 4_0);
//通知委托用户的位置已更新。（第一次定位到用户位置也会触发该方法
- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation NS_AVAILABLE(10_9, 4_0);
//通知委托尝试定位用户的位置失败。
- (void)mapView:(MKMapView *)mapView didFailToLocateUserWithError:(NSError *)error NS_AVAILABLE(10_9, 4_0);

//通知委托其中一个标注视图的拖动状态改变了。
- (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view didChangeDragState:(MKAnnotationViewDragState)newState 
   fromOldState:(MKAnnotationViewDragState)oldState NS_AVAILABLE(10_9, 4_0);

#if TARGET_OS_IPHONE
//定位用户位置模式改变时调用的方法
- (void)mapView:(MKMapView *)mapView didChangeUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated NS_AVAILABLE(NA, 5_0);
#endif
// 渲染地图覆盖物时触发
- (MKOverlayRenderer *)mapView:(MKMapView *)mapView rendererForOverlay:(id <MKOverlay>)overlay NS_AVAILABLE(10_9, 7_0);
- (void)mapView:(MKMapView *)mapView didAddOverlayRenderers:(NSArray *)renderers NS_AVAILABLE(10_9, 7_0);



// 当需要显示指定覆盖层对象时向委托请求覆盖层视图， -mapView:rendererForOverlay:
- (MKOverlayView *)mapView:(MKMapView *)mapView viewForOverlay:(id <MKOverlay>)overlay NS_DEPRECATED_IOS(4_0, 7_0);
//通知委托一个或多个覆盖层视图被添加到地图。Prefer -mapView:didAddOverlayRenderers:
- (void)mapView:(MKMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews NS_DEPRECATED_IOS(4_0, 7_0);


@end
