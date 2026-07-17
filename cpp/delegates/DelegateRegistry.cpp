#include "DelegateRegistry.h"

TypeDelegate* DelegateRegistry::getHandler(const std::string& type) {
  static MatDelegate matHandler;
  static MatVectorDelegate matVectorHandler;
  static RectDelegate rectHandler;
  static RectVectorDelegate rectVectorHandler;
  static PointDelegate pointHandler;
  static PointVectorDelegate pointVectorHandler;
  static Point2fDelegate point2fHandler;
  static Point2fVectorDelegate point2fVectorHandler;
  static PointVectorVectorDelegate pointVectorVectorHandler;
  static SizeDelegate sizeHandler;
  static Vec3bDelegate vec3bHandler;
  static ScalarDelegate scalarHandler;
  static RotatedRectDelegate rotatedRectHandler;
  static TermCriteriaDelegate termCriteriaHandler;
  static KeyPointVectorDelegate keyPointVectorHandler;
  static DMatchVectorDelegate dMatchVectorHandler;
  static DMatchVectorVectorDelegate dMatchVectorVectorHandler;

  if (type == "mat") return &matHandler;
  if (type == "mat_vector") return &matVectorHandler;
  if (type == "rect") return &rectHandler;
  if (type == "rect_vector") return &rectVectorHandler;
  if (type == "point") return &pointHandler;
  if (type == "point_vector") return &pointVectorHandler;
  if (type == "point2f") return &point2fHandler;
  if (type == "point2f_vector") return &point2fVectorHandler;
  if (type == "point_vector_vector") return &pointVectorVectorHandler;
  if (type == "size") return &sizeHandler;
  if (type == "vec3b") return &vec3bHandler;
  if (type == "scalar") return &scalarHandler;
  if (type == "rotated_rect") return &rotatedRectHandler;
  if (type == "term_criteria") return &termCriteriaHandler;
  if (type == "keypoint_vector") return &keyPointVectorHandler;
  if (type == "dmatch_vector") return &dMatchVectorHandler;
  if (type == "dmatch_vector_vector") return &dMatchVectorVectorHandler;

  return nullptr;
}


#include "MatVectorDelegate.h"
#include "RectDelegate.h"
#include "RectVectorDelegate.h"
#include "PointDelegate.h"
#include "PointVectorDelegate.h"
#include "Point2fDelegate.h"
#include "Point2fVectorDelegate.h"
#include "PointVectorVectorDelegate.h"
#include "SizeDelegate.h"
#include "Vec3bDelegate.h"
#include "ScalarDelegate.h"
#include "RotatedRectDelegate.h"
#include "TermCriteriaDelegate.h"
