/*	NSArray.h
Author	曾科兵（keven）
Date    2014/6/14
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSEnumerator.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSObjCRuntime.h>

@class NSData, NSIndexSet, NSString, NSURL;

/****************	Immutable Array		****************/

@interface NSArray : NSObject <NSCopying, NSMutableCopying, NSSecureCoding, NSFastEnumeration>
// 数组元素的个数
- (NSUInteger)count; 
// 下标为index的元素
- (id)objectAtIndex:(NSUInteger)index;
@end

@interface NSArray (NSExtendedArray)
// 在当前Array追加anObject返回新得Array，就两个不同的数组
- (NSArray *)arrayByAddingObject:(id)anObject;
// 在当前Array追加otherArray返回新得Array，就两个不同得数组
- (NSArray *)arrayByAddingObjectsFromArray:(NSArray *)otherArray;
// 使用当前的数组生成一个字符串，新生成的字符串使用提供的separator 字符进行隔开
- (NSString *)componentsJoinedByString:(NSString *)separator;
// 检测数据中是否包含指定的对象元素
- (BOOL)containsObject:(id)anObject;
// 前的数组生成字符串
- (NSString *)description; 
- (NSString *)descriptionWithLocale:(id)locale;
- (NSString *)descriptionWithLocale:(id)locale indent:(NSUInteger)level;
// 两个数组的第一个元素是否相同，如果相同，则返回 数组中，第一个元素的字符串，反之，返回null 
- (id)firstObjectCommonWithArray:(NSArray *)otherArray;
// 从数组中获取 NSRange 对象的数据存放到objects 中，NSRange 的数据标示从location,开始后面length 个数据
- (void)getObjects:(id __unsafe_unretained [])objects range:(NSRange)range;
// 判断制定的anObject 对象是否存在数组中如果存在返回，对象所在的下标如果不存在，返回的NSUInteger 与 NSNotFund 相同, 使用isEqual 进行比较
- (NSUInteger)indexOfObject:(id)anObject; 
- (NSUInteger)indexOfObject:(id)anObject inRange:(NSRange)range;

// 同上面两个方法一项，测试指定的对象是否在数组中不同的是，这里使用指针进行比较
// 如果数据存在，返回指定的下标，如果不存在，则返回NSNotFund 。
- (NSUInteger)indexOfObjectIdenticalTo:(id)anObject;
- (NSUInteger)indexOfObjectIdenticalTo:(id)anObject inRange:(NSRange)range;

// 比较两个数组是否相同 ，数组长度相同，并且相同位置上的元素也相同。
- (BOOL)isEqualToArray:(NSArray *)otherArray;

// 返回第一个元素，如果一个数组的长度为0 返回的对象为nil
- (id)firstObject NS_AVAILABLE(10_6, 4_0);
// 返回最有一个元素，如果一个数组的长度为0 返回的对象为nil
- (id)lastObject;


// 使用数组返回一个 NSEnumerator 对象，这个对象类似与一个指针，可以用来遍历 整个数组 指针从前向后遍历
-	(NSEnumerator *)objectEnumerator;
// 返回一个NSEnumerator 对象，这个对象类似一个指针，可以用来遍历真个数据，所不同的是，这个指针，是从后向前遍历
-	(NSEnumerator *)reverseObjectEnumerator;


// 生成一个NSData 的对象，主要是用来进行数组的排序。 在下面的方法中使用这个对象
-	(NSData *)sortedArrayHint;
// comparator：排序方法（自己定义） context ：上下文
-	(NSArray *)sortedArrayUsingFunction:(NSInteger (*)(id, id, void *))comparator context:(void *)context;
// comparator：排序方法（自己定义） context ：上下文 hint：[Array sortedArrayHint];
-	(NSArray *)sortedArrayUsingFunction:(NSInteger (*)(id, id, void *))comparator context:(void *)context hint:(NSData *)hint;

