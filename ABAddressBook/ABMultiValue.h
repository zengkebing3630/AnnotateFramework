/*
 *  ABMultiValue.h
 *  AddressBook
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 *  MultiValues are ordered, homogeneous collections of values. Each
 *  value has a unique persistent identifier which can be use to
 *  identify the value across changes to the MultiValue (ie. when
 *  the value's index may have changed). Each value may also have a
 *  non-unique string label.
 *
 */

#ifndef __ABMultiValue__
#define __ABMultiValue__

#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABRecord.h>

typedef CFTypeRef ABMultiValueRef;

typedef int32_t ABMultiValueIdentifier;
#define kABMultiValueInvalidIdentifier -1

// Type of the contained values
// 当前的多值对象是对应哪种类型，可以配合CFStringRef ABPersonCopyLocalizedPropertyName(ABPropertyID property);来显示类型
AB_EXTERN ABPropertyType ABMultiValueGetPropertyType(ABMultiValueRef multiValue);
//获取当前多值里面含有value的总数
AB_EXTERN CFIndex ABMultiValueGetCount(ABMultiValueRef multiValue);
//根据索引获取对应的value
AB_EXTERN CFTypeRef ABMultiValueCopyValueAtIndex(ABMultiValueRef multiValue, CFIndex index);
//获取里面所有的value
AB_EXTERN CFArrayRef ABMultiValueCopyArrayOfAllValues(ABMultiValueRef multiValue);
//根据索引获取其对应的标签，可以配合CFStringRef ABAddressBookCopyLocalizedLabel(CFStringRef label);来显示类型
AB_EXTERN CFStringRef ABMultiValueCopyLabelAtIndex(ABMultiValueRef multiValue, CFIndex index);
//获取注册的多值的Index
AB_EXTERN CFIndex ABMultiValueGetIndexForIdentifier(ABMultiValueRef multiValue, ABMultiValueIdentifier identifier);
//获取注册的多值value通过Index
AB_EXTERN ABMultiValueIdentifier ABMultiValueGetIdentifierAtIndex(ABMultiValueRef multiValue, CFIndex index);
//获取第一个Index的Value
AB_EXTERN CFIndex ABMultiValueGetFirstIndexOfValue(ABMultiValueRef multiValue, CFTypeRef value);

// Mutable multivalues

typedef CFTypeRef ABMutableMultiValueRef;
//根据type创建对应多值对象
AB_EXTERN ABMutableMultiValueRef ABMultiValueCreateMutable(ABPropertyType type);
//拷贝另一个多值对象来初始化多值对象
AB_EXTERN ABMutableMultiValueRef ABMultiValueCreateMutableCopy(ABMultiValueRef multiValue);
 //在多值里面添加新的属性。
AB_EXTERN bool ABMultiValueAddValueAndLabel(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, ABMultiValueIdentifier *outIdentifier);
//在多值里面Index插入新的属性
AB_EXTERN bool ABMultiValueInsertValueAndLabelAtIndex(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, CFIndex index, ABMultiValueIdentifier *outIdentifier);
//根据索引Index删除标签的value
AB_EXTERN bool ABMultiValueRemoveValueAndLabelAtIndex(ABMutableMultiValueRef multiValue, CFIndex index);
//根据索引Index替换对应的value
AB_EXTERN bool ABMultiValueReplaceValueAtIndex(ABMutableMultiValueRef multiValue, CFTypeRef value, CFIndex index);
//根据索引Index替换对应的标签
AB_EXTERN bool ABMultiValueReplaceLabelAtIndex(ABMutableMultiValueRef multiValue, CFStringRef label, CFIndex index);
    
#endif

