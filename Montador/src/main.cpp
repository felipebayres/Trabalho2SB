#include "PreProcessamento.hpp"
#include "MontadorUmaPassada.hpp"
using namespace std;
int main (int argc, char** argv) {
    // Flag que indica a presenca de dois arquivos no programa
    bool FlagSegundoArquivo = false;
    string NomeArquivo,NomeSegundoArquivo, NomeArquivoPreProcessado,NomeSegundoArquivoPreProcessado, NomeArquivoMontado;
    string NomeSegundoArquivoMontado;
    // Caso o usuario nao coloque nenhum programa no montador
    if (argc < 2){
        cout << "Insira o nome do arquivo a ser usado!" << "\n";
        return 0;
    }  
    NomeArquivo = argv[1];
    NomeArquivoPreProcessado = PreProcessamento(NomeArquivo,FlagSegundoArquivo);
    // Caso sejam passados dois programas para o montador
    if (argc == 3){
        FlagSegundoArquivo = true;
        NomeSegundoArquivo = argv[2];
        NomeSegundoArquivoPreProcessado = PreProcessamento(NomeSegundoArquivo,FlagSegundoArquivo);
        NomeSegundoArquivoMontado = MontadorUmaPassada(NomeSegundoArquivoPreProcessado,FlagSegundoArquivo);
    } 
    // REVER A INTERACAO COM OS DOIS ARQUIVOS PARA O MONTADOR!!!

    
    NomeArquivoMontado = MontadorUmaPassada(NomeArquivoPreProcessado,FlagSegundoArquivo);

    return 0;
}