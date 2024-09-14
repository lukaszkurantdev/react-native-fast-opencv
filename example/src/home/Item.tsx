import { useNavigation } from '@react-navigation/native';
import { useCallback } from 'react';
import { TouchableOpacity, View, Text, StyleSheet } from 'react-native';
import type { Route } from '../types';

interface ItemProps {
  title: string;
  emoji: string;
  description: string;
  route: Route;
  testId?: string;
}

export const Item = (props: ItemProps) => {
  const { title, emoji, description, route, testId } = props;
  const navigation = useNavigation();
  const gotoRoute = useCallback(() => {
    navigation.navigate(route);
  }, [route, navigation]);

  return (
    <TouchableOpacity
      onPress={gotoRoute}
      style={styles.container}
      testID={testId}
    >
      <View>
        <Text style={styles.title}>
          {title} {emoji}
        </Text>
        <Text style={styles.description}>{description}</Text>
      </View>
      <Text>👉</Text>
    </TouchableOpacity>
  );
};

const styles = StyleSheet.create({
  container: {
    backgroundColor: '#FFFFFF',
    padding: 16,
    flexDirection: 'row',
    justifyContent: 'space-between',
    alignItems: 'center',
    borderBottomColor: '#CCC',
    borderBottomWidth: 1,
  },
  title: {
    fontWeight: 'bold',
    paddingBottom: 4,
    color: 'black',
  },
  description: {
    color: 'black',
  },
});
