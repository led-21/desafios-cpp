// CalculadoraTutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <bitset>
#include "Calculator.h"

using namespace std;

int main()
{
    double x = 0.0;
    double y = 0.0;
    double result = 0.0;
    char oper = '+';


    std::cout << "Calculadora" << std::endl << std::endl;
    std::cout << "Por favor entre com a operacao. Formato: a+b | a-b | a*b | a/b"
        << std::endl;

    Calculator c;

    while (true)
    {
        cin >> x >> oper >> y;
        if (oper == '/' && y == 0)
        {
            cout << "Division by 0 exception" << endl;
            continue;
        }
        else 
        {
            result = c.Calculate(x, oper, y);
            cout << "Resultado em decimal: "<<result<< endl;
            cout << "Resultado em binario: " << bitset<32>(result).to_string() << endl;
            cout << "Resultado em hexadecimal: 0x" << hex << (int)result << endl;
            cout << "Resultado em octal: " << oct << (int)result << endl;
        }
    }
    return 0;

 }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
