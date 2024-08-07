#import <AppKit/AppKit.h>

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = NSApplicationMain(argc, argv);
    [pool release];
    return retVal;
}
