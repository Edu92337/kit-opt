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

/*
Solução inicial :[1,7,6,4,10,3,9,2,8,5,1]
Solução final   :[1,9,3,10,4,6,7,2,8,5,1]

->[9,3,10,4,6,7] foi invertido
*/
bool ILS::best_improvement_2_opt(Solucao* s){
    double best_delta = 0;
    int best_i, best_j;
    for(int i = 1;i<s->sequencia.size();i++){
        int vi = s->sequencia[i];
        int vi_prev = s->sequencia[i-1];
        for(int j = i+2;j<s->sequencia.size()-1;j++){
            //if(j == i+1 || j == i-1)continue;
            int vj = s->sequencia[j];
            int vj_prev = s->sequencia[j-1];
            double delta = -s->dist(vi,vi_prev) - s->dist(vj,vj_prev) 
            + s->dist(vi,vj_prev) + s->dist(vj,vi_prev);

            if(delta < best_delta){
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(best_delta < 0){
        // intervalo [i,j+1) -> [i,j]
        reverse(s->sequencia.begin()+best_i,s->sequencia.begin()+best_j + 1); 
        return true;
    }return false;
}


void ILS::busca_local(Solucao* s){
    // Vai buscar uma solução melhor na vizinhaça de um dos 
    // 5 métodos apresentados (swap,2-opt,or-opt,reinsertion,or-opt2)
    // Escolhido de forma aleatória
    std::vector<int>NL ={1,2,3,4,5};
    bool improved = false;

    while(!NL.empty()){
        int n = rand() % NL.size();
        switch(NL[n]){
            case 1:
                improved = best_improvement_swap(s);
                break;
            case 2:
                improved = best_improvement_2_opt(s);
                break;
            case 3:
                improved = best_improvement_or_opt(s,1);
                break;
            case 4:
                improved = best_improvement_or_opt(s,2);
                break;
            case 5:
                improved = best_improvement_or_opt(s,3);
                break;
        }
        //Se melhorou,mantém todas para tentar novamente até não ser possível mais melhorar
        if(improved) NL = {1,2,3,4,5}; 
        else NL.erase(NL.begin()+n); // remove essa vizinhança
    }
}



