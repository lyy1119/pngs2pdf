all:
	g++ -std=c++17 main.cpp -static -O2 -Wall -o pngs2pdf -lhpdf -lpng -lz -lm -lstdc++