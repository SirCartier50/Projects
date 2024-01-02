/***
 * Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{6}
 * BigIntegerTest.cpp
 * test file for the BigInteger ADT
 * ***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main() {
   string s1 = "9063574346363325007361058";
   string s3 = "10";
   string s5 = "12348148518469129628889";
   cout << "start" << endl;
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);
      BigInteger C = BigInteger(s5);

	     cout << endl;

		    cout << "A = " << A << endl;
			   cout << "B = " << B << endl;
			      cout << "C = " << C << endl;
				     cout << endl;

					    BigInteger D = A+B;
						   BigInteger E = B+A;
						      BigInteger F = D-E;
							     BigInteger G = 53234*A + 29384747*B + 928374*C;
								    BigInteger H = A*B;
									   BigInteger I = B*A;
									      BigInteger J = G*H*I;

										     cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
											    cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
												   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
												      cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
													     cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

														    cout << "D = " << D << endl;
															   cout << "E = " << E << endl;
															      cout << "(D==E) = " << ((D==E)?"True":"False") << endl;
																     cout << "F = " << F << endl;
																	    cout << "G = " << G << endl;
																		   cout << "H = " << H << endl;
																		      cout << "I = " << I << endl;
																			     cout << "(H==I) = " << ((H==I)?"True":"False") << endl;
																				    cout << "J = " << J << endl << endl;

																					   cout << endl;

																					      A += B;
																						     B -= C;
																							    C *= J;
																								   cout << "A = " << A << endl;
																								      cout << "B = " << B << endl;
																									     cout << "C = " << C << endl;
																										    cout << endl;

																											   cout << A*B*C*D*E*G*H*I*J << endl << endl;

																											      cout << endl;
    
      return EXIT_SUCCESS;
}

