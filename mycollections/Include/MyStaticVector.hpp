#ifndef MYCOLLECTIONS_STATICVECTOR_H
#define MYCOLLECTIONS_STATICVECTOR_H

#include <cstddef>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <optional>
#include "Iterator.hpp"

namespace mycollections {

template <class T, unsigned int N>
class StaticVector {
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
  value_type operator[](unsigned int i) const {
    return data[i];
  }
  /**
   * @brief Operator returning a reference to the indexed element
   *
   * @param i the index
   * @return T& the reference to the indexed element
   */
  reference operator[](unsigned int i) {
    return data[i];
  }

  /**
   * @brief Compares two vectors by checking the size and then performing and element to element comparison
   *
   * @param that the vector to compate this to
   * @return true  the vectors are the same
   * @return false the vectors are different
   */
  bool operator==(StaticVector& that) {
    if (that.getSize() != size) return false;
    for (auto ithis = begin(), ithat = that.begin(); ithis != end(); ithis++, ithat++) {
      if (*ithis != *ithat) return false;
    }
    return true;
  }

  /**
   * @brief Clears the vector, doesn't free what could have been moved inside
   *
   */
  void clear() {
    size = 0;
  }

  template <std::size_t S>
  bool contains(StaticVector<T, S>& that) {
    if (size < that.getSize()) {
      return false;
    }

    Iterator<T> thisI = this->iter();

    bool contains = false;
    while (thisI.hasNext()) {
      Iterator<T> thatI = that.iter();
      while (thatI.hasNext()) {
        if (thisI.next() != thatI.next()) {
          break;
        }
      }
      if (!thatI.hasNext()) {
        return true;
      }
    }
    return false;
  }
  /**
   * @brief Adds a value to the vector and increases the size
   *
   * @param v the value to append
   * @return true if the value was successfully inserted
   * @return false if the vector was full
   */
  bool push(value_type v) {
    if (size >= cap) return false;
    data[size] = v;
    size++;
    return true;
  }

  /**
   * @brief removes the last element from the vector
   *
   * @return std::optional<value_type> if the vector is empty, return none
   */
  std::optional<value_type> pop() {
    if (size == 0) return std::nullopt;
    value_type v = data[size];
    size--;
    return v;
  }

  unsigned int getSize() { return size; }

  constexpr unsigned int getCap() { return cap; }

  /**
   * @brief Creates an iterator object of the class
   *
   * @return Iterator<T>
   */
  Iterator<T> iter() {
    return Iterator<T>(this->begin(), this->end());
  }

  constexpr static const unsigned int cap2 = N;

private:
  unsigned int size = 0;
  constexpr static const unsigned int cap = N;
  T data[N];

  iterator begin() { return iterator(data); }
  iterator end() { return iterator(data + size); }
};

}  // namespace mycollections

#endif  // MYCOLLECTIONS_STATICVECTOR_H