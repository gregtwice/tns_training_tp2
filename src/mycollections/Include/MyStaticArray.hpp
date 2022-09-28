#ifndef MYCOLLECTIONS_STATICARRAY_H
#define MYCOLLECTIONS_STATICARRAY_H

#include "Iterator.hpp"
namespace mycollections {

template <class T, unsigned int N>
class StaticArray {
public:
  using value_type = T;
  using reference = T&;
  using iterator = value_type*;

  /**
   * @brief Operator returning a copy of the indexed element
   *
   * @param i the index
   * @return T the copied element
   */
  T operator[](unsigned int i) const {
    return data[i];
  }

  /**
   * @brief Operator returning a reference to the indexed element
   *
   * @param i the index
   * @return T& the reference to the indexed element
   */
  T& operator[](unsigned int i) {
    return data[i];
  }

  /**
   * @brief Compares two vectors by performing and element to element comparison
   *
   * @param that the vector to compate this to
   * @return true  the vectors are the same
   * @return false the vectors are different
   */
  bool operator==(StaticArray& that) {
    for (auto ithis = begin(), ithat = that.begin(); ithis != end(); ithis++, ithat++) {
      if (*ithis != *ithat) return false;
    }
    return true;
  }

  unsigned int getSize() { return size; }

  /**
   * @brief Creates an iterator object of the class
   *
   * @return Iterator<T>
   */
  Iterator<T> iter() {
    return Iterator<T>(this->begin(), this->end());
  }

  T data[N];

private:
  static const unsigned int size = N;
  iterator begin() { return iterator(data); }
  iterator end() { return iterator(data + size); }
};
}  // namespace mycollections

#endif