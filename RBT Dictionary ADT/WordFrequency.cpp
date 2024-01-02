/***
* Author: Mignot Mesele
* Title: WordFrequency.cpp
* Purpose: Top Client file for Dictionary ADT
***/

#include<iostream>
#include<fstream>
#include<string>

#include"Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
	size_t begin, end, len;
	ifstream in;
	ofstream out;
	string line;
	string tokenBuffer;
	string token;
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
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

	Dictionary A;
	while( getline(in, line) )  {
		len = line.length();
		tokenBuffer = "";
		begin = min(line.find_first_not_of(delim, 0), len);
		end   = min(line.find_first_of(delim, begin), len);
		token = line.substr(begin, end-begin);
		while( token!="" ){
			tokenBuffer += "   "+token+"\n";
			for (char& c : token) {
				c = std::tolower(c);
			}
			if(A.contains(token)){
				A.setValue(token, (A.getValue(token) + 1));
			}else{
				A.setValue(token, 1);
			}
			begin = min(line.find_first_not_of(delim, end+1), len);
			end   = min(line.find_first_of(delim, begin), len);
			token = line.substr(begin, end-begin);
		}
	}
	out << A << endl;
	in.close();
	out.close();
	return(EXIT_SUCCESS);
}
