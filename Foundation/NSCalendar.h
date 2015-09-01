/*	NSCalendar.h 日历相关
	Author  曾科兵（keven）
    Date    2014/6/14
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSDate.h>

#include <CoreFoundation/CFCalendar.h>

@class NSDateComponents, NSLocale, NSTimeZone, NSString;

typedef NS_ENUM(NSUInteger, NSCalendarUnit) {
	NSEraCalendarUnit = kCFCalendarUnitEra,
	NSYearCalendarUnit = kCFCalendarUnitYear,
	NSMonthCalendarUnit = kCFCalendarUnitMonth,
	NSDayCalendarUnit = kCFCalendarUnitDay,
	NSHourCalendarUnit = kCFCalendarUnitHour,
	NSMinuteCalendarUnit = kCFCalendarUnitMinute,
	NSSecondCalendarUnit = kCFCalendarUnitSecond,
	NSWeekCalendarUnit = kCFCalendarUnitWeek /* NS_DEPRECATED(10_4, 10_7, 2_0, 5_0) */,
	NSWeekdayCalendarUnit = kCFCalendarUnitWeekday,
	NSWeekdayOrdinalCalendarUnit = kCFCalendarUnitWeekdayOrdinal,
	NSQuarterCalendarUnit NS_ENUM_AVAILABLE(10_6, 4_0) = kCFCalendarUnitQuarter,
	NSWeekOfMonthCalendarUnit NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitWeekOfMonth,
	NSWeekOfYearCalendarUnit NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitWeekOfYear,
	NSYearForWeekOfYearCalendarUnit NS_ENUM_AVAILABLE(10_7, 5_0) = kCFCalendarUnitYearForWeekOfYear,
        NSCalendarCalendarUnit NS_ENUM_AVAILABLE(10_7, 4_0) = (1 << 20),
        NSTimeZoneCalendarUnit NS_ENUM_AVAILABLE(10_7, 4_0) = (1 << 21),
};

@interface NSCalendar : NSObject <NSCopying, NSSecureCoding>
 // 创建或初始化可用以下方法
+ (id)currentCalendar; // users preferred calendar, tracks changes
// 取得当前用户的逻辑日历(logical calendar)
+ (id)autoupdatingCurrentCalendar NS_AVAILABLE(10_5, 2_0);
// 取得当前用户的逻辑日历(logical calendar), ……
- (id)initWithCalendarIdentifier:(NSString *)ident;
/*Identifier范围
NSGregorianCalendar 阳历
NSBuddhistCalendar 佛历
NSChineseCalendar 中国日历
NSHebrewCalendar 希伯来日历
NSIslamicCalendar 伊斯兰日历
NSIslamicCivilCalendar 伊斯兰民事日历
NSJapaneseCalendar 日本日历
*/

- (NSString *)calendarIdentifier;

// 设置区域
- (void)setLocale:(NSLocale *)locale;
//获取区域
- (NSLocale *)locale;
// 设置时区
- (void)setTimeZone:(NSTimeZone *)tz;
//获取时区
- (NSTimeZone *)timeZone;
/*
设定每周的第一天从星期几开始，比如:
如需设定从星期日开始，则value传入1
如需设定从星期一开始，则value传入2
以此类推
*/
- (void)setFirstWeekday:(NSUInteger)weekday;
- (NSUInteger)firstWeekday;
// 设定作为(每年及每月)第一周必须包含的最少天数，比如:
// .如需设定第一周最少包括7天，则value传入7
- (void)setMinimumDaysInFirstWeek:(NSUInteger)mdw;
- (NSUInteger)minimumDaysInFirstWeek;

// 返回单元的最小/最大范围
- (NSRange)minimumRangeOfUnit:(NSCalendarUnit)unit;
- (NSRange)maximumRangeOfUnit:(NSCalendarUnit)unit;

// 返回某个特定时间(date)其对应的小的时间单元(smaller)在大的时间单元(larger)中的顺序，
- (NSRange)rangeOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;
// 返回某个特定时间(date)其对应的小的时间单元(smaller)在大的时间单元(larger)中的范围
- (NSUInteger)ordinalityOfUnit:(NSCalendarUnit)smaller inUnit:(NSCalendarUnit)larger forDate:(NSDate *)date;
// 用于返回日期date(参数)所在的那个日历单元unit(参数)的开始时间(sDate)。
// 其中参数unit指定了日历单元，参数sDate用于返回日历单元的第一天，
// 参数unitSecs用于返回日历单元的长度(以秒为单位)，参数date指定了一个特定的日期。
// 如果startDate和interval均为可计算的，那么函数返回YES否则返回NO.
- (BOOL)rangeOfUnit:(NSCalendarUnit)unit startDate:(NSDate **)datep interval:(NSTimeInterval *)tip forDate:(NSDate *)date NS_AVAILABLE(10_5, 2_0);
//从日期转换NSdate
- (NSDate *)dateFromComponents:(NSDateComponents *)comps;
- (NSDateComponents *)components:(NSUInteger)unitFlags fromDate:(NSDate *)date;

