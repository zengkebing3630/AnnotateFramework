/*	NSByteOrder.h
	Author  曾科兵（keven）
    Date    2014/6/14
*/

/*
ByteOrder定义了写入buffer时字节的顺序
字节序处理，   
所谓的Little-Endian,就是我们在学习汇编时候的高高低低原则,应用于i386PC的CPU中，
而Bit-Endian就是刚刚相反,应用于MAC机器中
*/
#import <Foundation/NSObjCRuntime.h>
#import <CoreFoundation/CFByteOrder.h>

enum {
    NS_UnknownByteOrder = CFByteOrderUnknown,
    NS_LittleEndian = CFByteOrderLittleEndian, //小端存储
    NS_BigEndian = CFByteOrderBigEndian //大端存储
};
//获取当前的字节的顺序
NS_INLINE long NSHostByteOrder(void) {
    return CFByteOrderGetCurrent();
}
//对short进行大小端交换
NS_INLINE unsigned short NSSwapShort(unsigned short inv) {
    return CFSwapInt16(inv);
}
//对int进行大小端交换
NS_INLINE unsigned int NSSwapInt(unsigned int inv) {
    return CFSwapInt32(inv);
}
//对long进行大小端交换
NS_INLINE unsigned long NSSwapLong(unsigned long inv) {
#if __LP64__
    return CFSwapInt64(inv);
#else
    return CFSwapInt32(inv);
#endif
}
//对long long进行大小端交换
NS_INLINE unsigned long long NSSwapLongLong(unsigned long long inv) {
    return CFSwapInt64(inv);
}
//将一个short型整数从big-endian转换为主机的endian格式
NS_INLINE unsigned short NSSwapBigShortToHost(unsigned short x) {
    return CFSwapInt16BigToHost(x);
}
//将一个int型整数从big-endian转换为主机的endian格式
NS_INLINE unsigned int NSSwapBigIntToHost(unsigned int x) {
    return CFSwapInt32BigToHost(x);
}
//将一个long型整数从big-endian转换为主机的endian格式
NS_INLINE unsigned long NSSwapBigLongToHost(unsigned long x) {
#if __LP64__
    return CFSwapInt64BigToHost(x);
#else
    return CFSwapInt32BigToHost(x);
#endif
}
//将一个long long型整数从big-endian转换为主机的endian格式
NS_INLINE unsigned long long NSSwapBigLongLongToHost(unsigned long long x) {
    return CFSwapInt64BigToHost(x);
}



//将一个short型整数从主机的endian格式 转换为big-endian
NS_INLINE unsigned short NSSwapHostShortToBig(unsigned short x) {
    return CFSwapInt16HostToBig(x);
}
//将一个int型整数从主机的endian格式 转换为big-endian
NS_INLINE unsigned int NSSwapHostIntToBig(unsigned int x) {
    return CFSwapInt32HostToBig(x);
}
//将一个long型整数从主机的endian格式 转换为big-endian
NS_INLINE unsigned long NSSwapHostLongToBig(unsigned long x) {
#if __LP64__
    return CFSwapInt64HostToBig(x);
#else
    return CFSwapInt32HostToBig(x);
#endif
}
//将一个long long型整数从主机的endian格式 转换为big-endian
NS_INLINE unsigned long long NSSwapHostLongLongToBig(unsigned long long x) {
    return CFSwapInt64HostToBig(x);
}

//小端处理

//将一个short型整数从Little-endian转换为主机的endian格式
NS_INLINE unsigned short NSSwapLittleShortToHost(unsigned short x) {
    return CFSwapInt16LittleToHost(x);
}
//将一个int型整数从Little-endian转换为主机的endian格式
NS_INLINE unsigned int NSSwapLittleIntToHost(unsigned int x) {
    return CFSwapInt32LittleToHost(x);
}
//将一个long型整数从Little-endian转换为主机的endian格式
NS_INLINE unsigned long NSSwapLittleLongToHost(unsigned long x) {
#if __LP64__
    return CFSwapInt64LittleToHost(x);
#else
    return CFSwapInt32LittleToHost(x);
#endif
}
//将一个long long型整数从Little-endian转换为主机的endian格式
NS_INLINE unsigned long long NSSwapLittleLongLongToHost(unsigned long long x) {
    return CFSwapInt64LittleToHost(x);
}


