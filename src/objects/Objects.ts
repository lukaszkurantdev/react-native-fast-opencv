import type { ObjectType } from './ObjectType';

export type Mat = { id: string; type: ObjectType.Mat };
export type MatVector = { id: string; type: ObjectType.MatVector };
export type Point = { id: string; type: ObjectType.Point };
export type PointVector = { id: string; type: ObjectType.PointVector };
export type Rect = { id: string; type: ObjectType.Rect };
export type RectVector = { id: string; type: ObjectType.RectVector };
export type Size = { id: string; type: ObjectType.Size };
export type Vec3b = { id: string; type: ObjectType.Vec3b };

export type Vector = MatVector | PointVector | RectVector;
export type Array = Mat | Vec3b;
