/***
 * Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{8}
 * Order.cpp
 * Top Client function for Dictionary ADT
 * ***/

#include<iostream>
#include<fstream>
#include<string>

#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
	ifstream in;
	ofstream out;
	string line;
	if( argc != 3 ){
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}
	in.open(argv[1]);
	if( !in.is_open() ){
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}

	out.open(argv[2]);
	if( !out.is_open() ){
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}

	int line_count = 0;
	Dictionary A;
	while(getline(in, line)){
		line_count++;
		A.setValue(line, line_count);
	}
	out << A << endl;
	out << A.pre_string() << endl;
	in.close();
	out.close();
	return(EXIT_SUCCESS);
}
