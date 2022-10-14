#ifndef INCLUDE_MYCOLLECTIONS_MYSTATICVECTOR
#define INCLUDE_MYCOLLECTIONS_MYSTATICVECTOR

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
    return _data[i];
  }
  /**
   * @brief Operator returning a reference to the indexed element
   *
   * @param i the index
   * @return T& the reference to the indexed element
   */
  reference operator[](unsigned int i) {
    return _data[i];
  }

  /**
   * @brief Compares two vectors by checking the size and then performing and element to element comparison
   *
   * @param that the vector to compate this to
   * @return true  the vectors are the same
   * @return false the vectors are different
   */
  bool operator==(StaticVector& that) const {
    if (that.getSize() != _size) return false;
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
    _size = 0;
  }

  /**
   * @brief Checks if the vector contains the other vector passed by reference
   *
   * @tparam S the size of the vector to check
   * @param that the vector to check
   * @return true 'that' is not contained in the vector
   * @return false 'that' is not contained in the vector
   */
  template <std::size_t S>
  bool contains(StaticVector<T, S>& that) const {
    if (_size < that.getSize()) {
      return false;
    }

    Iterator<T> thisI = this->iter();

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
    if (_size >= cap) return false;
    _data[_size] = v;
    _size++;
    return true;
  }

  /**
   * @brief Adds a moved value to the vector and increases the size
   *
   * @param v the moved value to append
   * @return true if the value was successfully inserted
   * @return false if the vector was full
   */
  bool push_m(T&& v) {
    if (_size >= cap) return false;
    _data[_size] = v;
    _size++;
    return true;
  }

  /**
   * @brief Removes an element of the vector by value
   * 
   * @param v the value to remove
   */
  void remove(value_type v) {
    for (int i = 0; i < getSize(); i++) {
      if (_data[i] == v) {
        for (int j = i + 1; j < getSize(); j++) {
          _data[j - 1] = _data[j];
        }
        _size -= 1;
        break;
      }
    }
  }

  /**
   * @brief removes the last element from the vector
   *
   * @return std::optional<value_type> if the vector is empty, return none
   */
  std::optional<value_type> pop() {
    if (_size == 0) return std::nullopt;
    value_type v = _data[_size];
    _size--;
    return v;
  }

  unsigned int getSize() const { return _size; }

  constexpr unsigned int getCap() const { return cap; }

  /**
   * @brief Creates an iterator object of the class
   *
   * @return Iterator<T>
   */
  Iterator<T> iter() const {
    return Iterator<T>(this->begin(), this->end());
  }

private:
  unsigned int _size = 0;
  constexpr static unsigned int cap = N;
  T _data[N];

  iterator begin() const { return iterator(_data); }
  iterator end() const { return iterator(_data + _size); }
};

}  // namespace mycollections

#endif /* INCLUDE_MYCOLLECTIONS_MYSTATICVECTOR */
