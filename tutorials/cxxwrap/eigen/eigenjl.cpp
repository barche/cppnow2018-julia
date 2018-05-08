#include <jlcxx/jlcxx.hpp>
#include <Eigen/Dense>

namespace jlcxx
{
  // Match the Eigen Matrix type, skipping the default parameters
  template<typename ScalarT, int Rows, int Cols>
  struct BuildParameterList<Eigen::Matrix<ScalarT, Rows, Cols>>
  {
    // We set the parameterlist to int64_t, to avoid having to wrap all parameters in Int32() in Julia
    typedef ParameterList<ScalarT, std::integral_constant<int64_t, Rows>, std::integral_constant<int64_t, Cols>> type;
  };
}

namespace eigenjl
{
  // Functor to add functions to a concrete Eigen matrix type
  struct WrapMatrix
  {
    // TypeWrapper is returned by add_type and for a generic type by apply
    template<typename MatrixT>
    void operator()(jlcxx::TypeWrapper<MatrixT>&& wrapper)
    {
      using namespace jlcxx;
      typedef typename MatrixT::Scalar ScalarT;

      // Conversion from Eigen to Julia
      wrapper.module().method("convert", [](SingletonType<ArrayRef<ScalarT, 2>>, MatrixT& eigen_mat)
      {
        return ArrayRef<ScalarT, 2>(eigen_mat.data(), eigen_mat.rows(), eigen_mat.cols());
      });

      // // Conversion from Julia array to Eigen
      wrapper.method("convert", [](SingletonType<MatrixT>, ArrayRef<ScalarT, 2> julia_array)
      {
        Eigen::Map<MatrixT> map(julia_array.data(), jl_array_dim(julia_array.wrapped(),0), jl_array_dim(julia_array.wrapped(),1));
        return MatrixT(map);
      });
    }
  };
}

JULIA_CPP_MODULE_BEGIN(registry)
  using namespace jlcxx;
  using namespace eigenjl;
  
  Module& mod = registry.create_module("Eigen");

  WrapMatrix()(mod.add_type<Eigen::MatrixXd>("MatrixXd"));

JULIA_CPP_MODULE_END
