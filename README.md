# The Julia language and C++

This is the companion repository for the C++Now 2018 talk ["The Julia Language and C++: The Perfect Marriage?"](http://sched.co/EC7F)

The slides are available in the file [cppnow2018-julia.ipynb](cppnow2018-julia.ipynb).

To run the tutorial, follow these steps:

1. Install Julia from http://julialang.org
2. From the Julia REPL, install the required packages:
```julia
Pkg.add("CxxWrap")
Pkg.add("IJulia")
Pkg.add("BenchmarkTools")
Pkg.add("Cxx") (warning: may take a long time)
```
3. Start the local notebook server
```julia
using IJulia
notebook()
```

You may also need to get the master version of `Cxx`, i.e:
```julia
Pkg.checkout("Cxx")
Pkg.build("Cxx")
```

## Tutorials
In the tutorials dir, the following is available:
* eigen3: C++ source code of the [Eigen](http://eigen.tuxfamily.org) header-only matrix library
* cxx: Notebook on how to use the Eigen library using Cxx.jl
* cxxwrap: Basic tutorials (`hello_world` and `types`) plus a tutorial on using Eigen from CxxWrap.jl