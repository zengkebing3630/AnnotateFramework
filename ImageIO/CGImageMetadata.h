// *****************************************************************************
// CGImageMetadata.h
// *****************************************************************************

#ifndef CGIMAGEMETADATA_H_
#define CGIMAGEMETADATA_H_

#include <ImageIO/ImageIOBase.h>
#include <CoreFoundation/CoreFoundation.h>

CF_IMPLICIT_BRIDGING_ENABLED

/*

  实现对图像元数据的访问,CGImageMetadata APIs允许用户查看和修改流行的图像格式的元数据。ImageIO支持EXIF，IPTC，和XMP元数据规范。
  请参阅CGImageSource.h中从CGImageSource读取CGImageMetadata的方法
  请参阅CGImageDestination.h中把CGImageMetadata写入CGImageDestination的方法
  CGImageDestinationCopyImageSource可以用来修改没有压缩的元数据
  开发者可以通过设置环境变量IIO_DEBUG_METADATA = 1启用额外的调试信息
  不要忽略IMAGEIO_AVAILABLE_STARTING
  不要忽略IMAGEIO_EXTERN
  不排序
 */


//对于CGImageMetadataTags不变的容器
typedef const struct CGImageMetadata *CGImageMetadataRef;

// 创建和识别CGImageMetadata容器
// 得到CGImageMetadata不透明类型标识符的类型
IMAGEIO_EXTERN CFTypeID CGImageMetadataGetTypeID(void);

//对于CGImageMetadataTags可变的容器
typedef struct CGImageMetadata *CGMutableImageMetadataRef;

//创建可变容器 CGImageMetadata
IMAGEIO_EXTERN CGMutableImageMetadataRef CGImageMetadataCreateMutable(void) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//拷贝一个CGImageMetadataTags不变的容器的内容来初始化可变容器
IMAGEIO_EXTERN CGMutableImageMetadataRef CGImageMetadataCreateMutableCopy(CGImageMetadataRef metadata) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// ****************************************************************************
// CGImageMetadataTag 一个独立的元数据标签，标签封装的EXIF，IPTC标签，或XMP属性。
// ****************************************************************************
// 
//一个独立的元数据标签，标签封装的EXIF，IPTC标签，或XMP属性,所有标记包含名称空间、前缀、名称、类型和值，CGImageMetadataTagCreate创建方法
typedef struct CGImageMetadataTag *CGImageMetadataTagRef;

//得到CGImageMetadataTag不透明类型标识符的类型
IMAGEIO_EXTERN CFTypeID CGImageMetadataTagGetTypeID(void) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


// ****************************************************************************
// Constants for use in a CGImageMetadataTag
// ****************************************************************************

// All metadata tags must contain a namespace. Clients may use one of the 
// public namespaces defined below or create their own namespace. If a caller
// defines their own namespace, it should comply with the guidelines set forth
// by Adobe in their XMP specification at:
// http://www.adobe.com/devnet/xmp.html.
// For example: "http://ns.adobe.com/exif/1.0/". 
// The caller must also register a custom namespace using 
// CGImageMetadataRegisterNamespaceForPrefix.

// Public, common namespaces.
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExif IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExifAux IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceExifEX IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceDublinCore IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceIPTCCore IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespacePhotoshop IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceTIFF IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceXMPBasic IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataNamespaceXMPRights IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// All metadata tags must contain a prefix. For the public namespaces defined
// above, no prefix is required - ImageIO will use appropriate defaults.  For 
// other namespaces a prefix is required. For example, while the exif namespace 
// is rather long ("http://ns.adobe.com/exif/1.0/"), when exported the shorter 
// string "exif" will be used to prefix all properties in the exif namespace 
// (example - "exif:Flash").

