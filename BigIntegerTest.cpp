//-----------------------------------------------------------------------------
// BigIntegerTest.cpp
// Test Client for the BigInteger ADT
// Bradley Haire
// bhaire
// pa6
//-----------------------------------------------------------------------------


#include "List.h"
#include "BigInteger.h"
using std::cout;
using std::cerr;
using std::endl;


int main(int argc, char** argv){ 
    std::string s1 = "9128734667000004389234563456345619187236478";
    std::string s3 = "9876545439000000000000000200000000000006543654365346534";
    std::string mine = "98217123809138";

    std::string compare_test_1 = "15000000";
    std::string compare_test_2 = "-10000";
    BigInteger * cmpt1 = new BigInteger(compare_test_1);
    BigInteger * cmpt2 = new BigInteger(compare_test_2);

    BigInteger result = cmpt1->add(*cmpt2);
    cout << result << endl;

    BigInteger* main_number1 = new BigInteger("8379843762389746289374629873469287346982734398723648972364873873");
    BigInteger* main_number2 = new BigInteger("087304260827364283746276342738437463783483764");

    cout << "first num: " << *main_number1 << endl;
    cout << "second num: " << *main_number2 << endl;

    cout << "sum: " << (*main_number1 + (*main_number2)) << endl;
    cout << "product: " << (*main_number1 * (*main_number2)) << endl;
    *main_number1 += *main_number2;
    cout << "sum: " << *main_number1 << endl;
    *main_number2 *= *main_number2;
    cout << "new product: " << *main_number2 << endl;

    cout << (*main_number1 == *main_number2) << endl;
    cout << "above should be false" << endl;
    cout << (*main_number1 < *main_number2) << endl;
    cout << (*main_number2 > *main_number1) << endl;
    cout << "2 above should both be true" << endl;

    cout << (*main_number1 >= *main_number2) << endl;
    cout << "above should be false" << endl;

    cout << (*main_number1 <= *main_number2) << endl;
    cout << "above should be true" << endl;

    cout << "diff: " << *main_number2 - (*main_number1) << endl;
    cout << "second diff (should be negative): " << *main_number1 - (*main_number2) << endl;

    *main_number1 -= *main_number2;
    cout << "should be the same as the above value: " << *main_number1 << endl;


    cout << "below will be a series of explicitly used functions, not operator overrides" << endl;
    cout << main_number1->add(*main_number2) << endl;
    cout << main_number2->sub(*main_number2) << endl;
    cout << main_number2->sub(*main_number1) << endl;

    BigInteger val = *main_number2;
    cout << "should be true: " <<  (val == *main_number2) << endl;
    cout << "should be 0, using compare: " << main_number2->compare(val) << endl;


    BigInteger* M = new BigInteger(mine);
    cout << "repr: " << *M << endl;

    delete cmpt1;
    delete cmpt2;

    delete main_number1;
    delete main_number2;
    delete M;

    return 0;
}