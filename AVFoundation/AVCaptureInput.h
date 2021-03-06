//AVCaptureInput.h

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreMedia/CMSync.h>
#if TARGET_OS_MAC && ! (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE || TARGET_OS_WIN32)
	#import <ApplicationServices/../Frameworks/CoreGraphics.framework/Headers/CGDirectDisplay.h>
#endif

@class AVCaptureInputPort;
@class AVCaptureInputInternal;

/*!
 @class AVCaptureInput
 @abstract
    AVCaptureInput is an abstract class that provides an interface for connecting capture input sources to an
    AVCaptureSession.

 @discussion
    Concrete instances of AVCaptureInput representing input sources such as cameras can be added to instances of
    AVCaptureSession using the -[AVCaptureSession addInput:] method. An AVCaptureInput vends one or more streams of
    media data. For example, input devices can provide both audio and video data. Each media stream provided by an input
    is represented by an AVCaptureInputPort object. Within a capture session, connections are made between
    AVCaptureInput instances and AVCaptureOutput instances via AVCaptureConnection objects that define the mapping
    between a set of AVCaptureInputPort objects and a single AVCaptureOutput.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureInput : NSObject 
{
@private
	AVCap/*
    File:  AVCaptureInput.h

    Framework:  AVFoundation
 
    Copyright 2010-2014 Apple Inc. All rights reserved.
*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMFormatDescription.h>
#import <CoreMedia/CMSync.h>
#if TARGET_OS_MAC && ! (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE || TARGET_OS_WIN32)
    #import <ApplicationServices/../Frameworks/CoreGraphics.framework/Headers/CGDirectDisplay.h>
#endif

@class AVCaptureInputPort;
@class AVCaptureInputInternal;

/*!
 @class AVCaptureInput
 @abstract
    AVCaptureInput is an abstract class that provides an interface for connecting capture input sources to an
    AVCaptureSession.

 @discussion
    Concrete instances of AVCaptureInput representing input sources such as cameras can be added to instances of
    AVCaptureSession using the -[AVCaptureSession addInput:] method. An AVCaptureInput vends one or more streams of
    media data. For example, input devices can provide both audio and video data. Each media stream provided by an input
    is represented by an AVCaptureInputPort object. Within a capture session, connections are made between
    AVCaptureInput instances and AVCaptureOutput instances via AVCaptureConnection objects that define the mapping
    between a set of AVCaptureInputPort objects and a single AVCaptureOutput.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureInput : NSObject  //录制输入
{
@private
    AVCaptureInputInternal *_inputInternal;
}

/*!
 @property ports
 @abstract
    The ports owned by the receiver.

 @discussion
    The value of this property is an array of AVCaptureInputPort objects, each exposing an interface to a single stream
    of media data provided by an input.
*/
//输入设备端口列表
@property(nonatomic, readonly) NSArray *ports;

@end


/*!
 @constant AVCaptureInputPortFormatDescriptionDidChangeNotification
 @abstract
    This notification is posted when the value of an AVCaptureInputPort instance's formatDescription property changes.

 @discussion
    The notification object is the AVCaptureInputPort instance whose format description changed.
*/
//输入设备的端口格式化描述变化时 广播通知
AVF_EXPORT NSString *const AVCaptureInputPortFormatDescriptionDidChangeNotification NS_AVAILABLE(10_7, 4_0);

@class AVCaptureInputPortInternal;

/*!
 @class AVCaptureInputPort
 @abstract
    An AVCaptureInputPort describes a single stream of media data provided by an AVCaptureInput and provides an
    interface for connecting that stream to AVCaptureOutput instances via AVCaptureConnection.

 @discussion
    Instances of AVCaptureInputPort cannot be created directly. An AVCaptureInput exposes its input ports via its ports
    property. Input ports provide information about the format of their media data via the mediaType and
    formatDescription properties, and allow clients to control the flow of data via the enabled property. Input ports
    are used by an AVCaptureConnection to define the mapping between inputs and outputs in an AVCaptureSession.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureInputPort : NSObject  //录制输入端口
{
@private
    AVCaptureInputPortInternal *_internal;
}

/*!
 @property input
 @abstract
    The input that owns the receiver.

 @discussion
    The value of this property is an AVCaptureInput instance that owns the receiver.
*/
@property(nonatomic, readonly) AVCaptureInput *input;  //录制输入设备

