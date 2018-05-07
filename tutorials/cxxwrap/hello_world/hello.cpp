#include <iostream>
#include <jlcxx/jlcxx.hpp>

void hello() { std::cout << "hello world!" << std::endl; }

JULIA_CPP_MODULE_BEGIN(registry)
  jlcxx::Module& mod = registry.create_module("Hello");

  mod.method("hello", hello);
  mod.method("hello_lambda", [] () { std::cout << "hello lambda!" << std::endl; });

JULIA_CPP_MODULE_END
