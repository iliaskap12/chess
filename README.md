# 2 PLAYER CHESS GAME BUILD WITH THE SGG LIBRARY AS A C++ SCHOOL PROJECT AT AUEB

## Install and build Ubuntu

We installed and built on Ubuntu using the following:

- Ubuntu 21.04 hirsute hippo
- g++11
- -std=c++20
- cmake version 3.22.1
- Ninja generator

We used CMake with FetchContent to include the SGG Library so there souldn't be many dependencies issues - at least  
we didn't face any. If OpenGL is missing - a common enough issue on Ubuntu, to install run the following:

```
sudo apt-get update
sudo apt-get install -y mesa-common-dev libgl1-mesa-dev libgles2-mesa-dev
```

To get the latest CMake version download it and build it directly from Kitware:

https://cmake.org/download/

On Linux place the downloaded tar file at your desired location, open terminal there, and run:

```
tar -xf cmake-${{ MAJOR_VERSION }}-${{ MINOR_VERSION }}-${{ PATCH_NUMBER }}.tar.gz
```

where the versioning numbers correspond to your download. We tested using CMake **3.22.1**. Next run:

```
cd cmake-${{ MAJOR_VERSION }}-${{ MINOR_VERSION }}-${{ PATCH_NUMBER }}
./bootstrap
make
sudo make install
```

If you don't have gcc-11 and g++-11 run:

```
sudo apt-get update
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt install -y gcc-11 g++-11
```

If you don't have ninja-build installed run:

```
sudo apt-get update
sudo apt-get install -y ninja-build
```

On our systems the default installation for each respectively was:

- /usr/bin/gcc-11
- /usr/bin/g++-11
- /usr/bin/ninja

and those paths our script uses. To find out were in your system are these installed run:

```
which gcc-11
which g++-11
which ninja
```

To download and build the source finally either download the *.zip file* from github and unzip on your desired location
or simply:

```
git clone https://iliaskap12.github.com/chess.git
```

if you have git installed. Then open your terminal on the download folder and run:

```
cd chess
```

Finally either run the build script using:

```
sh ./linux-buil-script.sh
```

or:

```
mkdir cmake-build-release && \
cmake -S . \
 -B cmake-build-release \
 -DCMAKE_CXX_COMPILER=/usr/bin/g++-11 \
 -DCMAKE_MAKE_PROGRAM=/usr/bin/ninja \
 -DCMAKE_CXX_STANDARD=20 \
 -DCMAKE_CXX_STANDARD_REQUIRED=ON \
 -DCMAKE_BUILD_TYPE=Release \
 -DCMAKE_CXX_EXTENSIONS=OFF \
 -G Ninja && \
cmake --build cmake-build-release --target chess
```

Be sure to change the installation paths of the compiler and the generator build engine if they are different on your
system or you want to use other tools. ***The program hasn't been tested with different toolchains though.***

FInally, to run the program run:

```
./cmake-build-release/src/chess
```
