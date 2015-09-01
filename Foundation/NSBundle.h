/*	NSBundle.h
	Author  曾科兵（keven）
    Date    2014/6/14
*/

#import <Foundation/NSObject.h>

@class NSArray, NSDictionary, NSString, NSURL, NSError;

/* Because NSBundle caches allocated instances, subclasses should be prepared
   to receive an already initialized object back from [super initWithPath:] */

// NSBundle 对象指代相应应用程序下的所有可用的文件系统。
// 可以用NSBundle操作应用程序下，所有可用的资源（包括，xib文件，数据文件，图片 等）。
// NSBundle是将程序中所有资源捆在一起的对象。
@interface NSBundle : NSObject {
@private
    NSUInteger		_flags;
    id		        _cfBundle;
    NSUInteger		_reserved2;
    Class		_principalClass;
    id                  _initialPath;
    id                  _resolvedPath;
    id                  _reserved3;
    id                  _lock;
}

/* Methods for creating or retrieving bundle instances. */
// 返回NSBundle 对象；可以用该对象来返回应用程序可操作的路径和文件
+ (NSBundle *)mainBundle;
//使用路径获取一个NSBundle 对象,这个路径应该是一个目录的全路径
+ (NSBundle *)bundleWithPath:(NSString *)path;
//使用路径初始化一个NSBundle
- (id)initWithPath:(NSString *)path;

//使用一个url 创建并初始化一个NSBundle对象(这是一个类方法)
// 这里的url 是一个特殊的 文件url路径
+ (NSBundle *)bundleWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
- (id)initWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
// 根据一个特殊的class 获取NSBundle
+ (NSBundle *)bundleForClass:(Class)aClass;
// 获取特定名称的bundle
+ (NSBundle *)bundleWithIdentifier:(NSString *)identifier;

// 官方标注，获取所有的非framework 的bundle;
// 使用NSBundle 获取所有的bundle信息
// (由于ios安全沙盒的限制，所有的获取的资源，是应用程序的资源)
+ (NSArray *)allBundles;
// 获取应用程序加载的所有framework的资源，
+ (NSArray *)allFrameworks;

/* Methods for loading and unloading bundles. */
// 判断bundle 加载ing
- (BOOL)load;
// 判断bundle 加载完成
- (BOOL)isLoaded;
// 判断bundle 没有加载
- (BOOL)unload;
// 加载资源，如果有错误的话，会放置错误信息
- (BOOL)preflightAndReturnError:(NSError **)error NS_AVAILABLE(10_5, 2_0);
- (BOOL)loadAndReturnError:(NSError **)error NS_AVAILABLE(10_5, 2_0);

/* Methods for locating various components of a bundle. */
// 获取bundle 类实例的 url 
- (NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);
// 获取bundle 类实例的 resourceUrl 资源
- (NSURL *)resourceURL NS_AVAILABLE(10_6, 4_0);
// 获取bundle 类实例的 可执行的URL 
- (NSURL *)executableURL NS_AVAILABLE(10_6, 4_0);
// 返回一个,文件的URL，使用一个特殊的名称）
- (NSURL *)URLForAuxiliaryExecutable:(NSString *)executableName NS_AVAILABLE(10_6, 4_0);

// 获取私有的frameworkdURL
- (NSURL *)privateFrameworksURL NS_AVAILABLE(10_6, 4_0);
// 获取共享的frameworkdURL
- (NSURL *)sharedFrameworksURL NS_AVAILABLE(10_6, 4_0);
//  获取支持的Bundle的Url
- (NSURL *)sharedSupportURL NS_AVAILABLE(10_6, 4_0);
// 获取添加插件的URL 
- (NSURL *)builtInPlugInsURL NS_AVAILABLE(10_6, 4_0);
// appStore URL
- (NSURL *)appStoreReceiptURL NS_AVAILABLE(10_7, 7_0);
// 获取bundle 的path 路径
- (NSString *)bundlePath;
// 获取bundle 的资源路径字符串
- (NSString *)resourcePath;
// 获取bundle 可执行文件路径
- (NSString *)executablePath;
// 获取bundle 辅助的path
- (NSString *)pathForAuxiliaryExecutable:(NSString *)executableName;
// 获取私有的路径框架
- (NSString *)privateFrameworksPath;
// 获取共享的framework path 路径
- (NSString *)sharedFrameworksPath;
// 获取共享的路径
- (NSString *)sharedSupportPath;
// 获取插件的路径
- (NSString *)builtInPlugInsPath;

/* Methods for locating bundle resources.  Instance methods locate resources in the bundle indicated by the receiver; class methods take an argument pointing to a bundle on disk.  In the class methods, bundleURL is a URL pointing to the location of a bundle on disk, and may not be nil; bundlePath is the path equivalent of bundleURL, an absolute path pointing to the location of a bundle on disk.  By contrast, subpath is a relative path to a subdirectory inside the relevant global or localized resource directory, and should be nil if the resource file in question is not in a subdirectory.  Where appropriate, localizationName is the name of a .lproj directory in the bundle, minus the .lproj extension; passing nil for localizationName retrieves only global resources, whereas using a method without this argument retrieves both global and localized resources (using the standard localization search algorithm).  */

