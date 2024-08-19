#import "FastOpencv.h"
#import <React-callinvoker/ReactCommon/CallInvoker.h>
#import <React/RCTBridge+Private.h>
#import <jsi/jsi.h>


using namespace facebook;

@implementation FastOpencv

@synthesize bridge = _bridge;

RCT_EXPORT_MODULE()

- (void)invalidate {
  _bridge = nil;
}

- (void)setBridge:(RCTBridge *)bridge {
  _bridge = bridge;
}

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(install)
{
    RCTCxxBridge *cxxBridge = (RCTCxxBridge *)_bridge;
    
    if (!cxxBridge.runtime) {
        return @(false);
    }
    jsi::Runtime& runtime = *(jsi::Runtime*)cxxBridge.runtime;
    auto callInvoker = cxxBridge.jsCallInvoker;
        facebook::jsi::Runtime *jsRuntime =
            (facebook::jsi::Runtime *)cxxBridge.runtime;
    
    OpenCVPlugin::installOpenCV(*jsRuntime, callInvoker);
    
    return @(true);
}

// Don't compile this code when we build for the old architecture.
#ifdef RCT_NEW_ARCH_ENABLED
- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
    (const facebook::react::ObjCTurboModule::InitParams &)params
{
    RCTCxxBridge *cxxBridge = (RCTCxxBridge *)_bridge;
      auto callInvoker = cxxBridge.jsCallInvoker;
      facebook::jsi::Runtime *jsRuntime =
          (facebook::jsi::Runtime *)cxxBridge.runtime;
    
    OpenCVPlugin::installOpenCV(*jsRuntime, callInvoker);
    
    return std::make_shared<facebook::react::NativeFastOpencvSpecJSI>(params);
}
#endif

- (void)install:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject { 
    <#code#>
}

@end
