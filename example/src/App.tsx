import { ImageExample } from './examples/ImageExample';
import { Route, type StackParamList } from './types';
import { CameraRealtimeDetection } from './examples/CameraRealtimeDetection';
import { NavigationContainer } from '@react-navigation/native';
import { createNativeStackNavigator } from '@react-navigation/native-stack';
import { Home } from './home/Home';
import { CameraPassthrough } from './examples/CameraPassthrough';
import { DocumentDetection } from './examples/DocumentDetection';

const Stack = createNativeStackNavigator<StackParamList>();

export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator>
        <Stack.Screen
          name={Route.Home}
          component={Home}
          options={{ title: 'Examples' }}
        />
        <Stack.Screen name={Route.ImageBlur} component={ImageExample} />
        <Stack.Screen
          name={Route.CameraPassthrough}
          component={CameraPassthrough}
        />
        <Stack.Screen
          name={Route.CameraRealtimeDetection}
          component={CameraRealtimeDetection}
        />
        <Stack.Screen
          name={Route.DocumentDetection}
          component={DocumentDetection}
        />
      </Stack.Navigator>
    </NavigationContainer>
  );
}
