#ifndef MYCOLLECTIONS_STATICVECTOR_H
#define MYCOLLECTIONS_STATICVECTOR_H

#include <iostream>
#include <iterator>
#include <algorithm>
#include <optional>

namespace mycollections {

template <class T, unsigned int N>
class StaticVector {
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

  bool operator==(StaticVector& that) {
    if (that.getSize() != size) return false;
    for (auto ithis = begin(), ithat = that.begin(); ithis != end(); ithis++, ithat++) {
      if (*ithis != *ithat) return false;
    }
    return true;
  }

  bool push(value_type v) {
    if (size >= cap) return false;
    data[size] = v;
    size++;
    return true;
  }

  std::optional<value_type> pop() {
    if (size == 0) return std::nullopt;
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

#endif  // MYCOLLECTIONS_STATICVECTOR_H