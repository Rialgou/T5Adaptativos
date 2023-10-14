all: grasp

test: grasp

grasp: grasp.cpp
	g++ $^ -o grasp.out

test_grasp: grasp | 
	./test_grasp.sh