//将一个short型整数从主机的endian格式 转换为little-endian
NS_INLINE unsigned short NSSwapHostShortToLittle(unsigned short x) {
    return CFSwapInt16HostToLittle(x);
}
//将一个int型整数从主机的endian格式 转换为little-endian
NS_INLINE unsigned int NSSwapHostIntToLittle(unsigned int x) {
    return CFSwapInt32HostToLittle(x);
}
//将一个long型整数从主机的endian格式 转换为little-endian
NS_INLINE unsigned long NSSwapHostLongToLittle(unsigned long x) {
#if __LP64__
    return CFSwapInt64HostToLittle(x);
#else
    return CFSwapInt32HostToLittle(x);
#endif
}
//将一个long long型整数从主机的endian格式 转换为little-endian
NS_INLINE unsigned long long NSSwapHostLongLongToLittle(unsigned long long x) {
    return CFSwapInt64HostToLittle(x);
}


typedef struct {unsigned int v;} NSSwappedFloat;
typedef struct {unsigned long long v;} NSSwappedDouble;
//对一个主机的endian格式的float 进行大小端交换
NS_INLINE NSSwappedFloat NSConvertHostFloatToSwapped(float x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->sf;
}
//对一个大小端交换后的 float 转换成 主机的endian格式
NS_INLINE float NSConvertSwappedFloatToHost(NSSwappedFloat x) {
    union fconv {
	float number;
	NSSwappedFloat sf;
    };
    return ((union fconv *)&x)->number;
}
//对一个主机的endian格式的double进行大小端交换
NS_INLINE NSSwappedDouble NSConvertHostDoubleToSwapped(double x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->sd;
}
//对一个大小端交换后的 double 转换成 主机的endian格式
NS_INLINE double NSConvertSwappedDoubleToHost(NSSwappedDouble x) {
    union dconv {
	double number;
	NSSwappedDouble sd;
    };
    return ((union dconv *)&x)->number;
}
//对float大小端交换
NS_INLINE NSSwappedFloat NSSwapFloat(NSSwappedFloat x) {
    x.v = NSSwapInt(x.v);
    return x;
}
//对double大小端交换
NS_INLINE NSSwappedDouble NSSwapDouble(NSSwappedDouble x) {
    x.v = NSSwapLongLong(x.v);
    return x;
}

#if defined(__BIG_ENDIAN__)
//
NS_INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}

NS_INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}

NS_INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSConvertHostDoubleToSwapped(x);
}
//对float进行编码，从主机的endian格式 转换成Bing endian 之后进行编码
NS_INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSConvertHostFloatToSwapped(x);
}

NS_INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}

NS_INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}
//对float进行编码，从主机的endian格式 转换成Little endian 之后进行编码
NS_INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}
//对float进行编码，从主机的endian格式 转换成Little endian之后进行编码
NS_INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}

#elif defined(__LITTLE_ENDIAN__)
//对NSSwappedDouble，从big endian格式 转换成host endian  通过double大小端交换 得到double
NS_INLINE double NSSwapBigDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(NSSwapDouble(x));
}
//对NSSwappedFloat，从big endian格式 转换成host endian  通过float大小端交换 得到float
NS_INLINE float NSSwapBigFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(NSSwapFloat(x));
}
//对double，从host endian格式 转换成bing endian  通过double大小端交换 得到NSSwappedouble
NS_INLINE NSSwappedDouble NSSwapHostDoubleToBig(double x) {
    return NSSwapDouble(NSConvertHostDoubleToSwapped(x));
}
//对Float，从host endian格式 转换成bing endian  通过float大小端交换 得到NSSwappedFloat
NS_INLINE NSSwappedFloat NSSwapHostFloatToBig(float x) {
    return NSSwapFloat(NSConvertHostFloatToSwapped(x));
}
//对NSSwappedDouble，从little endian格式 转换成主机的 endian  通过double大小端交换 得到double
NS_INLINE double NSSwapLittleDoubleToHost(NSSwappedDouble x) {
    return NSConvertSwappedDoubleToHost(x);
}
//对NSSwappedFloat，从little endian格式 转换成主机的 endian  通过float大小端交换 得到float
NS_INLINE float NSSwapLittleFloatToHost(NSSwappedFloat x) {
    return NSConvertSwappedFloatToHost(x);
}
//对double，从主机的endian格式 转换成little endian  通过float大小端交换
NS_INLINE NSSwappedDouble NSSwapHostDoubleToLittle(double x) {
    return NSConvertHostDoubleToSwapped(x);
}
//对float，从主机的endian格式 转换成little endian  通过float大小端交换
NS_INLINE NSSwappedFloat NSSwapHostFloatToLittle(float x) {
    return NSConvertHostFloatToSwapped(x);
}

#else
#error Do not know the endianess of this architecture
#endif

