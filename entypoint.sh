#!/bin/bash


if [ ! -d libs/MLX42 ]
then
	cd libs/
	git clone https://github.com/codam-coding-college/MLX42.git
	if [ ! -f MLX42/libmlx42.a ]
	then
		cd MLX42
		brew install glfw
		brew install cmake
		cmake -B build 
		cmake --build build -j4
		cd ../../
	fi
fi
make

