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
    vector<int>CL = nos_restantes(&s);
    while(!CL.empty()){
        vector<Insertion_info> custo_insercao = calcular_custo_insercao(s,CL);
        ordena(custo_insercao);
        alfa = (double) rand()/RAND_MAX;
        int selecionado = rand()%((int)ceil(alfa * custo_insercao.size()));
        s.add_no(custo_insercao[selecionado].no_inserido);
        CL = nos_restantes(&s);
    }
    s.calcula_valor_obj(); // Atualiza o custo dessa solução criada
    return s;
}


bool ILS::best_improvement_swap(Solucao* s){
    double best_delta = 0;
    int best_i, best_j; // Melhores candidatos a troca
    for(int i = 1;i<s->sequencia.size()-1;i++){
        // Itera por todos os pares, comparando o custo novo
        // mantendo os Nós adjacentes
        int vi = s->sequencia[i];
        int vi_next = s->sequencia[i+1];
        int vi_prev = s->sequencia[i-1];
        for(int j = i+1;j<s->sequencia.size()-1;j++){
            int vj = s->sequencia[j];
            int vj_next = s->sequencia[j+1];
            int vj_prev = s->sequencia[j-1];
            double delta = -s->dist(vi_prev,vi) - s->dist(vi,vi_next) + s->dist(vi_prev,vj)
                + s->dist(vj,vi_next) - s->dist(vj_prev,vj) -s->dist(vj,vj_next)
                +s->dist(vj_prev,vi) + s->dist(vi,vj_next);
            
            if(delta < best_delta){
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        
        }
    }
    // Melhor custo novo é menor que o custo anterior 
    // -> indica melhora na solução
    if(best_delta < 0){
        std::swap(s->sequencia[best_i],s->sequencia[best_j]);
        s->valor_obj += best_delta;
        return true;
    }
    return false; // Não achou na vizinhança um vizinho com custo menor
}



