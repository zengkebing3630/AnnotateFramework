/*
 * Copyright (c) 2000, 2002 - 2008 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*-
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)stdlib.h	8.5 (Berkeley) 5/19/95
 */

#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <Availability.h>

#include <_types.h>
#if !defined(_ANSI_SOURCE)
#include <sys/wait.h>
#if (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
#include <alloca.h>
#endif /* (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */
#endif /* !_ANSI_SOURCE */

/* DO NOT REMOVE THIS COMMENT: fixincludes needs to see:
 * _GCC_SIZE_T */
#include <sys/_types/_size_t.h>

#if !defined(_ANSI_SOURCE) && (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
#include <sys/_types/_ct_rune_t.h>
#include <sys/_types/_rune_t.h>
#endif	/* !_ANSI_SOURCE && (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */

#include <sys/_types/_wchar_t.h>

typedef struct {
	int quot;		/* quotient */
	int rem;		/* remainder */
} div_t;

typedef struct {
	long quot;		/* quotient */
	long rem;		/* remainder */
} ldiv_t;

#if !__DARWIN_NO_LONG_LONG
typedef struct {
	long long quot;
	long long rem;
} lldiv_t;
#endif /* !__DARWIN_NO_LONG_LONG */

#include <sys/_types/_null.h>

#define	EXIT_FAILURE	1
#define	EXIT_SUCCESS	0

#define	RAND_MAX	0x7fffffff

#ifdef _USE_EXTENDED_LOCALES_
#include <_xlocale.h>
#endif /* _USE_EXTENDED_LOCALES_ */

#ifndef MB_CUR_MAX
#ifdef _USE_EXTENDED_LOCALES_
#define	MB_CUR_MAX	(___mb_cur_max())
#ifndef MB_CUR_MAX_L
#define	MB_CUR_MAX_L(x)	(___mb_cur_max_l(x))
#endif /* !MB_CUR_MAX_L */
#else /* !_USE_EXTENDED_LOCALES_ */
extern int __mb_cur_max;
#define	MB_CUR_MAX	__mb_cur_max
#endif /* _USE_EXTENDED_LOCALES_ */
#endif /* MB_CUR_MAX */

#if !defined(_ANSI_SOURCE) && (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)) \
    && defined(_USE_EXTENDED_LOCALES_) && !defined(MB_CUR_MAX_L)
#define	MB_CUR_MAX_L(x)	(___mb_cur_max_l(x))
#endif

__BEGIN_DECLS
void	 abort(void) __dead2; //使程序立即非正常终止，一般不对缓冲区清仓。
int	 abs(int) __pure2;//返回整数变元num的绝对值。
/*
	使得程序终止时调用由func指针指向的函数。如果成功注册，则函数返回0值，否则返回非0值。
最少应允许注册32个终止函数，被注册的函数以注册的反序调用。
*/
int	 atexit(void (*)(void));
/*
	把str指向的串转换为双精度浮点值，串中必须含合法的浮点数，否则返回值不确定。
串中的数可以由有效浮点数中的任何字符结束，如空白符、除句号外的标点符号和E或e之外的字符等。
*/
double	 atof(const char *);
/*
	把str指向的串转换为整数(int)值。串中必须含合法整型数，否则返回值无定义。
串中的整数内容可由任何不是该整数的一部分的字符终止，如空白符、标点符号和字符等。
*/
int	 atoi(const char *);
/*
	把str指向的串转换为长整数(long int)值。串中必须含合法整型数，否则返回值无定义。
串中的整数内容可由任何不是该整数的一部分的字符终止，如空白符、标点符号和字符等。
*/
long	 atol(const char *);
#if !__DARWIN_NO_LONG_LONG
long long
	 atoll(const char *);//该函数是C99增加的。把str指向的串转换为长长整数(long long int)型值。其他方面类似于atol()。
#endif /* !__DARWIN_NO_LONG_LONG */
	 /*
	函数对buf指向的已排序数组实施对分查找(binary search)，返回与key指向的关键字匹配的第一个成员的指针。num说明数组中的元素数目，size指出每个元素占有的字节数。
函数指针compare指向的函数把关键字key和数组元素比较，比较函数的形式为：
arg1是key指针，arg2是数组元素指针。
返回值必须如下：
arg1 < arg2时，返回值<0；
arg1 == arg2时，返回值=0；
arg1 > arg2时，返回值>0。
数组必须已经按升序排序，最低地址处放最低元素。
如果数组中不含关键字，则函数返回空指针。
	 */
