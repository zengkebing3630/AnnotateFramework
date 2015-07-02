// CBPeripheralManager.h


#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBError.h>
#import <CoreBluetooth/CBPeripheralManagerConstants.h>
#import <Foundation/Foundation.h>

/*!
 *  @enum CBPeripheralManagerAuthorizationStatus
 *
 *  @discussion Represents the current state of a CBPeripheralManager.
 *
 *  @constant CBPeripheralManagerAuthorizationStatusNotDetermined	User has not yet made a choice with regards to this application.
 *  @constant CBPeripheralManagerAuthorizationStatusRestricted		This application is not authorized to share data while backgrounded. The user cannot change this application’s status, possibly due to active restrictions such as parental controls being in place.
 *  @constant CBPeripheralManagerAuthorizationStatusDenied			User has explicitly denied this application from sharing data while backgrounded.
 *  @constant CBPeripheralManagerAuthorizationStatusAuthorized		User has authorized this application to share data while backgrounded.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralManagerAuthorizationStatus) { //蓝牙设备授权状态
	CBPeripheralManagerAuthorizationStatusNotDetermined = 0,// 授权状态不确
	CBPeripheralManagerAuthorizationStatusRestricted,// 授权状态是受限制的 
	CBPeripheralManagerAuthorizationStatusDenied,// 授权状态是拒绝的 （未授权）
	CBPeripheralManagerAuthorizationStatusAuthorized,	// 授权状态是已授权	
} NS_ENUM_AVAILABLE(NA, 7_0);

/*!
 *  @enum CBPeripheralManagerState
 *
 *  @discussion Represents the current state of a CBPeripheralManager.
 *
 *  @constant CBPeripheralManagerStateUnknown       State unknown, update imminent.
 *  @constant CBPeripheralManagerStateResetting     The connection with the system service was momentarily lost, update imminent.
 *  @constant CBPeripheralManagerStateUnsupported   The platform doesn't support the Bluetooth Low Energy Peripheral/Server role.
 *  @constant CBPeripheralManagerStateUnauthorized  The application is not authorized to use the Bluetooth Low Energy Peripheral/Server role.
 *  @constant CBPeripheralManagerStatePoweredOff    Bluetooth is currently powered off.
 *  @constant CBPeripheralManagerStatePoweredOn     Bluetooth is currently powered on and available to use.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralManagerState) { //外设设备管理器状态
	CBPeripheralManagerStateUnknown = 0,// 初始的时候是未知的
	CBPeripheralManagerStateResetting,//正在重置状态
	CBPeripheralManagerStateUnsupported,//设备不支持的状态
	CBPeripheralManagerStateUnauthorized,// 设备未授权状态
	CBPeripheralManagerStatePoweredOff,//设备关闭状态
	CBPeripheralManagerStatePoweredOn,// 设备开启状态 -- 可用状态
} NS_ENUM_AVAILABLE(NA, 6_0);

/*!
 *  @enum CBPeripheralManagerConnectionLatency
 *
 *  @discussion The latency of a peripheral-central connection controls how frequently messages can be exchanged.
 *
 *	@constant CBPeripheralManagerConnectionLatencyLow       Prioritizes rapid communication over battery life.
 *	@constant CBPeripheralManagerConnectionLatencyMedium    A balance between communication frequency and battery life.
 *	@constant CBPeripheralManagerConnectionLatencyHigh      Prioritizes extending battery life over rapid communication.
 *
 */
typedef NS_ENUM(NSInteger, CBPeripheralManagerConnectionLatency) { //延时类型
	CBPeripheralManagerConnectionLatencyLow = 0,//低连接延时
	CBPeripheralManagerConnectionLatencyMedium,//中等连接延时
	CBPeripheralManagerConnectionLatencyHigh//高连接延时
} NS_ENUM_AVAILABLE(NA, 6_0);


@class CBCentral, CBService, CBMutableService, CBCharacteristic, CBMutableCharacteristic, CBATTRequest;
@protocol CBPeripheralManagerDelegate;

