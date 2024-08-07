#import <AppKit/AppKit.h>

@class RootViewController;

@interface AppController : NSObject <NSApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

