/*	NSSet.h
	Copyright (c) 1994-2015, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>

@class NSArray, NSDictionary, NSString;

/****************	Immutable Set	****************/

NS_ASSUME_NONNULL_BEGIN

@interface NSSet<__covariant ObjectType> : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>

@property (readonly) NSUInteger count;
- (nullable ObjectType)member:(ObjectType)object;
//将集合放入迭代器。
- (NSEnumerator<ObjectType> *)objectEnumerator;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

@end

@interface NSSet<ObjectType> (NSExtendedSet)

@property (readonly, copy) NSArray<ObjectType> *allObjects;
- (nullable ObjectType)anyObject;
//判断这个集合中是否存在传入的对
- (BOOL)containsObject:(ObjectType)anObject;
@property (readonly, copy) NSString *description;
- (NSString *)descriptionWithLocale:(nullable id)locale;
- (BOOL)intersectsSet:(NSSet<ObjectType> *)otherSet;
- (BOOL)isEqualToSet:(NSSet<ObjectType> *)otherSet;
//判断集合中的所有数据是否都相等与objeset集合中
- (BOOL)isSubsetOfSet:(NSSet<ObjectType> *)otherSet;

- (void)makeObjectsPerformSelector:(SEL)aSelector NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(nullable id)argument NS_SWIFT_UNAVAILABLE("Use enumerateObjectsUsingBlock: or a for loop instead");

- (NSSet<ObjectType> *)setByAddingObject:(ObjectType)anObject NS_AVAILABLE(10_5, 2_0);
- (NSSet<ObjectType> *)setByAddingObjectsFromSet:(NSSet<ObjectType> *)other NS_AVAILABLE(10_5, 2_0);
- (NSSet<ObjectType> *)setByAddingObjectsFromArray:(NSArray<ObjectType> *)other NS_AVAILABLE(10_5, 2_0);

- (void)enumerateObjectsUsingBlock:(void (^)(ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
- (void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(ObjectType obj, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

- (NSSet<ObjectType> *)objectsPassingTest:(BOOL (^)(ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
- (NSSet<ObjectType> *)objectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(ObjectType obj, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

@end

@interface NSSet<ObjectType> (NSSetCreation)

+ (instancetype)set;
+ (instancetype)setWithObject:(ObjectType)object;
+ (instancetype)setWithObjects:(const ObjectType [])objects count:(NSUInteger)cnt;
+ (instancetype)setWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
+ (instancetype)setWithSet:(NSSet<ObjectType> *)set;
+ (instancetype)setWithArray:(NSArray<ObjectType> *)array;

- (instancetype)initWithObjects:(ObjectType)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set copyItems:(BOOL)flag;
- (instancetype)initWithArray:(NSArray<ObjectType> *)array;

@end

/****************	Mutable Set	****************/

@interface NSMutableSet<ObjectType> : NSSet<ObjectType>
//向集合中动态的添加对象
- (void)addObject:(ObjectType)object;
//删除集合中的一个对象
- (void)removeObject:(ObjectType)object;
- (nullable instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

@end

@interface NSMutableSet<ObjectType> (NSExtendedMutableSet)
//向集合中添加数据从array
- (void)addObjectsFromArray:(NSArray<ObjectType> *)array;
//原始集合 与 otherSet 交集
- (void)intersectSet:(NSSet<ObjectType> *)otherSet;
//原始集合 与 otherSet  差集
- (void)minusSet:(NSSet<ObjectType> *)otherSet;
//删除集合中的所有对象
- (void)removeAllObjects;
//原始集合 与otherSet 合集
- (void)unionSet:(NSSet<ObjectType> *)otherSet;

- (void)setSet:(NSSet<ObjectType> *)otherSet;

@end

@interface NSMutableSet<ObjectType> (NSMutableSetCreation)

+ (instancetype)setWithCapacity:(NSUInteger)numItems;

@end

/****************	Counted Set	****************/

@interface NSCountedSet<ObjectType> : NSMutableSet<ObjectType> {
    @private
    id _table;
    void *_reserved;
}

- (instancetype)initWithCapacity:(NSUInteger)numItems NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithArray:(NSArray<ObjectType> *)array;
- (instancetype)initWithSet:(NSSet<ObjectType> *)set;

- (NSUInteger)countForObject:(ObjectType)object;

- (NSEnumerator<ObjectType> *)objectEnumerator;
- (void)addObject:(ObjectType)object;
- (void)removeObject:(ObjectType)object;

@end

NS_ASSUME_NONNULL_END
