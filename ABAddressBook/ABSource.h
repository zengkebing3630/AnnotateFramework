/*
 *  ABSource.h
 *  AddressBook
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */


#ifndef __ABSource__
#define __ABSource__

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABPerson.h>

#include <Availability.h>

#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

#define kABSourceTypeSearchableMask  0x01000000

enum {
    kABSourceTypeLocal       = 0x0, //本地
    kABSourceTypeExchange    = 0x1,
    kABSourceTypeExchangeGAL = kABSourceTypeExchange | kABSourceTypeSearchableMask,

    kABSourceTypeMobileMe    = 0x2,

    kABSourceTypeLDAP        = 0x3 | kABSourceTypeSearchableMask,
    
    kABSourceTypeCardDAV     = 0x4,
    kABSourceTypeCardDAVSearch = kABSourceTypeCardDAV | kABSourceTypeSearchableMask,
};
typedef int ABSourceType; //通讯录数据类型

#endif

AB_EXTERN const ABPropertyID kABSourceNameProperty __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // string
AB_EXTERN const ABPropertyID kABSourceTypeProperty __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0); // CFNumberRef of ABSourceType (int)

//获取拷贝默认通讯录
AB_EXTERN ABRecordRef ABAddressBookCopyDefaultSource(ABAddressBookRef addressBook) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
//获取特定的sourceID通讯录
AB_EXTERN ABRecordRef ABAddressBookGetSourceWithRecordID(ABAddressBookRef addressBook, ABRecordID sourceID) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
//获取拷贝所有通讯录
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllSources(ABAddressBookRef addressBook) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

#endif
