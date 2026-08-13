#include<iostream>
#include<vector>
#include"solucao.hpp"

Solucao::Solucao(int argc, char* argv[]) : Data(argc, argv[1]){
    valor_obj = 0;
}

void Solucao::exibe_solucao(){
    for(int i = 0;i<sequencia.size();i++){
        std::cout<<sequencia[i]<<" -> ";
    } std::cout<<'\n';
}

void Solucao::add_no(double x){
    sequencia.push_back(x);
}

void Solucao::calcula_valor_obj(){
    Solucao::valor_obj = 0;
    for(int i = 0;i<Solucao::sequencia.size()-1;i++){
        // incrementa o custo de ir da cidade atual (i) para a proxima da sequencia (i + 1)
        Solucao::valor_obj += getDistance(sequencia[i],sequencia[i+1]);
    }
}