/***
 * Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{6}
 * ListTest.cpp
 * Test file for List ADT
 * ***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

	   int i, n=10;
	      List A, B, C, D;

		     for(i=1; i<=n; i++){
				       A.insertAfter(i);
					         B.insertAfter(11-i);
							       C.insertBefore(i);
								         D.insertBefore(11-i);
										 	printf("%d\n", i);
											   }

			    cout << endl;
				   cout << "A = " << A << endl;
				      cout << "A.position() = " << A.position() << endl;
					     cout << "B = " << B << endl;
						    cout << "B.position() = " << B.position() << endl;
							   cout << "C = " << C << endl;
							      cout << "C.position() = " << C.position() << endl;
								     cout << "D = " << D << endl;
									    cout << "D.position() = " << D.position() << endl;
										   cout << endl;

										      A.moveBack();
											     B.moveBack();
												    C.moveFront();
													   D.moveFront();

													      cout << "A = " << A << endl;
														     cout << "A.position() = " << A.position() << endl;
															    cout << "B = " << B << endl;
																   cout << "B.position() = " << B.position() << endl;
																      cout << "C = " << C << endl;
																	     cout << "C.position() = " << C.position() << endl;
																		    cout << "D = " << D << endl;
																			   cout << "D.position() = " << D.position() << endl;

																			      cout << endl << "B: ";
																				     for(i=1; i<=7; i++){
																						       cout << B.movePrev() << " ";
																							      }
																					    cout << endl << "B.position() = " << B.position() << endl;
																						   
																						   cout << endl << "C: ";
																						      for(i=1; i<=7; i++){
																								        cout << C.moveNext() << " ";
																										   }
																							     cout << endl << "C.position() = " << C.position() << endl;

																								    cout << endl;
																									   cout << "A==B is " << (A==B?"true":"false") << endl;
																									      cout << "B==C is " << (B==C?"true":"false") << endl;
																										     cout << "C==D is " << (C==D?"true":"false") << endl;
																											    cout << "D==A is " << (D==A?"true":"false") << endl;
																												   cout << endl;

																												      cout << B.findNext(5) << endl;
																													     cout << B << endl;
																														    B.eraseBefore();
																															   B.eraseAfter();
																															      cout << B << endl;
																																     cout << B.position() << endl;
																																	    cout << B.findPrev(2) << endl;
																																		   B.eraseBefore();
																																		      B.eraseAfter();
																																			     cout << B << endl;
																																				    cout << B.position() << endl; 
																																					   cout << B.findNext(20) << endl; 
																																					      cout << B.position() << endl;
																																						     cout << B.findPrev(20) << endl;
																																							    cout << B.position() << endl;
																																								   cout << endl;

																																								      for( i=10; i>=1; i--){
																																										        A.insertAfter(i);
																																												      A.movePrev();
																																													     }
																																									     cout << "A = " << A << endl;
																																										    for( i=1; i<=15; i++){
																																												      A.moveNext();
																																													     }
																																											   cout << A.position() << endl;
																																											      A.cleanup();
																																												     cout << "A = " << A << endl;
																																													    cout << A.position() << endl;
																																														   cout << endl;
																																														      List E = A;
																																															     cout << "A = " << A << endl;
																																																    cout << "E = " << E << endl;
																																																	   cout << "E==A is " << (E==A?"true":"false") << endl;

																																																	      cout << endl;
}



