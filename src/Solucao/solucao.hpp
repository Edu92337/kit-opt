#pragma once
#include"Data.h"
#include<vector>

typedef struct Solucao Solucao;

struct Solucao : public Data{
    Solucao(int argc,char* argv[]);
    std::vector<int>sequencia;
    double valor_obj;
    void exibe_solucao();
    void add_no(double x);
    void calcula_valor_obj();
};