- (NSDate *)dateByAddingComponents:(NSDateComponents *)comps toDate:(NSDate *)date options:(NSUInteger)opts;

- (NSDateComponents *)components:(NSUInteger)unitFlags fromDate:(NSDate *)startingDate toDate:(NSDate *)resultDate options:(NSUInteger)opts;

@end

enum {
	NSWrapCalendarComponents = kCFCalendarComponentsWrap,  // option for adding
};


// This is a just used as an extensible struct, basically;
// note that there are two uses: one for specifying a date
// via components (some components may be missing, making the
// specific date ambiguous), and the other for specifying a
// set of component quantities (like, 3 months and 5 hours).
// Undefined fields have (or fields can be set to) the value
// NSUndefinedDateComponent.
// NSDateComponents is not responsible for answering questions
// about a date beyond the information it has been initialized
// with; for example, if you initialize one with May 6, 2004,
// and then ask for the weekday, you'll get Undefined, not Thurs.
// A NSDateComponents is meaningless in itself, because you need
// to know what calendar it is interpreted against, and you need
// to know whether the values are absolute values of the units,
// or quantities of the units.
// When you create a new one of these, all values begin Undefined.

enum {
	NSUndefinedDateComponent = NSIntegerMax
};
//日历解析类
@interface NSDateComponents : NSObject <NSCopying, NSSecureCoding>
//返回日历
- (NSCalendar *)calendar NS_AVAILABLE(10_7, 4_0);
//返回时区
- (NSTimeZone *)timeZone NS_AVAILABLE(10_7, 4_0);
//返回区域
- (NSInteger)era;
//返回年
- (NSInteger)year;
// 返回月
- (NSInteger)month;
// 返回天
- (NSInteger)day;
// 返回小时
- (NSInteger)hour;
// 返回分钟
- (NSInteger)minute;
// 返回秒
- (NSInteger)second;
// 返回星期
- (NSInteger)week;
// 返回星期的天数
- (NSInteger)weekday;
//返回星期几
- (NSInteger)weekdayOrdinal;
//返回季度
- (NSInteger)quarter NS_AVAILABLE(10_6, 4_0);
// 返回一个月得星期数
- (NSInteger)weekOfMonth NS_AVAILABLE(10_7, 5_0);
// 返回一个年得星期数
- (NSInteger)weekOfYear NS_AVAILABLE(10_7, 5_0);
// 今年的月数
- (NSInteger)yearForWeekOfYear NS_AVAILABLE(10_7, 5_0);
// 闰月
- (BOOL)isLeapMonth NS_AVAILABLE(10_8, 6_0);

- (void)setCalendar:(NSCalendar *)cal NS_AVAILABLE(10_7, 4_0);
- (void)setTimeZone:(NSTimeZone *)tz NS_AVAILABLE(10_7, 4_0);
- (void)setEra:(NSInteger)v;
- (void)setYear:(NSInteger)v;
- (void)setMonth:(NSInteger)v;
- (void)setDay:(NSInteger)v;
- (void)setHour:(NSInteger)v;
- (void)setMinute:(NSInteger)v;
- (void)setSecond:(NSInteger)v;
- (void)setWeek:(NSInteger)v;
- (void)setWeekday:(NSInteger)v;
- (void)setWeekdayOrdinal:(NSInteger)v;
- (void)setQuarter:(NSInteger)v NS_AVAILABLE(10_6, 4_0);
- (void)setWeekOfMonth:(NSInteger)w NS_AVAILABLE(10_7, 5_0);
- (void)setWeekOfYear:(NSInteger)w NS_AVAILABLE(10_7, 5_0);
- (void)setYearForWeekOfYear:(NSInteger)y NS_AVAILABLE(10_7, 5_0);
- (void)setLeapMonth:(BOOL)lm NS_AVAILABLE(10_8, 6_0);

- (NSDate *)date NS_AVAILABLE(10_7, 4_0);

@end