// Public, common prefixes.
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExif IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExifAux IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixExifEX IMAGEIO_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixDublinCore IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixIPTCCore IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixPhotoshop IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixTIFF IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixXMPBasic IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
IMAGEIO_EXTERN const CFStringRef  kCGImageMetadataPrefixXMPRights IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// Metadata value type constants.
/*!
 * @typedef CGImageMetadataType
 * @abstract The XMP type for a CGImageMetadataTag
 * @discussion CGImageMetadataType defines a list of constants used to indicate
 * the type for a CGImageMetadataTag. If you are reading metadata, use the type 
 * to determine how to interpret the CGImageMetadataTag's value. If you are 
 * creating a CGImageMetadataTag, use the type to specify how the tag 
 * should be serialized in XMP. String types have CFStringRef values, array 
 * types have CFArray values, and structure types have CFDictionary values.
 * @const kCGImageMetadataTypeDefault The type will be interpretted based on the
 * CFType of the tag's value. This is only used when creating a new 
 * CGImageMetadataTag - no existing tags should have this value. CFString 
 * defaults to kCGImageMetadataTypeString, CFArray defaults to 
 * kCGImageMetadataTypeArrayOrdered, and CFDictionary defaults to
 * kCGImageMetadataTypeStructure.
 * @const kCGImageMetadataTypeString A string value. CFNumber and CFBoolean 
 * values will be converted to a string.
 * @const kCGImageMetadataTypeArrayUnordered An array where order does not matter.
 * Serialized in XMP as <rdf:Bag>.
 * @const kCGImageMetadataTypeArrayOrdered An array where order is preserved.
 * Serialized in XMP as <rdf:Seq>.
 * @const kCGImageMetadataTypeAlternateArray An ordered array where all elements
 * are alternates for the same value. Serialized in XMP as <rdf:Alt>.
 * @const kCGImageMetadataTypeAlternateText A special case of an alternate array
 * where all elements are different localized strings for the same value. 
 * Serialized in XMP as an alternate array of strings with xml:lang qualifiers.
 * @const kCGImageMetadataTypeStructure A collection of keys and values. Unlike
 * array elements, fields of a structure may belong to different namespaces.
 */
typedef enum CGImageMetadataType {
    kCGImageMetadataTypeInvalid = -1,
    kCGImageMetadataTypeDefault = 0,
    kCGImageMetadataTypeString = 1,
    kCGImageMetadataTypeArrayUnordered = 2,
    kCGImageMetadataTypeArrayOrdered = 3,
    kCGImageMetadataTypeAlternateArray = 4,
    kCGImageMetadataTypeAlternateText = 5,
    kCGImageMetadataTypeStructure = 6
} CGImageMetadataType;

// ****************************************************************************
// 创建一个CGImageMetadataTagRef
// ****************************************************************************

//创建一个CGImageMetadataTagRef
//xmlns:标签的命名空间,该值可以是一个常见的XMP上面定义的命名空间，
//如kCGImageMetadataNamespaceExif，或一个自定义的命名空间URI cfstring。
//自定义命名空间必须是有效的XML命名空间。按照惯例，命名空间应该结束与“/”或“#”。例如，EXIF使用命名空间"http://ns.adobe.com/exif/1.0/"
//prefix:命名空间的缩写,如果该名称空间被定义为常量，则该值可以为NULL。
//自定义前缀必须是有效的XML名称。例如，前缀用于“http://ns.adobe.com/exif/1.0/”是“EXIF”。该标签的XMP系列将使用前缀。
//前缀也基于CGImageMetadata路径重要功能,CGImageMetadataCopyStringValueWithPath Or CGImageMetadataSetValueWithPath
//name:标签的名称。它必须是一个有效的XMP的名字
//type:标签的值类型。必须是一个常数从CGImageMetadataType获取
//value:标签的价值。允许CFTypes包括CFStringRef，CFNumberRef, CFBooleanRef, CFArrayRef, and CFDictionaryRef
//CFTypes 和Value必须对应，CFArray必须CFStringRef或CGImageMetadataTagRef组成
//CFDictionary的keys必须是XMP有效的名字CFStringRef
//
//Values 必须CFStringRef或CGImageMetadataTagRef组成
//值的浅拷贝存储在标签中。因此，在标签创建修改一个可变的值不会影响标签的价值
//返回一个CGImageMetadataTagRef指针。如果一个标记不能创建指定参数，返回NULL。
IMAGEIO_EXTERN CGImageMetadataTagRef 
CGImageMetadataTagCreate (CFStringRef xmlns, 
                          CFStringRef prefix, 
                          CFStringRef name,
                          CGImageMetadataType type,
                          CFTypeRef value) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//拷贝CGImageMetadataTag命名空间
