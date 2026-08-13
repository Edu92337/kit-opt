#include<vector>
#include<iostream>
#include<algorithm>
#include"Data.h"

typedef struct Dsu {
    int nos;
    std::vector<int> pais;
    //Heurística de tamanho
    std::vector<int> size;
    Dsu(int n);
    void make_set(int v);
    int find_set(int v);
    void union_set(int a, int b);

    //Minimum spanning tree
    double** mst;
    void gera_mst(Data* d);


} Dsu;

Dsu::Dsu(int n){
    nos = n;
    pais.resize(n);
    size.resize(n);
    // Aloca a Árvore como matriz no mesmo formato de Data
    mst = new double* [n];
    for(int i = 0;i<n;i++){
        mst[i] = new double[n];
        for(int j = 0;j < n;j++) mst[i][j] = 0;
    }
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

//Gera a mst com Kruskal sem ordenar
void Dsu::gera_mst(Data* d){
    for(int i = 0;i<nos;i++) make_set(i);
    int qnt = 0;
    
    while(qnt<nos-1){

        double menor = __DBL_MAX__;
        int u = -1;
        int v = -1;

        for(int i = 0;i<nos;i++){
            for(int j = 0;j<nos;j++){
                if(find_set(i) == find_set(j))continue;
                double distancia = d->getDistance(i,j);

                if(distancia < menor){
                    menor = distancia;
                    u = i;
                    v = j;
                }
            }
        }
        union_set(u,v);
        mst[u][v] = menor;
        mst[v][u] = menor;
        qnt++;
    }
}