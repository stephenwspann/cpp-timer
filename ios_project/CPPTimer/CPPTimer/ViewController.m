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
    
    // start a 5 second timer without blocking viewDidLoad?
    [_timer startTimer:5];
    
    NSLog(@"viewDidLoad completed.");
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)timerEnded {
    NSLog(@"Obj-C: timerEnded.");
}

- (void)timerTicked:(int32_t)secondsRemaining {
    NSLog(@"Obj-C: timerTicked with %d seconds remaining.", secondsRemaining);
}

@end