void	*bsearch(const void *, const void *, size_t,
	    size_t, int (*)(const void *, const void *));
void	*calloc(size_t, size_t);
/*
	函数返回numerator/denominator操作的商和余数，返回值的结构类型是div_t，该结构有以下两个域：
int quot;
int rem;
*/
div_t	 div(int, int) __pure2;
/*
	该函数使程序立即正常终止，这意味着调用由atexit()注册的终止函数，并且清空和关闭任何打开的文件。
环境支持时，exit_code值传给调用进程。
*/
void	 exit(int) __dead2;
void	 free(void *);
/*
	函数返回一个指针，指向实现定义的环境信息表中与name指向的串有关的环境信息。千万不要用代码修改该串。
没有查到匹配数据时，返回空指针。
*/
char	*getenv(const char *);
long	 labs(long) __pure2;//返回num的绝对值。
/*
	函数返回numerator/denominator操作的商和余数，返回值的结构类型是ldiv_t，该结构有以下两个域：
long int quot;
long int rem;
*/
ldiv_t	 ldiv(long, long) __pure2;
#if !__DARWIN_NO_LONG_LONG
long long
	 llabs(long long);//由C99增加，返回num的绝对值。
	 /*
		由C99增加，函数返回numerator/denominator操作的商和余数，返回值的结构类型是lldiv_t，该结构有以下两个域：
long long int quot;
long long int rem;
	 */
lldiv_t	 lldiv(long long, long long);
#endif /* !__DARWIN_NO_LONG_LONG */
void	*malloc(size_t);
int	 mblen(const char *, size_t);
size_t	 mbstowcs(wchar_t * __restrict , const char * __restrict, size_t);
int	 mbtowc(wchar_t * __restrict, const char * __restrict, size_t);
int 	 posix_memalign(void **, size_t, size_t) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_0);
/*
	使用Quicksort算法对buf指向的数组进行排序，num是数组中元素的数目，size说明每个元素的大小(按字节)。
比较函数compare的形式如下：
int func_name(const void *arg1, const voie *arg2);
其返回值必须如下所示：
arg1 < arg2， <0
arg1 == arg2, ==0
arg1 > arg2, >0
数组按升序排列，最低地址处放最小元素。
*/
void	 qsort(void *, size_t, size_t,
	    int (*)(const void *, const void *));
/*
	产生伪随机数序列，每次它被调用时返回一个0到RAND_MAX间的整数。RAND_MAX值至少是32767。
*/
int	 rand(void);
void	*realloc(void *, size_t);
void	 srand(unsigned);//为rand()生成的伪随机数序列设置起点。
/*
	函数把start指向的字符串中存储的数字串表达式转换成双精度浮点值(double)，然后返回转换结果。
过程如下：首先滤掉start前导空白符，然后逐个读入构成数的字符，任何非浮点数成分的字符都会终止上述过程，这类字符包括空白、标点(英文句号除外)和非E非e的字母等。最后，若原始串未用完，则end置为指向剩余串的开始字符。
溢出产生时，函数返回HUGE_VAL(代表上溢)或-HUGE_VAL(代表下溢)，并且全局变量errno置为ERANGE。如果start未指向一个数值，则不发生转换并返回0。
如果范围有错，则返回0，errno也置为ERANGE。
*/
double	 strtod(const char *, char **) __DARWIN_ALIAS(strtod);
float	 strtof(const char *, char **) __DARWIN_ALIAS(strtof);//该函数由C99增加。与strtod()类似，只是它返回float类型值。
/*
	把start指向的串中的数字串表达式转换为长整数，然后返回转换结果。数字串的基(进制)有radix决定。如radix为0，进制由说明常数的规则决定；如radix为非0，它必须是2到36间的一个值。
end的使用类似于strtod()的讨论。
如果结果不能用长整数表示，则返回LONG_MAX或LONG_MIN，并且errno设为ERANGE。如果start不指向一个数，则不产生转换，返回0。
*/
long	 strtol(const char *, char **, int);
long double
	 strtold(const char *, char **);//该函数由C99增加。处理类似于strtod()，只是它返回long double型值。
