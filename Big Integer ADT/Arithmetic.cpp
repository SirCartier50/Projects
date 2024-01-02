/***
 * Author: Mignot Mesele
 * Title: Arithmetic.cpp
 * Purpose: Test File for BigInteger ADT
 * ***/

#include<iostream>
#include<fstream>
#include<string>
#include "BigInteger.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   ifstream in;
   ofstream out;
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
	std::string a;
	std::string b;
   in >> a;
   in >> b;
   BigInteger A = BigInteger(a);
   BigInteger B = BigInteger(b);
   out << A << "\n\n";
   out << B << "\n\n";
   out << A+B << "\n\n";
   out << A-B << "\n\n";
   out << A-A << "\n\n";
   out << (3*A)-(2*B) << "\n\n";
   out << A*B << "\n\n";
   out << A*A << "\n\n";
   out << B*B << "\n\n";
   out << (9*(((A*A)*A)*A))+(16*((((B*B)*B)*B)*B)) << "\n\n";
   in.close();
   out.close();	
   return 0;
}
