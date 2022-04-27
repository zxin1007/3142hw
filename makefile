lab1: 
	cd 01_primitives && g++ file_in.cpp -o main && ./main

lab2: calculator
	cd lab2 && ./calculator

calculator: 
	cd lab2 && g++ calculator.cpp -o calculator

lab3: main 
		cd lab3 && mkdir -p output && cd src && ./main

main:
	cd lab3/src && g++ main.cpp -o main