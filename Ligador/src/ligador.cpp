#include <bits/stdc++.h>
#include "ligador.hpp"

using namespace std;

int main (int argc, char** argv) {
    // Para abrir os Dois arquivos modulos
    ifstream ArquivoObjetoUm,ArquivoObjetoDois;
    // Representacoes da tabela de definicoes e da tabela de uso
    map<string,int> TabelaGlobalDefinicoes;
    map<string,TabelaUso> TabelaDeUsoModuloUm,TabelaDeUsoModuloDois;

    vector<int> VetorModuloUm , VetorModuloDois;
    string NomeArquivoObjetoUm,NomeArquivoObjetoDois;

    string linha;
    bool FlagSegundoArquivo = false;

    // Caso o ligador seja chamado sem argumentos 
    if (argc < 2){
        cout << "Insira o nome do arquivo a ser usado!" << "\n";
        return 0;
    }  
    // Nome do primeiro arquivo objeto
    NomeArquivoObjetoUm = argv[1];
    ofstream ArquivoFinal(NomeArquivoObjetoUm + "1");
    
    // Caso tenham dois arquivos de entrada
    if (argc == 3){
        FlagSegundoArquivo = true;
        NomeArquivoObjetoDois = argv[2];
    }
    // Abre o primeiro arquivo objeto
    ArquivoObjetoUm.open(NomeArquivoObjetoUm);
    if (!ArquivoObjetoUm.is_open()){
        cout << "Não foi possível abrir o arquivo " << NomeArquivoObjetoUm << "\n";
        return 0;
    }
    // Caso só tenha um arquivo objeto
    if (FlagSegundoArquivo == false){
        while(getline(ArquivoObjetoUm, linha)){
            //cout << linha << endl;
            istringstream buf(linha),aux(linha);
            vector<string> v;
            //Separa todas as palavras da linha e coloca elas em um vector
            for(string palavra; buf >> palavra; ){
                v.push_back(palavra);
            }
            //Procura a linha que possui o código
            if(v[0] == "T:"){
                for (int i = 1; i < v.size() ; i++)
                    ArquivoFinal << v[i] << " ";


            }
        }
    }
    //Caso sejam dois arquivos objetos
    else{
        //Conta em qual linha do header esta no momento
        int Header = 0,TamanhoProgramaModuloUm,TamanhoProgramaModuloDois;
        int FatorDeCorrecao;
        vector<int> VetorDeRelativos;
        string NomeProgramaModuloUm,NomeProgramaModuloDois;
        while(getline(ArquivoObjetoUm, linha)){
            //cout << linha << endl;
            istringstream buf(linha),aux(linha);
            vector<string> v;
            //Separa todas as palavras da linha e coloca elas em um vector
            for(string palavra; buf >> palavra; ){
                v.push_back(palavra);
            }
            //Capta toda a informacao dos headers
            if(v[0] == "H:" && Header == 0){
                NomeProgramaModuloUm = v[1];
                cout << NomeProgramaModuloUm << endl;
                Header++;
            }
            else if ( v[0] == "H:" && Header == 1){
                FatorDeCorrecao = stoi(v[1]);
                cout << FatorDeCorrecao << endl;
                Header++;
            }
            else if (v[0] == "H:" && Header == 2){
                for (int i = 1; i < v.size() ; i++){
                    VetorDeRelativos.push_back(stoi(v[i]));
                    cout << v[i] << " ";
                }
                Header++;
            }
            // Pega todos os dados da tabela de uso
            else if (v[0] == "U:"){
                string Variavel = v[1];
                for (int i = 2 ; i < v.size(); i++){
                    TabelaDeUsoModuloUm[Variavel].LugaresUsados.push_back(stoi(v[i]));
                }
            }
            // Monta a tabela global de definicoes
            else if(v[0] == "D"){
                string Label = v[1];
                for (int i = 2 ; i < v.size(); i++){
                    TabelaGlobalDefinicoes[Label] = stoi(v[2]);
                }
            }
            // Armazena o codigo maquina em um vetor
            if(v[0] == "T:"){
                for (int i = 1; i < v.size() ; i++)
                    VetorModuloUm.push_back(stoi(v[i]));
            }
        }


    }
    ArquivoObjetoUm.close();
    ArquivoFinal.close();
    return 0;
}