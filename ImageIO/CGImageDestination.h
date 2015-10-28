/*
 * ImageIO - CGImageDestination.h
 * Copyright (c) 2004-2010 Apple Inc. All rights reserved.
 *
 */

/*
	编辑图片，形成新的图片，图片数据目的地
 */

#ifndef CGIMAGEDESTINATION_H_
#define CGIMAGEDESTINATION_H_

#include <ImageIO/ImageIOBase.h>

typedef struct CGImageDestination *CGImageDestinationRef;

#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/CGImageSource.h>
#include <ImageIO/CGImageMetadata.h>

CF_IMPLICIT_BRIDGING_ENABLED

/*
	下面的选项设置用于CGImageDestinationAddImage 和 CGImageDestinationAddImageFromSource 的输出效果
	适用于单张图片 对应单个图片目的地
 */

//向CGImageDestinationRef设置写入图像目的地的图片的压缩比率,如果CGImageDestinationRef支持的话
//CFNumberRef 0.0~1.0
//0意为着最大压缩率
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationLossyCompressionQuality  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//向CGImageDestinationRef设置BackgroundColor,混合渲染图片 + BackgroundColor，CGImageDestinationRef不支持 alpha
//设置的Value == CGColorRef没有alpha，不设置默认白色
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationBackgroundColor  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//缩放图像的像素的最大宽度和高度。
//设置的Value == CFNumberRef
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationImageMaxPixelSize  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

//启用或禁用嵌入JPEG缩略图
//设置的Value == kCFBooleanTrue ||  kCFBooleanFalse ,默认kCFBooleanFalse
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationEmbedThumbnail  IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/*

	获取CGImageDestinationRef 信息方法
 */

//获取一个CFTypeID类型标示符用于CGImageDestinations
IMAGEIO_EXTERN CFTypeID CGImageDestinationGetTypeID(void)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//返回支持的目的地的Uniform Type Identifiers(UTIs)，可以用CFShow()来打印结果 一般格式：com.apple.pict,publick.jpeg,public.tiff等
IMAGEIO_EXTERN CFArrayRef CGImageDestinationCopyTypeIdentifiers(void)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

/*
	提供三种创建图片CGImageDestinationRef数据目的地的方法
 */
