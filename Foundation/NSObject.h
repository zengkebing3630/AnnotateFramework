/*	NSObject.h
	Author  曾科兵（keven）
    Date    2014/6/14
*/

#include <TargetConditionals.h>
#import <objc/NSObject.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSZone.h>

@class NSInvocation, NSMethodSignature, NSCoder, NSString, NSEnumerator;
@class Protocol;

/***************	Basic protocols		***************/

@protocol NSCopyin

// 拷贝 复制任意对象的内存
- (id)copyWithZone:(NSZone *)zone;

@end

@protocol NSMutableCopying
// 深度拷贝  该类来完成易变的对象拷贝
- (id)mutableCopyWithZone:(NSZone *)zone;

@end

@protocol NSCoding
// 归档 允许对象编译它的实例变量
- (void)encodeWithCoder:(NSCoder *)aCoder;
// 解档 允许一个对象初始化它自身的解码实例变量
- (id)initWithCoder:(NSCoder *)aDecoder;

@end

// Objects which are safe to be encoded and decoded across privilege boundaries should adopt NSSecureCoding instead of NSCoding. Secure coders (those that respond YES to requiresSecureCoding) will only encode objects that adopt the NSSecureCoding protocol.
// NOTE: NSSecureCoding guarantees only that an archive contains the classes it claims. It makes no guarantees about the suitability for consumption by the receiver of the decoded content of the archive. Archived objects which  may trigger code evaluation should be validated independently by the consumer of the objects to verify that no malicious code is executed (i.e. by checking key paths, selectors etc. specified in the archive).

@protocol NSSecureCoding <NSCoding>
@required
// This method must be return YES on all classes that allow secure coding. Subclasses of classes that adopt NSSecureCoding and override initWithCoder: must also override this method and return YES.
// The Secure Coding Guide should be consulted when writing methods that decode data.
+ (BOOL)supportsSecureCoding;
@end

/***********	Base class		***********/

@interface NSObject (NSCoderMethods)
// 获取指定的版本号，如果没有设置版本号，默认为0
+ (NSInteger)version;
// 设置版本号
+ (void)setVersion:(NSInteger)aVersion;
// 对象编码
- (Class)classForCoder;
// 对象编码
- (id)replacementObjectForCoder:(NSCoder *)aCoder;
// 对象编码
- (id)awakeAfterUsingCoder:(NSCoder *)aDecoder NS_REPLACES_RECEIVER;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSObject (NSDeprecatedMethods)

+ (void)poseAsClass:(Class)aClass NS_DEPRECATED(10_0, 10_5, 2_0, 2_0)
#if __OBJC2__
UNAVAILABLE_ATTRIBUTE
#endif
;

@end
#endif


/***********	Discardable Content		***********/

@protocol NSDiscardableContent
@required
// 如果舍弃内容可用，返回YES
- (BOOL)beginContentAccess;
// 丢掉不可用的内容
- (void)endContentAccess;
// 处理计数为0的内容
- (void)discardContentIfPossible;
// 判断内容是否被丢弃
- (BOOL)isContentDiscarded;
@end

@interface NSObject (NSDiscardableContentProxy)
// 可丢弃代理类别
// 创建一个接收者对象的代理。
- (id)autoContentAccessingProxy NS_AVAILABLE(10_6, 4_0);
@end

// 内存分配
/***********	Object Allocation / Deallocation		*******/
    
