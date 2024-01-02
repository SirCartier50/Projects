/***
 * Author: Mignot Mesele
 * Title: BigInteger.cpp
 * Purpose: BigInteger ADT
 * ***/

#include <stdexcept>
#include "BigInteger.h"

const long POWER = 9;
const long BASE = 1000000000;

/*** Constructors ***/

BigInteger::BigInteger() {
    signum = 0;
}

BigInteger::BigInteger(long x) {
    if (x < 0) {
        signum = -1;
        x = -x;
    } else if (x > 0) {
        signum = 1;
    } else {
        signum = 0;
    }
    while (x > 0) {
        digits.insertAfter(x % BASE);
        x = x / BASE;
    }
}

BigInteger::BigInteger(std::string s) {
    if (s[0] == '-') {
        signum = -1;
        s.erase(0, 1);
    } else if (s[0] == '+') {
        signum = 1;
        s.erase(0, 1);
    } else {
        signum = 1;
    }
    for (char ch : s) {
        if (!isdigit(ch)) {
            throw std::invalid_argument("String contains non-number!\n");
        }
	}
    int i = s.length()-1;
    long x;
    while (i >= 0) {
	if((s.length() - i)%POWER == 0){
		x = std::stoi(s.substr(i,POWER));
		digits.insertAfter(x);
	}
	i--;
    }
    if(s.length()%POWER != 0){
	x = std::stoi(s.substr(0,(s.length()%POWER)));
	digits.insertAfter(x);
    }
	digits.moveFront();
	while(digits.length() > 0 && digits.peekNext() == 0){
		digits.eraseAfter();
	}
	if(digits.length() == 0){
		signum = 0;
	}

}

BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}

/*** Access functions ***/

int BigInteger::sign() const {
    return signum;
}

int BigInteger::compare(const BigInteger& N) const {
	List L = N.digits;
	List A = this->digits;
        if(signum > N.sign()){
                return 1;
        }else if(signum < N.sign()){
                return -1;
        }
        if(A.length() > L.length()){
                if(signum == 1){
                        return 1;
                }else if(signum == -1){
                        return -1;
                }
        }else if(A.length() < L.length()){
                if(signum == 1){
                        return -1;
                }else if(signum == -1){
                        return 1;
                }
        }
        if(signum == 1){
        
                A.moveFront();
                L.moveFront();
                while(A.position() < A.length() && L.position() < L.length()){
                        if(A.peekNext() > L.peekNext()){
                                return 1;
                        }else if(A.peekNext() < L.peekNext()){
                                return -1;
                        }else{
                                A.moveNext();
                                L.moveNext();
                        }
                }
                return 0;
        }else if(signum == -1){
                A.moveFront();
                L.moveFront();
                while(A.position() < A.length() && L.position() < L.length()){
                        if(A.position() == 0 && L.position() == 0){
                                if(A.peekNext() > L.peekNext()){
                                        return 1;
                                }else if(A.peekNext() < L.peekNext()){
                                        return -1;
                                }else{
                                        A.moveNext();
                                        L.moveNext();
                                }
                        }
                        if(A.peekNext() > L.peekNext()){
                                return -1;
                        }else if(A.peekNext() < L.peekNext()){
                                return 1;
                        }else{
                                A.moveNext();
                                L.moveNext();
                        }
                }
                return 0;
        }
        return 0;

}

void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

void BigInteger::negate() {
    if (signum != 0) {
        signum = -signum;
    }
}

void negateList(List& L){
        L.moveFront();
        while(L.position() < L.length()){
                L.setAfter((-1*L.peekNext()));
                L.moveNext();
        }
}

void sumList(List& S, List A, List B, int sgn){
        if(sgn == 0){
			S = A;
            return;
		}
	if(A.length() == 0){
		S = B;
		return;
	}
	S.clear();
        A.moveBack();
        B.moveBack();
        while(A.position() > 0 && B.position() > 0){
                S.insertAfter(A.peekPrev() + B.peekPrev());
                A.movePrev();
                B.movePrev();
        }
        while(A.position() > 0){
                S.insertAfter(A.peekPrev());
                A.movePrev();
        }
        while(B.position() > 0){
                S.insertAfter(B.peekPrev());
                B.movePrev();
        }
}