+ (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath inBundleWithURL:(NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);
+ (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath inBundleWithURL:(NSURL *)bundleURL NS_AVAILABLE(10_6, 4_0);
// 使用bundle 创建一个资源文件的URL
- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext NS_AVAILABLE(10_6, 4_0);
// 使用资源文件的名称以及扩展名，还有子路径
- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath NS_AVAILABLE(10_6, 4_0);
// 同上一个方法，不同的是添加了本地资源文件的信息
- (NSURL *)URLForResource:(NSString *)name withExtension:(NSString *)ext subdirectory:(NSString *)subpath localization:(NSString *)localizationName NS_AVAILABLE(10_6, 4_0);
// 根据文件的后缀名称和子目录，获取一个NSURL 的数组
- (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath NS_AVAILABLE(10_6, 4_0);
// 同上面的方法，添加了本地化的一个资源文件
- (NSArray *)URLsForResourcesWithExtension:(NSString *)ext subdirectory:(NSString *)subpath localization:(NSString *)localizationName NS_AVAILABLE(10_6, 4_0);
// 根据资源文件的名称，或者是文件的后缀名称以及目录的路径，获取 path
+ (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)bundlePath;
// 根据文件的扩展名，以及资源的路径，获取一个数组
+ (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)bundlePath;
// 根据文件的名称和扩展名获取 path 名称
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext;
// 根据文件的名称和扩展名获取 path 名称还有子路径
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath;
// 根据文件的名称和扩展名获取 path 名称
- (NSString *)pathForResource:(NSString *)name ofType:(NSString *)ext inDirectory:(NSString *)subpath forLocalization:(NSString *)localizationName;
// 根据文件的扩展名和子目录获取一个资源文件的数组
- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath;
// 同上，添加了资源文件的一个路径
- (NSArray *)pathsForResourcesOfType:(NSString *)ext inDirectory:(NSString *)subpath forLocalization:(NSString *)localizationName;

/* Method for retrieving localized strings. */
/*
NSBundle *main = [NSBundle mainBundle];
NSString *aString = [main localizedStringForKey:@"Key1"
                                            value:@"DefaultValue1"
                                            table:@"Find"];
上面的代码会在Find.strings中查找"Key1"对应的vuale字符串. 
如果没有提供用户指定的语言的本地化资源,
那么就会查找第二个所选语言,如果第二个也没有本地化资源,就依次找下去.
 如果到最后还是没有找到,那么 ""DefaultValue1"将会返回
*/
- (NSString *)localizedStringForKey:(NSString *)key value:(NSString *)value table:(NSString *)tableName NS_FORMAT_ARGUMENT(1);

/* Methods for obtaining various information about a bundle. */
// 返回当前bundle的唯一标示:(即：应用的唯一标示)
- (NSString *)bundleIdentifier;
// 获取资源文件的dictionary 对象
- (NSDictionary *)infoDictionary;
// 返回本地化资源的NSDictionary 对象
- (NSDictionary *)localizedInfoDictionary;
// 根据key 值获取本地化资源对象的值
- (id)objectForInfoDictionaryKey:(NSString *)key;
// 根据类名字符串获取一个类对象
- (Class)classNamed:(NSString *)className;
// 返回主要的类
- (Class)principalClass;

/* Methods for dealing with localizations. */
// 本地化的语言列表
- (NSArray *)preferredLocalizations;	// a subset of this bundle's localizations, re-ordered into the preferred order for this process's current execution environment; the main bundle's preferred localizations indicate the language (of text) the user is most likely seeing in the UI
// 返回本地化资源的列表
- (NSArray *)localizations;		// list of language names this bundle appears to be localized to
// 使用创建的类获取本地化语言
- (NSString *)developmentLocalization;

// 返回指定的列表，对象将使用定位为当前用户的一个或多个本地化资源。
+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray;
+ (NSArray *)preferredLocalizationsFromArray:(NSArray *)localizationsArray forPreferences:(NSArray *)preferencesArray;

/* Method for determining executable architectures. */
enum {
    NSBundleExecutableArchitectureI386      = 0x00000007,
    NSBundleExecutableArchitecturePPC       = 0x00000012,
    NSBundleExecutableArchitectureX86_64    = 0x01000007,
    NSBundleExecutableArchitecturePPC64     = 0x01000012
};

- (NSArray *)executableArchitectures NS_AVAILABLE(10_5, 2_0);

@end

#define NSLocalizedString(key, comment) \
	    [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:nil]
#define NSLocalizedStringFromTable(key, tbl, comment) \
	    [[NSBundle mainBundle] localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
	    [bundle localizedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedStringWithDefaultValue(key, tbl, bundle, val, comment) \
	    [bundle localizedStringForKey:(key) value:(val) table:(tbl)]

FOUNDATION_EXPORT NSString * const NSBundleDidLoadNotification;
FOUNDATION_EXPORT NSString * const NSLoadedClasses;	// notification key

