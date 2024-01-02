/***
 * Author: Mignot Mesele
 * Title: BigInteger.h
 * Purpose: BigInteger ADT Header
 * ***/

#include<iostream>
#include<string>
#include"List.h"

#ifndef BIG_INTEGER_H_INCLUDE_
#define BIG_INTEGER_H_INCLUDE_

class BigInteger {
private:
    int signum;
    List digits;

public:
    BigInteger();
    BigInteger(long x);
    BigInteger(std::string s);
    BigInteger(const BigInteger& N);

    int sign() const;
    int compare(const BigInteger& N) const;

    void makeZero();
    void negate();

    BigInteger add(const BigInteger& N) const;
    BigInteger sub(const BigInteger& N) const;
    BigInteger mult(const BigInteger& N) const;

    std::string to_string();

    friend std::ostream& operator<<(std::ostream& stream, BigInteger N);
    friend bool operator==(const BigInteger& A, const BigInteger& B);
    friend bool operator<(const BigInteger& A, const BigInteger& B);
    friend bool operator<=(const BigInteger& A, const BigInteger& B);
    friend bool operator>(const BigInteger& A, const BigInteger& B);
    friend bool operator>=(const BigInteger& A, const BigInteger& B);
    friend BigInteger operator+(const BigInteger& A, const BigInteger& B);
    friend BigInteger operator+=(BigInteger& A, const BigInteger& B);
    friend BigInteger operator-(const BigInteger& A, const BigInteger& B);
    friend BigInteger operator-=(BigInteger& A, const BigInteger& B);
    friend BigInteger operator*(const BigInteger& A, const BigInteger& B);
    friend BigInteger operator*=(BigInteger& A, const BigInteger& B);
};

#endif

