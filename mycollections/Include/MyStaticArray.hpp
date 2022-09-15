#ifndef MYCOLLECTIONS_STATICARRAY_H
#define MYCOLLECTIONS_STATICARRAY_H

namespace mycollections {

template <class T, unsigned int N>
class StaticArray {
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

  bool operator==(StaticArray& that) {
    for (auto ithis = begin(), ithat = that.begin(); ithis != end(); ithis++, ithat++) {
      if (*ithis != *ithat) return false;
    }
    return true;
  }

  unsigned int getSize() { return size; }

  iterator begin() { return iterator(data); }
  iterator end() { return iterator(data + size); }

  T data[N];

private:
  static const unsigned int size = N;
};
}  // namespace mycollections

#endif