FOUNDATION_EXPORT id NSAllocateObject(Class aClass, NSUInteger extraBytes, NSZone *zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE; //负责的obj-C对象分配内存

FOUNDATION_EXPORT void NSDeallocateObject(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;// 重新分配对象内存

FOUNDATION_EXPORT id NSCopyObject(id object, NSUInteger extraBytes, NSZone *zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE NS_DEPRECATED(10_0, 10_8, 2_0, 6_0);// 返回对象的精确副本，深复制

// 如果请求内存地址成功，返回YES，否则NO
FOUNDATION_EXPORT BOOL NSShouldRetainWithZone(id anObject, NSZone *requestedZone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

// 增加额外的引用计数
FOUNDATION_EXPORT void NSIncrementExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
// 如果引用计数为0，返回YES，否则NO
FOUNDATION_EXPORT BOOL NSDecrementExtraRefCountWasZero(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
// 返回引用计数数
FOUNDATION_EXPORT NSUInteger NSExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

#if __has_feature(objc_arc)

// After using a CFBridgingRetain on an NSObject, the caller must take responsibility for calling CFRelease at an appropriate time. 
NS_INLINE CF_RETURNS_RETAINED CFTypeRef CFBridgingRetain(id X) {使用CFBridgingRetain。//则需要自己手动释放（CFRelease）
    return (__bridge_retained CFTypeRef)X;
}

NS_INLINE id CFBridgingRelease(CFTypeRef CF_CONSUMED X) { //减少引用计数
    return (__bridge_transfer id)X;
}

#else

// This function is intended for use while converting to ARC mode only.//转换为ARC模式，系统自动处理添加，和释放引用计数 
NS_INLINE CF_RETURNS_RETAINED CFTypeRef CFBridgingRetain(id X) {  //增加引用计数
    return X ? CFRetain((CFTypeRef)X) : NULL;
}

// This function is intended for use while converting to ARC mode only.  
NS_INLINE id CFBridgingRelease(CFTypeRef CF_CONSUMED X) {//减少引用计数
    return [(id)CFMakeCollectable(X) autorelease];
}

#endif
/*	NSObject.h
	Copyright (c) 1994-2012, Apple Inc. All rights reserved.
*/

#ifndef _OBJC_NSOBJECT_H_
#define _OBJC_NSOBJECT_H_

#include <objc/objc.h>
#include <objc/NSObjCRuntime.h>

@class NSString, NSMethodSignature, NSInvocation;

@protocol NSObject

- (BOOL)isEqual:(id)object;
// 返回一个整数，可以用来作为哈希表结构中的表地址
- (NSUInteger)hash;

- (Class)superclass;
- (Class)class;
- (id)self;
- (struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;

 // 将指定的消息配送到接收器，应用aSelector指定的消息
- (id)performSelector:(SEL)aSelector;
- (id)performSelector:(SEL)aSelector withObject:(id)object;
- (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;
// 判断是否接收器是否从NSObject继承 继承返回YES
- (BOOL)isProxy;
// 判断是否是这个类或者这个类的子类的实例
- (BOOL)isKindOfClass:(Class)aClass;
// 判断是否是这个类的实例
- (BOOL)isMemberOfClass:(Class)aClass;
// 判断是否符合协议
- (BOOL)conformsToProtocol:(Protocol *)aProtocol;
// 判断是否实现了某方法
- (BOOL)respondsToSelector:(SEL)aSelector;

- (id)retain OBJC_ARC_UNAVAILABLE;
- (oneway void)release OBJC_ARC_UNAVAILABLE;
- (id)autorelease OBJC_ARC_UNAVAILABLE;
- (NSUInteger)retainCount OBJC_ARC_UNAVAILABLE;
// 允许一个对象返回一个字符串来描述它的内容
- (NSString *)description;
@optional
// 返回一个字符串，描述在调试器中的接收器演示的内容
- (NSString *)debugDescription;

@end


__OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0)
OBJC_ROOT_CLASS
OBJC_EXPORT
@interface NSObject <NSObject> {
    Class isa  OBJC_ISA_AVAILABILITY;
}
// 无论何时，只要一个类或者Categories只要被添加到Objective-C的运行时就会调用此方法；加载后实现这个方法来执行类的特殊行为。
// 初始化加载
+ (void)load;
// 一个类的实例在使用前需要先初始化.initialize 在一个类中只被调用一次。如果你想为一个类或类的Categories执行独立的初始化，你可以实现load方法。
 // 初始化对象
+ (void)initialize;
- (id)init;

+ (id)new;
+ (id)allocWithZone:(struct _NSZone *)zone;
+ (id)alloc;
- (void)dealloc;
// 在垃圾收集器运行期间进行一些特殊的工作.
- (void)finalize;
// 复制任意对象的内存
- (id)copy;
// 复制易变的对象
- (id)mutableCopy;

+ (id)copyWithZone:(struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;
+ (id)mutableCopyWithZone:(struct _NSZone *)zone OBJC_ARC_UNAVAILABLE;

+ (Class)superclass;
+ (Class)class;

// 测试了一个给定的类实例化之后， 是否实现了一个指定的方法
+ (BOOL)instancesRespondToSelector:(SEL)aSelector;
// 判断接收器（对象或者类）符合一个给定的协议（protocol）
+ (BOOL)conformsToProtocol:(Protocol *)protocol;
// 定位并且返回接收者实现该方法的地址，因此可以作为一个方法来调用。
// 传入参数aSelector必须是有效切非空的，可以用respondsToSelector: 这个方法提前判断。
// 一个 获取指向方法实现IMP 的指针
- (IMP)methodForSelector:(SEL)aSelector;
// 同上方法，这个是定位类方法 ,返回的实施地址选择器
+ (IMP)instanceMethodForSelector:(SEL)aSelector;
// 处理不被接收者识别的信息,处理消息接收
- (void)doesNotRecognizeSelector:(SEL)aSelector;

// 转发消息
- (id)forwardingTargetForSelector:(SEL)aSelector __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);
// 允许一个对象把消息转发给另一个对象
- (void)forwardInvocation:(NSInvocation *)anInvocation;


// 返回NSMethodSignature对象，这个对象包含被标示的类方法的描述。 获得类和方法的签名
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector;

// 返回NSMethodSignature对象，这个对象包含被标示的实例方法的描述。 
+(NSMethodSignature*)instanceMethodSignatureForSelector:(SEL)aSelector;

// 允许弱参考引用标量
- (BOOL)allowsWeakReference UNAVAILABLE_ATTRIBUTE;
// 保留弱参照变量
- (BOOL)retainWeakReference UNAVAILABLE_ATTRIBUTE;

// 以字符串的形式返回对接收者类内容的描述。
+ (NSString *)description;
// 判断一个类是否是另一个类的子类
+ (BOOL)isSubclassOfClass:(Class)aClass;

// 动态的为一个类方法提供了一个SEL实现方法。返回YES表明这个方法已经找到并被添加到接收者，否则返回NO。
+ (BOOL)resolveClassMethod:(SEL)sel __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

// 动态的为一个实例方法提供了一个SEL实现方法。返回YES表明这个方法已经找到并被添加到接收者，否则返回NO。
+ (BOOL)resolveInstanceMethod:(SEL)sel __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

@end

#endif

