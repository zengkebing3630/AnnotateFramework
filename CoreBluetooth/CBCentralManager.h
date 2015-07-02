//CBCentralManager.h


#ifndef _CORE_BLUETOOTH_H_
#warning Please do not import this header file directly. Use <CoreBluetooth/CoreBluetooth.h> instead.
#endif

#import <CoreBluetooth/CBDefines.h>
#import <CoreBluetooth/CBAdvertisementData.h>
#import <CoreBluetooth/CBCentralManagerConstants.h>
#import <Foundation/Foundation.h>

/*!
 *  @enum CBCentralManagerState
 *
 *  @discussion Represents the current state of a CBCentralManager.
 *
 *  @constant CBCentralManagerStateUnknown       State unknown, update imminent.
 *  @constant CBCentralManagerStateResetting     The connection with the system service was momentarily lost, update imminent.
 *  @constant CBCentralManagerStateUnsupported   The platform doesn't support the Bluetooth Low Energy Central/Client role.
 *  @constant CBCentralManagerStateUnauthorized  The application is not authorized to use the Bluetooth Low Energy Central/Client role.
 *  @constant CBCentralManagerStatePoweredOff    Bluetooth is currently powered off.
 *  @constant CBCentralManagerStatePoweredOn     Bluetooth is currently powered on and available to use.
 *
 */
typedef NS_ENUM(NSInteger, CBCentralManagerState) {//中央管理器状态
	CBCentralManagerStateUnknown = 0,// 初始的时候是未知的（刚刚创建的时候）
	CBCentralManagerStateResetting, //正在重置状态
	CBCentralManagerStateUnsupported,//设备不支持的状态
	CBCentralManagerStateUnauthorized,// 设备未授权状态
	CBCentralManagerStatePoweredOff,//设备关闭状态
	CBCentralManagerStatePoweredOn,// 设备开启状态 -- 可用状态
};

@protocol CBCentralManagerDelegate;
@class CBUUID, CBPeripheral;

/*!
 *  @class CBCentralManager
 *
 *  @discussion Entry point to the central role. Commands should only be issued when its state is <code>CBCentralManagerStatePoweredOn</code>.
 *
 */
NS_CLASS_AVAILABLE(10_7, 5_0)
CB_EXTERN_CLASS @interface CBCentralManager : NSObject  //中央管理器

/*!
 *  @property delegate
 *
 *  @discussion The delegate object that will receive central events.
 *
 */
@property(weak, nonatomic) id<CBCentralManagerDelegate> delegate; //代理

/*!
 *  @property state
 *
 *  @discussion The current state of the peripheral, initially set to <code>CBCentralManagerStateUnknown</code>. Updates are provided by required
 *              delegate method {@link centralManagerDidUpdateState:}.
 *
 */
@property(readonly) CBCentralManagerState state; //管理器状态

/*!
 *  @method initWithDelegate:queue:
 *
 *  @param delegate The delegate that will receive central role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *
 *  @discussion     The initialization call. The events of the central role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 */
 //初始化管理器，代理，线程
- (instancetype)initWithDelegate:(id<CBCentralManagerDelegate>)delegate queue:(dispatch_queue_t)queue; 

/*!
 *  @method initWithDelegate:queue:options:
 *
 *  @param delegate The delegate that will receive central role events.
 *  @param queue    The dispatch queue on which the events will be dispatched.
 *  @param options  An optional dictionary specifying options for the manager.
 *
 *  @discussion     The initialization call. The events of the central role will be dispatched on the provided queue.
 *                  If <i>nil</i>, the main queue will be used.
 *
 *	@seealso		CBCentralManagerOptionShowPowerAlertKey
 *	@seealso		CBCentralManagerOptionRestoreIdentifierKey
 *
 */
//初始化管理器 代理，线程，支持类型
- (instancetype)initWithDelegate:(id<CBCentralManagerDelegate>)delegate queue:(dispatch_queue_t)queue options:(NSDictionary *)options NS_AVAILABLE(NA, 7_0) NS_DESIGNATED_INITIALIZER;