//用CGDataConsumerRef创建一个图像目的地，type:图像文件的类型标识符,count:数量的图像（不包括缩略图）,options选项:可用于请求附加创建选项,无则填NULL
IMAGEIO_EXTERN CGImageDestinationRef CGImageDestinationCreateWithDataConsumer(CGDataConsumerRef consumer, CFStringRef type, size_t count, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//用CFMutableDataRef二进制数据创建一个图像目的地，type:图像文件的类型标识符,count:数量的图像（不包括缩略图）,options选项:可用于请求附加创建选项,无则填NULL
IMAGEIO_EXTERN CGImageDestinationRef CGImageDestinationCreateWithData(CFMutableDataRef data, CFStringRef type, size_t count, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//用CFURLRef文件数据创建一个图像目的地，type:图像文件的类型标识符,count:数量的图像（不包括缩略图）,options选项:可用于请求附加创建选项,无则填NULL
IMAGEIO_EXTERN CGImageDestinationRef CGImageDestinationCreateWithURL(CFURLRef url, CFStringRef type, size_t count, CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


/*
	增量向CGImageDestinationRef添加图片 三种方法
 */

//向CGImageDestinationRef设置下一张CGImageRef图像
//CGImageRef携带properties指定的可选属性
//如果在图像目标的原始计数中添加多个图像，则记录错误。
IMAGEIO_EXTERN void CGImageDestinationAddImage(CGImageDestinationRef idst, CGImageRef image, CFDictionaryRef properties)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//向CGImageDestinationRef设置下一张图像CGImageSourceRef下标为Index（0~）的图片
//CGImageSourceRef下标为Index（0~）的图片携带properties指定的可选属性
//如果properties == kCFNull,在目标相应的properties将被删除
IMAGEIO_EXTERN void CGImageDestinationAddImageFromSource(CGImageDestinationRef idst, CGImageSourceRef isrc, size_t index, CFDictionaryRef properties)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

 //向CGImageDestinationRef设置下一张图像CGImageRef数据是CGImageMetadataRef
//CGImageRef携带properties指定的可选属性
//如果在图像目标的原始计数中添加多个图像，则记录错误。
IMAGEIO_EXTERN void CGImageDestinationAddImageAndMetadata(CGImageDestinationRef idst, 
                                                          CGImageRef image,
                                                          CGImageMetadataRef metadata,
                                                          CFDictionaryRef options)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//向CGImageDestinationRef指定适用于所有的图像的properties
IMAGEIO_EXTERN void CGImageDestinationSetProperties(CGImageDestinationRef idst, CFDictionaryRef properties)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);

//向CGImageDestinationRef写入任何数据URL，CGDataConsumerRef等必须第一时间调用这个方法否则CGImageDestinationRef地址将失效,调用这个方法只会不能添加额外的数据。
//返回TRue则写入成功，false则是写入失败
IMAGEIO_EXTERN bool CGImageDestinationFinalize(CGImageDestinationRef idst)  IMAGEIO_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);


 /*
 	下面的KES是用于CGImageDestinationCopyImageSource 中的options

  */

//为CGImageDestinationRef设置元数据标记
//设置Value == CGImageMetadataRef,默认情况下，所有的EXIF，IPTC，和XMP标签将被取代
//使用kCGImageDestinationMergeMetadata合并标签与图像中的源存在的标签。
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationMetadata IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// 如果 kCFBooleanTrue  元数据将从源复制和kCGImageDestinationMetadata指定标签合并，
// 如果CGImageSourceRef源中不存在一个标记，则将添加。
// 如果标记存在于CGImageSourceRef源中，它将被更新。
// 元数据标签可以通过设置标签的价值kCFNull删除。
// 设置Value == CFBoooleanRef，默认kCFBooleanFalse
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationMergeMetadata IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//如果设置kCFBooleanTrue，XMP数据将不会被写入到目标,如果使用kCGImageDestinationMetadata，EXIF，IPTC将保留，但XMP包将不会被写入文件
// 设置Value == CFBoooleanRef，默认kCFBooleanFalse
IMAGEIO_EXTERN const CFStringRef kCGImageMetadataShouldExcludeXMP IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


//如果设置kCFBooleanTrue，GPS数据不会在XMP中被写入数据或相应的EXIF或corresponding
//这个标志不能过滤任何专有的位置数据可以存储在一个制造商的EXIF MakerNote或自定义XMP properties
// 设置Value == CFBoooleanRef，默认kCFBooleanFalse
IMAGEIO_EXTERN const CFStringRef kCGImageMetadataShouldExcludeGPS IMAGEIO_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

//更新图像元数据的DateTime参数,DateTime只有在原始图像中存在才会更新
//如果设置 value ==  CFStringRef 或 CFDateRef
//如果是 CFStringRef 写入在 Exif中DateTime 或 ISO8601中DateTime,Exif和ISO8601是互斥的在kCGImageDestinationMetadata
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationDateTime IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//更新图像元数据中的方向。图像数据本身不会旋转
//如果存在，该值应该是一个CFNumberRef从1到8。这个选项是互斥的kCGImageDestinationMetadata。
IMAGEIO_EXTERN const CFStringRef kCGImageDestinationOrientation IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//可以用来修改没有压缩的元数据
 //向CGImageDestinationRef无损拷贝的图像源的内容。
 //图像数据将不会被修改。通过添加上面定义的options的键和值，可以修改图像的元数据。
 //不能添加其他的图像应添加到图像的目的地。
 //此方法只会不用调用CGImageDestinationFinalize()会自动返回
 //图像类型的目的地必须匹配的图像源。如果操作成功，返回真实
 //如果出现错误，错误将返回CFErrorRef
 //此操作不支持所有图像格式
IMAGEIO_EXTERN bool CGImageDestinationCopyImageSource(CGImageDestinationRef idst, 
                                                      CGImageSourceRef isrc, 
                                                      CFDictionaryRef options, 
                                                      CFErrorRef* err) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


CF_IMPLICIT_BRIDGING_DISABLED

#endif /* CGIMAGEDESTINATION_H_ */
