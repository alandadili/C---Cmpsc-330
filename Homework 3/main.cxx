//THIS FILE IS NOT CREATED BY ME. I HAVE ONLY ADDED THE HEADER COMMENTS AND MY OWN TEST CASES AT THE BOTTOM OF THE MAIN FUNCTION
//---------------------------------------------------------------------
// Name: Aland Adili
// Email: ava6698@psu.edu
// Class: CMPSC 330
// Homework 3
// Due Date: November 14, 2025
//
// Description: This program implements the ExactNumber class, 
// which represents rational numbers (fractions) with exact precision, 
// avoiding the rounding errors inherent in floating-point arithmetic.
//
// Acknowledgement:
// 1. Consulted with students in Sunlab
// 2. Utilized copilot to help with assisting with directory to compile and run the exe file 
// 3. Utilized copilot to help with comments
// 4. Utilized copilot to help with indentation
// 5. Utilized stack overflow to understand why it wasnt compiling/creating an exe file
//---------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>
#include <string>
#include "exact_number.h"


using namespace std;


string error_msg(string rand, ExactNumber& n, double ans)
{
    ostringstream msg;
    msg << "  " << rand << " failed with " << static_cast<double>(n) << "... expecting " << ans;
    return msg.str();
}

string error_msg(string rand, ExactNumber& n1, ExactNumber& n2, bool ans)
{
    ostringstream msg;
    msg << "  " << rand << " failed with " << ans << "... expecting " << !ans
        << " => " << n1 << " : " << n2 << endl;
    return msg.str();
}


