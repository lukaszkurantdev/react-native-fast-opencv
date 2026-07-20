import type { ColormapTypes } from '../../constants/ImageProcessing';
import type { Mat } from '../../objects/Objects';

export type ColorMap = {
  applyColorMap(src: Mat, dst: Mat, colormap: ColormapTypes): void;
};
