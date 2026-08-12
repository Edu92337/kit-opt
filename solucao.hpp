#pragma once
#include<vector>

typedef struct solucao Solucao;

struct solucao{
    std::vector<int>sequencia;
    double valor_obj;
    void exibe_solucao();
    void add_no(double x);
    void calcula_valor_obj();
};


