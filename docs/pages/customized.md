# Customized calculations (C++)

> Only in advanced cases.

In special cases where you will need maximum performance or some functionality is missing from the library, you can easily create your own code in C++ and run it from JS code.

As the code can be written in C++, the solution will be fully cross-platform and does not need different implementations for iOS and Android.

In file `cpp/react-native-fast-opencv.cpp` find this lines:

```cpp
/// ...
} else if (propName == "clearBuffers") {
    return jsi::Function::createFromHostFunction(
      runtime, jsi::PropNameID::forAscii(runtime, "clearBuffers"), 1,
      [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
        size_t count) -> jsi::Value {
              
      FOCV_Storage::clear();
      return true;
    });
  }

  return jsi::HostObject::get(runtime, propNameId);
}
// ...
```

Add your own else check with your own customized name of function:

```cpp
else if (propName == "customFunction") {
    return jsi::Function::createFromHostFunction(
      runtime, jsi::PropNameID::forAscii(runtime, "clearBuffers"), 1,
      [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
        size_t count) -> jsi::Value {

        // Params
        FOCV_FunctionArguments args(runtime, arguments);

        // Example – first param is string
        auto param1 = args.asString(0);

        // Second param is Mat
        auto functionName = args.asMatPtr(1);

        // etc

        // Calculations... 
        // HERE OpenCV functions and API is available
        // Check how to get parameters from function
        // Examples in FOCV_Function.cpp

      // return JSI data or just do something...
    });
  }
```

Compile et voilà – you can use it in your JS code:

```js
OpenCV.customFunction(params);
```