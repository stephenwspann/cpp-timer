#import <UIKit/UIKit.h>

#import "CPPTTimerListener.h"

@interface ViewController : UIViewController<CPPTTimerListener>

@property (nonatomic, strong) IBOutlet UILabel *timerLabel;

@end