/*!
 *  @class CBPeripheralManager
 *
 *  @discussion The <code>CBPeripheralManager</code> class is an abstraction of the Peripheral and Broadcaster GAP roles, and the GATT Server
 *              role. Its primary function is to allow you to manage published services within the GATT database, and to advertise these services
 *              to other devices.
 *              Each application has sandboxed access to the shared GATT database. You can add services to the database by calling {@link addService:};
 *              they can be removed via {@link removeService:} and {@link removeAllServices}, as appropriate. While a service is in the database,
 *              it is visible to and can be accessed by any connected GATT Client. However, applications that have not specified the "bluetooth-peripheral"
 *              background mode will have the contents of their service(s) "disabled" when in the background. Any remote device trying to access
 *              characteristic values or descriptors during this time will receive an error response.
 *              Once you've published services that you want to share, you can ask to advertise their availability and allow other devices to connect
 *              to you by calling {@link startAdvertising:}. Like the GATT database, advertisement is managed at the system level and shared by all
 *              applications. This means that even if you aren't advertising at the moment, someone else might be!
 *
 */
NS_CLASS_AVAILABLE(NA, 6_0)
CB_EXTERN_CLASS @interface CBPeripheralManager : NSObject  //外设管理器

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive peripheral events.
 *
 */
@property(weak, nonatomic) id<CBPeripheralManagerDelegate> delegate;

/*!
 *  @property state
 *
 *  @discussion The current state of the peripheral, initially set to <code>CBPeripheralManagerStateUnknown</code>. Updates are provided by required
 *              delegate method @link peripheralManagerDidUpdateState: @/link.
 *
 */
@property(readonly) CBPeripheralManagerState state; //当前状态

/*!
 *  @property isAdvertising
 *
 *  @discussion Whether or not the peripheral is currently advertising data.
 *
 */
@property(readonly) BOOL isAdvertising;//当前是否正在广播数据

/*!
 *  @method authorizationStatus
 *
 *  @discussion	This method does not prompt the user for access. You can use it to detect restricted access and simply hide UI instead of
 *				prompting for access.
 *
 *  @return		The current authorization status for sharing data while backgrounded. For the constants returned, see {@link CBPeripheralManagerAuthorizationStatus}.
 *
 *  @see		CBPeripheralManagerAuthorizationStatus
 */
+ (CBPeripheralManagerAuthorizationStatus)authorizationStatus NS_AVAILABLE(NA, 7_0); //蓝牙设备授权状态

/*!
 *  @method initWithDelegate:queue:
 *
 *  @param delegate The delegate that will receive peripheral role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *
 *  @discussion     The initialization call. The events of the peripheral role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 */
 //创建  如果queue为nil那么就是在主线程中使用
- (instancetype)initWithDelegate:(id<CBPeripheralManagerDelegate>)delegate queue:(dispatch_queue_t)queue;

/*!
 *  @method initWithDelegate:queue:options:
 *
 *  @param delegate The delegate that will receive peripheral role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *  @param options  An optional dictionary specifying options for the manager.
 *
 *  @discussion     The initialization call. The events of the peripheral role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 *	@seealso		CBPeripheralManagerOptionShowPowerAlertKey
 *	@seealso		CBPeripheralManagerOptionRestoreIdentifierKey
 *
 */

 //相较于第一个创建方法多了一个可选项options
//其中options里面有两个key值
//CBPeripheralManagerOptionRestoreIdentifierKey ----对应的值是一个字典（数组）创建一个CBPeripheralManager的一个实例时从options中取出值去恢复Peripheral的状态
//CBPeripheralManagerOptionShowPowerAlertKey ----对应的值是一个NSNumber类型BOOL值，它标识了在系统peripheral创建在蓝牙关闭的情况下是否应该显示一个警告对话框
- (instancetype)initWithDelegate:(id<CBPeripheralManagerDelegate>)delegate queue:(dispatch_queue_t)queue options:(NSDictionary *)options NS_AVAILABLE(NA, 7_0) NS_DESIGNATED_INITIALIZER;

