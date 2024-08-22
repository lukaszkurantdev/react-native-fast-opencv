package com.fastopencv

import android.util.Log
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactMethod
import com.facebook.react.turbomodule.core.interfaces.CallInvokerHolder


class FastOpencvModule internal constructor(context: ReactApplicationContext) :
  FastOpencvSpec(context) {

  override fun getName(): String {
    return NAME
  }

  companion object {
    const val NAME = "FastOpencv"

    init {
      System.loadLibrary("react-native-fast-opencv")
    }
  }

  private external fun nativeInstall(jsiRuntimeRef: Long, jsCallInvokerHolder: CallInvokerHolder?)

  @ReactMethod(isBlockingSynchronousMethod = true)
  override fun install(): Boolean {
    val jsContext = reactApplicationContext.javaScriptContextHolder

    try {
      if (jsContext == null) {
        Log.e(NAME, "React Application Context was null!")
        return false
      }
      val jsiRuntimeRef = jsContext!!.get()
      val jsCallInvokerHolder = reactApplicationContext.catalystInstance.jsCallInvokerHolder

      nativeInstall(jsiRuntimeRef, jsCallInvokerHolder)

      return true
    } catch (exception: Exception) {
      Log.e(NAME, "Failed to initialize react-native-worklets-core!", exception)

    }

    return false
  }
}
