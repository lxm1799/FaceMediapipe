# FaceMediapipe
这是一个基于meidapipe实现静态图片检测的库，可以实现毫秒级获取检测可信度分数。
由于#https://github.com/google/mediapipe
在iOS中的支持目前并不完善，所以自己研究获取的检测数据，可信度可能会有误差。

#How to use 

1、将framework添加进入项目，在general->Frameworks->设置为“Embed & Sign”
2、目前仅支持在真机上测试

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
    
    ///如果启动Graph失败，则无法检测
    if([self.faceMediapipe startGraph]){
        self.startTimeInterval = [[NSDate new] timeIntervalSince1970] * 1000;
        ///注意：检测的时候，只要具备眼睛、鼻子、下巴等特征就会结果，同时结果可能会有误差，所以dog也会有score分数
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

-(void)didOutputDetectionScores:(NSArray<NSNumber *> *)scores{
    NSTimeInterval endTimeInterval = [[NSDate new] timeIntervalSince1970] * 1000;
    NSLog(@"didOutputDetectionScores  exec time = %f(hs)",endTimeInterval - self.startTimeInterval);
    for NSNumber *number in scores{
       NSLog(@"didOutputDetectionScores  score = %@",number);
    }
}
```