/*!
 *  @method retrievePeripherals:
 *
 *  @param peripheralUUIDs  A list of <code>CFUUIDRef</code> objects.
 *
 *  @discussion             Attempts to retrieve the <code>CBPeripheral</code> object(s) that correspond to <i>peripheralUUIDs</i>.
 *
 *	@deprecated				Use {@link retrievePeripheralsWithIdentifiers:} instead.
 *
 *  @see                    centralManager:didRetrievePeripherals:
 *
 */
//检索外围设备通过传入一个UUID数组
- (void)retrievePeripherals:(NSArray *)peripheralUUIDs NS_DEPRECATED(NA, NA, 5_0, 7_0);

/*!
 *  @method retrievePeripheralsWithIdentifiers:
 *
 *  @param identifiers	A list of <code>NSUUID</code> objects.
 *
 *  @discussion			Attempts to retrieve the <code>CBPeripheral</code> object(s) with the corresponding <i>identifiers</i>.
 *
 *	@return				A list of <code>CBPeripheral</code> objects.
 *
 */
//检索外围设备通过传入一个identifiers数组
- (NSArray *)retrievePeripheralsWithIdentifiers:(NSArray *)identifiers NS_AVAILABLE(NA, 7_0);

/*!
 *  @method retrieveConnectedPeripherals
 *
 *  @discussion Retrieves all peripherals that are connected to the system. Note that this set can include peripherals which were connected by other
 *              applications, which will need to be connected locally via {@link connectPeripheral:options:} before they can be used.
 *
 *	@deprecated	Use {@link retrieveConnectedPeripheralsWithServices:} instead.
 *
 *	@see        centralManager:didRetrieveConnectedPeripherals:
 *
 */
 // 检索已连接的外围设备
- (void)retrieveConnectedPeripherals NS_DEPRECATED(NA, NA, 5_0, 7_0);

/*!
 *  @method retrieveConnectedPeripheralsWithServices
 *
 *  @discussion Retrieves all peripherals that are connected to the system and implement any of the services listed in <i>serviceUUIDs</i>.
 *				Note that this set can include peripherals which were connected by other applications, which will need to be connected locally
 *				via {@link connectPeripheral:options:} before they can be used.
 *
 *	@return		A list of <code>CBPeripheral</code> objects.
 *
 */
 //通过服务的UUID数组返回已经连接的服务数组
- (NSArray *)retrieveConnectedPeripheralsWithServices:(NSArray *)serviceUUIDs NS_AVAILABLE(NA, 7_0);

/*!
 *  @method scanForPeripheralsWithServices:options:
 *
 *  @param serviceUUIDs A list of <code>CBUUID</code> objects representing the service(s) to scan for.
 *  @param options      An optional dictionary specifying options for the scan.
 *
 *  @discussion         Starts scanning for peripherals that are advertising any of the services listed in <i>serviceUUIDs</i>. Although strongly discouraged,
 *                      if <i>serviceUUIDs</i> is <i>nil</i> all discovered peripherals will be returned. If the central is already scanning with different
 *                      <i>serviceUUIDs</i> or <i>options</i>, the provided parameters will replace them.
 *                      Applications that have specified the <code>bluetooth-central</code> background mode are allowed to scan while backgrounded, with two
 *                      caveats: the scan must specify one or more service types in <i>serviceUUIDs</i>, and the <code>CBCentralManagerScanOptionAllowDuplicatesKey</code>
 *                      scan option will be ignored.
 *
 *  @see                centralManager:didDiscoverPeripheral:advertisementData:RSSI:
 *  @seealso            CBCentralManagerScanOptionAllowDuplicatesKey
 *	@seealso			CBCentralManagerScanOptionSolicitedServiceUUIDsKey
 *
 */
 //扫描外设，以服务UUID列表， 支持的类型 ， serviceUUIDs是一个CBUUID数组，如果serviceUUIDs是nil为空的话所有的被发现的peripheral将要被返回
- (void)scanForPeripheralsWithServices:(NSArray *)serviceUUIDs options:(NSDictionary *)options;

