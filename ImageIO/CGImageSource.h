/*
 * ImageIO - CGImageSource.h
 * Copyright (c) 2004-2010 Apple Inc. All rights reserved.
 *
 */

/*
	对图像数据读取任务的抽象，通过它可以获得图像对象、缩略图、图像的属性(包括Exif信息)
 */


#ifndef CGIMAGESOURCE_H_
#define CGIMAGESOURCE_H_

#include <ImageIO/ImageIOBase.h>

typedef struct CGImageSource *CGImageSourceRef;

#include <CoreGraphics/CoreGraphics.h>
#include "CGImageMetadata.h"

CF_IMPLICIT_BRIDGING_ENABLED

enum CGImageSourceStatus {
    kCGImageStatusUnexpectedEOF = -5, //将要开始
    kCGImageStatusInvalidData = -4, //无效的数据
    kCGImageStatusUnknownType = -3,  //不知道的类型
    kCGImageStatusReadingHeader = -2, //读取头部
    kCGImageStatusIncomplete = -1,  //不完整
    kCGImageStatusComplete = 0      //完整
};
typedef enum CGImageSourceStatus CGImageSourceStatus;

/*
下面是options 字典的KEY，创建CGImageSourceRef使用
 */

//指定图像源文件格式的 “最佳猜测”,如果指定，该键的值必须是一个cfstringref，更多Type信息看UTType.h
IMAGEIO_EXTERN const CFStringRef kCGImageSourceTypeIdentifierHint  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//该属性使用在 CGImageSourceCopyPropertiesAtIndex 和 CGImageSourceCreateImageAtIndex 方法中，是否缓存Cache
//如果指定这Value必须是CFBooleanRef，kCFBooleanFalse：表示没有缓存，kCFBooleanTrue表示缓存
//在64位框架中默认是kCFBooleanTrue，32位框架默认是kCFBooleanFalse
IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldCache  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//指定图像在创建时确定解码和是否缓存，
//如果指定这Value必须是CFBooleanRef，kCFBooleanFalse：表示图像解码将发生在渲染时间，kCFBooleanTrue表示创建时就确定decoding和cache
IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldCacheImmediately  IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

//指定图像(如果文件支持的)是否返回浮点性数据，返回Float数据需要额外资源来渲染
//如果指定这Value必须是CFBooleanRef，kCFBooleanFalse：表示返回整型，kCFBooleanTrue表示Float
//默认kCFBooleanFalse
IMAGEIO_EXTERN const CFStringRef kCGImageSourceShouldAllowFloat  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/*
	下面的KEY用于创建缩略图CGImageSourceCreateThumbnailAtIndex
 */

//指定是否自动创建了缩略图如果照片缺失，
//如果指定这Value必须是CFBooleanRef，kCFBooleanFalse：表示返回不自动创建，kCFBooleanTrue表示缩略图会从完整Image创建，受kCGImageSourceThumbnailMaxPixelSize限制，
//如果kCGImageSourceThumbnailMaxPixelSize没有设置，缩略图将是完整的图像的大小
//默认kCFBooleanFalse
IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailFromImageIfAbsent  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//指定一个缩略图是否应该从完整的图像中创建甚至已经存在缩略图。
//如果指定这Value必须是CFBooleanRef，kCFBooleanFalse：表示返回不自动创建，kCFBooleanTrue表示缩略图会从完整Image创建，受kCGImageSourceThumbnailMaxPixelSize限制，
//如果kCGImageSourceThumbnailMaxPixelSize没有设置，缩略图将是完整的图像的大小
//默认kCFBooleanFalse

IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailFromImageAlways  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//指定一个缩略图的最大宽度和高度
//如果不指定，缩略图的宽度和高度是不限的。缩略图可以作为图像本身一样大
//如果指定这Value必须是CFNumberRef
IMAGEIO_EXTERN const CFStringRef kCGImageSourceThumbnailMaxPixelSize  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//根据像素的方向和像素长宽比例确定是否旋转和缩放的缩略图。
//如果指定这Value必须是CFBooleanRef，kCFBooleanFalse||kCFBooleanTrue
//默认kCFBooleanFalse
IMAGEIO_EXTERN const CFStringRef kCGImageSourceCreateThumbnailWithTransform  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/*
	下面是从ImageSource中获取信息方法
 */

