//******************************************************************
//
//  Gerald Ellsworth
//  Z1885378
//  CSCI 463-1
// 
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//******************************************************************

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::hex;
using std::dec;
using std::internal;
using std::setfill;
using std::setw;
using std::endl;

/**
 * Prints the binary, sign, exponent, significand, and binary notation for a hex value.
 *
 * Takes a given hex value and extracts it's sign, exponent, and significand,
 * and then prints them as well as the full number in binary notation. If any values
 * are considered special cases, it prints whether it is +/- 0, infinity, or NaN.
 *
 * @param x A 32 bit hex value whose mantissa, exponent, and sign we wish to print.
 * 
 **************************************************************************************/
void printBinFloat(uint32_t x) {
    uint32_t hexMask = 0x80000000;
    uint32_t manCheck = 0x007fffff;
    uint32_t expCheck = 0x000000ff;
    uint32_t expSubtract = 0x0000007f;
    uint32_t signCheck = 0x00000001;

    cout << internal << setfill('0');                       //fills empty space with 0's if hex value is too small.

    cout << hex << "0x" << setw(8) << x << " = ";           //prints 0x before the hex value.

    //Loop to print all values of the hex as binary. It will either
    //print a 1 or 0 depending on whether input matches a significant bit.
    //Do a right shift to move the significant bit over to check next value,
    //then finally create a space every after every 4th character in the binary.
    for (int i = 0; i < 32; i++) {
        cout << (x & hexMask ? '1':'0');
        hexMask = (hexMask >> 1);

        if ((i + 1) % 4 == 0 && (i + 1) != 32)
            cout << " ";
    }
    cout << endl;

    uint32_t man = x & manCheck;                            //places the mantissa into its own variable.
    uint32_t nanExp = ((x >> 23) & expCheck);               //variable used to check if NaN.
    uint32_t exp = ((x >> 23) & expCheck) - expSubtract;    //places the exponent into its own variable after subtracting 127 (7f in hex) from it.
    uint32_t sign = (x >> 31) & signCheck;                  //places the sign into its own variable, checking it against a single '1'.

    cout << dec << "sign: " << sign << endl;
    cout << hex << " exp: " << "0x" << setw(8) << exp << dec << " (" << (int32_t) exp << ")" << endl;
    cout << hex << " sig: " << "0x" << setw(8) << man << endl;

    uint32_t posInfChk = 0x7f800000;
    uint32_t negInfChk = 0xff800000;
    uint32_t posZeroChk = 0x00000000;
    uint32_t negZeroChk = 0x80000000;

    //If x is equivalent to any of these values, it is a
    //special case and its final notation can be assumed.
    if (x == posInfChk) {
        cout << "+inf"<< endl;
        return;
    }
    if (x == negInfChk) {
        cout << "-inf" << endl;
        return;
    }
    if (x == posZeroChk) {
        cout << "+0" << endl;
        return;
    }
    if (x == negZeroChk) {
        cout << "-0" << endl;
        return;
    }
    if (nanExp == 0xff && man != 0x00) {
        cout << "NaN" << endl;
        return;
    }

    int32_t absExp;                                     //variable for a signed integer
    int32_t manLn = 23;                                 //length of the mantissa
    uint32_t manMask = 0x00800000;                            //hex value used for an '& mask'.

    man = man | 0x00800000;                             //sets leading binary value of mantissa to '1' to model the implied 1 in notation.

    if (sign)                                           //if the sign bit is a 1, we print a negative sign.
        cout << "-";
    else                                                //if the sign bit is a 0, we print a positive sign.
        cout << "+";

    //If the exponent is positive or zero, we create a tracker variable
    //and set the exponent to it's signed value to be used in a loop.
    //Loop up to the value of the exponent printing the mantissa and
    //shifting our bit checker after each loop. When we reach the end
    //of the loop, we print the binary point and if the amount of loops
    //done is greater than 23, we also print the final 0. However, if
    //i was less than 23, we have more digits to print, so we jump into
    //another for loop to finish printing them. We then return as there
    //is no need to continue and check if the exponent is negative.
    if ((int32_t) exp >= 0) {
        int i = 0;
        absExp = (int32_t) exp;
        for ( ; i <= absExp; ++i) {
            cout << (man & manMask ? '1':'0');
            manMask = manMask >> 1;
            if (i == absExp) {
                cout << ".";   
                if (i > manLn)
                    cout << "0";
            }
        }
        for ( ; i <= manLn; ++i) {
            cout << (man & manMask ? '1':'0'); 
            manMask = manMask >> 1;
        }
        cout << endl;
        return;
    } 
    
    //If the value of the exponent is negative, multiply
    //the value by -1 so we can work with a positive integer.
    //Since we know that we're working with a number less than
    //1, we can print the 0 and binary point immediately. We
    //then loop to print all of the zeros representing the shifts
    //before going into another loop to print the mantissa.
    if ((int32_t) exp < 0) {
        absExp = ((int32_t) exp) * -1;
        cout << "0.";
        for (int i = 1; i < absExp; ++i) {
            cout << "0";
        }
        for (int j = 0; j <= manLn; ++j) {
            cout << (man & manMask ? '1':'0');
            manMask = manMask >> 1;
        }
        cout << endl;
        return;
    }
}

int main() {
    uint32_t x;

    while (cin >> hex >> x) {                           //while loop to receive the value as a hex digit.
        printBinFloat(x);                               //call to the function to print each value.
    }
    return 0;
}
