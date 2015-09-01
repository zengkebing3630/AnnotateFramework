//  UIFont.h
//  UIKit
//
//  Copyright (c) 2007-2013, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIFontDescriptor.h>

NS_CLASS_AVAILABLE_IOS(2_0) @interface UIFont : NSObject <NSCopying>

// Returns an instance of the font associated with the text style and scaled appropriately for the user's selected content size category. See UIFontDescriptor.h for the complete list.
+ (UIFont *)preferredFontForTextStyle:(NSString *)style NS_AVAILABLE_IOS(7_0);

// Returns a font using CSS name matching semantics.
+ (UIFont *)fontWithName:(NSString *)fontName size:(CGFloat)fontSize;

// Returns an array of font family names for all installed fonts
+ (NSArray *)familyNames;

// Returns an array of font names for the specified family name
+ (NSArray *)fontNamesForFamilyName:(NSString *)familyName;

// Some convenience methods to create system fonts
+ (UIFont *)systemFontOfSize:(CGFloat)fontSize;
+ (UIFont *)boldSystemFontOfSize:(CGFloat)fontSize;
+ (UIFont *)italicSystemFontOfSize:(CGFloat)fontSize;

// lineHeight =   descender +  ascender

/*

----
----
----
-----
	文字分三段 ，descender 下一段， asscender，上两段
*/

// Font attributes
@property(nonatomic,readonly,retain) NSString *familyName;
@property(nonatomic,readonly,retain) NSString *fontName;
@property(nonatomic,readonly)        CGFloat   pointSize;
@property(nonatomic,readonly)        CGFloat   ascender; //偏上的字体高度
@property(nonatomic,readonly)        CGFloat   descender;//中间的字体的高度
@property(nonatomic,readonly)        CGFloat   capHeight;
@property(nonatomic,readonly)        CGFloat   xHeight;
@property(nonatomic,readonly)        CGFloat   lineHeight NS_AVAILABLE_IOS(4_0);
@property(nonatomic,readonly)        CGFloat   leading;

// Create a new font that is identical to the current font except the specified size
- (UIFont *)fontWithSize:(CGFloat)fontSize;

// Returns a font matching the font descriptor. If fontSize is greater than 0.0, it has precedence over UIFontDescriptorSizeAttribute in fontDescriptor.
+ (UIFont *)fontWithDescriptor:(UIFontDescriptor *)descriptor size:(CGFloat)pointSize NS_AVAILABLE_IOS(7_0);

// Returns a font descriptor which describes the font.
- (UIFontDescriptor *)fontDescriptor NS_AVAILABLE_IOS(7_0);

@end

 
