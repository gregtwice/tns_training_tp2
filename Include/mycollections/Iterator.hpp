#ifndef INCLUDE_MYCOLLECTIONS_ITERATOR
#define INCLUDE_MYCOLLECTIONS_ITERATOR

namespace mycollections {

template <class T>
class Iterator {
public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  /**
   * @brief Construct a new Iterator object
   *
   * @param first the first element of the container
   * @param end the pointer of the end of the container
   */
  Iterator(pointer first, pointer end) : _first(first), _current(first), _end(end), _index(0){};

  /**
   * @brief Increases the pointer of the iterator by one and returns the current value
   *
   * @return value_type the current value
   */
  value_type next() {
    value_type ret = *_current;
    _current++;
    _index++;
    return ret;
  };

  /**
   * @brief returns wether the Iterator can still call the next() method
   */
  bool hasNext() const {
    return _end != _current && _index < _max;
  };

  /**
   * @brief Consumes the iterator and counts the number of elements in it
   *
   * @return int the number of elements of the iterator
   */
  int count() {
    int c = 0;
    while (hasNext()) {
      c++;
      next();
    }
    return c;
  }

  /**
   * @brief Calls a lambda on each elements of the iterator
   *
   * Exemple to print all the elements of the iterator
   * @code {.cpp}
   * auto iter = mycollections::StaticVector<...,...> myVec;
   * myVec.iter().forEach([](auto v) { std::cout << *v << "\n"; });
   * @endcode
   * 
   * @tparam Functor a C++ lambda
   * @param f the lambda to call
   * @return Iterator& the iterator that has been reset to allow to chain calls to Iterator methods
   */
  template <typename Functor>
  Iterator& forEach(Functor f) {
    while (hasNext()) {
      f(next());
    }

    return reset();
  }

  /**
   * @brief Skips the n firsts elements of the iterator
   * 
   * @param n the number of elements to skip
   * @return Iterator& 
   */
  Iterator& skip(unsigned int n) {
    for (unsigned int i = 0; i < n && hasNext(); i++) {
      next();
      _index--;
    }
    return *this;
  }

  /**
   * @brief Limits the number of elements in the iterator
   * 
   * @param n the number of elements to get
   * @return Iterator& 
   */
  Iterator& take(unsigned int n) {
    _max = n;
    return *this;
  }

  /**
   * @brief Resets the iterator, making the current element point to the first element
   * 
   * @return Iterator& 
   */
  Iterator& reset() {
    _current = _first;
    return *this;
  }

  /**
   * @brief Returns the value currenty pointed by the iterator
   *
   * @return reference
   */
  reference operator*() const {
    return *_current;
  }

  /**
   * @brief Consumes the iterator and returns the last value
   *
   * @return reference the last value
   */
  reference last() {
    pointer current;
    while (hasNext()) {
      current = _current;
      next();
    }
    return *current;
  }

private:
  const pointer _first;
  pointer _current;
  const pointer _end;
  unsigned int _index;
  unsigned int _max = -1;
};

}  // namespace mycollections
#endif /* INCLUDE_MYCOLLECTIONS_ITERATOR */
