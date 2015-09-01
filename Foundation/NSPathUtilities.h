/*	NSPathUtilities.h
Author  曾科兵（keven）
Date    2014/6/23
操作路径名
*/

#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>

@interface NSString (NSStringPathExtensions)

//根据components中得元素构造有效路径
+ (NSString *)pathWithComponents:(NSArray *)components;
//析构路径，获得组成此路径的各个部分
- (NSArray *)pathComponents;

//判断是不是决定路径
- (BOOL)isAbsolutePath;

//提取路径的最后一个组成部分
- (NSString *)lastPathComponent;
// 删除路径的最后一个组成部分
- (NSString *)stringByDeletingLastPathComponent;
// 将path添加到现有路径的末尾
- (NSString *)stringByAppendingPathComponent:(NSString *)str;

// 从路径的最后一个组成部分中提取其扩展名
- (NSString *)pathExtension;
// 从文件的最后一部分删除扩展名
- (NSString *)stringByDeletingPathExtension;
// 将路径中得代字符扩展成用户主目录(~)或指定用户的主目录(~user)
- (NSString *)stringByAppendingPathExtension:(NSString *)str;

// 把用户的主目录路径替换为波浪号 例如/User/mike/textFile.txt 转换为~/textFile.txt
- (NSString *)stringByAbbreviatingWithTildeInPath;
// 通过把波浪号替换为当前用户的主目录，例如~/textFile.txt转换为扩展的绝对路径/User/mike/textFile.txt
- (NSString *)stringByExpandingTildeInPath;
// stringbyStandardizingPath 通过尝试解析~、..、.、和符号链接来标准化路径
- (NSString *)stringByStandardizingPath;
//尝试解析路径中的符号链接 返回标准化后的路径
- (NSString *)stringByResolvingSymlinksInPath;
// 将paths数组加到后面
- (NSArray *)stringsByAppendingPaths:(NSArray *)paths;
// outputName:引用传参,最长文件路径，matchesIntoArray:文件名数组，filterTypes:扩展名数组
- (NSUInteger)completePathIntoString:(NSString **)outputName caseSensitive:(BOOL)flag matchesIntoArray:(NSArray **)outputArray filterTypes:(NSArray *)filterTypes;

//返回合法文件名
- (__strong const char *)fileSystemRepresentation NS_RETURNS_INNER_POINTER; 
// 最长maxLength情况下，是否放的进路径？如果用户的home目录不存在则返回整理后的原路径
- (BOOL)getFileSystemRepresentation:(char *)cname maxLength:(NSUInteger)max;

@end

@interface NSArray (NSArrayPathExtensions)
//过滤文件类型
- (NSArray *)pathsMatchingExtensions:(NSArray *)filterTypes;

@end
// 返回当前用户的登录名
FOUNDATION_EXPORT NSString *NSUserName(void);
// 返回当前用户的完整用户名
FOUNDATION_EXPORT NSString *NSFullUserName(void);
// 返回当前用户主目录的路径
FOUNDATION_EXPORT NSString *NSHomeDirectory(void);
// 返回用户user的主目录
FOUNDATION_EXPORT NSString *NSHomeDirectoryForUser(NSString *userName);
 // 返回可用于创建零时文件的路径目录tmpDir
FOUNDATION_EXPORT NSString *NSTemporaryDirectory(void);

FOUNDATION_EXPORT NSString *NSOpenStepRootDirectory(void);

typedef NS_ENUM(NSUInteger, NSSearchPathDirectory) {
    NSApplicationDirectory = 1,             // supported applications (Applications)
    NSDemoApplicationDirectory,             // unsupported applications, demonstration versions (Demos)
    NSDeveloperApplicationDirectory,        // developer applications (Developer/Applications). DEPRECATED - there is no one single Developer directory.
    NSAdminApplicationDirectory,            // system and network administration applications (Administration)
    NSLibraryDirectory,                     // various documentation, support, and configuration files, resources (Library)
    NSDeveloperDirectory,                   // developer resources (Developer) DEPRECATED - there is no one single Developer directory.
    NSUserDirectory,                        // user home directories (Users)
    NSDocumentationDirectory,               // documentation (Documentation)
    NSDocumentDirectory,                    // documents (Documents)
    NSCoreServiceDirectory,                 // location of CoreServices directory (System/Library/CoreServices)
    NSAutosavedInformationDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 11,   // location of autosaved documents (Documents/Autosaved)
    NSDesktopDirectory = 12,                // location of user's desktop
    NSCachesDirectory = 13,                 // location of discardable cache files (Library/Caches)
    NSApplicationSupportDirectory = 14,     // location of application support files (plug-ins, etc) (Library/Application Support)
    NSDownloadsDirectory NS_ENUM_AVAILABLE(10_5, 2_0) = 15,              // location of the user's "Downloads" directory
    NSInputMethodsDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 16,           // input methods (Library/Input Methods)
    NSMoviesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 17,                 // location of user's Movies directory (~/Movies)
    NSMusicDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 18,                  // location of user's Music directory (~/Music)
    NSPicturesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 19,               // location of user's Pictures directory (~/Pictures)
    NSPrinterDescriptionDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 20,     // location of system's PPDs directory (Library/Printers/PPDs)
    NSSharedPublicDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 21,           // location of user's Public sharing directory (~/Public)
    NSPreferencePanesDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 22,        // location of the PreferencePanes directory for use with System Preferences (Library/PreferencePanes)
    NSApplicationScriptsDirectory NS_ENUM_AVAILABLE(10_8, NA) = 23,      // location of the user scripts folder for the calling application (~/Library/Application Scripts/code-signing-id)
    NSItemReplacementDirectory NS_ENUM_AVAILABLE(10_6, 4_0) = 99,	    // For use with NSFileManager's URLForDirectory:inDomain:appropriateForURL:create:error:
    NSAllApplicationsDirectory = 100,       // all directories where applications can occur
    NSAllLibrariesDirectory = 101,          // all directories where resources can occur
    NSTrashDirectory NS_ENUM_AVAILABLE(10_8, NA) = 102                   // location of Trash directory

};
// enum {
// NSUserDomainMask = 1,//用户主目录中
// NSLocalDomainMask = 2,//当前机器中
// NSNetworkDomainMask = 4,//网络中可见的主机
// NSSystemDomainMask = 8,//系统目录,不可修改(/System)
// NSAllDomainsMask = 0x0ffff,//全部
// };
typedef NS_OPTIONS(NSUInteger, NSSearchPathDomainMask) {
    NSUserDomainMask = 1,       // user's home directory --- place to install user's personal items (~)
    NSLocalDomainMask = 2,      // local to the current machine --- place to install items available to everyone on this machine (/Library)
    NSNetworkDomainMask = 4,    // publically available location in the local area network --- place to install items available on the network (/Network)
    NSSystemDomainMask = 8,     // provided by Apple, unmodifiable (/System)
    NSAllDomainsMask = 0x0ffff  // all domains: all of the above and future items
};
// 查找各种目录
FOUNDATION_EXPORT NSArray *NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory directory, NSSearchPathDomainMask domainMask, BOOL expandTilde);


