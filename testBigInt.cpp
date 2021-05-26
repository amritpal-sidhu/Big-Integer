#include <iostream>
#include "BigInt.h"

using std::cin;
using std::cout;
using std::endl;

int main() {

    BigInt test1, test2;

    test1 = "20000000100000040000";
    test2 = "-10006000005000500001";

    cout << test1 << " - " << test2 << " = " << test1-test2 << endl;

    // int factorial;
    // BigInt testNum, result;
    //
    // /* Begin of istream & ostream overload test */
    // cout << "Enter a BigInt to print to the screen: ";
    // cin >> testNum;
    // cout << "The BigInt is: " << testNum << endl << endl;
    //
    // do {
    //
    //     cout << "Enter a number to compute the factorial of: ";
    //     cin >> factorial;
    //
    // } while (factorial < 0);
    // /* End of istream & ostream overload test */
    //
    // /* Begin of factorial test */
    // /* Tests =,*,+, and += operator overloads */
    // result = factorial;
    // for (int i=factorial-1; i>1; i--) {
    //
    //     result = result * i;
    // }
    //
    // cout << result << endl;
    // /* End of factorial test */
    //
    // /* Begin of += operator overload test */
    // for (int i=0; i<10; i++) {
    //     testNum += i;
    //     cout << testNum << " ";
    // }
    // cout << endl;
    // /* End of += operator overload test */

    return 0;
}
