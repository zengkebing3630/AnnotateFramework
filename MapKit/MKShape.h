//
//  MKShape.h
//  MapKit
//
//  Copyright (c) 2010-2014, Apple Inc. All rights reserved.
//

#import <MapKit/MKFoundation.h>
#import <MapKit/MKAnnotation.h>

MK_CLASS_AVAILABLE(10_9, 4_0)

//一个抽象类，定义了所有基于形状的标注对象的基本属性。本类必须子类化不能直接使用。子类负责定义形状的几何信 息，还要提供继承自 MBAnnotation 协议的坐标属性
@interface MKShape : NSObject <MKAnnotation>

@property (nonatomic, copy) NSString *title;//本字符串显示在关联标注视图弹出气泡中。本属性的默认值为nil。
@property (nonatomic, copy) NSString *subtitle;//本字符串显示在关联标注视图弹出气泡中。本属性的默认值为nil

@end
