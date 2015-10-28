/*
 *  ABPerson.h
 *  AddressBook
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 *  An ABPerson corresponds to a contact such as a person or organization.
 *
 */

#ifndef __ABPerson__
#define __ABPerson__

#include <CoreFoundation/CoreFoundation.h>

#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABAddressBook.h>
#include <AddressBook/ABRecord.h>
#include <AddressBook/ABSource.h>

#include <Availability.h>

// ABPersonCreate creates a new person in the default source
//创建新的联系人。这样可以得到一个空记录，然后就可以向其中填充信息
AB_EXTERN ABRecordRef ABPersonCreate(void);
//从Source中创建新的联系人
AB_EXTERN ABRecordRef ABPersonCreateInSource(ABRecordRef source) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
//拷贝Person来创建新的联系人
AB_EXTERN ABRecordRef ABPersonCopySource(ABRecordRef person) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

// Returns an array of all the linked people, including the person passed in. If the person is not linked, returns an array with the person passed in.
// 拷贝所有联系人链接的数组
AB_EXTERN CFArrayRef ABPersonCopyArrayOfAllLinkedPeople(ABRecordRef person) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);

//获取属性property的类型
AB_EXTERN ABPropertyType ABPersonGetTypeOfProperty(ABPropertyID property);
// 根据应用设置的语言，可以国际化标签kABPersonNicknameProperty在中文环境下会得到“昵称”
AB_EXTERN CFStringRef ABPersonCopyLocalizedPropertyName(ABPropertyID property);

typedef uint32_t ABPersonSortOrdering; //排序方式
enum {
    kABPersonSortByFirstName = 0,
    kABPersonSortByLastName  = 1
};

AB_EXTERN ABPersonSortOrdering ABPersonGetSortOrdering(void);

typedef uint32_t ABPersonCompositeNameFormat;//复合数据的格式
enum  {
    kABPersonCompositeNameFormatFirstNameFirst = 0, //第一个名字在前, 顺序
    kABPersonCompositeNameFormatLastNameFirst  = 1  //最后一个名字前，倒序
};

// Composite Names
//创建一个数据格式
AB_EXTERN ABPersonCompositeNameFormat ABPersonGetCompositeNameFormat(void) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_7_0); // Deprecated. Call ABPersonGetCompositeNameFormatForRecord passing NULL for the record argument instead.
//获取Record数据格式
AB_EXTERN ABPersonCompositeNameFormat ABPersonGetCompositeNameFormatForRecord(ABRecordRef record) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0); // The appropriate "First, Last" or "Last, First" order for the contact depending on the detected locale of the contact's name. If the record has no first, middle and last name, or if the record is NULL, then the Contacts Display Order preference is returned.
//获取Record数据格式的分割符
AB_EXTERN CFStringRef ABPersonCopyCompositeNameDelimiterForRecord(ABRecordRef record) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0); // The delimiter that should be used to separate name components. If the record has no first, middle and last name, or if the record is NULL, then a default delimiter is returned.

// Images
typedef enum {
    kABPersonImageFormatThumbnail = 0,      // the square thumbnail  缩略图
    kABPersonImageFormatOriginalSize = 2    // the original image as set by ABPersonSetImageData 原尺寸图片
} ABPersonImageFormat;
//设置联系人头像
AB_EXTERN bool ABPersonSetImageData(ABRecordRef person, CFDataRef imageData, CFErrorRef* error);
//获取联系人头像，头像图片为原始图片
AB_EXTERN CFDataRef ABPersonCopyImageData(ABRecordRef person);
//获取联系人头像，format: kABPersonImageFormatThumbnail获取的头像图片为缩略图，kABPersonImageFormatOriginalSize获取的头像图片原始大小图片
AB_EXTERN CFDataRef ABPersonCopyImageDataWithFormat(ABRecordRef person, ABPersonImageFormat format) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_1);
//判断该联系人是否有头像
AB_EXTERN bool ABPersonHasImageData(ABRecordRef person);
//移除该联系人的头像
AB_EXTERN bool ABPersonRemoveImageData(ABRecordRef person, CFErrorRef* error);

// Sorting
// 比较两个Person名字，ordering排序方式
AB_EXTERN CFComparisonResult ABPersonComparePeopleByName(ABRecordRef person1, ABRecordRef person2, ABPersonSortOrdering ordering);

// Finding people
//获取通讯录中的联系人总数
AB_EXTERN CFIndex ABAddressBookGetPersonCount(ABAddressBookRef addressBook);
//根据recordID，获取对应的联系人实例
AB_EXTERN ABRecordRef ABAddressBookGetPersonWithRecordID(ABAddressBookRef addressBook, ABRecordID recordID);

