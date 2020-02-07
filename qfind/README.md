qfind
======

qfind is the generic method for searching data in a sequence

For testing use cmocka framework

Compiling
---------
install cmocka-1.1.5 download from: https://cmocka.org/files
cd qfind
mkdir build
cd build
cmake .. && make && make doc


Running test
--------
ctest -V

Access  documentations
-------
cd ./build/doc/doxygen/html
open_in_browser index.html