/*!
 *  @method startAdvertising:
 *
 *  @param advertisementData    An optional dictionary containing the data to be advertised.
 *
 *  @discussion                 Starts advertising. Supported advertising data types are <code>CBAdvertisementDataLocalNameKey</code>
 *                              and <code>CBAdvertisementDataServiceUUIDsKey</code>.
 *                              When in the foreground, an application can utilize up to 28 bytes of space in the initial advertisement data for 
 *                              any combination of the supported advertising data types. If this space is used up, there are an additional 10 bytes of 
 *                              space in the scan response that can be used only for the local name. Note that these sizes do not include the 2 bytes 
 *                              of header information that are required for each new data type. Any service UUIDs that do not fit in the allotted space 
 *                              will be added to a special "overflow" area, and can only be discovered by an iOS device that is explicitly scanning
 *                              for them.
 *                              While an application is in the background, the local name will not be used and all service UUIDs will be placed in the
 *                              "overflow" area. However, applications that have not specified the "bluetooth-peripheral" background mode will not be able 
 *                              to advertise anything while in the background.
 *
 *  @see                        peripheralManagerDidStartAdvertising:error:
 *  @seealso                    CBAdvertisementData.h
 *
 */

 //开始广播数据
- (void)startAdvertising:(NSDictionary *)advertisementData;

/*!
 *  @method stopAdvertising
 *
 *  @discussion Stops advertising.
 *
 */
 // 停止广播
- (void)stopAdvertising;

/*!
 *  @method setDesiredConnectionLatency:forCentral:
 *
 *  @param latency  The desired connection latency.
 *  @param central  A connected central.
 *
 *  @discussion     Sets the desired connection latency for an existing connection to <i>central</i>. Connection latency changes are not guaranteed, so the
 *                  resultant latency may vary. If a desired latency is not set, the latency chosen by <i>central</i> at the time of connection establishment
 *                  will be used. Typically, it is not necessary to change the latency.
 *
 *  @see            CBPeripheralManagerConnectionLatency
 *
 */

 // 设置一个连接延时类型for central 
- (void)setDesiredConnectionLatency:(CBPeripheralManagerConnectionLatency)latency forCentral:(CBCentral *)central;

/*!
 *  @method addService:
 *
 *  @param service  A GATT service.
 *
 *  @discussion     Publishes a service and its associated characteristic(s) to the local database. If the service contains included services,
 *                  they must be published first.
 *
 *  @see            peripheralManager:didAddService:error:
 */

 //添加一个service和与这个service相关联的characteristic到local database，如果他们已经存在他们必须首先被发布
- (void)addService:(CBMutableService *)service;

/*!
 *  @method removeService:
 *
 *  @param service  A GATT service.
 *
 *  @discussion     Removes a published service from the local database. If the service is included by other service(s), they must be removed
 *                  first.
 *
 */
 //从local database移除一个已经发布的服务，如果这个服务包含了其他服务，那么必须先移除前者
- (void)removeService:(CBMutableService *)service;

/*!
 *  @method removeAllServices
 *
 *  @discussion Removes all published services from the local database.
 *
 */
 //移除所有已经发布的服务service
- (void)removeAllServices;

/*!
 *  @method respondToRequest:withResult:
 *
 *  @param request  The original request that was received from the central.
 *  @param result   The result of attempting to fulfill <i>request</i>.
 *
 *  @discussion     Used to respond to request(s) received via the @link peripheralManager:didReceiveReadRequest: @/link or
 *                  @link peripheralManager:didReceiveWriteRequests: @/link delegate methods.
 *
 *  @see            peripheralManager:didReceiveReadRequest:
 *  @see            peripheralManager:didReceiveWriteRequests:
 */

 //响应一个从central传过来读或者写请求
//响应已连接的central的读写请求，当peripheral接收到central的读或者写的 characteristic 的 value时候
 //peripheral会回调peripheralManager：didReceiveReadRequest：或者peripheralManager：didReceiveWriteRequest：
- (void)respondToRequest:(CBATTRequest *)request withResult:(CBATTError)result;