//拷贝通讯录中全部联系人记录 
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeople(ABAddressBookRef addressBook);
//拷贝通讯录中source中全部联系人记录 
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeopleInSource(ABAddressBookRef addressBook, ABRecordRef source) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
//拷贝通讯录中source中全部联系人记录 ，sortOrdering排序方式
AB_EXTERN CFArrayRef ABAddressBookCopyArrayOfAllPeopleInSourceWithSortOrdering(ABAddressBookRef addressBook, ABRecordRef source, ABPersonSortOrdering sortOrdering) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
//根据名字获取对应的联系人记录
AB_EXTERN CFArrayRef ABAddressBookCopyPeopleWithName(ABAddressBookRef addressBook, CFStringRef name);

// VCard
    // Creates an array of people from a vcard representation. Source is optional. The people
    // will be created in the source given as the first argument, or the default source if NULL.
    // 用VCardData创建People
AB_EXTERN CFArrayRef ABPersonCreatePeopleInSourceWithVCardRepresentation(ABRecordRef source, CFDataRef vCardData) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
    // Creates a vCard representation of the people passed in.
    // 用People创建用户名片
AB_EXTERN CFDataRef ABPersonCreateVCardRepresentationWithPeople(CFArrayRef people) __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Generic labels
AB_EXTERN const CFStringRef kABWorkLabel;
AB_EXTERN const CFStringRef kABHomeLabel;
AB_EXTERN const CFStringRef kABOtherLabel;

// Property keys
AB_EXTERN const ABPropertyID kABPersonFirstNameProperty;          // First name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonLastNameProperty;           // Last name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonMiddleNameProperty;         // Middle name - kABStringPropertyType
AB_EXTERN const ABPropertyID kABPersonPrefixProperty;             // Prefix ("Sir" "Duke" "General") - kABStringPropertyType//读取prefix前缀 
AB_EXTERN const ABPropertyID kABPersonSuffixProperty;             // Suffix ("Jr." "Sr." "III") - kABStringPropertyType//读取suffix后缀 
AB_EXTERN const ABPropertyID kABPersonNicknameProperty;           // Nickname - kABStringPropertyType //读取nickname呢称  
AB_EXTERN const ABPropertyID kABPersonFirstNamePhoneticProperty;  // First name Phonetic - kABStringPropertyType //读取firstname拼音音标  
AB_EXTERN const ABPropertyID kABPersonLastNamePhoneticProperty;   // Last name Phonetic - kABStringPropertyType//读取lastname拼音音标 
AB_EXTERN const ABPropertyID kABPersonMiddleNamePhoneticProperty; // Middle name Phonetic - kABStringPropertyType//读取middlename拼音音标 
AB_EXTERN const ABPropertyID kABPersonOrganizationProperty;       // Company name - kABStringPropertyType//读取organization公司 
AB_EXTERN const ABPropertyID kABPersonJobTitleProperty;           // Job Title - kABStringPropertyType//读取jobtitle工作 
AB_EXTERN const ABPropertyID kABPersonDepartmentProperty;         // Department name - kABStringPropertyType//读取department部门
AB_EXTERN const ABPropertyID kABPersonEmailProperty;              // Email(s) - kABMultiStringPropertyType //获取email多值 
AB_EXTERN const ABPropertyID kABPersonBirthdayProperty;           // Birthday associated with this person - kABDateTimePropertyType//读取birthday生日 
AB_EXTERN const ABPropertyID kABPersonNoteProperty;               // Note - kABStringPropertyType//读取note备忘录 
AB_EXTERN const ABPropertyID kABPersonCreationDateProperty;       // Creation Date (when first saved)//第一次添加该条记录的时间  
AB_EXTERN const ABPropertyID kABPersonModificationDateProperty;   // Last saved date//最后一次修改該条记录的时间  

// Addresses
AB_EXTERN const ABPropertyID kABPersonAddressProperty;            // Street address - kABMultiDictionaryPropertyType  //读取地址多值 
AB_EXTERN const CFStringRef kABPersonAddressStreetKey;//街道
AB_EXTERN const CFStringRef kABPersonAddressCityKey;//城市
AB_EXTERN const CFStringRef kABPersonAddressStateKey;//省
AB_EXTERN const CFStringRef kABPersonAddressZIPKey;//邮编
AB_EXTERN const CFStringRef kABPersonAddressCountryKey;//国家
AB_EXTERN const CFStringRef kABPersonAddressCountryCodeKey;//国家编号

/*
 * kABPersonAddressCountryCodeKey code must be in the form of 2 character iso 3166 country codes
 *
 * eg:
 *    fr = France
 *    us = United States
 * etc.
 *
 */

// Dates
AB_EXTERN const ABPropertyID kABPersonDateProperty;               // Dates associated with this person - kABMultiDatePropertyType//获取dates多值
AB_EXTERN const CFStringRef kABPersonAnniversaryLabel;

