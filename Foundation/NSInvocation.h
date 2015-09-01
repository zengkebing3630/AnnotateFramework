NSInvocation.h


#import <Foundation/NSObject.h>
#include <stdbool.h>

@class NSMethodSignature;

@interface NSInvocation : NSObject {
@private
    __strong void *_frame;
    __strong void *_retdata;
    id _signature;
    id _container;
    uint8_t _retainedArgs;
    uint8_t _reserved[15];
}

+ (NSInvocation *)invocationWithMethodSignature:(NSMethodSignature *)sig; //只能用这个方法初始化这个方法 

@property (readonly, retain) NSMethodSignature *methodSignature;//返回值，参数标示

- (void)retainArguments;//对参数retain
@property (readonly) BOOL argumentsRetained;//是否被retain

@property (assign) id target;//接受事件的人
@property SEL selector;//选择器

- (void)getReturnValue:(void *)retLoc;//获取返回值
- (void)setReturnValue:(void *)retLoc;//设置返回值

- (void)getArgument:(void *)argumentLocation atIndex:(NSInteger)idx;//获取参数
- (void)setArgument:(void *)argumentLocation atIndex:(NSInteger)idx;//设置参数

- (void)invoke;//开始分发事件
- (void)invokeWithTarget:(id)target;//给target分发事件

@end


#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
#if MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5

enum _NSObjCValueType {
    NSObjCNoType = 0,
    NSObjCVoidType = 'v',
    NSObjCCharType = 'c',
    NSObjCShortType = 's',
    NSObjCLongType = 'l',
    NSObjCLonglongType = 'q',
    NSObjCFloatType = 'f',
    NSObjCDoubleType = 'd',
    NSObjCBoolType = 'B',
    NSObjCSelectorType = ':',
    NSObjCObjectType = '@',
    NSObjCStructType = '{',
    NSObjCPointerType = '^',
    NSObjCStringType = '*',
    NSObjCArrayType = '[',
    NSObjCUnionType = '(',
    NSObjCBitfield = 'b'
} NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);

typedef struct {
    NSInteger type NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
    union {
    	char charValue;
	short shortValue;
	long longValue;
	long long longlongValue;
	float floatValue;
	double doubleValue;
	bool boolValue;
	SEL selectorValue;
	id objectValue;
	void *pointerValue;
	void *structLocation;
	char *cStringLocation;
    } value NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);
} NSObjCValue NS_DEPRECATED(10_0, 10_5, 2_0, 2_0);

#endif
#endif

