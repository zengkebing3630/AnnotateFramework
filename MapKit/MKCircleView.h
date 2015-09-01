//
//  MKCircleView.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MKCircle.h>
#import <MapKit/MKFoundation.h>
#import <MapKit/MKOverlayPathView.h>

//负责提供 MBCircle 标注对象的视觉展示。这个视图填充绘制这个标注表示的圆形区域。
//你可以修改继承自 MBOverlayPathView　 类的属性来更变圆形的颜色或者其它绘制属性。本类通常直接使用而不是子类化
@interface MKCircleView : MKOverlayPathView

//使用指定的圆形覆盖层对象初始化并返回一个新的覆盖层视图。 
- (instancetype)initWithCircle:(MKCircle *)circle;

//包含圆形区域绘制信息的覆盖层对象。 
@property (nonatomic, readonly) MKCircle *circle;

@end
