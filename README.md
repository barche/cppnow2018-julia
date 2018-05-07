# The Julia language and C++

This is the companion repository for the C++Now 2018 talk ["The Julia Language and C++: The Perfect Marriage?"](http://sched.co/EC7F)

The slides are available in the file [cppnow2018-julia.ipynb](cppnow2018-julia.ipynb).

To run the tutorial, follow these steps:

1. Install Julia from http://julialang.org
2. From the Julia REPL, install the required packages:
```julia
Pkg.add("Cxx")
Pkg.add("CxxWrap")
Pkg.add("IJulia")
Pkg.add("BenchmarkTools")
```
3. Start the local notebook server
```julia
using IJulia
notebook()
```
