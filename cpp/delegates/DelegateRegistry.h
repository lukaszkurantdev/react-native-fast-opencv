#include "TypeDelegate.hpp"

#include "MatDelegate.h"
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
#include "KeyPointVectorDelegate.h"
#include "DMatchVectorDelegate.h"
#include "DMatchVectorVectorDelegate.h"

#ifndef DelegateRegistry_h
#define DelegateRegistry_h

class DelegateRegistry {
public:
  static TypeDelegate* getHandler(const std::string& type);
};

#endif // !DelegateRegistry_h
