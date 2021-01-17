/*
Ben Kaufmann
12/10/2020
PA5


*/







#include "ProbingHash.h"
#include "Hash.h"
#include "ChainingHash.h"
#include "ParallelProbingHash.h"
#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ofstream output;
	int value;
	output.open("HashAnalysis.txt");
	auto start = chrono::high_resolution_clock::now();
	ChainingHash<int, int> table(101);
	for (int i = 1; i < 1000001; i++) {
		table.emplace(i, i);
	}
	output << "------------ChainHashing-----------" << endl;
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
	output << "Insert duration: " << duration.count() << " seconds" << endl;

	start = chrono::high_resolution_clock::now();
	value = table.at(177);
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::seconds>(stop - start);
	output << "Search for 177 duration: " << duration.count() << " seconds" << endl;

	start = chrono::high_resolution_clock::now();
	value = table.at(2000000);
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::seconds>(stop - start);
	output << "Search for 2000000 duration: " << duration.count() << " seconds" << endl;

	start = chrono::high_resolution_clock::now();
	table.erase(177);
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::seconds>(stop - start);
	output << "Erase for 177 duration: " << duration.count() << " seconds" << endl;

	start = chrono::high_resolution_clock::now();
	ProbingHash<int, int> linTable(101);
	for (int i = 1; i < 1000001; i++) {
		linTable.emplace(i, i);
	}
	output << "------------ProbeHashing-----------" << endl;
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::seconds>(stop - start);
	output << "Insert duration: " << duration.count() << " seconds" << endl;

	start = chrono::high_resolution_clock::now();
	value = linTable.at(177);
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::seconds>(stop - start);
	output << "Search for 177 duration: " << duration.count() << " seconds" << endl;

	start = chrono::high_resolution_clock::now();
	value = linTable.at(2000000);
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::seconds>(stop - start);
	output << "Search for 2000000 duration: " << duration.count() << " seconds" << endl;

	start = chrono::high_resolution_clock::now();
	linTable.erase(177);
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::seconds>(stop - start);
	output << "Erase for 177 duration: " << duration.count() << " seconds" << endl;

	output.close();
	return 0;
}