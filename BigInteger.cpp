//-----------------------------------------------------------------------------
// BigInteger.cpp
// Implementation file for the BigInteger ADT
// Bradley Haire
// bhaire
// pa6
//-----------------------------------------------------------------------------


#include<iostream>
#include<string>

#include"BigInteger.h"

static const long base = 1000000000;
static const int power = 9;

using std::cerr;
using std::cout;
using std::cin;
using std::endl;

BigInteger::BigInteger() {
    this->signum = 0;
    this->digits = List();
}

BigInteger::BigInteger(std::string s) {
    if (s.length() < 1) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    std::string new_string;
    if (s[0] == '-') {
        this->signum = -1;
        new_string = s.substr(1);
    } else if (s[0] == '+') {
        this->signum = 1;
        new_string = s.substr(1);
    } else {
        this->signum = 1;
        new_string = s;
    }
    if (new_string.length() < 1) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    for (int i = 0; i < int(new_string.length()); i++) {
        if (!isdigit(new_string[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    std::string pow_str = "";
    List * curr = new List();
    while (new_string.length() >= power) {
        pow_str = new_string.substr(new_string.length()-power);
        new_string = new_string.substr(0, new_string.length()-power);
        curr->insertAfter(std::stol(pow_str));
    }
    if (new_string.length() > 0) {
        curr->insertAfter(std::stol(new_string));
    }
    this->digits = *curr;
    delete curr;
}

BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = List(N.digits);
}

int BigInteger::sign() const {
    return this->signum;
}

int BigInteger::compare(const BigInteger& N) const {
    // if one is positive and the other is negative
    if (N.signum == -1 && this->signum != -1) {
        return 1;
    }
    else if (N.signum != -1 && this->signum == -1) {
        return -1;
    }
    // if one is longer than the other, this is dependent upon the sign
    if (N.digits.length() < this->digits.length() && N.signum == 1) {
        return 1;
    }
    else if (N.digits.length() < this->digits.length() && N.signum == -1) {
        return -1;
    }
    else if (N.digits.length() > this->digits.length() && N.signum == 1) {
        return -1;
    }
    else if (N.digits.length() > this->digits.length() && N.signum == -1) {
        return 1;
    }
    else {
        // number of digits from a shallow perspective is equal

        List this_list = List(this->digits);
        List N_list = List(N.digits);
        this_list.moveFront();
        N_list.moveFront();
        while (N_list.position() < N_list.length()) {// This for loop may need to iterate one extra time, I cant remember if N.position == N.length is a valid cursor index
        long n_val = N_list.peekNext();
        long this_val = this_list.peekNext();
        if (n_val < this_val) {
            return 1;
        }
        else if (n_val > this_val) {
            return -1;
        }
        this_list.moveNext();
        N_list.moveNext();
        }
    }
    return 0;
    
    
}

void BigInteger::makeZero() {
    this->signum = 0;
    this->digits.clear();
}

void BigInteger::negate() {
    this->signum *= -1;
}

static void negateList(List& L) {
    for (L.moveFront(); L.position() < L.length(); L.moveNext()) {
        L.setAfter(-1 * L.peekNext());
    }
}


void vector_add(List& to_set, List& one, List& two, int sign) {
    to_set.clear();
    to_set.moveBack();
    if (one.length() == 0) {
        List l = List();
        for (two.moveBack(); two.position(); two.movePrev()) {
            to_set.insertAfter(two.peekPrev());
        }
        return;
    }
    else if (two.length() == 0) {
        List l = List();
        for (one.moveBack(); one.position(); one.movePrev()) {
            to_set.insertAfter(one.peekPrev());
        }
        return;
    }
    one.moveBack();
    two.moveBack();
    while (one.position() && two.position()) {
        to_set.insertAfter(one.movePrev() + sign*two.movePrev());
    }
    while (one.position()) {
        to_set.insertAfter(one.movePrev());
    }
    while (two.position()) {
        to_set.insertAfter(sign*two.movePrev());
    }
    return;
}

static int normalize(List& L) {
    if (L.length() == 0) {
        return 0;
    }

    if(L.front() == 0) {
        while (L.length()) {
            if (L.front() == 0) {
                L.moveFront();
                L.eraseAfter();
            }
            else {
                break;
            }
            
        }
    }
    if (L.length() == 0) {
        return 0;
    }
    int sign = 0;

    if (L.front() < 0) {
        negateList(L);
        sign = -1;
    } else {
        sign = 1;
    }

    L.moveBack();

    ListElement carry = 0;
    ListElement val = 0;
    for (L.moveBack(); L.position(); L.movePrev()) {
        val = L.peekPrev() + carry;
        if (val >= 0) {
            carry = val / base;
        } else {
            if (val % base == 0) {
                carry = val / base;
            } else {
                carry = (val / base) - 1;
            }
        }
        
        val = val - (carry * base);
        L.setBefore(val);
    }    

    if (carry > 0) {
        L.moveFront();
        L.insertBefore(carry);
    }
    if (carry < 0) {
        cerr << "Something has gone horribly wrong" << endl;
    }

    return sign;
}

void shiftList(List& L, long p) {
    L.moveBack();
    for (long i = 0; i < p; i++) {
        L.insertAfter(0);
    }
}

void scalarMultList(List& L, ListElement m) {
    for (L.moveBack(); L.position(); L.movePrev()) {
        L.setBefore(m * L.peekPrev());
    }
}

BigInteger BigInteger::add(const BigInteger& N) const {

    BigInteger bi = BigInteger();
    if(!this->signum && !N.signum) {
        return bi;
    }
    if (!this->signum) {
        return BigInteger(N);
    }
    if (!N.signum) {
        return BigInteger(*this);
    }
    List this_list = List(this->digits);
    List N_list = List(N.digits);

    if (this->signum == -1) {
        negateList(this_list);
    }
    if (N.signum == -1) {
        negateList(N_list);
    }
    List l;
    vector_add(bi.digits, this_list, N_list, 1);
    bi.signum = normalize(bi.digits);
    return bi;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger myInt = BigInteger(N);
    myInt.negate();
    return this->add(myInt);
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger result;
    if (this->signum == 0 || N.signum == 0) {
        return result;
    }
    List this_digits = List(this->digits);
    List N_digits = List(N.digits);
    List temp = List();
    long i = 0;
    for (this_digits.moveBack(); this_digits.position(); this_digits.movePrev()) {
        List curr = List(N_digits);
        scalarMultList(curr, this_digits.peekPrev());

        normalize(curr);
        shiftList(curr, i);
        normalize(curr);
        vector_add(temp, result.digits, curr, 1);
        normalize(temp);
        result.digits = temp;
        i++;
    }
    result.signum = (this->signum * N.signum);
    return result;
}

std::string BigInteger::to_string() {
    if (this->signum == 0) {
        return "0";
    }
    else {
        std::string result = "";
        if (this->signum == -1) {
            result += "-";
        }
        for (this->digits.moveFront(); this->digits.position() < this->digits.length(); this->digits.moveNext()) {
            long curr = this->digits.peekNext();
            if (curr == 0) {
                for (int i = 0; i < power; i++) {
                    result += "0";
                }
            } else {
                std::string curr_str = std::to_string(curr);
                if (curr_str.length() < power) {
                    std::string zeros = "";
                    for (long unsigned int i = 0; i < power - curr_str.length(); i++) {
                        zeros += "0";
                    }
                    result += zeros + curr_str;
                } else {
                    result += curr_str;
                }
            }
        }
        while (result[0] == '0') {
            result.erase(0,1);
        }
        if (result[0] == '+' || result[0] == '-') {
            while (result[1] == '0') {
                result.erase(1,1);
            }
        }
        return result;
    }
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    stream << N.to_string();
    return stream;
}

bool operator==( const BigInteger& A, const BigInteger& B ) {
    if  (A.BigInteger::compare(B) == 0) return true;
    else return false;
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
    if  (A.BigInteger::compare(B) == -1) return true;
    else return false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) return false;
    else return true;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) return true;
    else return false;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) return false;
    else return true;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}
