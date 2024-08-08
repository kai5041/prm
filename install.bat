mkdir build
g++ -o build/prm src/build.cpp src/main.cpp src/new_cpp.cpp src/new_project.cpp src/run.cpp -Iinclude -std=c++17
@ cp build/prm.exe C:\Windows\System32