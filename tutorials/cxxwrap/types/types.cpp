#include <jlcxx/jlcxx.hpp>

class A
{
public:
  A(int value) : m_value(value) {}

  virtual int get_a() { return m_value; }
private:
  int m_value;
};

class TwiceA : public A
{
public:
  TwiceA(int value) : A(value) {}
  virtual int get_a() { return 2*A::get_a(); }
};

template<typename T1, typename T2>
class SimplePair
{
public:
  typedef T1 x_type;
  typedef T2 y_type;

  SimplePair(const T1 x, const T2 y) : m_x(x), m_y(y) {}
  T1 get_x() const { return m_x; }
  T2 get_y() const { return m_y; }
private:
  T1 m_x;
  T2 m_y;
};

namespace jlcxx
{
  // Needed for automatic downcast
  template<> struct SuperType<TwiceA> { typedef A type; };
}

JULIA_CPP_MODULE_BEGIN(registry)
  jlcxx::Module& mod = registry.create_module("Types");

  mod.add_type<A>("A")
    .constructor<int>()
    .method("get_a",&A::get_a);

  mod.add_type<TwiceA>("TwiceA", jlcxx::julia_type<A>())
    .constructor<int>();

  auto pair_type = mod.add_type<jlcxx::Parametric<jlcxx::TypeVar<1>, jlcxx::TypeVar<2>>>("SimplePair");
  // Apply just for bool
  pair_type.apply<SimplePair<bool,bool>>([](auto wrapped)
  {
    typedef typename decltype(wrapped)::type WrappedT;
    typedef typename WrappedT::x_type x_type;
    typedef typename WrappedT::y_type y_type;
    wrapped.template constructor<x_type,y_type>();
    wrapped.method("get_x", &WrappedT::get_x);
    wrapped.method("get_y", &WrappedT::get_y);
  });

  // Apply for any combination of the types in the lists
  pair_type.apply_combination<SimplePair, jlcxx::ParameterList<int, float, double>, jlcxx::ParameterList<int, float, double>>([](auto wrapped)
  {
    typedef typename decltype(wrapped)::type WrappedT;
    typedef typename WrappedT::x_type x_type;
    typedef typename WrappedT::y_type y_type;
    wrapped.template constructor<x_type,y_type>();
    wrapped.method("get_x", &WrappedT::get_x);
    wrapped.method("get_y", &WrappedT::get_y);
  });

  mod.method("smartA", [] (int x) { return std::make_shared<A>(x); } );

JULIA_CPP_MODULE_END
