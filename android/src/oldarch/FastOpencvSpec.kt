package com.fastopencv

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.Promise

abstract class FastOpencvSpec internal constructor(context: ReactApplicationContext) :
  ReactContextBaseJavaModule(context) {

  abstract fun install(): Boolean
}
