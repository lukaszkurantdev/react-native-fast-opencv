#import "FastOpencv.h"
#import <React-callinvoker/ReactCommon/CallInvoker.h>
#import <React/RCTBridge+Private.h>
#import <jsi/jsi.h>

@interface RCTBridge (RCTTurboModule)
- (std::shared_ptr<facebook::react::CallInvoker>)jsCallInvoker;
@end

using namespace facebook;

@implementation FastOpencv
RCT_EXPORT_MODULE()


RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(install)
{
    RCTBridge* bridge = [RCTBridge currentBridge];
    RCTCxxBridge* cxxBridge = (RCTCxxBridge*)bridge;
    if (!cxxBridge.runtime) {
        return @(false);
    }
    jsi::Runtime& runtime = *(jsi::Runtime*)cxxBridge.runtime;
    
    OpenCVPlugin::installOpenCV(runtime, [bridge jsCallInvoker]);
    
    return @(true);
}

// Don't compile this code when we build for the old architecture.
#ifdef RCT_NEW_ARCH_ENABLED
- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
    (const facebook::react::ObjCTurboModule::InitParams &)params
{
    return std::make_shared<facebook::react::NativeFastOpencvSpecJSI>(params);
}
#endif

@end
