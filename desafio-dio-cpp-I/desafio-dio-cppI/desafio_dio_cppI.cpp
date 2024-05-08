#include "main.h"

#include <iostream>

#include "Conta.h"
#include "ContaInvestimento.h"
#include "ContaPoupanca.h"

using namespace std;

int main()
{
    ContaInvestimento conta_investimento(1,1,2500,20,5,1999);
    ContaPoupanca conta_poupanca(1,1,2500,20,5,1999);
    
    cout<<"-----------------------------------"<<endl;
    cout<<"CONTA INVESTIMENTO"<<endl;
    conta_investimento.CalcularValorTarifaManutenção();
    conta_investimento.Depositar(30);
    conta_investimento.Sacar(800);
    cout<<"-----------------------------------"<<endl;
    cout<<"CONTA POUPANCA"<<endl;
    conta_poupanca.CalcularValorTarifaManutenção();
    conta_poupanca.Sacar(3000);
    cout<<"-----------------------------------"<<endl;
    
    return 0;
}