/*!
 @property mediaType
 @abstract
    The media type of the data provided by the receiver.

 @discussion
    The value of this property is a constant describing the type of media, such as AVMediaTypeVideo or AVMediaTypeAudio,
    provided by the receiver. Media type constants are defined in AVMediaFormat.h.
*/
@property(nonatomic, readonly) NSString *mediaType; //录制类型，音频或视频，定义在AVMediaFormat.h

/*!
 @property formatDescription
 @abstract
    The format of the data provided by the receiver.

 @discussion
    The value of this property is a CMFormatDescription that describes the format of the media data currently provided
    by the receiver. Clients can be notified of changes to the format by observing the
    AVCaptureInputPortFormatDescriptionDidChangeNotification.
*/
@property(nonatomic, readonly) CMFormatDescriptionRef formatDescription; //格式化描述，此属性起变化，会通过AVCaptureInputPortFormatDescriptionDidChangeNotification 来广播通知

/*!
 @property enabled
 @abstract
    Whether the receiver should provide data.

 @discussion
    The value of this property is a BOOL that determines whether the receiver should provide data to outputs when a
    session is running. Clients can set this property to fine tune which media streams from a given input will be used
    during capture. The default value is YES.
*/
@property(nonatomic, getter=isEnabled) BOOL enabled;  //Session是否可以提供数据到输出设备

/*!
 @property clock
 @abstract
 Provides access to the "native" clock used by the input port.
 @discussion
 The clock is read-only.
 */
@property(nonatomic, readonly) __attribute__((NSObject)) CMClockRef clock NS_AVAILABLE(10_9, 7_0);


@end

@class AVCaptureDevice;
@class AVCaptureDeviceInputInternal;

/*!
 @class AVCaptureDeviceInput
 @abstract
    AVCaptureDeviceInput is a concrete subclass of AVCaptureInput that provides an interface for capturing media from an
    AVCaptureDevice.

 @discussion
    Instances of AVCaptureDeviceInput are input sources for AVCaptureSession that provide media data from devices
    connected to the system, represented by instances of AVCaptureDevice.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureDeviceInput : AVCaptureInput   //录制输入设备,提供录制界面
{
@private
    AVCaptureDeviceInputInternal *_internal;
}

/*!
 @method deviceInputWithDevice:error:
 @abstract
    Returns an AVCaptureDeviceInput instance that provides media data from the given device.

 @param device
    An AVCaptureDevice instance to be used for capture.
 @param outError
    On return, if the given device cannot be used for capture, points to an NSError describing the problem.
 @result
    An AVCaptureDeviceInput instance that provides data from the given device, or nil, if the device could not be used
    for capture.

 @discussion
    This method returns an instance of AVCaptureDeviceInput that can be used to capture data from an AVCaptureDevice in
    an AVCaptureSession. This method attempts to open the device for capture, taking exclusive control of it if
    necessary. If the device cannot be opened because it is no longer available or because it is in use, for example,
    this method returns nil, and the optional outError parameter points to an NSError describing the problem.
*/
+ (id)deviceInputWithDevice:(AVCaptureDevice *)device error:(NSError **)outError; //得到AVCaptureDeviceInput，如设备不能录制，则返回nil

