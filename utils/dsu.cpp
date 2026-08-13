#include<vector>
#include<iostream>


typedef struct Dsu {
    std::vector<int> pais;
    //Heurística de tamanho
    std::vector<int> size;
    Dsu(int n);
    void make_set(int v);
    int find_set(int v);
    void union_set(int a, int b);
} Dsu;

Dsu::Dsu(int n){
    pais.resize(n);
    size.resize(n);
}

void Dsu::make_set(int v){
    pais[v] = v;
    size[v] = 1;
}

//Busca o conjunto com path compression
int Dsu::find_set(int v){
    if(v == pais[v])return v;
    return pais[v] = find_set(pais[v]);
}

void Dsu::union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a != b){
        if(size[a] < size[b]) std::swap(a,b);
        pais[b] = a;
        size[a] += size[b];
    }
}