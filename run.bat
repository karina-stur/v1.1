cmake CMakeLists.txt
cmake --install .
cmake --build .
copy src\*.txt Debug\*.txt
cd Debug\
v1.1.exe
pause
