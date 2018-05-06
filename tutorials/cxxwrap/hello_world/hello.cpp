#include <iostream>
#include <jlcxx/jlcxx.hpp>

void hello() { std::cout << "hello world!" << std::endl; }

template<int N>
struct Foo
{
};

template<typename T, int N1, int N2>
struct Combined
{
  Foo<N1+N2> m_data;
};

JULIA_CPP_MODULE_BEGIN(registry)
  jlcxx::Module& mod = registry.create_module("Hello");

  mod.method("hello", hello);

JULIA_CPP_MODULE_END