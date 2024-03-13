
# matlibcpp
A Linear Algebra and Machine Learning Library in C++

# Matrices:
Matrices are RXC collections of P data types

What's nice about this library is that sizes and data types are checked _at compile time_. 

Example Usage:
```
Matrix<int, 2, 3> aM{{1, 2, 3}, {4, 5, 6}}
Matrix<int, 3, 3> bM{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}

std::cout << aM * bM << std::endl;
std::cout << bM.T() * aM << std::endl;
std::cout << pNorm(bM, 4) << std::endl;
```