/*!
 @method initWithDevice:error:
 @abstract
    Creates an AVCaptureDeviceInput instance that provides media data from the given device.

 @param device
    An AVCaptureDevice instance to be used for capture.
 @param outError
    On return, if the given device cannot be used for capture, points to an NSError describing the problem.
 @result
    An AVCaptureDeviceInput instance that provides data from the given device, or nil, if the device could not be used
    for capture.

 @discussion
    This method creates an instance of AVCaptureDeviceInput that can be used to capture data from an AVCaptureDevice in
    an AVCaptureSession. This method attempts to open the device for capture, taking exclusive control of it if
    necessary. If the device cannot be opened because it is no longer available or because it is in use, for example,
    this method returns nil, and the optional outError parameter points to an NSError describing the problem.
*/
- (id)initWithDevice:(AVCaptureDevice *)device error:(NSError **)outError; //得到AVCaptureDeviceInput，如设备不能录制，则返回nil

/*!
 @property device
 @abstract
    The device from which the receiver provides data.

 @discussion
    The value of this property is the AVCaptureDevice instance that was used to create the receiver.
*/
@property(nonatomic, readonly) AVCaptureDevice *device; //当前用于录制的输入设备

@end


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@class AVCaptureScreenInputInternal;

/*!
 @class AVCaptureScreenInput
 @abstract
    AVCaptureScreenInput is a concrete subclass of AVCaptureInput that provides an interface for capturing media from
    a screen or portion thereof.

 @discussion
    Instances of AVCaptureScreenInput are input sources for AVCaptureSession that provide media data from
    one of the screens connected to the system, represented by CGDirectDisplayIDs.
*/
NS_CLASS_AVAILABLE(10_7, NA)
@interface AVCaptureScreenInput : AVCaptureInput  //录制输入设备,提供录制界面，可以满屏或者一个矩形，还可以显示
{
@private
    AVCaptureScreenInputInternal *_internal;
}

/*!
 @method initWithDisplayID:
 @abstract
    Creates an AVCaptureScreenInput instance that provides media data from the given display.
 
 @param displayID
    The id of the display from which to capture video.  CGDirectDisplayID is defined in <CoreGraphics/CGDirectDisplay.h>
 @result
    An AVCaptureScreenInput instance that provides data from the given screen, or nil, if the screen could not be used
    for capture.

 @discussion
    This method creates an instance of AVCaptureScreenInput that can be used to capture data from a display in
    an AVCaptureSession. This method validates the displayID. If the display cannot be used because it is not available
    on the system, for example, this method returns nil.
*/
- (id)initWithDisplayID:(CGDirectDisplayID)displayID;

/*!
 @property minFrameDuration
 @abstract
    A property indicating the screen input's minimum frame duration.

 @discussion
    An AVCaptureScreenInput's minFrameDuration is the reciprocal of its maximum frame rate.  This property
    may be used to request a maximum frame rate at which the input produces video frames.  The requested
    rate may not be achievable due to overall bandwidth, so actual frame rates may be lower.
*/
@property(nonatomic) CMTime minFrameDuration;//最小帧率

/*!
 @property cropRect
 @abstract
    A property indicating the bounding rectangle of the screen area to be captured in pixels.

 @discussion
    By default, AVCaptureScreenInput captures the entire area of the displayID with which it is associated.
    To limit the capture rectangle to a subsection of the screen, set the cropRect property, which
    defines a smaller section of the screen in the screen's coordinate system.  The origin (0,0) is
    the bottom-left corner of the screen.
*/
@property(nonatomic) CGRect cropRect; //录制矩形区域

/*!
 @property scaleFactor
 @abstract
    A property indicating the factor by which video buffers captured from the screen are to be scaled.

 @discussion
    By default, AVCaptureScreenInput captures the video buffers from the display at a scale factor
    of 1.0 (no scaling).  Set this property to scale the buffers by a given factor.  For instance,
    a 320x240 capture area with a scaleFactor of 2.0f produces video buffers at 640x480.
*/
@property(nonatomic) CGFloat scaleFactor;//放大因子 默认：1.0，320 * 240 ， 2.0：640 * 480

