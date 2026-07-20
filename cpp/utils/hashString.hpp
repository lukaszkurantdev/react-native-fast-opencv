#include <opencv2/opencv.hpp>

#ifndef hashString_hpp
#define hashString_hpp

constexpr uint64_t hashString(const char* str, size_t length) {
  uint64_t hash = 14695981039346656037ull;
  const uint64_t fnv_prime = 1099511628211ull;

  for (size_t i = 0; i < length; ++i) {
      hash ^= static_cast<uint64_t>(str[i]);
      hash *= fnv_prime;
  }

  return hash;
}

#endif // !FOCV_Function_hpp
