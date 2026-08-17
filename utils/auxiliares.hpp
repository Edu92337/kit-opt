#pragma once
#include<random>
#include<vector>
#include<algorithm>
#include"solucao.hpp"


void ordena(vector<Insertion_info>&custo_insercao){
    sort(custo_insercao.begin(),custo_insercao.end(),
        [](Insertion_info a,Insertion_info b){
            return a.custo < b.custo; // ordem crescente
    });
}

vector<int> tres_nos_aleatorios(Solucao s){
    int n = s.data->getDimension();
    int no1,no2,no3;
    no1 = 1 + rand() % n;
    no2 = 1 + rand() % n;
    while(no2 == no1) no2 = 1 + rand() % n;
    no3 = 1 + rand() % n;
    while(no3 == no2 || no3 == no1) no3 = 1 + rand() % n;
    return {no1,no2,no3};
}

vector<int> nos_restantes(Solucao* s){
    vector<int>restantes;
    for(int i = 1;i<=s->data->getDimension();i++){
        if(count(s->sequencia.begin(),s->sequencia.end(),i) == 0)restantes.push_back(i);
    }return restantes;
}