#if !__DARWIN_NO_LONG_LONG
long long 
	 strtoll(const char *, char **, int);//该函数由C99增加。处理类似于strtol()，只是它返回long long int型值。
#endif /* !__DARWIN_NO_LONG_LONG */
	 /*
	把start指向的串中的数字表达式转换为无符号长整数。执行过程类似于strtol()。
如果结果不能按无符号长整数表示，则返回ULONG_MAX或ULONG_MIN，且全局变量errno置为ERANGE。
	 */
unsigned long
	 strtoul(const char *, char **, int);
#if !__DARWIN_NO_LONG_LONG
unsigned long long
	 strtoull(const char *, char **, int);//该函数由C99增加。处理类似于strtoul()，只是它返回unsigned long long int型值。
#endif /* !__DARWIN_NO_LONG_LONG */
	 //把str指向的串作为命令传入操作系统的命令处理程序。该函数与具体环境有关。
int	 system(const char *) __DARWIN_ALIAS_C(system) __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0,__MAC_NA,__IPHONE_2_0,__IPHONE_8_0, "Use posix_spawn APIs instead.");
size_t	 wcstombs(char * __restrict, const wchar_t * __restrict, size_t);
int	 wctomb(char *, wchar_t);

#ifndef _ANSI_SOURCE
/*
	该函数由C99增加。该函数类似于exit()，但有下列差别：
没有调用atexit()注册的函数；
没有调用signal()注册的信号处理程序；
打开的文件不必清空或关闭。
*/
void	_Exit(int) __dead2;
long	 a64l(const char *);
double	 drand48(void);
char	*ecvt(double, int, int *__restrict, int *__restrict); /* LEGACY */
double	 erand48(unsigned short[3]); 
char	*fcvt(double, int, int *__restrict, int *__restrict); /* LEGACY */
char	*gcvt(double, int, char *); /* LEGACY */
int	 getsubopt(char **, char * const *, char **);
int	 grantpt(int);
#if __DARWIN_UNIX03
char	*initstate(unsigned, char *, size_t); /* no  __DARWIN_ALIAS needed */
#else /* !__DARWIN_UNIX03 */
char	*initstate(unsigned long, char *, long);
#endif /* __DARWIN_UNIX03 */
long	 jrand48(unsigned short[3]);
char	*l64a(long);
void	 lcong48(unsigned short[7]);
long	 lrand48(void);
char	*mktemp(char *);
int	 mkstemp(char *);
long	 mrand48(void); 
long	 nrand48(unsigned short[3]);
int	 posix_openpt(int);
char	*ptsname(int);
int	 putenv(char *) __DARWIN_ALIAS(putenv);
long	 random(void);
int	 rand_r(unsigned *);
#if (__DARWIN_UNIX03 && !defined(_POSIX_C_SOURCE)) || defined(_DARWIN_C_SOURCE) || defined(_DARWIN_BETTER_REALPATH)
char	*realpath(const char * __restrict, char * __restrict) __DARWIN_EXTSN(realpath);
#else /* (!__DARWIN_UNIX03 || _POSIX_C_SOURCE) && !_DARWIN_C_SOURCE && !_DARWIN_BETTER_REALPATH */
char	*realpath(const char * __restrict, char * __restrict) __DARWIN_ALIAS(realpath);
#endif /* (__DARWIN_UNIX03 && _POSIX_C_SOURCE) || _DARWIN_C_SOURCE || _DARWIN_BETTER_REALPATH */
unsigned short
	*seed48(unsigned short[3]);
int	 setenv(const char *, const char *, int) __DARWIN_ALIAS(setenv);
#if __DARWIN_UNIX03
void	 setkey(const char *) __DARWIN_ALIAS(setkey);
#else /* !__DARWIN_UNIX03 */
int	 setkey(const char *);
#endif /* __DARWIN_UNIX03 */
char	*setstate(const char *);
void	 srand48(long);
#if __DARWIN_UNIX03
void	 srandom(unsigned);
#else /* !__DARWIN_UNIX03 */
void	 srandom(unsigned long);
#endif /* __DARWIN_UNIX03 */
int	 unlockpt(int);
#if __DARWIN_UNIX03
int	 unsetenv(const char *) __DARWIN_ALIAS(unsetenv);
#else /* !__DARWIN_UNIX03 */
void	 unsetenv(const char *);
#endif /* __DARWIN_UNIX03 */
#endif	/* !_ANSI_SOURCE */

