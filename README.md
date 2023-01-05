# FaceMediapipe
这是一个基于meidapipe实现静态图片检测的库，可以实现毫秒级获取检测可信度分数。
由于#https://github.com/google/mediapipe
在iOS中的支持目前并不完善，所以自己研究获取的检测数据，可信度可能会有误差。

##how to use 
```
#import "ViewController.h"
#import <FaceMediapipe/FaceMediapipe.h>

@interface ViewController ()<FaceMediapipeDelegate>
@property (assign, nonatomic) NSTimeInterval startTimeInterval;
@property (strong, nonatomic) FaceMediapipe *faceMediapipe;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.faceMediapipe = [[FaceMediapipe alloc] initWithMode:cpu];
    self.faceMediapipe.delegate = self;
    
    ///如果启动Graph则无法检测
    if([self.faceMediapipe startGraph]){
        self.startTimeInterval = [[NSDate new] timeIntervalSince1970] * 1000;
        ///注意：检测的时候，只要具备眼睛、鼻子、下巴等特征会有误差，所以dog也可能会有score分数
        UIImage *man = [UIImage imageNamed:@"man.jpeg"];
        UIImage *follwer = [UIImage imageNamed:@"follwer.jpeg"];
        UIImage *dog = [UIImage imageNamed:@"dog.jpeg"];
        ///提供数据源，结果在didOutputDetectionScore返回
        [self.faceMediapipe sendImage:man];
    }
}

-(void)dealloc{
    [self.faceMediapipe stopGraph];
}

-(void)didOutputDetectionScore:(NSNumber *)score{
    NSTimeInterval endTimeInterval = [[NSDate new] timeIntervalSince1970] * 1000;
    NSLog(@"didOutputDetectionScore  score = %@  exec time = %f(hs)",score,endTimeInterval - self.startTimeInterval);
}
```

