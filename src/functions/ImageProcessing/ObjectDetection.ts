import type { TemplateMatchModes } from '../../constants/ImageProcessing';
import type { Mat } from '../../objects/Objects';

export type ObjectDetection = {
  /**
   * Compares a template against overlapped image regions
   * @param name Function name
   * @param image Image where the search is running. It must be 8-bit or 32-bit floating-point
   * @param templ Searched template. It must be not greater than the source image and have the same data type.
   * @param result Map of comparison results. It must be single-channel 32-bit floating-point. If image is W×H and templ is w×h , then result is (W−w+1)×(H−h+1) .
   * @param method Parameter specifying the comparison method, @see TemplateMatchModes
   * @param mask Mask of searched template. It must have the same datatype and size with templ. It is not set by default. Currently, only the TM_SQDIFF and TM_CCORR_NORMED methods are supported
   */
  invoke(
    name: 'matchTemplate',
    image: Mat,
    templ: Mat,
    result: Mat,
    method: TemplateMatchModes,
    mask: Mat
  ): void;
};