/*!
 *  @method updateValue:forCharacteristic:onSubscribedCentrals:
 *
 *  @param value            The value to be sent via a notification/indication.
 *  @param characteristic   The characteristic whose value has changed.
 *  @param centrals         A list of <code>CBCentral</code> objects to receive the update. Note that centrals which have not subscribed to
 *                          <i>characteristic</i> will be ignored. If <i>nil</i>, all centrals that are subscribed to <i>characteristic</i> will be updated.
 *
 *  @discussion             Sends an updated characteristic value to one or more centrals, via a notification or indication. If <i>value</i> exceeds
 *							{@link maximumUpdateValueLength}, it will be truncated to fit.
 *
 *  @return                 <i>YES</i> if the update could be sent, or <i>NO</i> if the underlying transmit queue is full. If <i>NO</i> was returned,
 *                          the delegate method @link peripheralManagerIsReadyToUpdateSubscribers: @/link will be called once space has become
 *                          available, and the update should be re-sent if so desired.
 *
 *  @see                    peripheralManager:central:didSubscribeToCharacteristic:
 *  @see                    peripheralManager:central:didUnsubscribeFromCharacteristic:
 *  @see                    peripheralManagerIsReadyToUpdateSubscribers:
 *	@seealso				maximumUpdateValueLength
 */
 //为订阅了peripheral的central更新characteristic里面的值
- (BOOL)updateValue:(NSData *)value forCharacteristic:(CBMutableCharacteristic *)characteristic onSubscribedCentrals:(NSArray *)centrals;

@end


/*!
 *  @protocol CBPeripheralManagerDelegate
 *
 *  @discussion The delegate of a @link CBPeripheralManager @/link object must adopt the <code>CBPeripheralManagerDelegate</code> protocol. The
 *              single required method indicates the availability of the peripheral manager, while the optional methods provide information about
 *              centrals, which can connect and access the local database.
 *
 */
@protocol CBPeripheralManagerDelegate <NSObject>

@required

/*!
 *  @method peripheralManagerDidUpdateState:
 *
 *  @param peripheral   The peripheral manager whose state has changed.
 *
 *  @discussion         Invoked whenever the peripheral manager's state has been updated. Commands should only be issued when the state is 
 *                      <code>CBPeripheralManagerStatePoweredOn</code>. A state below <code>CBPeripheralManagerStatePoweredOn</code>
 *                      implies that advertisement has paused and any connected centrals have been disconnected. If the state moves below
 *                      <code>CBPeripheralManagerStatePoweredOff</code>, advertisement is stopped and must be explicitly restarted, and the
 *                      local database is cleared and all services must be re-added.
 *
 *  @see                state
 *
 */

 //仅仅在CBPeripheralManagerStatePoweredOn的时候可用
 //当CBPeripheral的状态是ON的时候,才能够进行创建服务，发布等等操作，Peripheral的初始状态时是Unknown
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral;

@optional

/*!
 *  @method peripheralManager:willRestoreState:
 *
 *  @param peripheral	The peripheral manager providing this information.
 *  @param dict			A dictionary containing information about <i>peripheral</i> that was preserved by the system at the time the app was terminated.
 *
 *  @discussion			For apps that opt-in to state preservation and restoration, this is the first method invoked when your app is relaunched into
 *						the background to complete some Bluetooth-related task. Use this method to synchronize your app's state with the state of the
 *						Bluetooth system.
 *
 *  @seealso            CBPeripheralManagerRestoredStateServicesKey;
 *  @seealso            CBPeripheralManagerRestoredStateAdvertisementDataKey;
 *
 */

//peripheral提供信息，dict包含了应用程序关闭是系统保存的peripheral的信息，用dic去恢复peripheral
//app状态的保存或者恢复，这是第一个被调用的方法当APP进入后台去完成一些蓝牙有关的工作设置，使用这个方法同步app状态通过蓝牙系统
//dic里面有两对key值分别对应服务（数组）和数据（数组）
- (void)peripheralManager:(CBPeripheralManager *)peripheral willRestoreState:(NSDictionary *)dict;