IMAGEIO_EXTERN CFStringRef CGImageMetadataTagCopyNamespace(CGImageMetadataTagRef tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//拷贝CGImageMetadataTag命名空间的缩写
IMAGEIO_EXTERN CFStringRef CGImageMetadataTagCopyPrefix(CGImageMetadataTagRef tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//拷贝CGImageMetadataTag标签的名称
IMAGEIO_EXTERN CFStringRef CGImageMetadataTagCopyName(CGImageMetadataTagRef tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//拷贝CGImageMetadataTag标签的值类型，改变返回标签值不会影响CGImageMetadataTag
//CGImageMetadataSetValueWithPath || CGImageMetadataSetTagWithPath 来改变标签的值类型类型值
IMAGEIO_EXTERN CFTypeRef CGImageMetadataTagCopyValue(CGImageMetadataTagRef tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//得到的CGImageMetadataTag类型
IMAGEIO_EXTERN CGImageMetadataType CGImageMetadataTagGetType(CGImageMetadataTagRef tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataTagCopyQualifiers
 * @abstract Return a copy of the tag's qualifiers
 * @discussion XMP allows properties to contain supplemental properties called
 * qualifiers. Qualifiers are themselves CGImageMetadataTags with their own 
 * namespace, prefix, name, and value. A common use is the xml:lang qualifier
 * for elements of an alternate-text array.
 * @return Returns a copy of the array of qualifiers. Elements of the array are 
 * CGImageMetadataTags. Returns NULL if the tag does not have any qualifiers. 
 * The copy is shallow, the qualifiers are not deep copied.
 */
IMAGEIO_EXTERN CFArrayRef CGImageMetadataTagCopyQualifiers(CGImageMetadataTagRef tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


// ****************************************************************************
// Functions for copying CGImageMetadataTagRefs from a CGImageMetadataRef. 
// These functions make it easier for the caller to traverse complex nested 
// structures of metadata, similar to KVC-compliant Objective-C classes.
// ****************************************************************************
///*! @functiongroup Retrieving CGImageMetadataTagRefs from a CGImageMetadataRef */
/*!
 * @function CGImageMetadataCopyTags
 * @abstract Obtain an array of tags from a CGImageMetadataRef
 * @return Returns an array with a shallow copy of all top-level 
 * CGImageMetadataTagRefs in a CGImageMetadataRef.
 */
IMAGEIO_EXTERN CFArrayRef CGImageMetadataCopyTags(CGImageMetadataRef metadata) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataCopyTagWithPath
 * @abstract Searches for a specific CGImageMetadataTag in a CGImageMetadataRef
 * @discussion This is the primary function for clients to obtain specific 
 * metadata properties from an image. The 'path' mechanism provides a way to 
 * access both simple top-level properties, such as Date & Time, or complex 
 * deeply-nested properties with ease.
 * @param metadata A collection of metadata tags.
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property). If the parent
 * is provided, the effective path will be the concatenation of the parent's path
 * and the 'path' parameter. This is useful for accessing array elements or 
 * structure fields inside nested tags.
 * @param path A string representing a path to the desired tag. Paths consist of
 * a tag prefix (i.e. "exif") joined with a tag name (i.e. "Flash") by a colon 
 * (":"), such as CFSTR("exif:Flash"). 
 * Elements of ordered and unordered arrays are accessed via 0-based indices inside square [] brackets.
 * Elements of alternate-text arrays are accessed by an RFC 3066 language code inside square [] brackets.
 * Fields of a structure are delimited by a period, '.'.
 * Qualifiers are delimited by the '?' character. Only tags with string values (kCGImageMetadataTypeString)
 * are allowed to have qualifiers - arrays and structures may not contain qualifiers.
 *
 * If parent is NULL, a prefix must be specified for the first tag. Prefixes for
 * all subsequent tags are optional. If unspecified, the prefix is 
 * inherented from the nearest parent tag with a prefix. Custom prefixes must be
 * registered using @link CGImageMetadataRegisterNamespaceForPrefix @/link prior to use 
 * in any path-based functions.
 *
 * Examples:
 *  <ul>
 *    <li>'path' = CFSTR("xmp:CreateDate")</li>       
 *    <li>'path' = CFSTR("exif:Flash.Fired")</li>
 *    <li>'parent' = tag at path CFSTR("exif:Flash"), path = CFSTR("exif:Fired") (equivilent to previous)</li>
 *    <li>'path' = CFSTR("exif:Flash.RedEyeMode")</li>
 *    <li>'path' = CFSTR("dc:title")</li>
 *    <li>'path' = CFSTR("dc:subject")</li>
 *    <li>'path' = CFSTR("dc:subject[2]") </li>
 *    <li>'parent' = tag at path CFSTR("dc:subject"), path = CFSTR("[2]") (equivilent to previous)</li>
 *    <li>'path' = CFSTR("dc:description[x-default])"</li>
 *    <li>'path' = CFSTR("dc.description[de])"</li>
 *    <li>'path' = CFSTR("dc.description[fr])"</li>
 *    <li>'path' = CFSTR("foo:product)"</li>
 *    <li>'path' = CFSTR("foo:product?bar:manufacturer)"</li>
 *  </ul>
 * @return Returns a copy of CGImageMetadataTag matching 'path', or NULL if no 
 * match is found. The copy of the tag's value is shallow. Tags
 * copied from an immutable CGImageMetadataRef are also immutable. Because this
 * function returns a copy of the tag's value, any modification of the tag's 
 * value must be followed by a CGImageMetadataSetTagWithPath to commit the 
 * change to the metadata container.
 */
IMAGEIO_EXTERN CGImageMetadataTagRef CGImageMetadataCopyTagWithPath(CGImageMetadataRef metadata, CGImageMetadataTagRef parent, CFStringRef path) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataCopyStringValueWithPath
 * @abstract Searches for a specific tag in a CGImageMetadataRef and returns its
 * string value.
 * @discussion This is a convenience method for searching for a tag at path and
 * extracting the string value.
 * @param metadata A collection of metadata tags.
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property).
 * @param path A string with the path to the desired tag. Please consult
 * the documentation of @link CGImageMetadataCopyTagWithPath @/link for 
 * information about path syntax.
 * @return Returns a string from a CGImageMetadataTag located at 'path'. The 
 * tag must be of type kCGImageMetadataTypeString or kCGImageMetadataTypeAlternateText.
 * For AlternateText tags, the element with the "x-default" language qualifier 
 * will be returned. For other types, NULL will be returned.
 */
IMAGEIO_EXTERN CFStringRef CGImageMetadataCopyStringValueWithPath(CGImageMetadataRef metadata, CGImageMetadataTagRef parent, CFStringRef path) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

// ****************************************************************************
// Functions for modifying a CGMutableImageMetadataRef
// ****************************************************************************
///*! @functiongroup Modifying a CGMutableImageMetadataRef */
/*!
 * @function CGImageMetadataRegisterNamespaceForPrefix
 * @abstract Associates an XMP namespace URI with a prefix string.
 * @discussion This allows ImageIO to create custom metadata when it encounters 
 * an unrecognized prefix in a path (see CGImageMetadataCopyTagWithPath for more
 * information about path syntax). A namespace must be registered before it can 
 * be used to add custom metadata. All namespaces found in the image's metadata,
 * or defined as a constant above, will be pre-registered. Namespaces and 
 * prefixes must be unique.
 * @return Returns true if successful. Returns false and sets 'err' if an error 
 * or conflict occurs.
 */
IMAGEIO_EXTERN bool CGImageMetadataRegisterNamespaceForPrefix(CGMutableImageMetadataRef metadata, CFStringRef xmlns, CFStringRef prefix, CFErrorRef* err) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataSetTagWithPath
 * @abstract Sets the tag at a specific path in a CGMutableImageMetadata container or a parent tag
 * @discussion This is the primary function for adding new metadata tags to a 
 * metadata container, or updating existing tags. All tags required to reach 
 * the final tag (at the end of the path) will be created, if needed. Tags will
 * created with default types (ordered arrays). Creating tags will fail if a 
 * prefix is encountered that has not been registered. Use
 * @link CGImageMetadataRegisterNamespaceForPrefix @/link to associate a prefix
 * with a namespace prior to using a path-based CGImageMetadata function.
 * Note that if a parent tag is provided,
 * the children of that tag reference will be modified, which may be a different
 * reference from the tag stored in the metadata container. Since tags are normally
 * obtained as a copy, it is typically neccesary to use CGImageMetadataSetTagWithPath
 * to commit the changed parent object back to the metadata container (using
 * the parent's path and NULL for the parent).
 * @param metadata A mutable collection of metadata tags. 
 * Use @link CGImageMetadataCreateMutableCopy @/link or 
 * @link CGImageMetadataCreateMutable @/link to obtain a mutable metadata container.
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property). 
 * Note that if a parent tag is provided,
 * the children of that tag reference will be modified, which may be a different
 * reference from the tag stored in the metadata container. Since tags are normally
 * obtained as a copy, it is typically neccesary to use CGImageMetadataSetTagWithPath
 * to commit the changed parent object back to the metadata container (using
 * the parent's path and NULL for the parent).
 * @param path A string with the path to the desired tag. Please consult
 * the documentation of @link CGImageMetadataCopyTagWithPath @/link for 
 * information about path syntax.
 * @param tag The CGImageMetadataTag to be added to the metadata. The tag
 * will be retained.
 * @return Returns true if successful, false otherwise.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetTagWithPath(CGMutableImageMetadataRef metadata, CGImageMetadataTagRef parent, CFStringRef path, CGImageMetadataTagRef tag) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataSetValueWithPath
 * @abstract Sets the value of the tag at a specific path in a CGMutableImageMetadataRef container or a parent tag
 * @discussion This function is used to add new metadata values to a 
 * metadata container, or update existing tag values. All tags required to reach 
 * the final tag (at the end of the path) are created, if needed. Tags are
 * created with default types (i.e. arrays will be ordered). Creating tags will 
 * fail if a prefix is encountered that has not been registered. Use
 * @link CGImageMetadataRegisterNamespaceForPrefix @/link to associate a prefix
 * with a namespace prior to using a path-based CGImageMetadata function.
 *
 * Examples
 * <ul>
 *     <li>'path' = CFSTR("xmp:CreateDate"), 'value' = CFSTR("2011-09-20T14:54:47-08:00")</li>
 *     <li>'path' = CFSTR("dc:subject[0]"), 'value' = CFSTR("San Francisco")</li>
 *     <li>'path' = CFSTR("dc:subject[1]"), 'value' = CFSTR("Golden Gate Bridge")</li>
 *     <li>'path' = CFSTR("dc:description[en]") 'value' = CFSTR("my image description")</li>
 *     <li>'path' = CFSTR("dc:description[de]") 'value' = CFSTR("meine bildbeschreibung")</li>
 * </ul>
 * Note that if a parent tag is provided,
 * the children of that tag reference will be modified, which may be a different
 * reference from the tag stored in the metadata container. Since tags are normally
 * obtained as a copy, it is typically neccesary to use CGImageMetadataSetTagWithPath
 * to commit the changed parent object back to the metadata container (using
 * the parent's path and NULL for the parent).
 * @param metadata A mutable collection of metadata tags. 
 * Use @link CGImageMetadataCreateMutableCopy @/link or 
 * @link CGImageMetadataCreateMutable @/link to obtain a mutable metadata container.
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property).
 * @param path A string with the path to the desired tag. Please consult
 * the documentation of @link CGImageMetadataCopyTagWithPath @/link for 
 * information about path syntax.
 * @param value The value to be added to the CGImageMetadataTag matching the path.
 * The tag will be retained. The restrictions for the value are the same as in @link
 * CGImageMetadataTagCreate @/link.
 * @return Returns true if successful, false otherwise.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetValueWithPath(CGMutableImageMetadataRef metadata, CGImageMetadataTagRef parent, CFStringRef path, CFTypeRef value) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataRemoveTagWithPath
 * @abstract Removes the tag at a specific path from a CGMutableImageMetadata container or from the parent tag
 * @discussion Use this function to delete a metadata tag matching a specific 
 * path from a mutable metadata container. Note that if a parent tag is provided,
 * the children of that tag reference will be modified, which may be a different
 * reference from the tag stored in the metadata container. Since tags are normally
 * obtained as a copy, it is typically neccesary to use CGImageMetadataSetTagWithPath
 * to commit the changed parent object back to the metadata container (using
 * the parent's path and NULL for the parent).
 * @param parent A parent tag. If NULL, the path is relative to the root of the
 * CGImageMetadataRef (i.e. it is not a child of another property).
 * @param path A string with the path to the desired tag. Please consult
 * the documentation of @link CGImageMetadataCopyTagWithPath @/link for 
 * information about path syntax.
 */
IMAGEIO_EXTERN bool CGImageMetadataRemoveTagWithPath(CGMutableImageMetadataRef metadata, 
                                      CGImageMetadataTagRef parent,
                                      CFStringRef path) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


#ifdef __BLOCKS__
///*! @functiongroup Iterating through tags of CGImageMetadataRef */
/*!
 * @typedef CGImageMetadataTagBlock
 * @abstract The block type used by CGImageMetadataEnumerateTagsUsingBlock
 * @param path The full path to the tag in the metadata container.
 * @param tag The CGImageMetadataTagRef corresponding to the path in metadata.
 * @return Return true to continue iterating through the tags, or return false to stop.
 */
typedef bool(^CGImageMetadataTagBlock)(CFStringRef path, CGImageMetadataTagRef tag);

// Enumerates the children of the tag located at 'path'.
// If 'rootPath' is nil, all top-level tags in 'metadata' will be enumerated.
// Executes a CGImageMetadataTagBlock, 'block', for each CGImageMetadataTag.
// The block should return true to continue enumeration, or false to stop.
// Behavior is undefined if 'metadata' is modified during enumeration.

/*!
 * @function CGImageMetadataEnumerateTagsUsingBlock
 * @abstract Executes a given block using each tag in the metadata
 * @discussion This function iterates over all of the tags in a
 * CGImageMetadataRef, executing the block for each tag. The default behavior 
 * iterates over all top-level tags in the metadata. The path of the tag and 
 * the tag itself is passed to the block. The metadata cannot be modified inside
 * the block - consider adding the tags of interest into another collection.
 * @param metadata A collection of metadata tags.
 * @param rootPath Iteration will occur for all children of the tag matching
 * the root path. Please refer to CGImageMetadataCopyTagWithPath for information
 * about path syntax. If NULL or an empty string, the block will be executed 
 * for all top-level tags in the metadata container.
 * @param options A dictionary of options for iterating through the tags.
 * Currently the only supported option is kCGImageMetadataEnumerateRecursively,
 * which should be set to a CFBoolean.
 * @param block The block that is executed for each tag in metadata.
 */
IMAGEIO_EXTERN void CGImageMetadataEnumerateTagsUsingBlock(CGImageMetadataRef metadata,
                                            CFStringRef rootPath,
                                            CFDictionaryRef options,
                                            CGImageMetadataTagBlock block) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);
#endif

// A key for the 'options' of CGImageMetadataEnumerateTagsUsingBlock. If present,
// the value should be a CFBoolean. If true, tags will be enumerated recursively,
// if false, only the direct children of 'rootPath' will be enumerated. 
// The default is non-recursive.
IMAGEIO_EXTERN const CFStringRef kCGImageMetadataEnumerateRecursively IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


// ****************************************************************************
// Functions for working with constants defined in CGImageProperties.h
// Provides a bridge for values from CGImageCopyPropertiesAtIndex().
// Simplifies metadata access for properties defined EXIF and IPTC standards, 
// which have no notion of namespaces, prefixes, or XMP property types.
// Metadata Working Group guidance is factored into the mapping of 
// CGImageProperties to XMP. For example, setting Exif DateTimeOriginal will
// set the value of the corresponding XMP tag, which is photoshop:DateCreated
// ****************************************************************************

///*! @functiongroup Working with CGImageProperties */
/*!
 * @function CGImageMetadataCopyTagMatchingImageProperty
 * @abstract Searches for a specific CGImageMetadataTag matching a kCGImageProperty constant
 * @discussion Provides a bridge for values from CGImageCopyPropertiesAtIndex, simplifying 
 * access for properties defined in EXIF and IPTC standards, which have no notion of 
 * namespaces, prefixes, or XMP property types.
 * Metadata Working Group guidance is factored into the mapping of CGImageProperties to 
 * XMP compatible CGImageMetadataTags.
 * For example, kCGImagePropertyExifDateTimeOriginal will get the value of the 
 * corresponding XMP tag, which is photoshop:DateCreated. Note that property values will 
 * still be in their XMP forms, such as "YYYY-MM-DDThh:mm:ss" for DateTime, rather than
 * the EXIF or IPTC DateTime formats.
 * @param metadata A collection of metadata tags
 * @param dictionaryName the metadata subdictionary to which the image property belongs,
 * such as kCGImagePropertyExifDictionary or kCGImagePropertyIPTCDictionary. Not all
 * dictionaries and properties are supported at this time.
 * @param propertyName the name of the property. This must be a defined property constant
 * corresponding to the 'dictionaryName'. For example, kCGImagePropertyTIFFOrientation,
 * kCGImagePropertyExifDateTimeOriginal, or kCGImagePropertyIPTCKeywords. A warning
 * will be logged if the CGImageProperty is unsupported by CGImageMetadata.
 * @return Returns a CGImageMetadataTagRef with the appropriate namespace, prefix, 
 * tag name, and XMP value for the corresponding CGImageProperty. Returns NULL if the 
 * property could not be found.
 */
IMAGEIO_EXTERN CGImageMetadataTagRef 
CGImageMetadataCopyTagMatchingImageProperty(CGImageMetadataRef metadata, CFStringRef dictionaryName, CFStringRef propertyName) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

/*!
 * @function CGImageMetadataSetValueMatchingImageProperty
 * @abstract Sets the value of the CGImageMetadataTag matching a kCGImageProperty constant
 * @discussion Provides a bridge for values from CGImageCopyPropertiesAtIndex, simplifying 
 * changing property values defined in EXIF and IPTC standards, which have no notion of 
 * namespaces, prefixes, or XMP property types.
 * Metadata Working Group guidance is factored into the mapping of CGImageProperties to 
 * XMP compatible CGImageMetadataTags.
 * For example, setting kCGImagePropertyExifDateTimeOriginal will set the value of the 
 * corresponding XMP tag, which is photoshop:DateCreated. Note that property values should 
 * still be in their XMP forms, such as "YYYY-MM-DDThh:mm:ss" for DateTime, rather than
 * the EXIF or IPTC DateTime formats. Although this function will allow the caller to set
 * custom values for these properties, you should consult the appropriate specifications 
 * for details about property value formats for EXIF and IPTC tags in XMP.
 * @param metadata A mutable collection of metadata tags
 * @param dictionaryName the metadata subdictionary to which the image property belongs,
 * such as kCGImagePropertyExifDictionary or kCGImagePropertyIPTCDictionary. Not all
 * dictionaries and properties are supported at this time.
 * @param propertyName the name of the property. This must be a defined property constant
 * corresponding to the 'dictionaryName'. For example, kCGImagePropertyTIFFOrientation,
 * kCGImagePropertyExifDateTimeOriginal, or kCGImagePropertyIPTCKeywords. A warning
 * will be logged if the CGImageProperty is unsupported by CGImageMetadata.
 * @param value A CFTypeRef with the value for the tag. The same value restrictions apply
 * as in @link CGImageMetadataTagCreate @/link.
 * @return Returns true if successful, false otherwise.
 */
IMAGEIO_EXTERN bool CGImageMetadataSetValueMatchingImageProperty(CGMutableImageMetadataRef metadata,
                                                  CFStringRef dictionaryName,
                                                  CFStringRef propertyName,
                                                  CFTypeRef value) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


//将XMP数据的CGImageMetadataRef转换成序列化CFDataRef，常见的用处:在不支持XMP或者无法编辑的格式情况下创建sidecar文件
//CGImageMetadataRef元数据标签的集合
//options：应该是NULL。选项是目前不使用，但可用于未来版本。
IMAGEIO_EXTERN CFDataRef CGImageMetadataCreateXMPData (CGImageMetadataRef metadata,
                                        CFDictionaryRef options) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);

//将XMP数据CFDataRef转换成CGImageMetadataTags
//XMP数据转换成一系列的元数据标签。数据必须是一个完整的XMP树。XMP包报头支持(<?xpacket .. ?>)
//CFDataRef:XMP数据数据。
IMAGEIO_EXTERN CGImageMetadataRef CGImageMetadataCreateFromXMPData (CFDataRef data) IMAGEIO_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_7_0);


//所有的在ImageIO中CGImageMetadata APIs中的错误都可以用 kCFErrorDomainCGImageMetadata
IMAGEIO_EXTERN const CFStringRef kCFErrorDomainCGImageMetadata;

//错误类型
typedef enum CGImageMetadataErrors {
    kCGImageMetadataErrorUnknown = 0, //未知的
    kCGImageMetadataErrorUnsupportedFormat = 1,//不支持的格式
    kCGImageMetadataErrorBadArgument = 2,//参数错误
    kCGImageMetadataErrorConflictingArguments = 3,//参数冲突
    kCGImageMetadataErrorPrefixConflict = 4,//前缀冲突
} CGImageMetadataErrors;

CF_IMPLICIT_BRIDGING_DISABLED

#endif // CGIMAGEMETADATA_H_