// 这是用来排序的函数，comparator 这个参数，需要传入一个返回结果是NSComparisonResult 的函数，
-	(NSArray *)sortedArrayUsingSelector:(SEL)comparator;
// 截取数组的一部分元素组成新得数组
-	(NSArray *)subarrayWithRange:(NSRange)range;
// 把数组写入文件，atomically
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically;

// 让数组中的每个元素 都调用 aMethod 
- (void)makeObjectsPerformSelector:(SEL)aSelector;
- (void)makeObjectsPerformSelector:(SEL)aSelector withObject:(id)argument;

// 用NSIndexSet截取一个数组
- (NSArray *)objectsAtIndexes:(NSIndexSet *)indexes;
// 返回指定下标的一个对象
- (id)objectAtIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);

#if NS_BLOCKS_AVAILABLE
// 使用block 块遍历整个数组。这个block 需要三个参数，id obj 表示数组中的元素。
-	(void)enumerateObjectsUsingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
// 同上面的方法一项，区别在于，这里多添加了一个参数，用来标示 是从前向后遍历，还是从后往前遍历。
-	(void)enumerateObjectsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);
// 同上面的方法一项，不过NSIndexSet 参数标示，根据下标取出的数组，这里真正在block 中遍历的数组，是根据NSindexSet 取到的子数组
-   (void)enumerateObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts usingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_6, 4_0);