// Kind
AB_EXTERN const ABPropertyID kABPersonKindProperty;               // Person/Organization - kABIntegerPropertyType//获取kind值
AB_EXTERN const CFNumberRef kABPersonKindPerson;
AB_EXTERN const CFNumberRef kABPersonKindOrganization;

// Phone numbers
AB_EXTERN const ABPropertyID kABPersonPhoneProperty;              // Generic phone number - kABMultiStringPropertyType //读取电话多值
AB_EXTERN const CFStringRef kABPersonPhoneMobileLabel;            //移动电话 
AB_EXTERN const CFStringRef kABPersonPhoneIPhoneLabel __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);//iPhone电话
AB_EXTERN const CFStringRef kABPersonPhoneMainLabel; //主要电话  
AB_EXTERN const CFStringRef kABPersonPhoneHomeFAXLabel;//家庭传真 
AB_EXTERN const CFStringRef kABPersonPhoneWorkFAXLabel;//工作传真  
AB_EXTERN const CFStringRef kABPersonPhoneOtherFAXLabel __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);//其他传真  
AB_EXTERN const CFStringRef kABPersonPhonePagerLabel;//呼机  

// IM
AB_EXTERN const ABPropertyID kABPersonInstantMessageProperty;     // Instant Messaging - kABMultiDictionaryPropertyType //获取IM多值  
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceKey;     // Service ("Yahoo", "Jabber", etc.)
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceYahoo;
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceJabber;
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceMSN;
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceICQ;
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceAIM;
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceQQ __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceGoogleTalk __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceSkype __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceFacebook __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonInstantMessageServiceGaduGadu __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

AB_EXTERN const CFStringRef kABPersonInstantMessageUsernameKey;    // Username

// URLs
AB_EXTERN const ABPropertyID kABPersonURLProperty;                // URL - kABMultiStringPropertyType //获取URL多值  
AB_EXTERN const CFStringRef kABPersonHomePageLabel; // Home Page

// Related names
AB_EXTERN const ABPropertyID kABPersonRelatedNamesProperty;       // Names - kABMultiStringPropertyType
AB_EXTERN const CFStringRef kABPersonFatherLabel;    // Father
AB_EXTERN const CFStringRef kABPersonMotherLabel;    // Mother
AB_EXTERN const CFStringRef kABPersonParentLabel;    // Parent
AB_EXTERN const CFStringRef kABPersonBrotherLabel;   // Brother
AB_EXTERN const CFStringRef kABPersonSisterLabel;    // Sister
AB_EXTERN const CFStringRef kABPersonChildLabel;      // Child
AB_EXTERN const CFStringRef kABPersonFriendLabel;    // Friend
AB_EXTERN const CFStringRef kABPersonSpouseLabel;    // Spouse
AB_EXTERN const CFStringRef kABPersonPartnerLabel;   // Partner
AB_EXTERN const CFStringRef kABPersonAssistantLabel; // Assistant
AB_EXTERN const CFStringRef kABPersonManagerLabel;   // Manager
    
// Social Profile
AB_EXTERN const ABPropertyID kABPersonSocialProfileProperty __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);		// kABMultiDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonSocialProfileURLKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);			// string representation of a url for the social profile
    // the following properties are optional
    AB_EXTERN const CFStringRef kABPersonSocialProfileServiceKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);			// string representing the name of the service (Twitter, Facebook, LinkedIn, etc.)
    AB_EXTERN const CFStringRef kABPersonSocialProfileUsernameKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);			// string representing the user visible name
    AB_EXTERN const CFStringRef kABPersonSocialProfileUserIdentifierKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);	// string representing the service specific identifier (optional)

AB_EXTERN const CFStringRef kABPersonSocialProfileServiceTwitter __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceSinaWeibo __OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_6_0);
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceGameCenter __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceFacebook __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceMyspace __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceLinkedIn __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);
AB_EXTERN const CFStringRef kABPersonSocialProfileServiceFlickr __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_5_0);

// Alternate birthday
AB_EXTERN const ABPropertyID kABPersonAlternateBirthdayProperty __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);                // kABDictionaryPropertyType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayCalendarIdentifierKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);    // string representing the calendar identifier for CFCalendarRef
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayEraKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);                   // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayYearKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);                  // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayMonthKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);                 // CFNumberRef - kCFNumberNSIntegerType
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayIsLeapMonthKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);           // CFNumberRef - kCFNumberCharType (aka NSNumber Bool type)
AB_EXTERN const CFStringRef kABPersonAlternateBirthdayDayKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_8_0);                   // CFNumberRef - kCFNumberNSIntegerType

#endif
