/*
 *  ABGroup.h
 *  AddressBook
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 *  An ABGroup is a non-ordered collection of records.
 *
 */

#ifndef __ABGroup__
#define __ABGroup__

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>
#include <AddressBook/ABSource.h>

AB_EXTERN const int kABGroupNameProperty;

// ABGroupCreate creates a new group in the default source
// 创建新的群组
AB_EXTERN ABRecordRef ABGroupCreate(void);
// 以source原始数据创建群组
AB_EXTERN ABRecordRef ABGroupCreateInSource(ABRecordRef source) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
// 以拷贝source原始数据创建群组
AB_EXTERN ABRecordRef ABGroupCopySource(ABRecordRef group) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
//获取群组Group中所有的成员
AB_EXTERN CFArrayRef ABGroupCopyArrayOfAllMembers(ABRecordRef group);
//获取群组Group中所有的成员，群组Group通过SortOrdering排序过 
//ABPersonSortOrdering {kABPersonSortByFirstName,kABPersonSortByLastName}排序方式有第一个名字或者最后一个名字
AB_EXTERN CFArrayRef ABGroupCopyArrayOfAllMembersWithSortOrdering(ABRecordRef group, ABPersonSortOrdering sortOrdering);
//往群组Group添加成员person
AB_EXTERN bool ABGroupAddMember(ABRecordRef group, ABRecordRef person, CFErrorRef* error);
//从群组Group移除成员
AB_EXTERN bool ABGroupRemoveMember(ABRecordRef group, ABRecordRef member, CFErrorRef* error);

// Finding groups
//通过RecordId唯一标示找到指定数据，可能是 ABPerson,ABGroup
AB_EXTERN ABRecordRef ABAddressBookGetGroupWithRecordID(ABAddressBookRef addressBook, ABRecordID recordID);
//获取通讯录所有群组的总数量
AB_EXTERN CFIndex ABAddressBookGetGroupCount(ABAddressBookRef addressBook);
//获取拷贝所有的群组数据
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllGroups(ABAddressBookRef addressBook);
//从Source中拷贝所有的群组数据
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllGroupsInSource(ABAddressBookRef addressBook, ABRecordRef source) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

#endif

