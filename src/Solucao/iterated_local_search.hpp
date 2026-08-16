#pragma once
#include"solucao.hpp"


typedef struct ILS ILS;
struct ILS {
    Data* data;
    ILS(int argc,char** argv);
    float alfa;
    Solucao construcao();
    vector<Insertion_info> calcular_custo_insercao(Solucao& s, vector<int>&CL);
};

typedef struct  Insertion_info Insertion_info;
struct Insertion_info{
    int no_inserido;
    int aresta_removida;
    double custo;
};
