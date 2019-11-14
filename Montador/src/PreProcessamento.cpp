#include <bits/stdc++.h>
#include "PreProcessamento.hpp"

using namespace std;
map <string,int> MapaEQU;

string PreProcessamento(string NomeArquivo){
    string NomeArquivoPreProcessado;
    ifstream Arquivo;
    Arquivo.open(NomeArquivo);
    string linha,Aux,Aux2;
    // É uma flag que se estiver false ela nao imprime a linha no .txt
    bool FlagIF = true;
    NomeArquivoPreProcessado = NomeArquivo.substr(0, NomeArquivo.size()-4) + ".pre";
    ofstream ArquivoPreProcessado(NomeArquivoPreProcessado);

    if(!ArquivoPreProcessado.is_open()){
        cout << "Não foi possivel gerar o arquivo pre-processado " << "\n";
        return "";

    }
    
    
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo " << NomeArquivo << "\n";
        return "";
    }
    int ContadorLinhas = 0;
    while(getline(Arquivo, linha)){
        ContadorLinhas++;
        linha = TransformaMaiusculo(linha);
        linha = RetiraComentarios(linha);
        linha = RetiraEspacos(linha);
        
        // Verifica se há um rotulo com \n no código
        if (linha.back() == ':'){
            istringstream iss(linha);
            iss >> Aux;
            if(linha.size() == Aux.size()){
                getline(Arquivo,Aux2);
                Aux2 = RetiraEspacos(Aux2);
                Aux2 = RetiraComentarios(Aux2);
                linha = Aux + " " + Aux2;

            }
        }

        // Flag que decidira se a proxima linha do if ira ser escrita
        if(!FlagIF){
            linha = "";
            FlagIF = true;
        }
        //Verifica se a linha é uma diretiva EQU
        if (VerificaDiretiva(linha) == 1){
            DiretivasEQU(linha);
            linha = "";
        }
        // Verifica se a linha é uma diretiva IF
        else if (VerificaDiretiva(linha) == 2){
            //Se for pra retirar a proxima linha
            if (!DiretivasIF(linha))
                FlagIF = false;
            linha = "";
        }
        if(!linha.empty())
            ArquivoPreProcessado << linha << endl;
    
    }
    ArquivoPreProcessado.close();
    Arquivo.close();
    return NomeArquivoPreProcessado;
}

// Funcao que retira os comentarios do código e retira as tabulacoes do comeco do codigo
string RetiraComentarios(string linha){
    int i = 0,posicao = 0,AchouComentario = 0,QuantidadeApagar = 0;
    
    while(i < linha.size()){
        if(linha[i] == ';'){
            posicao = i;
            AchouComentario = 1;
            break;
        }
        i++;
    }
    QuantidadeApagar = linha.size() - posicao;
    if (AchouComentario == 1){
        linha.erase(posicao,QuantidadeApagar);
        
        
    }
    i = 0;
    while(i < linha.size()){
            if(isspace(linha[i])){
                linha.erase(i,1);
            }
            else
            {
                    break;
            }
            
    }
    return linha;
}
// Verifica se a linha de código é uma diretiva 
// 1 - Diretiva EQU
// 2 - Diretiva IF
int VerificaDiretiva(string linha){
    string palavra;
    istringstream iss(linha);

   while(iss){
      string Palavra;
      iss >> Palavra;
        if(Palavra.compare("EQU") == 0){
            return 1;
        }
        else if (Palavra.compare("IF") == 0){
            return 2;
        }
    }
    return 0;
}
//Armazena o valores dos label em um dicionario (map)
void DiretivasEQU(string linha){
    
    int Flag = 0,FlagLabel = 0;
    string palavra,Label;
    istringstream iss(linha);

    while(iss){
        int numero;
        string Palavra;
        iss >> Palavra;

        // A primeira palavra da diretiva é o label
        if(FlagLabel == 0){
            Label = Palavra.substr(0, Palavra.size()-1);;
            FlagLabel = 1;
        }
        //Se a flag ja estiver acionada, a proxima palavra é o valor do label
        if (Flag == 1){
            stringstream Valor(Palavra);
            Valor >> numero;
            MapaEQU[Label] = numero;
            //cout << numero << "\n";
            return;
        }
        // Se ele achar a EQU ele aciona a flag
        if(Palavra.compare("EQU") == 0)
            Flag = 1;
        
            
    }
    return;




}
// Funcao que verifica se o a proxima linha vai se manter no programa depois do pre-processamento
// true - A proxima linha ficara
// false - A proxima linha sera deletada
bool DiretivasIF(string linha){

    int Flag = 0;
    istringstream iss(linha);
    // Percorre todas as palavra da linha
    while(iss){
        string Palavra,Label;
        iss >> Palavra;

        if( Flag == 1){
            Label = Palavra;
            if(MapaEQU.count(Label)){
                int Valor = MapaEQU[Label];
                if ( Valor != 0)
                    return true;
                else 
                    return false;
            }
            // Caso o valor da label nao tenha sido declarado antes
            else{
                //cout << "Erro! Não foi encontrado valor do label:" << Label << endl;
                cout << "ERRO SEMANTICO"<< endl;
                return true;
            }
        }
        // Se ele achar a EQU ele aciona a flag
        if(Palavra.compare("IF") == 0)
            Flag = 1;
        
            
    }
}

string RetiraEspacos(string linha){
    istringstream iss(linha);
    string LinhaNova;
    while(iss){
        string Palavra;
        iss >> Palavra;
        LinhaNova = LinhaNova + Palavra;
        if(!LinhaNova.empty())   
            LinhaNova = LinhaNova + " ";  
    }
    LinhaNova = LinhaNova.substr(0, LinhaNova.size()-2);
    return LinhaNova;
}

string TransformaMaiusculo(string linha){
    // convert string to upper case
    std::for_each(linha.begin(), linha.end(), [](char & c){
        c = ::toupper(c);
    });

    return linha;
}