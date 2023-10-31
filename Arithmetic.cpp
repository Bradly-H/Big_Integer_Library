//-----------------------------------------------------------------------------
// Arithmetic.cpp
// Implementation file for the Arithmetic client file
// Bradley Haire
// bhaire
// pa6
//-----------------------------------------------------------------------------

#include "List.h"
#include "BigInteger.h"
#include <iostream>
#include <fstream>
using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char** argv){ 
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " invalid number of arguments " << endl;
        return(EXIT_FAILURE);
    }
    std::string file_1 = argv[1];
    std::string file_2 = argv[2];
    std::ifstream input(file_1);
    std::ofstream output(file_2);
    BigInteger A;
    BigInteger B;

    for (int i = 0; i < 3; i += 1) {
        std::string number;
        getline(input, number);
        if (i == 0) {
            A = BigInteger(number);
        }
        if (i == 1) {
            continue;
        }
        if (i == 2) {
            B = BigInteger(number);
        }
        
    }
    input.close();

    output << A << endl;
    output << endl;

    output << B << endl;
    output << endl;

    output << A+B << endl;
    output << endl;

    output << A-B << endl;
    output << endl;

    output << A-A << endl;
    output << endl;

    BigInteger scal_3 = BigInteger("3");
    BigInteger scal_2 = BigInteger("2");
    BigInteger A_3 = A*scal_3;
    BigInteger B_2 = B*scal_2;
    output << A_3 - B_2 << endl;
    output << endl;

    output << A*B << endl;
    output << endl;

    output << A*A << endl;
    output << endl;

    output << B*B << endl;
    output << endl;

    BigInteger scal_9 = BigInteger("9");
    BigInteger scal_16 = BigInteger("16");
    BigInteger final_left = scal_9*A*A*A*A;
    BigInteger final_right = scal_16*B*B*B*B*B;
    output << final_left + final_right << endl;
    return 0;
}