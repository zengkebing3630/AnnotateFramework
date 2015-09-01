//
//  UISearchController.h
//  UIKit

#import <UIKit/UIKit.h>
#import <UIKit/UIPresentationController.h>
#import <UIKit/UIViewControllerTransitioning.h>

@class UISearchController;

@protocol UISearchControllerDelegate <NSObject>
@optional
//显示 与 消失回调
- (void)willPresentSearchController:(UISearchController *)searchController;
- (void)didPresentSearchController:(UISearchController *)searchController;
- (void)willDismissSearchController:(UISearchController *)searchController;
- (void)didDismissSearchController:(UISearchController *)searchController;

// 当然SearchBar begin Editing  返回YES， Active == YES调用
- (void)presentSearchController:(UISearchController *)searchController;
@end

@protocol UISearchResultsUpdating <NSObject>
@required
//当然search获取焦点 | search.text | scope 发生改变 ,调用
- (void)updateSearchResultsForSearchController:(UISearchController *)searchController;
@end

NS_CLASS_AVAILABLE_IOS(8_0) @interface UISearchController : UIViewController <UIViewControllerTransitioningDelegate, UIViewControllerAnimatedTransitioning>

//初始化UISearchController，如searchResultsController == nil，需把UISearchController.view 加入到别的view之上
- (instancetype)initWithSearchResultsController:(UIViewController *)searchResultsController;

//搜索结果代理
@property (nonatomic, assign) id <UISearchResultsUpdating> searchResultsUpdater;

//设置是否有用
@property (nonatomic, assign, getter = isActive) BOOL active;

@property (nonatomic, assign) id <UISearchControllerDelegate> delegate;//代理
// 设置开始搜索时背景显示与否
@property (nonatomic, assign) BOOL dimsBackgroundDuringPresentation;
// 设置开始搜索时状态栏显示与否
@property (nonatomic, assign) BOOL hidesNavigationBarDuringPresentation; 
//设置显示搜索结果的控制器
@property (nonatomic, retain, readonly) UIViewController *searchResultsController;
//设置显示搜索Bar
@property (nonatomic, retain, readonly) UISearchBar *searchBar;
@end
