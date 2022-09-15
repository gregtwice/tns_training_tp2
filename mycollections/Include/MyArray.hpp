#ifndef MYCOLLECTIONS_ARRAY_H
#define MYCOLLECTIONS_ARRAY_H

#include <math.h>
#include <iterator>
#include <algorithm>

namespace mycollections {

template <class T, unsigned int N>
class Array {
public:
  using value_type = T;
  using reference = T&;
  using iterator = value_type*;

  T operator[](unsigned int i) const {
    return data[i];
  }

  T& operator[](unsigned int i) {
    return data[i];
  }

  bool operator==(Array& that) {
    if (that.getSize() != getSize()) return false;

    for (auto ithis = begin(), ithat = that.begin(); ithis != end(); ithis++, ithat++) {
      if (ithis != ithat) return false;
    }
    return true;
  }

  bool push(value_type v) {
    if (size >= cap) return false;
    data[size] = v;
    size++;
    return true;
  }

  value_type pop() {
    if (size == 0) return nullptr;
    value_type v = data[size];
    size--;
    return v;
  }

  unsigned int getSize() { return size; }

  unsigned int getCap() { return cap; }

  iterator begin() { return iterator(data); }
  iterator end() { return iterator(data + size); }

private:
  unsigned int size = 0;
  static const unsigned int cap = N;
  T data[N];
};

}  // namespace mycollections
#endif