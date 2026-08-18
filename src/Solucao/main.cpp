#include"Data.h"
#include"iterated_local_search.hpp"
#include"solucao.hpp"




int main(int arg,char* argv[]){
    if(arg < 2){
        cerr << "Uso: ./a <instancia.tsp>" << endl;
        return 1;
    }
    Data* data = new Data(arg,argv[1]);
    data->read();
    ILS heuristica(data);
    int max_iter = 50;
    int max_iter_ils;
    if(data->getDimension() >= 150){
        max_iter_ils = data->getDimension()/2;
    }else max_iter_ils = data->getDimension();
    Solucao s = heuristica.solver(max_iter,max_iter_ils);
    cout <<s.valor_obj<<endl;


    return 0;
}