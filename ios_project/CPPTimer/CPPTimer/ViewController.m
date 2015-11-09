#import "ViewController.h"
#import "CPPTTimer.h"

@interface ViewController () {
    CPPTTimer *_timer;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    // initialize the timer
    _timer = [CPPTTimer createWithListener:self];
    
    // start a 5 second timer
    [_timer startTimer:5];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)timerEnded {
    NSLog(@"timer ended.");
}

- (void)timerTicked:(int32_t)secondsRemaining {
    NSLog(@"timer ticked with %d seconds remaining.", secondsRemaining);
}

@end
