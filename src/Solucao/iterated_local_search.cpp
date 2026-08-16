#include"iterated_local_search.hpp"
#include"solucao.hpp"
#include"Data.h"
#include"auxiliares.hpp"
#include<random>



ILS::ILS(Data* data_original){
    data = data_original;
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

Solucao ILS::construcao(){
    Solucao s(data); // Recebe o mesmo ponteiro de data que a solução
    s.sequencia = tres_nos_aleatorios(s);
    vector<int>CL = nos_restantes(s);
    while(!CL.empty()){
        vector<Insertion_info> custo_insercao = calcular_custo_insercao(s,CL);
        ordena(custo_insercao);
        alfa = (double) rand()/RAND_MAX;
        int selecionado = rand()%((int)ceil(alfa * custo_insercao.size()));
        s.add_no(custo_insercao[selecionado].no_inserido);
        CL = nos_restantes(s);
    }
    return s;
}



