# Worklets Integration

Operations on images can be time-consuming, and the library works with synchronous functions, hence it is a good idea to move the execution of the operation to another thread, so as not to block the JavaScript thread. Integration with this library allows tasks to be delegated to another thread.


1. Add library:

```
yarn add react-native-worklets-core
```

And then:

```
cd ios && pod install
```

2. Add the babel plugin to your `babel.config.js`:

```
module.exports = {
  plugins: [
    ["react-native-worklets-core/plugin"],
    // ...
  ],
  // ...
};
```

3. Restart Metro with clean cache:

```
yarn start --reset-cache
```

You can find a detailed description of the installation process [here](https://github.com/margelo/react-native-worklets-core).


### Usage

The methods of use are [here](../usage#calculations-from-separated-thread).