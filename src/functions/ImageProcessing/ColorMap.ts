import type { ColormapTypes } from '../../constants/ImageProcessing';
import type { Mat } from '../../objects/Objects';

export type ColorMap = {
  invoke(
    name: 'applyColorMap',
    src: Mat,
    dst: Mat,
    colormap: ColormapTypes
  ): void;
};