/*!
 *  @method peripheralManagerDidStartAdvertising:error:
 *
 *  @param peripheral   The peripheral manager providing this information.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method returns the result of a @link startAdvertising: @/link call. If advertisement could
 *                      not be started, the cause will be detailed in the <i>error</i> parameter.
 *
 */

 // 开始向外广播数据  在startAdvertising方法之后回调
- (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(NSError *)error;

/*!
 *  @method peripheralManager:didAddService:error:
 *
 *  @param peripheral   The peripheral manager providing this information.
 *  @param service      The service that was added to the local database.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method returns the result of an @link addService: @/link call. If the service could
 *                      not be published to the local database, the cause will be detailed in the <i>error</i> parameter.
 *
 */

 // 当你发布一个服务和任何一个相关特征的描述到GATI数据库的时候执行，在addService:方法之后回调
- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError *)error;

/*!
 *  @method peripheralManager:central:didSubscribeToCharacteristic:
 *
 *  @param peripheral       The peripheral manager providing this update.
 *  @param central          The central that issued the command.
 *  @param characteristic   The characteristic on which notifications or indications were enabled.
 *
 *  @discussion             This method is invoked when a central configures <i>characteristic</i> to notify or indicate.
 *                          It should be used as a cue to start sending updates as the characteristic value changes.
 *
 */

 //central订阅了characteristic的值，
 // 当更新值的时候peripheral会调用【updateValue: forCharacteristic: onSubscribedCentrals:(NSArray*)centrals】去为数组里面的centrals更新对应characteristic的值，
 // 在更新过后peripheral为每一个central走一遍改代理方法
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method peripheralManager:central:didUnsubscribeFromCharacteristic:
 *
 *  @param peripheral       The peripheral manager providing this update.
 *  @param central          The central that issued the command.
 *  @param characteristic   The characteristic on which notifications or indications were disabled.
 *
 *  @discussion             This method is invoked when a central removes notifications/indications from <i>characteristic</i>.
 *
 */

 //当central取消订阅characteristic这个特征的值后调用方法。使用这个方法提示停止为这个central发送更新
- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic;

/*!
 *  @method peripheralManager:didReceiveReadRequest:
 *
 *  @param peripheral   The peripheral manager requesting this information.
 *  @param request      A <code>CBATTRequest</code> object.
 *
 *  @discussion         This method is invoked when <i>peripheral</i> receives an ATT request for a characteristic with a dynamic value.
 *                      For every invocation of this method, @link respondToRequest:withResult: @/link must be called.
 *
 *  @see                CBATTRequest
 *
 */

//当peripheral接受到一个读ATT读请求，数据在CBATTRequest
- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request;

/*!
 *  @method peripheralManager:didReceiveWriteRequests:
 *
 *  @param peripheral   The peripheral manager requesting this information.
 *  @param requests     A list of one or more <code>CBATTRequest</code> objects.
 *
 *  @discussion         This method is invoked when <i>peripheral</i> receives an ATT request or command for one or more characteristics with a dynamic value.
 *                      For every invocation of this method, @link respondToRequest:withResult: @/link should be called exactly once. If <i>requests</i> contains
 *                      multiple requests, they must be treated as an atomic unit. If the execution of one of the requests would cause a failure, the request
 *                      and error reason should be provided to <code>respondToRequest:withResult:</code> and none of the requests should be executed.
 *
 *  @see                CBATTRequest
 *
 */

//当peripheral接受到一个写请求的时候调用，参数有一个数组的CBATTRequest对象request
- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray *)requests;

/*!
 *  @method peripheralManagerIsReadyToUpdateSubscribers:
 *
 *  @param peripheral   The peripheral manager providing this update.
 *
 *  @discussion         This method is invoked after a failed call to @link updateValue:forCharacteristic:onSubscribedCentrals: @/link, when <i>peripheral</i> is again
 *                      ready to send characteristic value updates.
 *
 */

 //peripheral再次准备好发送Characteristic值的更新时候调用
//当updateValue: forCharacteristic:onSubscribedCentrals:方法调用因为底层用于传输Characteristic值更新的队列满了而更新失败的时候，实现这个委托再次发送改值
- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral;

@end
