#include "Simulador.hpp"
using namespace std;
int main (int argc, char** argv) {
    string NomeArquivo;
    if (argc < 2){
        cout << "Insira o nome do arquivo a ser usado!" << "\n";
        return 0;
    }   
    NomeArquivo = argv[1];
    Simulador(NomeArquivo);

    return 0;
}