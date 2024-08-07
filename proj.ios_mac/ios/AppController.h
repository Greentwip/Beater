#import <AppKit/AppKit.h>

@class RootViewController;

@interface AppController : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

