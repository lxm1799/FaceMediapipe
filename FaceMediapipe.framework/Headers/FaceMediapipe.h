//
//  FaceDetectionManager.h
//  FaceDetectionGpuApp
//
//  Created by luckyBoy on 2023/1/4.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

typedef enum : NSUInteger {
    cpu = 1,
    gpu = 2,
} DetectionMode;


/// A delegate that can receive frames from a MediaPipe graph.
@protocol FaceMediapipeDelegate <NSObject>
///获取输出分数
- (void)didOutputDetectionScore:(NSNumber *)score;

@end






NS_ASSUME_NONNULL_BEGIN

@interface FaceMediapipe : NSObject

-(instancetype)initWithMode:(DetectionMode)mode;
///代理
@property(weak,nonatomic) id<FaceMediapipeDelegate> delegate;
///开始启动Graph
- (BOOL)startGraph;

///停止Graph使用，如果你不在需要检测了，调用此代码
-(void)stopGraph;


/*----------------------------检测方法----------------------------*/
///Buffer检测
- (void)sendPixelBuffer:(CVPixelBufferRef)imageBuffer;

///静态图片检测
- (void)sendImage:(UIImage*)image;

///视频流Buffer检测
-(void)sendSampleBuffer:(CMSampleBufferRef)sampleBuffer;

+(CVPixelBufferRef)CVPixelBufferRefFromUiImage:(UIImage *)img;

+(UIImage *)imageFromCVPixelBufferRef:(CVPixelBufferRef)pixelBuffer;

@end




NS_ASSUME_NONNULL_END
