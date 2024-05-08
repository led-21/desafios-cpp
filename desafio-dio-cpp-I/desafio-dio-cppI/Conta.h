#pragma once
#include <iostream>

#include "DateTime.h"

class Conta
{
private:
    int TipoConta;
    int TipoCliente;
    DateTime DataAbertura;
    long Saldo;

public:
    Conta(int tipoConta, int tipoCliente, long saldo, int y, int m, int d): DataAbertura(y, m, d)
    {
        TipoConta = tipoConta;
        TipoCliente = tipoCliente;
        Saldo = saldo;
    }

    void Sacar(int valorSaque)
    {
        if (Saldo >= valorSaque)
        {
            Saldo -= valorSaque;
            std::cout << "Saldo disponivel: " << Saldo << std::endl;
        }
        else
        {
            std::cout << "A conta nao possui saldo suficiente para o saque" << std::endl;
        }
    }

    void Depositar(int valorDeposito)
    {
        Saldo += valorDeposito;
        std::cout << "Saldo disponivel: " << Saldo << std::endl;
    }

    void CalcularValorTarifaManutenção();
};
