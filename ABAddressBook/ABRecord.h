/*
 *  ABRecord.h
 *  AddressBook
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 *  An ABRecord corresponds to a persistent item, currently either
 *  a contact or a group. Records have a unique persistent integer
 *  ID and a collection of properties with integer keys.
 *
 */

#ifndef __ABRecord__
#define __ABRecord__

#include <AddressBook/AddressBookDefines.h>
#include <CoreFoundation/CoreFoundation.h>
        
typedef CFTypeRef ABRecordRef;

typedef int32_t ABRecordID;
typedef int32_t ABPropertyID;

typedef uint32_t ABRecordType;
enum {
    kABPersonType = 0, //用户
    kABGroupType  = 1, //群组
    kABSourceType = 2  //群组列表
};

#define kABMultiValueMask (1 << 8)
#define kABRecordInvalidID -1
#define kABPropertyInvalidID -1

typedef uint32_t ABPropertyType;
enum {
    kABInvalidPropertyType         = 0x0,
    kABStringPropertyType          = 0x1,
    kABIntegerPropertyType         = 0x2,
    kABRealPropertyType            = 0x3,
    kABDateTimePropertyType        = 0x4,
    kABDictionaryPropertyType      = 0x5,
    kABMultiStringPropertyType     = kABMultiValueMask | kABStringPropertyType,
    kABMultiIntegerPropertyType    = kABMultiValueMask | kABIntegerPropertyType,
    kABMultiRealPropertyType       = kABMultiValueMask | kABRealPropertyType,
    kABMultiDateTimePropertyType   = kABMultiValueMask | kABDateTimePropertyType,
    kABMultiDictionaryPropertyType = kABMultiValueMask | kABDictionaryPropertyType,
};
//返回 ABRecordID ，代表了 记录在底层数据库中的ID号。具有唯一性。
AB_EXTERN ABRecordID ABRecordGetRecordID(ABRecordRef record);
//返回记录类型。可以是 kABPersonType 和 kABGroupType,kABSourceType。
AB_EXTERN ABRecordType ABRecordGetRecordType(ABRecordRef record);
//根据标签获取对应的属性值
//CFTypeRef firstName = ABRecordCopyValue(personRef, kABPersonFirstNameProperty);//根据标签获取对应的属性值,以FirstName为例
AB_EXTERN CFTypeRef ABRecordCopyValue(ABRecordRef record, ABPropertyID property);
//设置对应标签的属性值
//ABRecordSetValue(personRef, kABPersonFirstNameProperty, (CFTypeRef)@"john", &err);//设置标签对应的属性值,以FirstName为例 
/*
设置ABRecordRef的属性值。
注意在设置ABRecordRef的值时又分为单值属性和多值属性：
单值属性设置只要通过ABRecordSetValue()方法指定属性名和值即可；
多值属性则要先通过创建一个ABMutableMultiValueRef类型的变量，然后通过ABMultiValueAddValueAndLabel()方法依次添加属性值，
最后通过ABRecordSetValue()方法将ABMutableMultiValueRef类型的变量设置为记录值。
*/
AB_EXTERN bool ABRecordSetValue(ABRecordRef record, ABPropertyID property, CFTypeRef value, CFErrorRef* error);
//移除对应的标签属性的值
//ABRecordRemoveValue(personRef, kABPersonFirstNameProperty, &err);//移除标签对应的属性值,以FirstName为例
AB_EXTERN bool ABRecordRemoveValue(ABRecordRef record, ABPropertyID property, CFErrorRef* error);
//获取联系人的全名,联系人（或群组）的复合信息（对于联系人则包括：姓、名、公司等信息，对于群组则返回组名称）。
AB_EXTERN CFStringRef ABRecordCopyCompositeName(ABRecordRef record);

#endif