/*!
 @property capturesMouseClicks
 @abstract
    A property indicating whether mouse clicks should be highlighted in the captured output.

 @discussion
    By default, AVCaptureScreenInput does not highlight mouse clicks in its captured output.  If this
    property is set to YES, mouse clicks are highlighted (a circle is drawn around the mouse for the
    duration of the click) in the captured output.
*/
@property(nonatomic) BOOL capturesMouseClicks; //手標点击高亮 在录制输出

/*!
 @property capturesCursor
 @abstract
    A property indicating whether the cursor should be rendered to the captured output.

 @discussion
    By default, AVCaptureScreenInput draws the cursor in its captured output.  If this property
    is set to NO, the captured output contains only the windows on the screen.  Cursor is
    omitted.  Note that cursor position and mouse button state at the time of capture is
    preserved in CMSampleBuffers emitted from AVCaptureScreenInput.  See the inline documentation
    for kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers in <CoreMediaIO/CMIOSampleBuffer.h>
*/
@property(nonatomic) BOOL capturesCursor NS_AVAILABLE(10_8, NA); //光标在录制输出 灰化，默认光标在录制输出中，NO，光标被删，只保留一个windows

/*!
 @property removesDuplicateFrames
 @abstract
    A property indicating whether duplicate frames should be removed by the input.

 @discussion
    By default, AVCaptureScreenInput performs frame differencing and when it detects duplicate
    frames, it drops them.  If this property is set to NO, the captured output receives all frames
    from the input.
*/
@property(nonatomic) BOOL removesDuplicateFrames NS_AVAILABLE(10_8, NA);//删除重复帧率

@end

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
tureInputInternal *_inputInternal;
}

/*!
 @property ports
 @abstract
    The ports owned by the receiver.

 @discussion
    The value of this property is an array of AVCaptureInputPort objects, each exposing an interface to a single stream
    of media data provided by an input.
*/
@property(nonatomic, readonly) NSArray *ports;//接口

@end


/*!
 @constant AVCaptureInputPortFormatDescriptionDidChangeNotification
 @abstract
    This notification is posted when the value of an AVCaptureInputPort instance's formatDescription property changes.

 @discussion
    The notification object is the AVCaptureInputPort instance whose format description changed.
*/
AVF_EXPORT NSString *const AVCaptureInputPortFormatDescriptionDidChangeNotification NS_AVAILABLE(10_7, 4_0);

@class AVCaptureInputPortInternal;

/*!
 @class AVCaptureInputPort
 @abstract
    An AVCaptureInputPort describes a single stream of media data provided by an AVCaptureInput and provides an
    interface for connecting that stream to AVCaptureOutput instances via AVCaptureConnection.

 @discussion
    Instances of AVCaptureInputPort cannot be created directly. An AVCaptureInput exposes its input ports via its ports
    property. Input ports provide information about the format of their media data via the mediaType and
    formatDescription properties, and allow clients to control the flow of data via the enabled property. Input ports
    are used by an AVCaptureConnection to define the mapping between inputs and outputs in an AVCaptureSession.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureInputPort : NSObject
{
@private
    AVCaptureInputPortInternal *_internal;
}

/*!
 @property input
 @abstract
    The input that owns the receiver.

 @discussion
    The value of this property is an AVCaptureInput instance that owns the receiver.
*/
@property(nonatomic, readonly) AVCaptureInput *input;

/*!
 @property mediaType
 @abstract
    The media type of the data provided by the receiver.

 @discussion
    The value of this property is a constant describing the type of media, such as AVMediaTypeVideo or AVMediaTypeAudio,
    provided by the receiver. Media type constants are defined in AVMediaFormat.h.
*/
@property(nonatomic, readonly) NSString *mediaType;

