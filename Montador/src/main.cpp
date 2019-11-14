#include "PreProcessamento.hpp"
#include "MontadorUmaPassada.hpp"
using namespace std;
int main (int argc, char** argv) {
    string NomeArquivo, NomeArquivoPreProcessado, NomeArquivoMontado;
    if (argc < 2){
        cout << "Insira o nome do arquivo a ser usado!" << "\n";
        return 0;
    }   
    NomeArquivo = argv[1];
    NomeArquivoPreProcessado = PreProcessamento(NomeArquivo);
    NomeArquivoMontado = MontadorUmaPassada(NomeArquivoPreProcessado);

    return 0;
}