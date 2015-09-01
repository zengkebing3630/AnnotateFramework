//
//  UISearchDisplayController.h
//  UIKit
#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UILabel.h>
#import <UIKit/UITableView.h>

@class UISearchBar, UITableView, UIViewController, UIPopoverController;
@protocol UITableViewDataSource, UITableViewDelegate, UISearchDisplayDelegate;

//从mac3.0 ，ios8.0 之后取代  UISearchController
@interface UISearchDisplayController : NSObject
//初始化UISearchDisplayController ，searchBar,viewController 必填
- (instancetype)initWithSearchBar:(UISearchBar *)searchBar contentsController:(UIViewController *)viewController;

@property(nonatomic,assign)                           id<UISearchDisplayDelegate> delegate;//代理

@property(nonatomic,getter=isActive)  BOOL            active;  // 配置 searchingVC,默认NO，animation == NO；
- (void)setActive:(BOOL)visible animated:(BOOL)animated;       // animate the view controller for searching

@property(nonatomic,readonly)                         UISearchBar                *searchBar;//搜索控件
@property(nonatomic,readonly)                         UIViewController           *searchContentsController; // the view we are searching (often a UITableViewController)
@property(nonatomic,readonly)                         UITableView                *searchResultsTableView;   // will return non-nil. create if requested
@property(nonatomic,assign)                           id<UITableViewDataSource>   searchResultsDataSource;  // 代理
@property(nonatomic,assign)                           id<UITableViewDelegate>     searchResultsDelegate;    // 代理
@property(nonatomic,copy)                             NSString                   *searchResultsTitle; //搜索结果的标题
//显示searchBar在navigation将覆盖内容VC上的navigationItem,默认YES
@property (nonatomic, assign) BOOL displaysSearchBarInNavigationBar;
//navigation上的navigationItem
@property (nonatomic, readonly) UINavigationItem *navigationItem;

@end

@protocol UISearchDisplayDelegate <NSObject>

@optional

//将要开始搜索时调用
- (void) searchDisplayControllerWillBeginSearch:(UISearchDisplayController *)controller;
//正在搜索时调用
- (void) searchDisplayControllerDidBeginSearch:(UISearchDisplayController *)controller;
//将要结束搜索时调用
- (void) searchDisplayControllerWillEndSearch:(UISearchDisplayController *)controller;
//正要结束搜索时调用
- (void) searchDisplayControllerDidEndSearch:(UISearchDisplayController *)controller;

//当正在加载显示结果TableView时调用
- (void)searchDisplayController:(UISearchDisplayController *)controller didLoadSearchResultsTableView:(UITableView *)tableView;
//将不加载结果TableView时调用
- (void)searchDisplayController:(UISearchDisplayController *)controller willUnloadSearchResultsTableView:(UITableView *)tableView;

//将要显示结果TableView
- (void)searchDisplayController:(UISearchDisplayController *)controller willShowSearchResultsTableView:(UITableView *)tableView;
//正要显示结果TableView
- (void)searchDisplayController:(UISearchDisplayController *)controller didShowSearchResultsTableView:(UITableView *)tableView;
//将要隐藏结果TableView
- (void)searchDisplayController:(UISearchDisplayController *)controller willHideSearchResultsTableView:(UITableView *)tableView;
//正要隐藏结果TableView
- (void)searchDisplayController:(UISearchDisplayController *)controller didHideSearchResultsTableView:(UITableView *)tableView;

//将要ReloadTableView For  searchString
- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchString:(NSString *)searchString;
//将要ReloadTableView For  searchScope
- (BOOL)searchDisplayController:(UISearchDisplayController *)controller shouldReloadTableForSearchScope:(NSInteger)searchOption;

@end
