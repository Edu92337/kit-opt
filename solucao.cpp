#include<iostream>
#include<vector>
#include"solucao.hpp"



void Solucao::exibe_solucao(){
    for(int i = 0;i<Solucao::sequencia.size();i++){
        std::cout<<Solucao::sequencia[i]<<" -> ";
    } std::cout<<'\n';
}

void Solucao::add_no(double x){
    Solucao::sequencia.push_back(x);
}

void Solucao::calcula_valor_obj(){
    Solucao::valor_obj = 0;
    for(int i = 0;i<Solucao::sequencia.size();i++){
        // incrementa o custo de ir da cidade atual (i) para a proxima da sequencia (i + 1)
        Solucao::valor_obj += matrizadj[Solucao::sequencia[i]][Solucao::sequencia[i+1]];
    }
}