#if !defined(_ANSI_SOURCE) && (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
#include <machine/types.h>

#include <sys/_types/_dev_t.h>
#include <sys/_types/_mode_t.h>

u_int32_t	arc4random(void);
void	 arc4random_addrandom(unsigned char * /*dat*/, int /*datlen*/);
void	 arc4random_buf(void * /*buf*/, size_t /*nbytes*/) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_3);
void	 arc4random_stir(void);
u_int32_t
	 arc4random_uniform(u_int32_t /*upper_bound*/) __OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_4_3);
#ifdef __BLOCKS__
int	 atexit_b(void (^)(void)) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
void	*bsearch_b(const void *, const void *, size_t,
	    size_t, int (^)(const void *, const void *)) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
#endif /* __BLOCKS__ */

	 /* getcap(3) functions */
char	*cgetcap(char *, const char *, int);
int	 cgetclose(void);
int	 cgetent(char **, char **, const char *);
int	 cgetfirst(char **, char **);
int	 cgetmatch(const char *, const char *);
int	 cgetnext(char **, char **);
int	 cgetnum(char *, const char *, long *);
int	 cgetset(const char *);
int	 cgetstr(char *, const char *, char **);
int	 cgetustr(char *, const char *, char **);

int	 daemon(int, int) __DARWIN_1050(daemon) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_5, __IPHONE_2_0, __IPHONE_2_0);
char	*devname(dev_t, mode_t);
char	*devname_r(dev_t, mode_t, char *buf, int len);
char	*getbsize(int *, long *);
int	 getloadavg(double [], int);
const char
	*getprogname(void);

int	 heapsort(void *, size_t, size_t,
	    int (*)(const void *, const void *));
#ifdef __BLOCKS__
int	 heapsort_b(void *, size_t, size_t,
	    int (^)(const void *, const void *)) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
#endif /* __BLOCKS__ */
int	 mergesort(void *, size_t, size_t,
	    int (*)(const void *, const void *));
#ifdef __BLOCKS__
int	 mergesort_b(void *, size_t, size_t,
	    int (^)(const void *, const void *)) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
#endif /* __BLOCKS__ */
void	 psort(void *, size_t, size_t,
	    int (*)(const void *, const void *)) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
#ifdef __BLOCKS__
void	 psort_b(void *, size_t, size_t,
	    int (^)(const void *, const void *)) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
#endif /* __BLOCKS__ */
void	 psort_r(void *, size_t, size_t, void *,
	    int (*)(void *, const void *, const void *))  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
#ifdef __BLOCKS__
void	 qsort_b(void *, size_t, size_t,
	    int (^)(const void *, const void *)) __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_2);
#endif /* __BLOCKS__ */
void	 qsort_r(void *, size_t, size_t, void *,
	    int (*)(void *, const void *, const void *));
int	 radixsort(const unsigned char **, int, const unsigned char *,
	    unsigned);
void	 setprogname(const char *);
int	 sradixsort(const unsigned char **, int, const unsigned char *,
	    unsigned);
void	 sranddev(void);
void	 srandomdev(void);
void	*reallocf(void *, size_t);
#if !__DARWIN_NO_LONG_LONG
long long
	 strtoq(const char *, char **, int);
unsigned long long
	 strtouq(const char *, char **, int);
#endif /* !__DARWIN_NO_LONG_LONG */
extern char *suboptarg;		/* getsubopt(3) external variable */
void	*valloc(size_t);
#endif	/* !_ANSI_SOURCE && !_POSIX_SOURCE */

/* Poison the following routines if -fshort-wchar is set */
#if !defined(__cplusplus) && defined(__WCHAR_MAX__) && __WCHAR_MAX__ <= 0xffffU
#pragma GCC poison mbstowcs mbtowc wcstombs wctomb
#endif
__END_DECLS

#ifdef _USE_EXTENDED_LOCALES_
#include <xlocale/_stdlib.h>
#endif /* _USE_EXTENDED_LOCALES_ */

#endif /* _STDLIB_H_ */
