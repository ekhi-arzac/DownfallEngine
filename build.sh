mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
mkdir ../bin
cp ./DownfallEngine ../bin/DownfallEngine