/*!
 @property formatDescription
 @abstract
    The format of the data provided by the receiver.

 @discussion
    The value of this property is a CMFormatDescription that describes the format of the media data currently provided
    by the receiver. Clients can be notified of changes to the format by observing the
    AVCaptureInputPortFormatDescriptionDidChangeNotification.
*/
@property(nonatomic, readonly) CMFormatDescriptionRef formatDescription;//

/*!
 @property enabled
 @abstract
    Whether the receiver should provide data.

 @discussion
    The value of this property is a BOOL that determines whether the receiver should provide data to outputs when a
    session is running. Clients can set this property to fine tune which media streams from a given input will be used
    during capture. The default value is YES.
*/
@property(nonatomic, getter=isEnabled) BOOL enabled;

/*!
 @property clock
 @abstract
 Provides access to the "native" clock used by the input port.
 @discussion
 The clock is read-only.
 */
@property(nonatomic, readonly) __attribute__((NSObject)) CMClockRef clock NS_AVAILABLE(10_9, 7_0);


@end

@class AVCaptureDevice;
@class AVCaptureDeviceInputInternal;

/*!
 @class AVCaptureDeviceInput
 @abstract
    AVCaptureDeviceInput is a concrete subclass of AVCaptureInput that provides an interface for capturing media from an
    AVCaptureDevice.

 @discussion
    Instances of AVCaptureDeviceInput are input sources for AVCaptureSession that provide media data from devices
    connected to the system, represented by instances of AVCaptureDevice.
*/
NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCaptureDeviceInput : AVCaptureInput 
{
@private
	AVCaptureDeviceInputInternal *_internal;
}

/*!
 @method deviceInputWithDevice:error:
 @abstract
    Returns an AVCaptureDeviceInput instance that provides media data from the given device.

 @param device
    An AVCaptureDevice instance to be used for capture.
 @param outError
    On return, if the given device cannot be used for capture, points to an NSError describing the problem.
 @result
    An AVCaptureDeviceInput instance that provides data from the given device, or nil, if the device could not be used
    for capture.

 @discussion
    This method returns an instance of AVCaptureDeviceInput that can be used to capture data from an AVCaptureDevice in
    an AVCaptureSession. This method attempts to open the device for capture, taking exclusive control of it if
    necessary. If the device cannot be opened because it is no longer available or because it is in use, for example,
    this method returns nil, and the optional outError parameter points to an NSError describing the problem.
*/
+ (id)deviceInputWithDevice:(AVCaptureDevice *)device error:(NSError **)outError;

/*!
 @method initWithDevice:error:
 @abstract
    Creates an AVCaptureDeviceInput instance that provides media data from the given device.

 @param device
    An AVCaptureDevice instance to be used for capture.
 @param outError
    On return, if the given device cannot be used for capture, points to an NSError describing the problem.
 @result
    An AVCaptureDeviceInput instance that provides data from the given device, or nil, if the device could not be used
    for capture.

 @discussion
    This method creates an instance of AVCaptureDeviceInput that can be used to capture data from an AVCaptureDevice in
    an AVCaptureSession. This method attempts to open the device for capture, taking exclusive control of it if
    necessary. If the device cannot be opened because it is no longer available or because it is in use, for example,
    this method returns nil, and the optional outError parameter points to an NSError describing the problem.
*/
- (id)initWithDevice:(AVCaptureDevice *)device error:(NSError **)outError;

/*!
 @property device
 @abstract
    The device from which the receiver provides data.

 @discussion
    The value of this property is the AVCaptureDevice instance that was used to create the receiver.
*/
@property(nonatomic, readonly) AVCaptureDevice *device;

@end


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))

@class AVCaptureScreenInputInternal;

/*!
 @class AVCaptureScreenInput
 @abstract
    AVCaptureScreenInput is a concrete subclass of AVCaptureInput that provides an interface for capturing media from
    a screen or portion thereof.

 @discussion
    Instances of AVCaptureScreenInput are input sources for AVCaptureSession that provide media data from
    one of the screens connected to the system, represented by CGDirectDisplayIDs.
*/
NS_CLASS_AVAILABLE(10_7, NA)
@interface AVCaptureScreenInput : AVCaptureInput 
{
@private
	AVCaptureScreenInputInternal *_internal;
}

