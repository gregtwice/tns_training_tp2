#ifndef SRC_INCLUDE_MYCOLLECTIONS_ITERATOR
#define SRC_INCLUDE_MYCOLLECTIONS_ITERATOR

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
  Iterator(pointer first, pointer end) : _first(first), _current(first), _end(end){};

  /**
   * @brief Increases the pointer of the iterator by one and returns the current value
   *
   * @return value_type the current value
   */
  value_type next() {
    value_type ret = *_current;
    _current++;
    return ret;
  };

  bool hasNext() {
    return _end != _current;
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

  template <typename Functor>
  Iterator& forEach(Functor f) {
    while (hasNext()) {
      f(next());
    }
    _current = _first;
    return *this;
  }

  /**
   * @brief Returns the value currenty pointed by the iterator
   *
   * @return reference
   */
  reference operator*() {
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
};

}  // namespace mycollections
#endif /* SRC_INCLUDE_MYCOLLECTIONS_ITERATOR */