int main()
{
    cout << "Testing ExactNumber..." << endl << endl;

    cout << "Manual check:";
    cout << "   operator<<   should print an ExactNumber as \"(a/b)\"" << endl;

    ExactNumber e1;    // default constructor
    cout << "  manual check for (0/1) : " << e1 << endl;

    ExactNumber e2(3);  // memberwise-copy constructor
    cout << "  manual check for (3/1) : " << e2 << endl;

    ExactNumber e3(5, 2);  // memberwise-copy constructor
    cout << "  manual check for (5/2) : " << e3 << endl;

    ExactNumber e4(e3);   // copy constructor
    cout << "  manual check for (5/2) : " << e4 << endl;

    ExactNumber e5(10, 5);  // simplification
    cout << "  manual check for (2/1) : " << e5 << endl;



    cout << endl;
    cout << "Automatic check" << endl;
    cout.precision(numeric_limits<double>::digits10);

    unsigned int num_tests = 0;
    unsigned int num_failed = 0;

    ExactNumber n1(2, 4), n2(5, 3), n3(5, 6), n4;

    // =
    num_tests++;
    n4 = n1;
    try { if (static_cast<double>(n4) != 1.0/2.0) throw error_msg("operator=", n4, 1.0/2.0); }
    catch(string m) { cout << m << endl; num_failed++; }

    // +=, -=, *=, /=
    num_tests++;
    n4 += n2;
    try { if (static_cast<double>(n4) != 13.0/6.0) throw error_msg("opeator=", n4, 13.0/6.0); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 -= n2;
    try { if (static_cast<double>(n4) != 1.0/2.0) throw error_msg("operator-=", n4, 1.0/2.0); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 *= n2;
    try { if (static_cast<double>(n4) != 5.0/6.0) throw error_msg("operator*=", n4, 5.0/6.0); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 /= n2;
    try { if (static_cast<double>(n4) != 1.0/2.0) throw error_msg("operator/=", n4, 1.0/2.0); }
    catch(string m) { cout << m << endl; num_failed++; }


    // +, -, *, /
    num_tests++;
    n4 = n1 + n2;
    try { if (static_cast<double>(n4) != 13.0/6.0) throw error_msg("operator+", n4, 13.0/6.0); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 = n1 - n2;
    try { if (static_cast<double>(n4) != -7.0/6.0) throw error_msg("operator-", n4, -7.0/6.0); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 = n1 * n2;
    try { if (static_cast<double>(n4) != 5.0/6.0) throw error_msg("operator*", n4, 5.0/6.0); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 = n1 / n2;
    try { if (static_cast<double>(n4) != 3.0/10.0) throw error_msg("operator/", n4, 3.0/10.0); }
    catch(string m) { cout << m << endl; num_failed++; }

    // ==, !=
    num_tests++;
    n4 = n1 * n2;
    bool result = n4 == n3;
    try { if (result != true) throw error_msg("operator==", n4, n3, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    result = n1 == n2;
    try { if(result != false) throw error_msg("operator==", n4, n1, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    result = n1 != n2;
    try { if (result != true) throw error_msg("operator!=", n1, n2, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    result = n4 != n3;
    try { if(result != false) throw error_msg("operator!=", n1, n2, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    // <, >, <=, >=
    num_tests++;
    result = n1 < n2;
    try { if (result != true) throw error_msg("operator<", n1, n2, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    result = n2 > n3;
    try { if (result != true) throw error_msg("operator>", n2, n3, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    result = n1 <= n2;
    try { if (result != true) throw error_msg("operator<=", n1, n2, result); }
    catch(string m) { cout << m << endl; num_failed++; }


    num_tests++;
    result = n2 <= n2;
    try { if (result != true) throw error_msg("operator<=", n2, n2, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    result = n2 >= n3;
    try { if (result != true) throw error_msg("operator>=", n2, n3, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    result = n2 >= n2;
    try { if (result != true) throw error_msg("operator>=", n2, n2, result); }
    catch(string m) { cout << m << endl; num_failed++; }

    // combination
    num_tests++;
    n4 = (n1 - n2) * n3 + n1;
    try {
        if (static_cast<double>(n4) != ExactNumber(-17, 36))
            throw error_msg("(n1 - n2) * n3 + n1", n4, -17.0/36.0);
    }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 = n1 * n1 / n1 / n1;
    try {
        if (static_cast<double>(n4) != ExactNumber(1, 1))
            throw error_msg("n1 * n1 / n1 / n1", n4, 1.0/1.0);
    }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 = n1 * n3 / n2 + n3 / n1 * n2;
    try {
        if (static_cast<double>(n4) != ExactNumber(109, 36))
            throw error_msg("n1 * n3 / n2 + n3 / n1 * n2", n4, 109.0/36.0);
    }
    catch(string m) { cout << m << endl; num_failed++; }

    num_tests++;
    n4 = (n1 + n2) / (n3 * (n1 - n2) / (n3 + n1 * n2));
    try {
        if(static_cast<double>(n4) != ExactNumber(-26, 7))
            throw error_msg("(n1 + n2) / (n3 * (n1 - n2) / (n3 + n1 * n2))", n4, -26.0/7.0);
    }
    catch(string m) { cout << m << endl; num_failed++; }

    // operator* involving 0
    ExactNumber n5(11, 3), n6(0, 5);
    num_tests++;
    n4 = n5 * n6;
    try {
        if (static_cast<double>(n4) != ExactNumber(0, 1))
            throw error_msg("operator* involving 0", n4, 0.0/1.0);
    }
    catch(string m) { cout << m << endl; num_failed++; }

    // operator/ involving 0
    num_tests++;
    n4 = n5 / n6;
    try {
        if(static_cast<double>(n4) != ExactNumber(1, 0))
            throw error_msg("operator/ involving 0", n4, 0.0/1.0);
    }
    catch(string m) { cout << m << endl; num_failed++; }

    /* Do not modify the code below */

    if (num_failed == 0)
        cout << "passed all " << num_tests << " default test cases" << endl;
    else
        cout << "failed " << num_failed << " default test cases out of " << num_tests << " default test cases" << endl;
    cout << endl;


    /********************************************************/
    /*                                                      */
    /*              add your test cases here                */
    /*                                                      */
    /********************************************************/









    // ---- 20 Custom Test Cases ----
    unsigned int extra_tests = 0, extra_failed = 0;
    auto expectEq = [&](const string &label, const ExactNumber &got, const ExactNumber &exp) {
        extra_tests++;
        if (got != exp) {
            cout << "  [FAIL] " << label << ": got " << got << " expected " << exp << endl;
            extra_failed++;
        }
    };
    auto expectTrue = [&](const string &label, bool cond) {
        extra_tests++;
        if (!cond) {
            cout << "  [FAIL] " << label << " expected true" << endl;
            extra_failed++;
        }
    };
    auto expectNear = [&](const string &label, double val, double exp, double eps = 1e-12) {
        extra_tests++;
        if (fabs(val - exp) > eps) {
            cout << "  [FAIL] " << label << " got " << val << " expected ~" << exp << endl;
            extra_failed++;
        }
    };

    // 1 Simplification large numbers
    expectEq("simplify large", ExactNumber(100,250), ExactNumber(2,5));
    // 2 Negative numerator & denominator -> positive
    expectEq("neg/neg positive", ExactNumber(-6,-8), ExactNumber(3,4));
    // 3 Addition producing simplification
    expectEq("add simplify", ExactNumber(1,4)+ExactNumber(3,8), ExactNumber(5,8));
    // 4 Subtraction to zero
    expectEq("sub to zero", ExactNumber(7,9)-ExactNumber(7,9), ExactNumber(0,1));
    // 5 Multiplication with zero numerator
    expectEq("mul zero", ExactNumber(0,3)*ExactNumber(9,11), ExactNumber(0,1));
    // 6 Division by zero gives +inf
    expectEq("div by zero +inf", ExactNumber(5,7)/ExactNumber(0,2), ExactNumber(1,0));
    // 7 Division by zero negative gives -inf
    expectEq("div by zero -inf", ExactNumber(-3,7)/ExactNumber(0,5), ExactNumber(-1,0));
    // 8 +inf + -inf -> 0/1 (implementation choice)
    expectEq("inf + -inf", ExactNumber(1,0)+ExactNumber(-1,0), ExactNumber(0,1));
    // 9 Infinite plus finite stays infinite
    expectEq("inf + finite", ExactNumber(1,0)+ExactNumber(2,3), ExactNumber(1,0));
    // 10 Multiplication chain
    expectEq("mul chain", ExactNumber(2,3)*ExactNumber(9,4)*ExactNumber(4,3), ExactNumber(2,1));
    // 11 Division chain
    expectEq("div chain", (ExactNumber(3,5)/ExactNumber(9,10))/ExactNumber(1,2), ExactNumber(4,3));
    // 12 Associativity of addition
    expectEq("assoc add", (ExactNumber(1,6)+ExactNumber(1,3))+ExactNumber(1,2), ExactNumber(1,6)+ (ExactNumber(1,3)+ExactNumber(1,2)) );
    // 13 Commutativity of multiplication
    expectEq("comm mul", ExactNumber(5,7)*ExactNumber(3,11), ExactNumber(3,11)*ExactNumber(5,7));
    // 14 Comparison less-than
    expectTrue("compare <", ExactNumber(1,3) < ExactNumber(2,5));
    // 15 Infinity greater than large finite
    expectTrue("inf > finite", ExactNumber(1,0) > ExactNumber(999999,1));
    // 16 Approximate conversion to double for 1/7
    expectNear("double convert", static_cast<double>(ExactNumber(1,7)), 1.0/7.0);
    // 17 Expression equivalence
    expectEq("expr equiv", (ExactNumber(2,4)+ExactNumber(3,9)), ExactNumber(5,6));
    // 18 -inf * -3 -> +inf
    expectEq("-inf * -3", ExactNumber(-1,0)*ExactNumber(-3,1), ExactNumber(1,0));
    // 19 Finite / infinity -> 0/1
    expectEq("finite / inf", ExactNumber(7,5)/ExactNumber(1,0), ExactNumber(0,1));
    // 20 Zero divided by non-zero -> 0/1
    expectEq("0 / finite", ExactNumber(0,4)/ExactNumber(5,7), ExactNumber(0,1));

    if (extra_failed == 0)
        cout << "passed all " << extra_tests << " custom test cases" << endl;
    else
        cout << "failed " << extra_failed << " custom test cases out of " << extra_tests << endl;
    cout << endl;

    return 0;
}
