#pragma once

#include <boost/optional.hpp>
#include <boost/range/adaptors.hpp>

typedef unsigned int uint;
typedef unsigned long ulong;


class NonCopyable {
protected:
  NonCopyable() = default;

public:
  NonCopyable(NonCopyable const &) = delete;

  NonCopyable &operator=(const NonCopyable &) = delete;
};

template<typename C>
auto
optional_front(C& c) {
  using type = boost::optional<typename C::reference>;
  if (c.empty()) {
    return type(boost::none);
  } else {
    return type(c.front());
  }
}

template<typename C>
auto
optional_front(C&& c) {
  using type = boost::optional<typename C::reference>;
  if (c.empty()) {
    return type(boost::none);
  } else {
    return type(c.front());
  }
}

template<typename C, typename UnaryPredicate>
auto
first_where(C& c, UnaryPredicate fn) {
  return optional_front(c | boost::adaptors::filtered(fn));
}

/*
template<typename Container, typename UnaryPredicate>
Container
filter(Container cont, UnaryPredicate pred) {
  Container x;
  std::copy_if(std::begin(cont), std::end(cont),
    std::back_inserter(x), pred);
  return x;
}

template<typename Container, typename UnaryPredicate>
long
count_if(Container cont, UnaryPredicate pred) {
  return std::count_if(std::begin(cont), std::end(cont), pred);
}

template<typename Container, typename UnaryPredicate>
void
for_each(Container cont, UnaryPredicate pred) {
  std::for_each(std::begin(cont), std::end(cont), pred);
}

template<class Container, class UnaryPredicate>
auto
find_if(Container cont, UnaryPredicate pred) {
  return std::find_if(std::begin(cont), std::end(cont), pred);
}*/
