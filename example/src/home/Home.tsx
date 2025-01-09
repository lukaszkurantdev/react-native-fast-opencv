import { ScrollView } from 'react-native';
import { Route } from '../types';
import { Item } from './Item';

interface ItemDetails {
  title: string;
  emoji: string;
  description: string;
  route: Route;
  testId?: string;
}

const items: ItemDetails[] = [
  {
    title: 'Image Blur',
    emoji: '🔍',
    description: 'Blur an image',
    route: Route.ImageBlur,
  },
  {
    title: 'Camera Passthrough',
    emoji: '📷',
    description: 'Pass camera feed through',
    route: Route.CameraPassthrough,
  },
  {
    title: 'Camera Realtime Detection',
    emoji: '📷',
    description: 'Detect objects in realtime',
    route: Route.CameraRealtimeDetection,
  },
  {
    title: 'Document Detection',
    emoji: '📷',
    description: 'Detect documents in realtime',
    route: Route.DocumentDetection,
  },
];

export const Home = () => {
  return (
    <ScrollView>
      {items.map((item, index) => (
        <Item key={index} {...item} />
      ))}
    </ScrollView>
  );
};
