import type { DataTypes } from '../constants/DataTypes';
import type { ObjectType } from './ObjectType';

export type Mat = { id: string; type: ObjectType.Mat };
export type MatVector = { id: string; type: ObjectType.MatVector };
export type Point = { id: string; type: ObjectType.Point };
export type PointVector = { id: string; type: ObjectType.PointVector };
export type Rect = { id: string; type: ObjectType.Rect };
export type RectVector = { id: string; type: ObjectType.RectVector };
export type Size = { id: string; type: ObjectType.Size };
export type Vec3b = { id: string; type: ObjectType.Vec3b };
export type Scalar = { id: string; type: ObjectType.Scalar };
export type RotatedRect = { id: string; type: ObjectType.RotatedRect };

export type Vector = MatVector | PointVector | RectVector;
export type Array = Mat | Vec3b;

export type Objects = {
  // Creation
  createObject(
    type: ObjectType.Mat,
    rows: number,
    cols: number,
    dataType: DataTypes
  ): Mat;
  createObject(type: ObjectType.MatVector): MatVector;
  createObject(type: ObjectType.Point, x: number, y: number): Point;
  createObject(type: ObjectType.PointVector): PointVector;
  createObject(
    type: ObjectType.Rect,
    x: number,
    y: number,
    width: number,
    height: number
  ): Rect;
  createObject(type: ObjectType.RectVector): RectVector;
  createObject(type: ObjectType.Size, width: number, height: number): Size;
  createObject(type: ObjectType.Vec3b, a: number, b: number, c: number): Vec3b;

  toJSValue(mat: Mat): {
    size: number;
    cols: number;
    rows: number;
    base64: string;
  };
  toJSValue(matVector: MatVector): {
    array: { size: number; cols: number; rows: number }[];
  };
  toJSValue(point: Point): {
    x: number;
    y: number;
  };
  toJSValue(pointVector: PointVector): {
    array: {
      x: number;
      y: number;
    }[];
  };
  toJSValue(rect: Rect): {
    x: number;
    y: number;
    width: number;
    height: number;
  };
  toJSValue(rectVector: RectVector): {
    array: {
      x: number;
      y: number;
      width: number;
      height: number;
    }[];
  };
  toJSValue(size: Size): {
    width: number;
    height: number;
  };
  toJSValue(vec3b: Vec3b): {
    a: number;
    b: number;
    c: number;
  };

  copyObjectFromVector(vector: MatVector, itemIndex: number): Mat;
  copyObjectFromVector(vector: PointVector, itemIndex: number): Point;
  copyObjectFromVector(vector: RectVector, itemIndex: number): Rect;
};
