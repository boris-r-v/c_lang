double_linked_list
======

For testing use cmocka framework

Compiling
---------
install cmocka-1.1.5 download from: https://cmocka.org/files
cd linked_list_void_ptr
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

