//
//  MKAnnotationView.h
//  MapKit
//
//  Copyright (c) 2009-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

//浮动框（callout）有变化时，发通知
MK_EXTERN NSString * const MKAnnotationCalloutInfoDidChangeNotification;

typedef NS_ENUM(NSUInteger, MKAnnotationViewDragState) {//大头针状态
    MKAnnotationViewDragStateNone = 0,      // 无状态
    MKAnnotationViewDragStateStarting,      // 开始
    MKAnnotationViewDragStateDragging,      // 拖动
    MKAnnotationViewDragStateCanceling,     // 取消
    MKAnnotationViewDragStateEnding         // 结束
} NS_ENUM_AVAILABLE(10_9, 4_0);

@protocol MKAnnotation;

@interface MKAnnotationView : UIView
//初始化大头针，以大头针信息及标示
- (instancetype)initWithAnnotation:(id <MKAnnotation>)annotation reuseIdentifier:(NSString *)reuseIdentifier;
//标识这个标注视图可复用的字符串。
@property (nonatomic, readonly) NSString *reuseIdentifier; //标示

//当视图被移动到复用队列时调用。重写，需要实现[super prepareForReuse]
- (void)prepareForReuse;

// 当前和视图关联的标注对象，包括标题、子标题、地理位置。
@property (nonatomic, strong) id <MKAnnotation> annotation;
// 大头针图片
@property (nonatomic, strong) UIImage *image;
// 点击大头针时弹出详情信息视图的偏移量
@property (nonatomic) CGPoint centerOffset;

//放置弹出气泡的偏移量（像素单位）
@property (nonatomic) CGPoint calloutOffset;

//左浮动框的偏移量
@property (nonatomic) CGPoint leftCalloutOffset;

//右浮动框的偏移量
@property (nonatomic) CGPoint rightCalloutOffset;

//可接受点击事件，默认YES，指示标注是否启用的布尔值。
@property (nonatomic, getter=isEnabled) BOOL enabled;

//可以设置高亮，默认NO，指示标注视图是否高亮的布尔值
@property (nonatomic, getter=isHighlighted) BOOL highlighted;

// 是否被选中状态，指示标注视当前是否被选中的布尔值。
@property (nonatomic, getter=isSelected) BOOL selected;
- (void)setSelected:(BOOL)selected animated:(BOOL)animated;

//是否支持显示浮动框，当YES，annotation Is selected ，浮动框）就显示，指示标注视图能否弹出气泡显示额外的信息。
@property (nonatomic) BOOL canShowCallout;
// 弹出详情左侧视图
@property (strong, nonatomic) UIView *leftCalloutAccessoryView;
// 弹出详情右侧视图
@property (strong, nonatomic) UIView *rightCalloutAccessoryView;

//是否可以拖动，如果 draggable = YES，和设置了 id<MKAnnotation> setCoordinate ，用户就可以在Map上拖动大头针，指示标注视图是否能被拖动的布尔值。
@property (nonatomic, getter=isDraggable) BOOL draggable NS_AVAILABLE(10_9, 4_0);

//大头针的状态，标注视图当前的拖动状态。
@property (nonatomic) MKAnnotationViewDragState dragState NS_AVAILABLE(10_9, 4_0);

//设置标注视图当前的拖动状态。
- (void)setDragState:(MKAnnotationViewDragState)newDragState animated:(BOOL)animated NS_AVAILABLE(10_9, 4_2);

@end
