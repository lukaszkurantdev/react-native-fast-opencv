# Customized calculations (C++)

> Only in advanced cases.

In special cases where you will need maximum performance or some functionality is missing from the library, you can easily create your own code in C++ and run it from JS code.

As the code can be written in C++, the solution will be fully cross-platform and does not need different implementations for iOS and Android.

### How dispatch works

Every function you call on the `OpenCV` object is resolved dynamically. In `cpp/react-native-fast-opencv.cpp`, the `OpenCVPlugin::get` method returns object factories (`Mat`, `Scalar`, ...) for known names, and for everything else it returns a host function that forwards the call to `FOCV_Function::invoke`, passing the property name as the first argument:

```cpp
// cpp/react-native-fast-opencv.cpp
return jsi::Function::createFromHostFunction(
    runtime, jsi::PropNameID::forAscii(runtime, propName), 0,
    [=](jsi::Runtime& runtime, const jsi::Value& thisValue, const jsi::Value* arguments,
        size_t count) -> jsi::Object {

    std::vector<jsi::Value> newArgs;
    newArgs.reserve(count + 1);
    newArgs.push_back(jsi::String::createFromUtf8(runtime, propName)); // function name
    for (size_t i = 0; i < count; i++) {
        newArgs.push_back(jsi::Value(runtime, arguments[i]));
    }

    auto result = FOCV_Function::invoke(runtime, newArgs.data(), newArgs.size());
    // ...
    return result;
});
```

This means you do **not** need to add your own branch here — any name you call from JS is automatically routed to `FOCV_Function::invoke`. You only need to handle it there.

### Adding your own function

In file `cpp/FOCV_Function.cpp`, `FOCV_Function::invoke` switches over the function name (hashed with `hashString`) and reads parameters through `FOCV_FunctionArguments`:

```cpp
jsi::Object FOCV_Function::invoke(jsi::Runtime& runtime, const jsi::Value* arguments, size_t count) {
  jsi::Object value(runtime);

  FOCV_FunctionArguments args(runtime, arguments, count);

  auto functionName = args.asString(0); // index 0 is the function name

  try {
    switch (hashString(functionName.c_str(), functionName.size())) {
      // ... existing cases (absdiff, add, cvtColor, ...)
    }
  } catch (cv::Exception& e) {
    // ...
  }

  return value;
}
```

Add your own `case` with the customized name of your function. Note that **the first argument (index 0) is the function name**, so your own parameters start at index 1:

```cpp
case hashString("customFunction", 14): { // 14 = length of "customFunction"

  // Example – first param (index 1) is a string
  auto param1 = args.asString(1);

  // Second param (index 2) is a Mat
  auto src = args.asMatPtr(2);

  // Third param (index 3) is a destination Mat
  auto dst = args.asMatPtr(3);

  // Calculations...
  // HERE OpenCV functions and API are available.
  // Check FOCV_FunctionArguments for all available getters
  // (asNumber, asBool, asScalarPtr, asSizePtr, asPointPtr, ...).

  // Optionally return a value to JS on the result object:
  value.setProperty(runtime, "value", 123);

  // ...or wrap and return a native object (e.g. a Mat):
  // return FOCV_JsiObject::wrap(runtime, "mat", std::make_shared<cv::Mat>(result));

} break;
```

`FOCV_Function::invoke` returns the `value` object, so anything you attach with `value.setProperty(...)` is available on the JS side. When you produce a new OpenCV object, wrap it with `FOCV_JsiObject::wrap` and return it directly — it becomes a Host object whose native memory is managed by the garbage collector, just like the built-in functions.

Compile et voilà – you can use it in your JS code:

```js
const result = OpenCV.customFunction(param1, src, dst);
```

> `OpenCV` is exported as the native host object typed as `OpenCVModel`, so TypeScript does not know your custom name. Add the signature to the type (or cast, e.g. `(OpenCV as any).customFunction(...)`) to call it without type errors — the runtime dispatch works regardless.
