/*
 *  ABAddressBook.h
 *  AddressBook
 *
 *  Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 */

#ifndef __ABAddressBook__
#define __ABAddressBook__

#include <AddressBook/AddressBookDefines.h>
#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/ABRecord.h>

AB_EXTERN const CFStringRef ABAddressBookErrorDomain;

enum {
    kABOperationNotPermittedByStoreError = 0,
    kABOperationNotPermittedByUserError
};

typedef CFTypeRef ABAddressBookRef;

// To check the app's access to contact data. Based upon the access, the app could
// display or hide its UI elements that would access any AddressBook API.
//
// kABAuthorizationStatusNotDetermined
// The user has not yet made a choice regarding whether this app can access the data class.
//
// kABAuthorizationStatusRestricted
// This application is not authorized to access the data class. The user cannot change
// this application’s status, possibly due to active restrictions such as parental controls
// being in place.
//
// kABAuthorizationStatusDenied
// The user explicitly denied access to the data class for this application.
//
// kABAuthorizationStatusAuthorized
// This application is authorized to access the data class.
//
typedef CF_ENUM(CFIndex, ABAuthorizationStatus) {
    kABAuthorizationStatusNotDetermined = 0,
    kABAuthorizationStatusRestricted,
    kABAuthorizationStatusDenied,
    kABAuthorizationStatusAuthorized
};
//通讯录的授权情况
AB_EXTERN ABAuthorizationStatus ABAddressBookGetAuthorizationStatus(void) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

// Call ABAddressBookCreateWithOptions to create an instance of AddressBook. The
// ABAddressBookRef will initially not have access to contact data. The app must
// then call ABAddressBookRequestAccessWithCompletion to request this access.
// The options argument is reserved for future use. Currently it will always be NULL.
// If access to contact data is already restricted or denied, this will fail returning
// a NULL ABAddressBookRef with error kABOperationNotPermittedByUserError.
//创建通讯录对象ABAddressBookRef
AB_EXTERN ABAddressBookRef ABAddressBookCreateWithOptions(CFDictionaryRef options, CFErrorRef* error) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

//创建通讯录
//获取本地通讯录数据库，相当于通讯录的一个引用，该对象非常重要，后面对通讯录的操作都离不开此对象
AB_EXTERN ABAddressBookRef ABAddressBookCreate(void) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_6_0);

// Users are able to grant or deny access to contact data on a per-app basis. To request
// access to contact data, call ABAddressBookRequestAccessWithCompletion. This will not
// block the app while the user is being asked to grant or deny access. Until access has
// been granted, a non-NULL ABAddressBookRef will not contain any contacts and any attempt to
// modify contacts will fail with CFErrorRef returning kABOperationNotPermittedByUserError.
// The user will only be prompted the first time access is requested; any subsequent calls
// to ABAddressBookCreateWithOptions will use the existing permissions. The completion
// handler is called on an arbitrary queue. If the ABAddressBookRef is used throughout the app,
// then all usage should be dispatched to the same queue to use ABAddressBookRef in a
// thread-safe manner.
typedef void(^ABAddressBookRequestAccessCompletionHandler)(bool granted, CFErrorRef error);
// 获得用户授权访问通讯录
AB_EXTERN void ABAddressBookRequestAccessWithCompletion(ABAddressBookRef addressBook,  ABAddressBookRequestAccessCompletionHandler completion) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

//保存修改后的通讯录，如增删改等操作。
AB_EXTERN bool ABAddressBookSave(ABAddressBookRef addressBook, CFErrorRef* error);
//判断当前通讯录实例是否有待保存项
AB_EXTERN bool ABAddressBookHasUnsavedChanges(ABAddressBookRef addressBook);
//在通讯录中新增联系人
AB_EXTERN bool ABAddressBookAddRecord(ABAddressBookRef addressBook, ABRecordRef record, CFErrorRef* error);
//在通讯录中删除联系人
AB_EXTERN bool ABAddressBookRemoveRecord(ABAddressBookRef addressBook, ABRecordRef record, CFErrorRef* error);

// Some labels are special keys representing generic labels. Use this function to obtain
// a localized string for a label to display to a user.
// 获取拷贝字符串数据本地化
AB_EXTERN CFStringRef ABAddressBookCopyLocalizedLabel(CFStringRef label);

// Register an external change callback if you want to be informed of changes to the
// shared Address Book database by other instances or processes. The callback will be
// invoked by CFRunLoop on the thread where it was registered. The ABAddressBook does
// not take any action by default to flush or synchronize cached state with the database.
// If you want to ensure that you don't see any stale values, use ABAddressBookRevert().

// The info argument may eventually contain information describing the change. Currently
// it will always be NULL.
//通讯录外部修改后，回调函数的定义形式。
typedef void (*ABExternalChangeCallback)(ABAddressBookRef addressBook, CFDictionaryRef info, void *context);

/*注册通讯录外部修改后的回调通知，并指定回调函数。
注：注册的回调方法有个注意点，在程序运行时，如果进行修改通讯录操作，其注册的回调方法亦会触发，且每修改一条记录，都会触发一次，
因此在程序运行时，建议取消注册，程序退到后台时，再重新注册
*/
AB_EXTERN void ABAddressBookRegisterExternalChangeCallback(ABAddressBookRef addressBook, ABExternalChangeCallback callback, void *context);

// When unregistering a callback both the callback and the context need to match the ones
// that were registered.
//取消通讯录外部修改后的回调通知
AB_EXTERN void ABAddressBookUnregisterExternalChangeCallback(ABAddressBookRef addressBook, ABExternalChangeCallback callback, void *context);

// ABAddressBookRevert() discards all cached properties and any unsaved changes so that
// records and properties retrieved subsequently will reflect any changes made by external
// ABAddressBook instances. If records were deleted externally, the corresponding ABRecord
// instances will return NULL for all properties. If necessary you can identify these
// deleted records by checking whether the class accessor (eg. ABPersonGetPersonWithRecordID())
// returns the record.
//还原系统通讯录
AB_EXTERN void ABAddressBookRevert(ABAddressBookRef addressBook);

#endif
