//------------------------------------------------
//               Ch07_01.cpp
//------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <string>
#include "XmmVal.h"

using namespace std;

extern "C" void AvxPackedAddI16_(const XmmVal& a, const XmmVal& b, XmmVal c[2]);
extern "C" void AvxPackedSubI16_(const XmmVal& a, const XmmVal& b, XmmVal c[2]);
extern "C" void AvxPackedAddU16_(const XmmVal& a, const XmmVal& b, XmmVal c[2]);
extern "C" void AvxPackedSubU16_(const XmmVal& a, const XmmVal& b, XmmVal c[2]);

//
// Signed packed addition and subtraction
//

void AvxPackedAddI16(void)
{
    alignas(16) XmmVal a;
    alignas(16) XmmVal b;
    alignas(16) XmmVal c[2];

    a.m_I16[0] = 10;          b.m_I16[0] = 100;
    a.m_I16[1] = 200;         b.m_I16[1] = -200;
    a.m_I16[2] = 30;          b.m_I16[2] = 32760;
    a.m_I16[3] = -32766;      b.m_I16[3] = -400;
    a.m_I16[4] = 50;          b.m_I16[4] = 500;
    a.m_I16[5] = 60;          b.m_I16[5] = -600;
    a.m_I16[6] = 32000;       b.m_I16[6] = 1200;
    a.m_I16[7] = -32000;      b.m_I16[7] = -950;

    AvxPackedAddI16_(a, b, c);

    cout << "\nResults for AxvPackedAddI16 - Wraparound Addition\n";
    cout << "a:     " << a.ToStringI16() << '\n';
    cout << "b:     " << b.ToStringI16() << '\n';
    cout << "c[0]:  " << c[0].ToStringI16() << '\n';
    cout << "\nResults for AxvPackedAddI16 - Saturated Addition\n";
    cout << "a:     " << a.ToStringI16() << '\n';
    cout << "b:     " << b.ToStringI16() << '\n';
    cout << "c[1]:  " << c[1].ToStringI16() << '\n';
}

void AvxPackedSubI16(void)
{
    alignas(16) XmmVal a;
    alignas(16) XmmVal b;
    alignas(16) XmmVal c[2];

    a.m_I16[0] = 10;          b.m_I16[0] = 100;
    a.m_I16[1] = 200;         b.m_I16[1] = -200;
    a.m_I16[2] = -30;         b.m_I16[2] = 32760;
    a.m_I16[3] = -32766;      b.m_I16[3] = 400;
    a.m_I16[4] = 50;          b.m_I16[4] = 500;
    a.m_I16[5] = 60;          b.m_I16[5] = -600;
    a.m_I16[6] = 32000;       b.m_I16[6] = 1200;
    a.m_I16[7] = -32000;      b.m_I16[7] = 950;

    AvxPackedSubI16_(a, b, c);

    cout << "\nResults for AxvPackedSubI16 - Wraparound Subtraction\n";
    cout << "a:     " << a.ToStringI16() << '\n';
    cout << "b:     " << b.ToStringI16() << '\n';
    cout << "c[0]:  " << c[0].ToStringI16() << '\n';
    cout << "\nResults for AxvPackedSubI16 - Saturated Subtraction\n";
    cout << "a:     " << a.ToStringI16() << '\n';
    cout << "b:     " << b.ToStringI16() << '\n';
    cout << "c[1]:  " << c[1].ToStringI16() << '\n';
}

//
// Unsigned packed addition and subtraction
//

void AvxPackedAddU16(void)
{
    XmmVal a;
    XmmVal b;
    XmmVal c[2];

    a.m_U16[0] = 10;          b.m_U16[0] = 100;
    a.m_U16[1] = 200;         b.m_U16[1] = 200;
    a.m_U16[2] = 300;         b.m_U16[2] = 65530;
    a.m_U16[3] = 32766;       b.m_U16[3] = 40000;
    a.m_U16[4] = 50;          b.m_U16[4] = 500;
    a.m_U16[5] = 20000;       b.m_U16[5] = 25000;
    a.m_U16[6] = 32000;       b.m_U16[6] = 1200;
    a.m_U16[7] = 32000;       b.m_U16[7] = 50000;

    AvxPackedAddU16_(a, b, c);

    cout << "\nResults for AxvPackedAddU16 - Wraparound Addition\n";
    cout << "a:     " << a.ToStringU16() << '\n';
    cout << "b:     " << b.ToStringU16() << '\n';
    cout << "c[0]:  " << c[0].ToStringU16() << '\n';
    cout << "\nResults for AxvPackedAddU16 - Saturated Addition\n";
    cout << "a:     " << a.ToStringU16() << '\n';
    cout << "b:     " << b.ToStringU16() << '\n';
    cout << "c[1]:  " << c[1].ToStringU16() << '\n';
}

void AvxPackedSubU16(void)
{
    XmmVal a;
    XmmVal b;
    XmmVal c[2];

    a.m_U16[0] = 10;          b.m_U16[0] = 100;
    a.m_U16[1] = 200;         b.m_U16[1] = 200;
    a.m_U16[2] = 30;          b.m_U16[2] = 7;
    a.m_U16[3] = 65000;       b.m_U16[3] = 5000;
    a.m_U16[4] = 60;          b.m_U16[4] = 500;
    a.m_U16[5] = 25000;       b.m_U16[5] = 28000;
    a.m_U16[6] = 32000;       b.m_U16[6] = 1200;
    a.m_U16[7] = 1200;        b.m_U16[7] = 950;

    AvxPackedSubU16_(a, b, c);

    cout << "\nResults for AxvPackedSubU16 - Wraparound Subtraction\n";
    cout << "a:     " << a.ToStringU16() << '\n';
    cout << "b:     " << b.ToStringU16() << '\n';
    cout << "c[0]:  " << c[0].ToStringU16() << '\n';
    cout << "\nResults for AxvPackedSubI16 - Saturated Subtraction\n";
    cout << "a:     " << a.ToStringU16() << '\n';
    cout << "b:     " << b.ToStringU16() << '\n';
    cout << "c[1]:  " << c[1].ToStringU16() << '\n';
}

int main()
{
    string sep(75, '-');

    AvxPackedAddI16();
    AvxPackedSubI16();
    cout << '\n' << sep << '\n';
    AvxPackedAddU16();
    AvxPackedSubU16();
    return 0;
}
