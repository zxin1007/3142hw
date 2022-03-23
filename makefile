lab1: 
	cd 01_primitives && g++ file_in.cpp -o main && ./main

lab2: calculator
	cd lab2 && ./calculator

calculator: 
	cd lab2 && g++ calculator.cpp -o calculator