// 根据条件用来获取一个NSUIndex 对象，主要是根据条件进行数据遍历使用
-	(NSUInteger)indexOfObjectPassingTest:(BOOL (^)(id obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
	

// 同上面的方法相同，却别在于，这里添加了一个参数，用来表示遍历是从前向后遍历还是从后遍历。
-(NSUInteger)indexOfObjectWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(id obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

// 这个添加了参数NSIntexSet 参数，用来获取子数组，然后使用这个子数组进行遍历，处理数据
- (NSUInteger)indexOfObjectAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(id obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

// 根据条件判断得到条件符合的集合Set
-	(NSIndexSet *)indexesOfObjectsPassingTest:(BOOL (^)(id obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);
// 同上面的方法相同，却别在于，这里添加了一个参数，用来表示遍历是从前向后遍历还是从后遍历。
-(NSIndexSet*)indexesOfObjectsWithOptions:(NSEnumerationOptions)opts passingTest:(BOOL (^)(id obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

// 这个添加了参数NSIntexSet 参数，用来获取子数组，然后使用这个子数组进行遍历，处理数据
- (NSIndexSet *)indexesOfObjectsAtIndexes:(NSIndexSet *)s options:(NSEnumerationOptions)opts passingTest:(BOOL (^)(id obj, NSUInteger idx, BOOL *stop))predicate NS_AVAILABLE(10_6, 4_0);

// 对数组进行排序操作  参数cmptr 是一个block 函数块，返回的数据类型是一个NSComparisonResult 对象
-	(NSArray *)sortedArrayUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

// 进行排序操作，NSSortOptions 排序的参数 用来表示是同时排序，还是稳定执行。
- (NSArray *)sortedArrayWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);

typedef NS_OPTIONS(NSUInteger, NSBinarySearchingOptions) {
	NSBinarySearchingFirstEqual = (1UL << 8),
	NSBinarySearchingLastEqual = (1UL << 9),
	NSBinarySearchingInsertionIndex = (1UL << 10),
};

- (NSUInteger)indexOfObject:(id)obj inSortedRange:(NSRange)r options:(NSBinarySearchingOptions)opts usingComparator:(NSComparator)cmp NS_AVAILABLE(10_6, 4_0); // binary search

#endif

@end

@interface NSArray (NSArrayCreation)

+ (instancetype)array;
+ (instancetype)arrayWithObject:(id)anObject;
+ (instancetype)arrayWithObjects:(const id [])objects count:(NSUInteger)cnt;
+ (instancetype)arrayWithObjects:(id)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
+ (instancetype)arrayWithArray:(NSArray *)array;

- (instancetype)init;	/* designated initializer */
- (instancetype)initWithObjects:(const id [])objects count:(NSUInteger)cnt;	/* designated initializer */

- (instancetype)initWithObjects:(id)firstObj, ... NS_REQUIRES_NIL_TERMINATION;
- (instancetype)initWithArray:(NSArray *)array;
- (instancetype)initWithArray:(NSArray *)array copyItems:(BOOL)flag;

+ (id /* NSArray * */)arrayWithContentsOfFile:(NSString *)path;
+ (id /* NSArray * */)arrayWithContentsOfURL:(NSURL *)url;
- (id /* NSArray * */)initWithContentsOfFile:(NSString *)path;
- (id /* NSArray * */)initWithContentsOfURL:(NSURL *)url;

@end

@interface NSArray (NSDeprecated)

/* This method is unsafe because it could potentially cause buffer overruns. You should use -getObjects:range: instead.
*/
- (void)getObjects:(id __unsafe_unretained [])objects;

@end

/****************	Mutable Array		****************/

@interface NSMutableArray : NSArray

- (void)addObject:(id)anObject;
- (void)insertObject:(id)anObject atIndex:(NSUInteger)index;
- (void)removeLastObject;
- (void)removeObjectAtIndex:(NSUInteger)index;
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(id)anObject;

@end

@interface NSMutableArray (NSExtendedMutableArray)
    
-	(void)addObjectsFromArray:(NSArray *)otherArray;
// -	交换指定 index1 和 index2 两个位置上的元素
-	(void)exchangeObjectAtIndex:(NSUInteger)idx1 withObjectAtIndex:(NSUInteger)idx2;
// -	如果指定的元素，如果元素不存在，则不移除
- (void)removeAllObjects;
- (void)removeObject:(id)anObject inRange:(NSRange)range;
- (void)removeObject:(id)anObject;

// 相当于删除 range位置的元素，然后在把 anobject 插入到这个位置
- (void)removeObjectIdenticalTo:(id)anObject inRange:(NSRange)range;
- (void)removeObjectIdenticalTo:(id)anObject;
- (void)removeObjectsFromIndices:(NSUInteger *)indices numIndices:(NSUInteger)cnt NS_DEPRECATED(10_0, 10_6, 2_0, 4_0);
- (void)removeObjectsInArray:(NSArray *)otherArray;
- (void)removeObjectsInRange:(NSRange)range;

// 使用otherArray 数组中 otherRange 位置上的元素，替换当前数组中 range 位置上的元素
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray *)otherArray range:(NSRange)otherRange;
- (void)replaceObjectsInRange:(NSRange)range withObjectsFromArray:(NSArray *)otherArray;
- (void)setArray:(NSArray *)otherArray;


// 对当前的数组排序，使用排序算法
- (void)sortUsingFunction:(NSInteger (*)(id, id, void *))compare context:(void *)context;
- (void)sortUsingSelector:(SEL)comparator;

- (void)insertObjects:(NSArray *)objects atIndexes:(NSIndexSet *)indexes;
- (void)removeObjectsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceObjectsAtIndexes:(NSIndexSet *)indexes withObjects:(NSArray *)objects;

// 使用一个对象数组，替换 indexes 位置上的 元素
- (void)setObject:(id)obj atIndexedSubscript:(NSUInteger)idx NS_AVAILABLE(10_8, 6_0);

#if NS_BLOCKS_AVAILABLE
- (void)sortUsingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);
- (void)sortWithOptions:(NSSortOptions)opts usingComparator:(NSComparator)cmptr NS_AVAILABLE(10_6, 4_0);
#endif

@end

@interface NSMutableArray (NSMutableArrayCreation)

+ (instancetype)arrayWithCapacity:(NSUInteger)numItems;

- (instancetype)init;	/* designated initializer */
- (instancetype)initWithCapacity:(NSUInteger)numItems;	/* designated initializer */

@end


