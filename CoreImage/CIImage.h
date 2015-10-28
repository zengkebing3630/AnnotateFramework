/* CoreImage - CIImage.h

   Copyright (c) 2011 Apple, Inc.
   All rights reserved. */

#import <Foundation/Foundation.h>
#import <CoreImage/CoreImageDefines.h>
#import <CoreVideo/CoreVideo.h>

/*
	图片（CIImage）： 代表一个图像，可代表关联后输出的图像。
 */
@class NSData, NSURL, NSDictionary;

@class CIContext, CIFilter, CIFilterShape, CIColor;

CORE_IMAGE_CLASS_EXPORT
@interface CIImage : NSObject <NSCoding, NSCopying>
{
#if !TARGET_OS_IPHONE
    __strong void *_state;
#endif
	void *_priv;
}

/*
	像素格式
 */

typedef int CIFormat;

CORE_IMAGE_EXPORT CIFormat kCIFormatARGB8 __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_6_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatBGRA8 __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA8 __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

CORE_IMAGE_EXPORT CIFormat kCIFormatRGBA16 __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAf __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_7_0);

/* RGBA values that are IEEE 754-2008 half float compliant. */
CORE_IMAGE_EXPORT CIFormat kCIFormatRGBAh __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_6_0);

/* Image dictionary keys. */

/*
	图片属性字典里面的 KEYS
 */

 //颜色空间  CGColorSpaceRef || [NSNull null]
CORE_IMAGE_EXPORT NSString *kCIImageColorSpace;

/*
	图片属性：imageWithCGImage:options:, initWithCGImage:options:, imageWithData:options:, initWithData:options:
	如果不设置，则properties自动设置成CGImageSourceCopyPropertiesAtIndex
	如果设置成[NSNull null]，properties清空
 */
CORE_IMAGE_EXPORT NSString *kCIImageProperties __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

//从 Image创建CIImage
+ (CIImage *)imageWithCGImage:(CGImageRef)image;
+ (CIImage *)imageWithCGImage:(CGImageRef)image options:(NSDictionary *)d;

//从layer创建CIImage
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
+ (CIImage *)imageWithCGLayer:(CGLayerRef)layer options:(NSDictionary *)d __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

 //创建一个新图像。
 //data:bitmap位图数据
 //bpr:bitmap位图数据大小
 //size:图片的Size
 //format：像素格式
 //colorSpace:颜色空间
+ (CIImage *)imageWithBitmapData:(NSData *)d bytesPerRow:(size_t)bpr
 size:(CGSize)size format:(CIFormat)f colorSpace:(CGColorSpaceRef)cs;

/* Creates a new image referencing the contents of the GL texture object
 * with identifier 'name'. The texture should have dimensions as defined
 * by 'size'. If 'flag' is true, then the contents of the texture are
 * flipped vertically when referenced. 'cs' defines the color space
 * that the image is defined in, if nil, the texture is not color matched.*/
+ (CIImage *)imageWithTexture:(unsigned int)name size:(CGSize)size
 flipped:(BOOL)flag colorSpace:(CGColorSpaceRef)cs __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_6_0);

//从文件里面创建一个新图像
+ (CIImage *)imageWithContentsOfURL:(NSURL *)url;
+ (CIImage *)imageWithContentsOfURL:(NSURL *)url options:(NSDictionary *)d;

//从二进制创建一个新图像
+ (CIImage *)imageWithData:(NSData *)data;
+ (CIImage *)imageWithData:(NSData *)data options:(NSDictionary *)d;

/* Creates a new image whose data is from the contents of a CVImageBuffer. */
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
+ (CIImage *)imageWithCVImageBuffer:(CVImageBufferRef)imageBuffer
 options:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Creates a new image whose data is from the contents of a CVPixelBufferRef. */
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)buffer __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);
+ (CIImage *)imageWithCVPixelBuffer:(CVPixelBufferRef)buffer options:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

/* Creates a new image from the contents of an IOSurface. */
#if !TARGET_OS_IPHONE
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
+ (CIImage *)imageWithIOSurface:(IOSurfaceRef)surface options:(NSDictionary *)d __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
#endif

/* Return or initialize a new image with an infinite amount of the color
 * 'color'. */
+ (CIImage *)imageWithColor:(CIColor *)color;

/* Create an empty Image. */
+ (CIImage *)emptyImage;

/* Initializers. */

- (id)initWithCGImage:(CGImageRef)image;
- (id)initWithCGImage:(CGImageRef)image options:(NSDictionary *)d;

- (id)initWithCGLayer:(CGLayerRef)layer __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
- (id)initWithCGLayer:(CGLayerRef)layer options:(NSDictionary *)d __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

- (id)initWithData:(NSData *)data;
- (id)initWithData:(NSData *)data options:(NSDictionary *)d;

- (id)initWithBitmapData:(NSData *)d bytesPerRow:(size_t)bpr size:(CGSize)size 
format:(CIFormat)f colorSpace:(CGColorSpaceRef)c;

- (id)initWithTexture:(unsigned int)name size:(CGSize)size flipped:(BOOL)flag colorSpace:(CGColorSpaceRef)cs __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_6_0);

