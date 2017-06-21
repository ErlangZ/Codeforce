build:
	g++ --std=c++11 -g ./817_B.cpp -o a
	./a < ./input.data
	python 817_B.py < input.data
