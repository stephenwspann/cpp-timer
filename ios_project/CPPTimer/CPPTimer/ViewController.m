#import "ViewController.h"
#import "CPPTTimer.h"

@interface ViewController () {
    CPPTTimer *_timer;
}

@end

@implementation ViewController

@synthesize timerLabel;

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    // initialize the timer
    _timer = [CPPTTimer createWithListener:self];
    
    // start a 5 second timer
    [_timer startTimer:5];
    
}

# pragma mark CPPTTimerListener methods

- (void)timerEnded {
    NSLog(@"Obj-C: timerEnded.");
}

- (void)timerTicked:(int32_t)secondsRemaining {
    NSLog(@"Obj-C: timerTicked with %d seconds remaining.", secondsRemaining);
    
    // without dispatch_async, background thread warning is thrown
    dispatch_async(dispatch_get_main_queue(), ^{
        timerLabel.text = [NSString stringWithFormat:@"%d", secondsRemaining];
    });
}

@end