/*!
 @method initWithDisplayID:
 @abstract
    Creates an AVCaptureScreenInput instance that provides media data from the given display.
 
 @param displayID
    The id of the display from which to capture video.  CGDirectDisplayID is defined in <CoreGraphics/CGDirectDisplay.h>
 @result
    An AVCaptureScreenInput instance that provides data from the given screen, or nil, if the screen could not be used
    for capture.

 @discussion
    This method creates an instance of AVCaptureScreenInput that can be used to capture data from a display in
    an AVCaptureSession. This method validates the displayID. If the display cannot be used because it is not available
    on the system, for example, this method returns nil.
*/
- (id)initWithDisplayID:(CGDirectDisplayID)displayID;

/*!
 @property minFrameDuration
 @abstract
    A property indicating the screen input's minimum frame duration.

 @discussion
    An AVCaptureScreenInput's minFrameDuration is the reciprocal of its maximum frame rate.  This property
    may be used to request a maximum frame rate at which the input produces video frames.  The requested
    rate may not be achievable due to overall bandwidth, so actual frame rates may be lower.
*/
@property(nonatomic) CMTime minFrameDuration;

/*!
 @property cropRect
 @abstract
    A property indicating the bounding rectangle of the screen area to be captured in pixels.

 @discussion
    By default, AVCaptureScreenInput captures the entire area of the displayID with which it is associated.
    To limit the capture rectangle to a subsection of the screen, set the cropRect property, which
    defines a smaller section of the screen in the screen's coordinate system.  The origin (0,0) is
    the bottom-left corner of the screen.
*/
@property(nonatomic) CGRect cropRect;

/*!
 @property scaleFactor
 @abstract
    A property indicating the factor by which video buffers captured from the screen are to be scaled.

 @discussion
    By default, AVCaptureScreenInput captures the video buffers from the display at a scale factor
    of 1.0 (no scaling).  Set this property to scale the buffers by a given factor.  For instance,
    a 320x240 capture area with a scaleFactor of 2.0f produces video buffers at 640x480.
*/
@property(nonatomic) CGFloat scaleFactor;

/*!
 @property capturesMouseClicks
 @abstract
    A property indicating whether mouse clicks should be highlighted in the captured output.

 @discussion
    By default, AVCaptureScreenInput does not highlight mouse clicks in its captured output.  If this
    property is set to YES, mouse clicks are highlighted (a circle is drawn around the mouse for the
    duration of the click) in the captured output.
*/
@property(nonatomic) BOOL capturesMouseClicks;

/*!
 @property capturesCursor
 @abstract
    A property indicating whether the cursor should be rendered to the captured output.

 @discussion
    By default, AVCaptureScreenInput draws the cursor in its captured output.  If this property
    is set to NO, the captured output contains only the windows on the screen.  Cursor is
    omitted.  Note that cursor position and mouse button state at the time of capture is
    preserved in CMSampleBuffers emitted from AVCaptureScreenInput.  See the inline documentation
    for kCMIOSampleBufferAttachmentKey_MouseAndKeyboardModifiers in <CoreMediaIO/CMIOSampleBuffer.h>
*/
@property(nonatomic) BOOL capturesCursor NS_AVAILABLE(10_8, NA);

/*!
 @property removesDuplicateFrames
 @abstract
    A property indicating whether duplicate frames should be removed by the input.

 @discussion
    By default, AVCaptureScreenInput performs frame differencing and when it detects duplicate
    frames, it drops them.  If this property is set to NO, the captured output receives all frames
    from the input.
*/
@property(nonatomic) BOOL removesDuplicateFrames NS_AVAILABLE(10_8, NA);

@end

#endif // (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
