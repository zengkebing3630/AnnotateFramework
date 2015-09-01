NSMethodSignature.h


#import <Foundation/NSObject.h>

@interface NSMethodSignature : NSObject {
@private
    void *_private;
    void *_reserved[6];
}

+ (NSMethodSignature *)signatureWithObjCTypes:(const char *)types;//[self,SEL,paraValues....]

@property (readonly) NSUInteger numberOfArguments;
- (const char *)getArgumentTypeAtIndex:(NSUInteger)idx NS_RETURNS_INNER_POINTER;

@property (readonly) NSUInteger frameLength;//参数的长度，bytes

- (BOOL)isOneway; //同步，异步

@property (readonly) const char *methodReturnType NS_RETURNS_INNER_POINTER;//返回类型
@property (readonly) NSUInteger methodReturnLength;//返回类型的长度，bytes

@end

