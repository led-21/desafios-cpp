#pragma once
#include "Conta.h"

class ContaPoupanca : public Conta
{
public:
    ContaPoupanca(int tipoConta, int tipoCliente, long saldo, int y, int m, int d): Conta(tipoConta, tipoCliente,
        saldo, y, m, d)
    {
        std::cout << "Conta poupança criada" << std::endl;
    }
    
    void CalcularValorTarifaManutenção()
    {
        std::cout<<"Valor tarifa poupança: 10"<<std::endl;
    }
};
