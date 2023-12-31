/***
 * Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{7}
 * DictionaryTest.cpp
 * Testing file for Dictionary ADT.
 * ***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string s;
   string S[] =   {
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };
   string T[] =   {
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",      
                  };
   Dictionary A;
   Dictionary B;


   cout << endl;
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+1);
   }
   B = A;
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;

   B.setValue("deschooler", 101);
   B.setValue("reinsurer", 102);
   B.setValue("glagolitic", 103);
   B.setValue("cul", 104);
   B.setValue("ambusher", 105);
   Dictionary C = B;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;
   cout << A.getValue("hemiolia") << endl;
   A.getValue("hemiolia") *= 10;
   cout << A.getValue("hemiolia") << endl << endl;
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;
   
   cout << endl;

   return( EXIT_SUCCESS );
}
