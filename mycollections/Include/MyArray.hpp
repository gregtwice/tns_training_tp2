#ifndef MYCOLLECTIONS_ARRAY_H
#define MYCOLLECTIONS_ARRAY_H

#include <math.h>

namespace mycollections {

template <class T, unsigned int N>
class Array {
public:
  T operator[](unsigned int i) const {
    return data[i];
  }
  T& operator[](unsigned int i) {
    return data[i];
  }

  unsigned int getSize() { return size; }

private:
  static const unsigned int size = N;
  T data[N];
};

}  // namespace mycollections
#endif