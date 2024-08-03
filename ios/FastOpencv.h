#ifdef __cplusplus
#import "react-native-fast-opencv.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNFastOpencvSpec.h"

@interface FastOpencv : NSObject <NativeFastOpencvSpec>
#else
#import <React/RCTBridgeModule.h>

@interface FastOpencv : NSObject <RCTBridgeModule>
#endif

@end
