# NNRTree

This is a C++ class wrapper around the Boost RTree library.

## Limitations
1. Since, the dimension (DIM) of the RTree is a compile-time constant. Users have to manually define the dimension and appropriately modify the member functions in NNRTree.cpp for arbitrary dimensions. A good workaround is setting an upperbound dimension (say 10) and whenever you are working with k < DIM, you can set the rest of the (DIM-k) dimensions to be zero.

## Build instructions

1. git clone https://github.com/pradeepr-roboticist/NNRTree.git
2. mkdir build
3. cmake ..
4. make
5. ./test_nnrtree

## Author

**Pradeep Rajendran**

* [github/pradeepr-roboticist](https://github.com/pradeepr-roboticist)

## License

Copyright © 2019 [Pradeep Rajendran](https://github.com/pradeepr-roboticist)
Released under the [GNU General Public License](https://github.com/pradeepr-roboticist/NNRTree/blob/master/LICENSE).