/*!
 *  @method stopScan:
 *
 *  @discussion Stops scanning for peripherals.
 *
 */

 //结束扫描
- (void)stopScan;

/*!
 *  @method connectPeripheral:options:
 *
 *  @param peripheral   The <code>CBPeripheral</code> to be connected.
 *  @param options      An optional dictionary specifying connection behavior options.
 *
 *  @discussion         Initiates a connection to <i>peripheral</i>. Connection attempts never time out and, depending on the outcome, will result
 *                      in a call to either {@link centralManager:didConnectPeripheral:} or {@link centralManager:didFailToConnectPeripheral:error:}.
 *                      Pending attempts are cancelled automatically upon deallocation of <i>peripheral</i>, and explicitly via {@link cancelPeripheralConnection}.
 *
 *  @see                centralManager:didConnectPeripheral:
 *  @see                centralManager:didFailToConnectPeripheral:error:
 *  @seealso            CBConnectPeripheralOptionNotifyOnConnectionKey
 *  @seealso            CBConnectPeripheralOptionNotifyOnDisconnectionKey
 *  @seealso            CBConnectPeripheralOptionNotifyOnNotificationKey
 *
 */

//通过options指定的选项去连接peripheral
- (void)connectPeripheral:(CBPeripheral *)peripheral options:(NSDictionary *)options;

/*!
 *  @method cancelPeripheralConnection:
 *
 *  @param peripheral   A <code>CBPeripheral</code>.
 *
 *  @discussion         Cancels an active or pending connection to <i>peripheral</i>. Note that this is non-blocking, and any <code>CBPeripheral</code>
 *                      commands that are still pending to <i>peripheral</i> may or may not complete.
 *
 *  @see                centralManager:didDisconnectPeripheral:error:
 *
 */

 //取消一个活跃的或者等待连接的peripheral的连接
- (void)cancelPeripheralConnection:(CBPeripheral *)peripheral;

@end


/*!
 *  @protocol CBCentralManagerDelegate
 *
 *  @discussion The delegate of a {@link CBCentralManager} object must adopt the <code>CBCentralManagerDelegate</code> protocol. The
 *              single required method indicates the availability of the central manager, while the optional methods allow for the discovery and
 *              connection of peripherals.
 *
 */
@protocol CBCentralManagerDelegate <NSObject>

@required

/*!
 *  @method centralManagerDidUpdateState:
 *
 *  @param central  The central manager whose state has changed.
 *
 *  @discussion     Invoked whenever the central manager's state has been updated. Commands should only be issued when the state is
 *                  <code>CBCentralManagerStatePoweredOn</code>. A state below <code>CBCentralManagerStatePoweredOn</code>
 *                  implies that scanning has stopped and any connected peripherals have been disconnected. If the state moves below
 *                  <code>CBCentralManagerStatePoweredOff</code>, all <code>CBPeripheral</code> objects obtained from this central
 *                  manager become invalid and must be retrieved or discovered again.
 *
 *  @see            state
 *
 */

//仅仅在CBCentralManagerStatePoweredOn的时候可用
 //当central的状态是OFF的时候,所有与中心连接的peripheral都将无效并且都要重新连接，central的初始状态时是Unknown
- (void)centralManagerDidUpdateState:(CBCentralManager *)central;

@optional

/*!
 *  @method centralManager:willRestoreState:
 *
 *  @param central      The central manager providing this information.
 *  @param dict			A dictionary containing information about <i>central</i> that was preserved by the system at the time the app was terminated.
 *
 *  @discussion			For apps that opt-in to state preservation and restoration, this is the first method invoked when your app is relaunched into
 *						the background to complete some Bluetooth-related task. Use this method to synchronize your app's state with the state of the
 *						Bluetooth system.
 *
 *  @seealso            CBCentralManagerRestoredStatePeripheralsKey;
 *  @seealso            CBCentralManagerRestoredStateScanServicesKey;
 *  @seealso            CBCentralManagerRestoredStateScanOptionsKey;
 *
 */

 //central提供信息，dict包含了应用程序关闭是系统保存的central的信息，用dic去恢复central
