#pragma once
#include"Data.h"
#include<vector>

typedef struct Solucao Solucao;

struct Solucao {
    Solucao(Data *data_original);
    Data* data;
    std::vector<int>sequencia;
    double valor_obj;
    void exibe_solucao();
    void add_no(double x);
    void calcula_valor_obj();
};


