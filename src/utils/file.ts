import { base64 } from './base64';
import RNFS from 'react-native-fs';

export async function readImageAsUint8Array(uri: string): Promise<Uint8Array> {
  const file = await RNFS.readFile(uri, 'base64');

  return base64.parse(file);
}

export function convertUint8ArrayToBase64(array: Uint8Array): string {
  return base64.stringify(array);
}