int normalizeList(List& L){
	int signum;
        if(L.front() < 0){
                signum = -1;
                negateList(L);
        }else if(L.front() > 0){
                signum = 1;
        }else{
                L.moveFront();
                while(L.peekNext() == 0 && L.position() == L.length()){
                        L.eraseAfter();
                }
        }
        L.moveBack();
        while(L.position() > 0){
                if(L.peekPrev() < 0){
                        L.movePrev();
                        L.setBefore(L.peekPrev()-1);
                        L.moveNext();
                        L.setBefore(BASE+L.peekPrev());
                }else{
                        if(L.position() > 1){
                                long i = L.peekPrev()%BASE;
                                i = L.peekPrev() - i;
                                i = i/BASE;
                                L.movePrev();
                                L.setBefore(L.peekPrev() + i);
                                L.moveNext();
				L.setBefore(L.peekPrev()%BASE);
                        }else if((L.peekPrev()%BASE)>0){
                                long i = L.peekPrev()%BASE;
                                i = L.peekPrev() - i;
                                i = i/BASE;
				L.setBefore(L.peekPrev()%BASE);
				if(i > 0){	
					L.movePrev();
                                	L.insertBefore(i);
					L.moveNext();
				}
				
                        }
                }
                L.movePrev();
        }
        L.moveFront();
        while(L.peekNext() == 0 && L.position() < L.length()){
                L.eraseAfter();
		if(L.length() == 0){
			break;
		}
        }
        return signum;
}       
void shiftList(List& L, int p){
        L.moveBack();
        for(int i = 0; i < p; i++){
                L.insertAfter(0);
        }
}

void scalarMultList(List& L, ListElement m){
        L.moveFront();
        while(L.position() < L.length()){
                L.setAfter((m * L.peekNext()));
                L.moveNext();
        }
}

BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger sum;
	List A = digits;
	List B = N.digits;
	if(signum == -1){
		negateList(A);
        }
	if(N.signum == -1){
		negateList(B);
	}
        sumList(sum.digits, A, B, 1);
        sum.signum = normalizeList(sum.digits);
        return sum;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
	BigInteger diff;
	List A = digits;
	List B = N.digits;

        if(signum == -1){
                negateList(A);
        }
        negateList(B);
	if(N.signum == -1){
		negateList(B);
	}
        sumList(diff.digits, A, B, 1);
        diff.signum=normalizeList(diff.digits);
        return diff;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger prod;
	List A = N.digits;
	List B = digits;
	int y = 0;
	if(N.signum == signum){
        	y = 1;	
     }else if( N.signum == 0 || signum == 0){
		y = 0;
	}
	else{
		y = -1;
	}
        int x = 0;
        A.moveBack();
        while(A.position() > 0){
			List L = B;
            List C = prod.digits;
            scalarMultList(L, A.peekPrev());
			shiftList(L, x);
            sumList(prod.digits, C, L, 1);
            normalizeList(prod.digits);
            A.movePrev();
            x++;
		
        }

	prod.signum = y;
        return prod;
}


/*** Other functions ***/

std::string BigInteger::to_string(){
        digits.moveFront();
        std::string s = "";
        if(digits.length() == 0){
                s += std::to_string(0)+" ";
                return s;
        }else if(signum < 0){
                s += "-";
        }
	while(digits.position() < digits.length()){
		std::string x= std::to_string(digits.peekNext());
		if(x.size() < POWER && digits.position() != 0){
			int y = POWER - x.size();
			while(y > 0){
				x = '0' + x;
				y--;
			}
		}
		s += x;
        digits.moveNext();
	}
        return s;
}


std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.to_string();
}


bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == -1;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == -1 || A.compare(B) == 0;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 1;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 1 || A.compare(B) == 0;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B){
        return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B){
        A = A.add(B);
        return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B){
        return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B){
        A = A.sub(B);
        return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B){
        return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B){
        A = A.mult(B);
        return A;
}

