#pragma once
#include "Conta.h"

class ContaInvestimento : public Conta
{
public:
    ContaInvestimento(int tipoConta, int tipoCliente, long saldo, int y, int m, int d): Conta(tipoConta, tipoCliente,
        saldo, y, m, d)
    {
        std::cout << "Conta investimento criada" << std::endl;
    }

    void CalcularValorTarifaManutenção()
    {
        std::cout << "Valor tarifa investimento: 10" << std::endl;
    }
};