- (id)initWithContentsOfURL:(NSURL *)url;
- (id)initWithContentsOfURL:(NSURL *)url options:(NSDictionary *)d;

#if !TARGET_OS_IPHONE
- (id)initWithIOSurface:(IOSurfaceRef)surface __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
- (id)initWithIOSurface:(IOSurfaceRef)surface options:(NSDictionary *)d __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
#endif

- (id)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
- (id)initWithCVImageBuffer:(CVImageBufferRef)imageBuffer options:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

- (id)initWithCVPixelBuffer:(CVPixelBufferRef)buffer __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);
- (id)initWithCVPixelBuffer:(CVPixelBufferRef)buffer options:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_5_0);

- (id)initWithColor:(CIColor *)color;

/* Returns a new image representing the original image with the transform
 * 'matrix' appended to it. */
- (CIImage *)imageByApplyingTransform:(CGAffineTransform)matrix;

/* Returns a new image representing the original image with a transform
 * appied to it based on an orientation value.
 * Orientation values from 1 to 8 as defined in the TIFF spec are supported.
 * Returns original image if the image is of infinite extent. */
- (CIImage *)imageByApplyingOrientation:(int)orientation __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Returns a CGAffineTransform for an orientation value that can be appied to an image.
 * Orientation values from 1 to 8 as defined in the TIFF spec are supported.
 * Returns CGAffineTransformIdentity if the image is of infinite extent.*/
- (CGAffineTransform)imageTransformForOrientation:(int)orientation __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Return a new image formed by compositing the receiver image over 'dest'. */
- (CIImage *)imageByCompositingOverImage:(CIImage *)dest __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Return a new image cropped to a rectangle. */
- (CIImage *)imageByCroppingToRect:(CGRect)r;

/* Return a new infinte image by replicating the pixels of the receiver image's extent. */
- (CIImage *)imageByClampingToExtent __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* Return a rect the defines the bounds of non-(0,0,0,0) pixels */
- (CGRect)extent;

/* A convenience method for applying a filter to an image.
 * The method returns outputImage of the filter after setting the
 * filter's inputImage to the method receiver and other parameters
 * from from the key/value pairs of 'params'. */
- (CIImage *)imageByApplyingFilter:(NSString *)filterName withInputParameters:(NSDictionary*)params __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);


/* Returns the metadata properties of an image. If the image is the
 * output of one or more CIFilters, then the metadata of the root inputImage
 * will be returned. See also kCIImageProperties. */
- (NSDictionary*)properties __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/* Return the Domain of Definition of the image. */
- (CIFilterShape *)definition __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Returns the URL of the image when the image was created using the imageWithContentsOfURL APIs.
 * This method will return nil, if the URL cannot be determined. */
- (NSURL *)url __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Returns if possible the color space of the image it was defined in.
 * This method will return nil, if the color space cannot be determined. */
- (CGColorSpaceRef)colorSpace __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Returns the rectangle of image 'im" that is required to render
 * the rectangle 'r' of the receiver.  This may return a null rect. */
- (CGRect)regionOfInterestForImage:(CIImage *)im inRect:(CGRect)r __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_6_0);

@end

@interface CIImage (AutoAdjustment)

/* Image auto adjustment keys. */

/* These are the options dictionary keys which can be specified when calling 
 * the autoAdjustmentFiltersWithOptions: method.
 */

/* If CFBoolean value is false then dont attempt to apply enhancement filters.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT NSString *kCIImageAutoAdjustEnhance __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/* If CFBoolean value is false then dont attempt to apply red eye filter.
 * If not specified, the option is assumed to be present and true.
 */
CORE_IMAGE_EXPORT NSString *kCIImageAutoAdjustRedEye __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/* If value is an array of detected CIFeatures, then use these features
 * to determine the AutoAdjustEnhance and or AutoAdjustRedEye filters.
 * If not specified, receiver will call CIDetector.
 */
CORE_IMAGE_EXPORT NSString *kCIImageAutoAdjustFeatures __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

/* If CFBoolean value is false then don't attempt to apply crop filter.
 * If not specified, the option is assumed to be present and false.
 */
CORE_IMAGE_EXPORT NSString *kCIImageAutoAdjustCrop __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);

/* If CFBoolean value is false then don't attempt to apply auto-level.
 * If not specified, the option is assumed to be present and false.
 */
CORE_IMAGE_EXPORT NSString *kCIImageAutoAdjustLevel __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_8_0);


/* Return an array of filters to apply to an image to improve its 
 * skin tones, saturation, contrast, shadows and repair red-eyes or LED-eyes.
 *
 * The options dictionary can contain a CIDetectorImageOrientation key value. 
 * The value for this key is an integer NSNumber from 1..8 such as that
 * found in kCGImagePropertyOrientation.  If present, the adjustment will be done
 * based on that orientation but any coordinates in the returned filters will
 * still be based on those of the sender image.
 */
- (NSArray *)autoAdjustmentFilters __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);
- (NSArray *)autoAdjustmentFiltersWithOptions:(NSDictionary *)dict __OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_5_0);

@end
