NSDistantObject.h


#import <Foundation/NSProxy.h>

@class Protocol, NSConnection, NSCoder;

@interface NSDistantObject : NSProxy <NSCoding> {
    @private
    id         _knownSelectors;
    NSUInteger _wireCount;
    NSUInteger _refCount;
    id         _proto;
    uint16_t   ___2;
    uint8_t    ___1;
    uint8_t    _wireType;
    id         _remoteClass;
}

// Do not attempt to subclass NSDistantObject -- it is futile
// Do not use these next two methods
+ (id)proxyWithTarget:(id)target connection:(NSConnection *)connection;
- (instancetype)initWithTarget:(id)target connection:(NSConnection *)connection;

+ (id)proxyWithLocal:(id)target connection:(NSConnection *)connection;
- (instancetype)initWithLocal:(id)target connection:(NSConnection *)connection;

- (instancetype)initWithCoder:(NSCoder *)inCoder NS_DESIGNATED_INITIALIZER;

- (void)setProtocolForProxy:(Protocol *)proto;

@property (readonly, retain) NSConnection *connectionForProxy;

@end

