#include"Data.h"
#include"iterated_local_search.hpp"
#include"solucao.hpp"
#include <chrono>



int main(int arg,char* argv[]){
    if(arg < 2){
        cerr << "Uso: ./a <instancia.tsp>" << endl;
        return 1;
    }
    Data* data = new Data(arg,argv[1]);
    data->read();
    //std::cout << "Instância: " << data->getInstanceName() << std::endl;
    //std::cout << "Dimensão: " << data->getDimension() << std::endl;
    ILS heuristica(data);
    int max_iter = 50;
    int max_iter_ils;
    if(data->getDimension() >= 150){
        max_iter_ils = data->getDimension()/2;
    }else max_iter_ils = data->getDimension();
    //Solucao s = heuristica.construcao();

    auto inicio = std::chrono::high_resolution_clock::now();
    Solucao s = heuristica.solver(max_iter,max_iter_ils);
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = fim - inicio;
    std::cout << "Tempo: " << tempo.count() << " segundos\n";
    std::cout <<"Custo: "<<s.valor_obj<<std::endl;


    return 0;
}