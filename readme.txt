To install Catch2:
cd ~/dev/
git clone https://github.com/catchorg/Catch2.git
cd Catch2/
cmake -Bbuild -H. -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install

To build neutils:
cd ~/dev/c++/neutils/
mkdir build/
cd build/
cmake ..
make

Debug neutils:
cd ~/dev/c++/neutils/
mkdir Debug/
cd Debug/
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

Release neutils:
cd ~/dev/c++/neutils/
mkdir Debug/
cd Debug/
cmake -DCMAKE_BUILD_TYPE=Release ..
make