//获取一个CFTypeID类型标示符用于CGImageSources
IMAGEIO_EXTERN CFTypeID CGImageSourceGetTypeID (void)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//返回同一类型修饰符identifiers的数组，表示支持的图像源,可以用CFShow()来打印结果， 一般格式：com.apple.pict,publick.jpeg,public.tiff等
IMAGEIO_EXTERN CFArrayRef CGImageSourceCopyTypeIdentifiers(void)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//返回图片源CGImageSourceRef标识符的类型，此类型是源“容器”的类型，这不一定是容器中图像的类型,例如：JPEG2000图片格式是.icns格式，但是CGImageSourceGetType返回是com.apple.icns
IMAGEIO_EXTERN CFStringRef CGImageSourceGetType(CGImageSourceRef isrc)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//从CGImageSourceRef获取图像总数不包含缩略图，CGImageSourceRef可能有多张图片
IMAGEIO_EXTERN size_t CGImageSourceGetCount(CGImageSourceRef isrc)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//返回的图像源CGImageSourceRef的属性,这些属性适用于一般的容器
IMAGEIO_EXTERN CFDictionaryRef CGImageSourceCopyProperties(CGImageSourceRef isrc, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//返回在CGImageSourceRef下标为Index(0~)图像的属性，options选项:可用于请求附加创建选项,无则填NULL
IMAGEIO_EXTERN CFDictionaryRef CGImageSourceCopyPropertiesAtIndex(CGImageSourceRef isrc, size_t index, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//返回的图像源CGImageSourceRef的总体状况,CGImageSourceStatus状态可以用来CGImageSourceUpdateData后的状态变化
IMAGEIO_EXTERN CGImageSourceStatus CGImageSourceGetStatus(CGImageSourceRef isrc)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//返回数据源CGImageSourceRef下标为Index(0~)图像的属性的状况，CGImageSourceStatus状态可以用来CGImageSourceUpdateData后的状态变化
IMAGEIO_EXTERN CGImageSourceStatus CGImageSourceGetStatusAtIndex(CGImageSourceRef isrc, size_t index)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/*
	下面提供三种创建图片源CGImageSourceRef的方法
 */
//从CGDataProviderRef提供者(提供商) 创建一个图像源，options选项:可用于请求附加创建选项,无则填NULL
IMAGEIO_EXTERN CGImageSourceRef CGImageSourceCreateWithDataProvider(CGDataProviderRef provider, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//从CFDataRef二进制数据创建一个图像源，options选项:可用于请求附加创建选项,无则填NULL
IMAGEIO_EXTERN CGImageSourceRef CGImageSourceCreateWithData(CFDataRef data, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//从CFURLRef地址文件创建CGImageSourceRef，options选项:可用于请求附加创建选项,无则填NULL
IMAGEIO_EXTERN CGImageSourceRef CGImageSourceCreateWithURL(CFURLRef url, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//从CGImageSourceRef获取图片的源数据CGImageMetadataRef(使用情况看CGImageMetadata.h)，下标是Index(0~)，options选项:可用于请求附加创建选项,无则填NULL
IMAGEIO_EXTERN CGImageMetadataRef CGImageSourceCopyMetadataAtIndex (CGImageSourceRef isrc, size_t index, CFDictionaryRef options) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_7_0);

 /*
 	下面提供了三种创建CGImageRef 方法
  */
//从CGImageSourceRef获取图像，CGImageSourceRef可能有多张图片，index(0~)是第几张，options选项:可用于请求附加创建选项
IMAGEIO_EXTERN CGImageRef CGImageSourceCreateImageAtIndex(CGImageSourceRef isrc, size_t index, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//从CGImageSourceRef获取缩略图，CGImageSourceRef可能有多张图片，index(0~)是第几张，options选项:可用于请求附加创建选项
IMAGEIO_EXTERN CGImageRef CGImageSourceCreateThumbnailAtIndex(CGImageSourceRef isrc, size_t index, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

// 创建一个增量图像源，在创建时没有提供数据，确保以CGImageSourceUpdateDataProvider()或CGImageSourceUpdateData增量添加数据，options选项:可用于请求附加创建选项
IMAGEIO_EXTERN CGImageSourceRef CGImageSourceCreateIncremental(CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/*
	增量添加数据
 */
//向CGImageSourceRef增量添加数据，新的数据 = 以前的数据 + 新数据，final:数据是否完整的标志
IMAGEIO_EXTERN void CGImageSourceUpdateData(CGImageSourceRef isrc, CFDataRef data, bool final)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//从新的数据提供中心向CGImageSourceRef增量添加数据，新的数据 = 以前的数据 + 新数据，final:数据是否完整的标志
IMAGEIO_EXTERN void CGImageSourceUpdateDataProvider(CGImageSourceRef isrc, CGDataProviderRef provider, bool final)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/*
	删除图片Cache
 */
//从CGImageSourceRef中删除已经解码的图片，下标:index(0~)
IMAGEIO_EXTERN void CGImageSourceRemoveCacheAtIndex(CGImageSourceRef isrc, size_t index) IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);


CF_IMPLICIT_BRIDGING_DISABLED


#endif  /* CGIMAGESOURCE_H_ */
