#include <bits/stdc++.h>
#include "ligador.hpp"

using namespace std;

int main (int argc, char** argv) {
    // Para abrir os Dois arquivos modulos
    ifstream ArquivoObjetoUm,ArquivoObjetoDois;
    // Representacoes da tabela de definicoes e da tabela de uso
    map<string,int> TabelaGlobalDefinicoes;
    map<string,TabelaUso> TabelaDeUsoModuloUm,TabelaDeUsoModuloDois;

    vector<string> VetorModuloUm , VetorModuloDois;
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
    string NomeArquivoObjetoFinal = NomeArquivoObjetoUm.substr(0, NomeArquivoObjetoUm.size()-4) + ".fv";
    ofstream ArquivoFinal(NomeArquivoObjetoUm.substr(0, NomeArquivoObjetoUm.size()-4) + ".fv");
    
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
        ArquivoObjetoDois.open(NomeArquivoObjetoDois);
        if (!ArquivoObjetoDois.is_open()){
             cout << "Não foi possível abrir o arquivo " << NomeArquivoObjetoDois << "\n";
            return 0;
        }
    
        //Conta em qual linha do header esta no momento
        int Header = 0,TamanhoProgramaModuloUm,TamanhoProgramaModuloDois;
        int FatorDeCorrecao,FatorDeCorrecaoDois;
        vector<int> VetorDeRelativosUm,VetorDeRelativosDois;
        string NomeProgramaModuloUm,NomeProgramaModuloDois;
        
        //Pega os dados do primeiro arquivo
        while(getline(ArquivoObjetoUm, linha)){
            //cout << linha << endl;
            istringstream buf(linha);
            vector<string> v;
            //Separa todas as palavras da linha e coloca elas em um vector
            for(string palavra; buf >> palavra; ){
                v.push_back(palavra);
            }
            //Capta toda a informacao dos headers
            if(v[0] == "H:" && Header == 0){
                NomeProgramaModuloUm = v[1];
                //cout << NomeProgramaModuloUm << endl;
                Header++;
            }
            else if ( v[0] == "H:" && Header == 1){
                FatorDeCorrecao = stoi(v[1]);
                //cout << FatorDeCorrecao << endl;
                Header++;
            }
            else if (v[0] == "H:" && Header == 2){
                for (int i = 1; i < v.size() ; i++){
                   VetorDeRelativosUm.push_back(stoi(v[i]));
                    //cout << v[i] << " ";
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
            else if(v[0] == "D:"){
                string Label = v[1];
                for (int i = 2 ; i < v.size(); i++){
                    TabelaGlobalDefinicoes[Label] = stoi(v[i]);
                    //cout << Label << "-" << v[i] << endl;
                }
            }
            // Armazena o codigo maquina em um vetor
            if(v[0] == "T:"){
                for (int i = 1; i < v.size() ; i++){
                    VetorModuloUm.push_back((v[i]));
                    //cout << v[i] << " ";
                }
            }
        }




        
        // Pega as informacoes do segundo modulo
        Header = 0;
        while(getline(ArquivoObjetoDois, linha)){
            //cout << linha << endl;
            istringstream buf(linha);
            vector<string> v;
            //Separa todas as palavras da linha e coloca elas em um vector
            for(string palavra; buf >> palavra; ){
                v.push_back(palavra);
            }
            //Capta toda a informacao dos headers
            if(v[0] == "H:" && Header == 0){
                NomeProgramaModuloDois = v[1];
                //cout << NomeProgramaModuloDois << endl;
                Header++;
            }
            else if ( v[0] == "H:" && Header == 1){
                FatorDeCorrecaoDois = stoi(v[1]);
                //cout << FatorDeCorrecaoDois << endl;
                Header++;
            }
            else if (v[0] == "H:" && Header == 2){
                for (int i = 1; i < v.size() ; i++){
                    VetorDeRelativosDois.push_back(stoi(v[i]));
                    //cout << v[i] << " ";
                }
                Header++;
            }
            // Pega todos os dados da tabela de uso
            else if (v[0] == "U:"){
                string Variavel = v[1];
                for (int i = 2 ; i < v.size(); i++){
                    TabelaDeUsoModuloDois[Variavel].LugaresUsados.push_back(stoi(v[i]));
                }
            }
            // Monta a tabela global de definicoes
            else if(v[0] == "D:"){
                string Label = v[1];
                for (int i = 2 ; i < v.size(); i++){
                    TabelaGlobalDefinicoes[Label] = stoi(v[i]) + FatorDeCorrecao;
                    //cout << Label << ":" << TabelaGlobalDefinicoes[Label];
                    //cout << Label << "-" << v[i] << endl;
                }
            }
            // Armazena o codigo maquina em um vetor
            if(v[0] == "T:"){
                for (int i = 1; i < v.size() ; i++){
                    VetorModuloDois.push_back(v[i]);
                    //cout << v[i] << " ";
                }
            }
        }
        //Coloca os valores da tabela global de definicoes na tabela de uso
        for(auto& Simbolo : TabelaDeUsoModuloUm){
            //Procura o valor que o modulo A pegou do modulo B
            if(TabelaGlobalDefinicoes.count(Simbolo.first) == 1){
                auto itr = TabelaGlobalDefinicoes.find(Simbolo.first);
                //cout << Simbolo.first << "-" << itr->second << endl;
                TabelaDeUsoModuloUm[Simbolo.first].Valor = itr->second;
                
            }
        
        }
        //Coloca os valores da tabela global de definicoes na tabela de uso
        for(auto& Simbolo : TabelaDeUsoModuloDois){
            //Procura o valor que o modulo B pegou do modulo A
            if(TabelaGlobalDefinicoes.count(Simbolo.first) == 1){
                auto itr = TabelaGlobalDefinicoes.find(Simbolo.first);
                //cout << Simbolo.first << "-" << itr->second << endl;
                TabelaDeUsoModuloDois[Simbolo.first].Valor = itr->second;   
            }
        }
    
    
    
        ArquivoObjetoDois.close();
        //Substitui o valor das variaveis externas no ModuloUm
        for(auto& Simbolo : TabelaDeUsoModuloUm){
            //Olha todos os lugares que o simbolo foi usado
            for(int i = 0; i < Simbolo.second.LugaresUsados.size();i++){
                //Passa por todo o codigo
                int LugarEncontrado = Simbolo.second.LugaresUsados[i];
                VetorModuloUm[LugarEncontrado] = to_string(Simbolo.second.Valor + stoi(VetorModuloUm[LugarEncontrado]));
            }
        }
        //Guarda todos os lugares em que tiveram uma variavel externa no modulo dois (para que nao se adicione o Fator de correcao)
        vector<int> LugaresMudadosModuloDois;
        for(auto& Simbolo : TabelaDeUsoModuloDois){
            //Olha todos os lugares que o simbolo foi usado
            for(int i = 0; i < Simbolo.second.LugaresUsados.size();i++){
                //Passa por todo o codigo
                int LugarEncontrado = Simbolo.second.LugaresUsados[i];
                VetorModuloDois[LugarEncontrado] = to_string(Simbolo.second.Valor + stoi(VetorModuloDois[LugarEncontrado]));
                LugaresMudadosModuloDois.push_back(LugarEncontrado);
            }
        }
        //Adiciona o fator de correcao nas variaveis do modulo dois ( no modulo um isso foi feito na tabela de definicoes globais)
        int j = 0;
        for (int i = 0; i < VetorDeRelativosDois.size() ; i++){
            sort(LugaresMudadosModuloDois.begin(), LugaresMudadosModuloDois.end());
            int LugarMudado;
            if(j < LugaresMudadosModuloDois.size())
                LugarMudado = LugaresMudadosModuloDois[j];
            int LugarPrecisaMudar = VetorDeRelativosDois[i];
            if(LugarPrecisaMudar != LugarMudado){
                VetorModuloDois[LugarPrecisaMudar] = to_string(stoi(VetorModuloDois[LugarPrecisaMudar]) + FatorDeCorrecao );
            }
            else{
                j++;
            }
        }
        VetorModuloUm.insert( VetorModuloUm.end(), VetorModuloDois.begin(), VetorModuloDois.end() );
        for (int i = 0 ; i < VetorModuloUm.size() ; i++){
            //cout << VetorModuloUm[i] << " ";
            ArquivoFinal << VetorModuloUm[i] << " ";
        }
    }
    
    ArquivoObjetoUm.close();
    ArquivoFinal.close();
    cout << "Gerado arquivo objeto final: " << NomeArquivoObjetoFinal << endl;
    

    return 0;
}