//app状态的保存或者恢复，这是第一个被调用的方法当APP进入后台去完成一些蓝牙有关的工作设置，使用这个方法同步app状态通过蓝牙系统
- (void)centralManager:(CBCentralManager *)central willRestoreState:(NSDictionary *)dict;

/*!
 *  @method centralManager:didRetrievePeripherals:
 *
 *  @param central      The central manager providing this information.
 *  @param peripherals  A list of <code>CBPeripheral</code> objects.
 *
 *  @discussion         This method returns the result of a {@link retrievePeripherals} call, with the peripheral(s) that the central manager was
 *                      able to match to the provided UUID(s).
 *
 */

//于周边，中央能匹配到 UUID时被调用，在retrievePeripherals：方法之后调用
- (void)centralManager:(CBCentralManager *)central didRetrievePeripherals:(NSArray *)peripherals;

/*!
 *  @method centralManager:didRetrieveConnectedPeripherals:
 *
 *  @param central      The central manager providing this information.
 *  @param peripherals  A list of <code>CBPeripheral</code> objects representing all peripherals currently connected to the system.
 *
 *  @discussion         This method returns the result of a {@link retrieveConnectedPeripherals} call.
 *
 */

 //peripherals表示当前连接central的所有peripherals，在retrieveConnectedPeripherals方法之后回调
- (void)centralManager:(CBCentralManager *)central didRetrieveConnectedPeripherals:(NSArray *)peripherals;

/*!
 *  @method centralManager:didDiscoverPeripheral:advertisementData:RSSI:
 *
 *  @param central              The central manager providing this update.
 *  @param peripheral           A <code>CBPeripheral</code> object.
 *  @param advertisementData    A dictionary containing any advertisement and scan response data.
 *  @param RSSI                 The current RSSI of <i>peripheral</i>, in dBm. A value of <code>127</code> is reserved and indicates the RSSI
 *								was not available.
 *
 *  @discussion                 This method is invoked while scanning, upon the discovery of <i>peripheral</i> by <i>central</i>. A discovered peripheral must
 *                              be retained in order to use it; otherwise, it is assumed to not be of interesbe cleaned up by the central manager. For
 *                              a list of <i>advertisementData</i> keys, see {@link CBAdvertisementDataLocalNameKey} and t and will other similar constants.
 *
 *  @seealso                    CBAdvertisementData.h
 *
 */
 //中央发现外设。外设距离。数据
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI;

/*!
 *  @method centralManager:didConnectPeripheral:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has connected.
 *
 *  @discussion         This method is invoked when a connection initiated by {@link connectPeripheral:options:} has succeeded.
 *
 */

 //中央连接外设成功,在connectPeripheral:options:方法之后调用
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral;

/*!
 *  @method centralManager:didFailToConnectPeripheral:error:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has failed to connect.
 *  @param error        The cause of the failure.
 *
 *  @discussion         This method is invoked when a connection initiated by {@link connectPeripheral:options:} has failed to complete. As connection attempts do not
 *                      timeout, the failure of a connection is atypical and usually indicative of a transient issue.
 *
 */

 //中央连接外设失败,在connectPeripheral:options:方法之后调用
- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

/*!
 *  @method centralManager:didDisconnectPeripheral:error:
 *
 *  @param central      The central manager providing this information.
 *  @param peripheral   The <code>CBPeripheral</code> that has disconnected.
 *  @param error        If an error occurred, the cause of the failure.
 *
 *  @discussion         This method is invoked upon the disconnection of a peripheral that was connected by {@link connectPeripheral:options:}. If the disconnection
 *                      was not initiated by {@link cancelPeripheralConnection}, the cause will be detailed in the <i>error</i> parameter. Once this method has been
 *                      called, no more methods will be invoked on <i>peripheral</i>'s <code>CBPeripheralDelegate</code>.
 *
 */

 //中央断开外设的连接，在cancelPeripheralConnection方法之后调用
- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error;

@end
