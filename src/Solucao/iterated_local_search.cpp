#include"iterated_local_search.hpp"
#include"solucao.hpp"
#include"Data.h"
#include<random>


ILS::ILS(int argc,char** argv){
    data = new Data(argc,argv[1]);
    data -> read();
}

vector<Insertion_info> ILS::calcular_custo_insercao(Solucao& s, vector<int>&CL){
    vector<Insertion_info>custo_insercao((s.sequencia.size()-1)*CL.size());
    int l = 0;
    for(int a = 0;a<s.sequencia.size()-1;a++){
        int i = s.sequencia[a];
        int j = s.sequencia[a+1];
        for(int k : CL){
            custo_insercao[l].custo = data->getDistance(i,k) + data->getDistance(j,k) - data->getDistance(i,j);
            custo_insercao[l].no_inserido = k;
            custo_insercao[l].aresta_removida = a;
            l++;
        }
    }
    return custo_insercao;
}



