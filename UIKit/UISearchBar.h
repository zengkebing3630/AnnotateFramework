//
//  UISearchBar.h
//  UIKit
//
//  Copyright (c) 2008-2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UITextField.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIBarButtonItem.h>
#import <UIKit/UIBarCommon.h>

typedef NS_ENUM(NSInteger, UISearchBarIcon) {
    UISearchBarIconSearch, // The magnifying glass
    UISearchBarIconClear, // The circle with an x in it
    UISearchBarIconBookmark, // The open book icon
    UISearchBarIconResultsList, // The list lozenge icon
};

typedef NS_ENUM(NSUInteger, UISearchBarStyle) {
    UISearchBarStyleDefault,    // currently UISearchBarStyleProminent
    UISearchBarStyleProminent,  // used my Mail, Messages and Contacts
    UISearchBarStyleMinimal     // used by Calendar, Notes and Music
} NS_ENUM_AVAILABLE_IOS(7_0);


@protocol UISearchBarDelegate;
@class UITextField, UILabel, UIButton, UIColor;

NS_CLASS_AVAILABLE_IOS(2_0) @interface UISearchBar : UIView <UIBarPositioning, UITextInputTraits>

@property(nonatomic)        UIBarStyle              barStyle;             //控件的样式
@property(nonatomic,assign) id<UISearchBarDelegate> delegate;             //设置控件的委托
@property(nonatomic,copy)   NSString               *text;                 //控件上面的显示的文字
@property(nonatomic,copy)   NSString               *prompt;               //显示在顶部的单行文字，通常作为一个提示行
@property(nonatomic,copy)   NSString               *placeholder;          //半透明的提示文字，输入搜索内容消失
@property(nonatomic)        BOOL                    showsBookmarkButton;  //是否在控件的右端显示一个书的按钮(没有文字的时候)
@property(nonatomic)        BOOL                    showsCancelButton;    //是否显示cancel按钮
@property(nonatomic)        BOOL                    showsSearchResultsButton//是否在控件的右端显示搜索结果按钮(没有文字的时候)
@property(nonatomic, getter=isSearchResultsButtonSelected) BOOL searchResultsButtonSelected //搜索结果按钮是否被选中
- (void)setShowsCancelButton:(BOOL)showsCancelButton animated:(BOOL)animated;//设置是否显示Cancel按钮
@property(nonatomic,retain) UIColor *tintColor;//bar的颜色(具有渐变效果)
@property(nonatomic,retain) UIColor *barTintColor;  // default is nil

@property (nonatomic) UISearchBarStyle searchBarStyle;//控件的风格

@property(nonatomic,assign,getter=isTranslucent) BOOL translucent; ///指定控件是否会有透视效果
@property(nonatomic,copy) NSArray   *scopeButtonTitles       //搜索栏下部的选择栏，数组里面的内容是按钮的标题
@property(nonatomic)      NSInteger  selectedScopeButtonIndex //搜索栏下部的选择栏按钮的个数
@property(nonatomic)      BOOL       showsScopeBar            //控制搜索栏下部的选择栏是否显示出来
//设置一个遮盖视图
@property (nonatomic, readwrite, retain) UIView *inputAccessoryView;
@property(nonatomic,retain) UIImage *backgroundImage ;//背景图
@property(nonatomic,retain) UIImage *scopeBarBackgroundImage;//控制搜索栏下部的选择栏背景图

//设置背景
- (void)setBackgroundImage:(UIImage *)backgroundImage forBarPosition:(UIBarPosition)barPosition barMetrics:(UIBarMetrics)barMetrics;
- (UIImage *)backgroundImageForBarPosition:(UIBarPosition)barPosition barMetrics:(UIBarMetrics)barMetrics;

//设置搜索框的框背景
- (void)setSearchFieldBackgroundImage:(UIImage *)backgroundImage forState:(UIControlState)state;
- (UIImage *)searchFieldBackgroundImageForState:(UIControlState)state;

//设置按钮的图片
- (void)setImage:(UIImage *)iconImage forSearchBarIcon:(UISearchBarIcon)icon state:(UIControlState)state;
- (UIImage *)imageForSearchBarIcon:(UISearchBarIcon)icon state:(UIControlState)state;

//搜索栏下部的选择栏Button的背景图
- (void)setScopeBarButtonBackgroundImage:(UIImage *)backgroundImage forState:(UIControlState)state; 
- (UIImage *)scopeBarButtonBackgroundImageForState:(UIControlState)state;

//设置设置搜索栏下部的选择栏Button 中间分隔中间的图片
- (void)setScopeBarButtonDividerImage:(UIImage *)dividerImage forLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState;
- (UIImage *)scopeBarButtonDividerImageForLeftSegmentState:(UIControlState)leftState rightSegmentState:(UIControlState)rightState;

//设置搜索栏下部的选择栏Button的Text的富文本
- (void)setScopeBarButtonTitleTextAttributes:(NSDictionary *)attributes forState:(UIControlState)state;
- (NSDictionary *)scopeBarButtonTitleTextAttributesForState:(UIControlState)state;

//设置搜索框中文框的背景的偏移量
@property(nonatomic) UIOffset searchFieldBackgroundPositionAdjustment;

//设置搜索框中文框的文本的偏移量
@property(nonatomic) UIOffset searchTextPositionAdjustment;

//设置按钮的图片的偏移量
- (void)setPositionAdjustment:(UIOffset)adjustment forSearchBarIcon:(UISearchBarIcon)icon;
- (UIOffset)positionAdjustmentForSearchBarIcon:(UISearchBarIcon)icon;
@end

@protocol UISearchBarDelegate <UIBarPositioningDelegate>

@optional

- (BOOL)searchBarShouldBeginEditing:(UISearchBar *)searchBar;                      //将要编辑， 成为第一响应者
- (void)searchBarTextDidBeginEditing:(UISearchBar *)searchBar;                     // 开始编辑
- (BOOL)searchBarShouldEndEditing:(UISearchBar *)searchBar;                        // 将要结束编辑，取消第一响应者
- (void)searchBarTextDidEndEditing:(UISearchBar *)searchBar;                       // 结束编辑
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText;   //文本已经改变，（包含清除）
- (BOOL)searchBar:(UISearchBar *)searchBar shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text; // 文本改变之前调用

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar;                     // 键盘上的搜索按钮被点击
- (void)searchBarBookmarkButtonClicked:(UISearchBar *)searchBar;                   // bookmark按钮 被点击
- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar;                     // cancel按钮被点击
- (void)searchBarResultsListButtonClicked:(UISearchBar *)searchBar;                // results按钮被点击

- (void)searchBar:(UISearchBar *)searchBar selectedScopeButtonIndexDidChange:(NSInteger)selectedScope;//下面分页栏的按钮被点击

@end
