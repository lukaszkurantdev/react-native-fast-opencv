package com.fastopencv

import android.util.Log
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.turbomodule.core.interfaces.CallInvokerHolder

class FastOpencvModule(reactContext: ReactApplicationContext) :
  NativeFastOpencvSpec(reactContext) {

  private external fun nativeInstall(
    jsiRuntimeRef: Long,
    jsCallInvokerHolder: CallInvokerHolder
  )

  override fun install(): Boolean {
    return try {
      val jsContext = reactApplicationContext.javaScriptContextHolder
      if (jsContext == null) {
        Log.e(NAME, "JavaScript context holder was null!")
        return false
      }

      val jsCallInvokerHolder = reactApplicationContext.getJSCallInvokerHolder()
      if (jsCallInvokerHolder == null) {
        Log.e(NAME, "JS call invoker holder was null!")
        return false
      }

      nativeInstall(jsContext.get(), jsCallInvokerHolder)
      true
    } catch (exception: Exception) {
      Log.e(NAME, "Failed to install OpenCV JSI bindings!", exception)
      false
    }
  }

  companion object {
    const val NAME = NativeFastOpencvSpec.NAME

    init {
      System.loadLibrary("react-native-fast-opencv")
    }
  }
}
