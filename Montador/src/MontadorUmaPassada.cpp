#include <string.h>
#include <iostream>
#include <fstream>
#include "MontadorUmaPassada.hpp"

string MontadorUmaPassada(string NomeArquivo,bool DoisArquivos){
    // Aqui sao declaradas todas as tabelas usadas
    map<string,TabelaSimbolos> TabelaDeSimbolos;
    map<string,TabelaUsos> TabelaUso;
    map<string,TabelaDefinicao> TabelaDefinicoes;

    vector<int> VetorRealocacoes;
    ifstream Arquivo;
    Arquivo.open(NomeArquivo);
    string linha;
    bool FlagText = false , FlagData = false, FlagLabel = false;
    int ContadorLinhas = 0;
    
    //Verifica se existe a secao text e coloca ela na primeira posicao e coloca o nome do modulo na tabela de simbolos
    string NomeModulo = PadronizaSection(NomeArquivo,DoisArquivos);
    if( DoisArquivos){
        NomeModulo = NomeModulo.substr(0, NomeModulo.size()-1);
        TabelaDeSimbolos[NomeModulo].definido = true;
        TabelaDeSimbolos[NomeModulo].Valor =  0;
        TabelaDefinicoes[NomeModulo].definido = true;
        TabelaDefinicoes[NomeModulo].Valor = 0;
    }
    
    string NomeArquivoObjeto;
    NomeArquivoObjeto = NomeArquivo.substr(0, NomeArquivo.size()-4) + ".obj";
    ofstream ArquivoObjeto(NomeArquivoObjeto);

    vector<string> VetorObjeto;

    if(!ArquivoObjeto.is_open()){
        cout << "Não foi possivel gerar o arquivo objeto " << "\n";
        return "";
    }
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo pre-processado " << NomeArquivo << "\n";
        return "";
    }
    if ( DoisArquivos){
        getline(Arquivo, linha);
    }
    getline(Arquivo,linha);
    int LinhasArquivo = 1;
    while(Arquivo.peek() != EOF){
        //Conta as linhas do arquivo pre processado
        if (linha.compare("SECTION TEXT") == 0 && FlagText == false){
            FlagText = true;
            
            
            while(getline(Arquivo, linha)){
                LinhasArquivo++;
                istringstream buf(linha),aux(linha);
                vector<string> v;
                string auxiliar;
                //Verificar se existe a declaracao de outra section
                aux >> auxiliar;
                if(auxiliar.compare("SECTION") == 0){
                    break;
                }
                //Separa todas as palavras da linha e coloca elas em um vector
                for(string palavra; buf >> palavra; ){
                    v.push_back(palavra);
                    // imprime todas as palavras da linha cout << palavra << endl;
                }
                
                
                
                
                int i = 0;
                string palavra = v[i];
                // Essas variaveis guardam o numero que o argumento pode receber(vetor);
                int VetorArgumento[2] = {0,0};
                
                // Verifica se a primeira palavra da linha é um label
                if(palavra.back() == ':'){
                    palavra = palavra.substr(0, palavra.size()-1);
                    //Verifica se o label é valido
                    if(ValidaToken(palavra)){
                        // Verifica a diretiva e coloca o label na tabela de simbolos
                        
                        if(DoisArquivos == true){
                            if(v[1] == "EXTERN"){
                                TabelaDeSimbolos[palavra].externo = true;
                                TabelaDeSimbolos[palavra].Valor = 0;
                            }                        
                        }
                        //Verifica se o label ja foi visto antes e se ele nao é uma diretiva de modulo
                        if(TabelaDeSimbolos.count(palavra) == 1 && ValidaInstrucao(v[1]) != 15){
                            //Verifica se o label esta definido
                            if (TabelaDeSimbolos[palavra].definido == false){
                                TabelaDeSimbolos[palavra].definido = true;
                                TabelaDeSimbolos[palavra].Valor = ContadorLinhas;
                                TabelaDeSimbolos[palavra].Tipo = 0;
                                // Coloca na tabela de definicoes o valor do label ( CASO TENHA MODULO)
                                if(TabelaDeSimbolos[palavra].publico == true){
                                    TabelaDefinicoes[palavra].Valor = ContadorLinhas;
                                    TabelaDefinicoes[palavra].definido = true;
                                }
                            }
                            else
                            {
                                //cout << "Simbolo na linha " << LinhasArquivo << " ja foi definido antes" << endl;    
                                cout<< "Simbolo ja foi definido -Linha: " << LinhasArquivo << endl; 
                            }
                        }
                        //Se o simbolo nao tiver na tabela ainda e se nao é uma diretiva de modulo
                        else if (ValidaInstrucao(v[1]) != 15) {
                            
                            TabelaDeSimbolos[palavra].definido = true;
                            TabelaDeSimbolos[palavra].Tipo = 0;
                            TabelaDeSimbolos[palavra].Valor = ContadorLinhas;
                            // Procura se o label é public
                            if(TabelaDefinicoes.count(palavra) == 1){
                                TabelaDefinicoes[palavra].Valor == ContadorLinhas;
                                TabelaDefinicoes[palavra].definido == true;
                            }
                        
                        }
                    }
                    //Caso o label nao seja valido
                    else{
                        
                        //cout << "Linha:" << LinhasArquivo << endl;
                        cout << "Token invalido -Linha: " << LinhasArquivo << endl;
                    }
                    FlagLabel = true;
                    i++;
                }
                
                
                // A partir daqui é feito o tratamento da instrucao em si;
                palavra = v[i];
                
                int numero = ValidaInstrucao(palavra);
                // Ele so vai analizar a linha se nao for uma diretiva de modulo
                if(numero != 15 && numero != 16){
                
                    // Verifica se a instrucao existe no assembly inventado
                    if (numero < 0){
                            //cout << "Instrucao " << palavra << " inexistente" << endl;
                            //cout << "Linha:" << LinhasArquivo << endl;
                            cout << "Instrucao nao existe no assembly -Linha: " << LinhasArquivo << endl;
                        }
                    // Separa os argumentos da instrucao copy em dois simbolos
                    if (numero == 9){
                        int k = i;
                        string Aux;
                        Aux = v[i+1];
                        v.pop_back();
                        istringstream ss(Aux);
                        string token;
                        while(getline(ss, token, ',')){
                            int k = i+1;
                            v.push_back(token);
                            k++;

                        }
                        //Para printar o vector da linha depois dos ajustes
                        //for(int l = 0; l < v.size();l++)
                        //cout <<"V[" <<l<<"]=" << v[l] << " ";
                    }
                    int tamanho = v.size();
                    if(FlagLabel){
                        tamanho = tamanho - 1;
                    }
                    // Verifica se tem a quantidade certa de argumentos da instrucao
                    if ((numero < 8 && tamanho != 2) || (numero == 9 && tamanho != 3) || ((numero > 9 && numero < 14) && tamanho != 2) || (numero == 14 && tamanho != 1)){
                        //cout << "Numero invalido de argumentos pra instrucao " << palavra << endl;
                        //cout << "Linha:" << LinhasArquivo << endl;
                        cout << "Quantidade errada de argumentos -Linha: " << LinhasArquivo << endl;
                    }
                        ContadorLinhas++;
                        //Escreve as instrucoes no arquivo
                        VetorObjeto.push_back(to_string(numero));
                }



                // ****** A partir daqui é feito  o tratamento dos operandos *******
                int l = 0;
                for (int j = i+1; j < v.size();j++){
                    palavra = v[j];
                    //Verifica se a instrucao pode receber vetor como operando
                    if (numero >=5 && numero <= 13){
                        int pos = palavra.find_first_of('+');
                        
                        //Se tiver um vetor com mais de uma posicao
                        if (pos != -1){
                            string TamanhoVetor_str;
                            TamanhoVetor_str = v[j].substr(pos+1,-1);
                            v[j].erase(pos,v[j].size()-pos);
                            palavra = v[j];
                            VetorArgumento[l] = stoi(TamanhoVetor_str);
                            //Guarda o maior valor de spaces que a instrucao quer mexer para verificar se o vetor tem realmente o tamanho
                            if (TabelaDeSimbolos[palavra].QuantidadeSpace <= stoi(TamanhoVetor_str))
                                TabelaDeSimbolos[palavra].QuantidadeSpace = stoi(TamanhoVetor_str);
                        }
                    }
                    if(ValidaToken(palavra)){
                        //Verfifica se é a diretiva PUBLIC
                        if (numero == 16){
                            TabelaDeSimbolos[palavra].publico = true;
                        }
                        //Verifica se o label ja foi definido antes
                        else{

                            if(TabelaDeSimbolos.count(palavra) == 1 ){
                                if(TabelaDeSimbolos[palavra].definido == true){
                                    //Verifica se a instrucao de jumps possui um pulo correto
                                    int Instrucao = stoi (VetorObjeto.back());
                                    
                                    if((Instrucao >= 5 && Instrucao <= 8) && TabelaDeSimbolos[palavra].Tipo != 0){
                                        //cout << "Jump para label invalido" << endl;
                                        //cout << "Linha:" << LinhasArquivo << endl;
                                        cout << "Jump para label invalido -Linha: " << LinhasArquivo << endl;
                                    }
                                    else if ( Instrucao >=1 && Instrucao <= 4 && TabelaDeSimbolos[palavra].Tipo == 0){
                                        //cout << "Linha:" << LinhasArquivo << endl;
                                        //cout << "Operacao com operando invalido" << endl;
                                        cout << "Operacao com operando invalido -Linha: " << LinhasArquivo << endl;
                                    }
                                    //Escreve no arquivo a posicao correta se o label ja foi definido
                                    VetorRealocacoes.push_back(ContadorLinhas);
                                    VetorObjeto.push_back(to_string(TabelaDeSimbolos[palavra].Valor + VetorArgumento[l]));
                                }
                                // Se ele nao estiver definido, é colocado o lugar de uso na tabela e o valor inicial do vetor  
                                else{
                                    // Se o operando for um valor externo
                                    if(TabelaDeSimbolos[palavra].externo == true){
                                        TabelaUso[palavra].LugaresUsados.push_back(ContadorLinhas);
                                    }
                                    // Coloca o endereco do operando na lista de realocacao
                                    VetorRealocacoes.push_back(ContadorLinhas);
                                    TabelaDeSimbolos[palavra].LugaresUsados.push_back(ContadorLinhas);  
                                    VetorObjeto.push_back(to_string(VetorArgumento[l]));
                                    TabelaDeSimbolos[palavra].LinhasUsadas.push_back(LinhasArquivo);
                                }
                            }
                            //Se nao foi definido antes é escrito na tabela de simbolos
                            else {
                                if(TabelaDeSimbolos[palavra].externo == true){
                                        TabelaUso[palavra].LugaresUsados.push_back(ContadorLinhas);
                                    }
                                VetorRealocacoes.push_back(ContadorLinhas);
                                VetorObjeto.push_back(to_string(VetorArgumento[l]));
                                TabelaDeSimbolos[palavra].definido = false;
                                TabelaDeSimbolos[palavra].Valor = -1;
                                TabelaDeSimbolos[palavra].LugaresUsados.push_back(ContadorLinhas);
                                TabelaDeSimbolos[palavra].LinhasUsadas.push_back(LinhasArquivo);
                            }
                        }
                        
                    }

                    else{
                        //cout << "Linha:" << LinhasArquivo << endl;
                        cout << "Token invalido -Linha: " << LinhasArquivo << endl;
                    }
                if ( numero != 15 && numero != 16)
                    ContadorLinhas++;
                    l++;
                }
                // Para debuggar a quantidade de espacos se for um vetor
                    //cout << "instrucao:" << v[i] << endl;
                    //cout << VetorArgumento[0] << " " << VetorArgumento[1] << endl;
                FlagLabel = false;
            }
            
        }
            
        if (linha.compare("SECTION DATA") == 0 && FlagData == false){
            FlagData = true;
            while(getline(Arquivo, linha)){
                LinhasArquivo++;
                istringstream buf(linha),aux(linha);
                vector<string> v;
                string auxiliar;
                
                //Verificar se existe a declaracao de outra section
                aux >> auxiliar;
                if(auxiliar.compare("SECTION") == 0){
                    break;
                }
                
                // Separa a linha por palavras e armazena cada uma em uma posicao do vector
                for(string palavra; buf >> palavra; ){
                    v.push_back(palavra);
                    //cout << palavra << endl;
                }
                int i = 0;
                string palavra = v[i];
                string Label;
                
                // Verifica se a primeira palavra da linha é um label
                if(palavra.back() == ':'){
                    palavra = palavra.substr(0, palavra.size()-1);
                    Label = palavra;
                    //Verifica se o label é valido   
                    if(ValidaToken(palavra)){
                        //Verifica se o label ja foi visto antes
                        if(TabelaDeSimbolos.count(palavra) == 1){
                            //Se o label ja estiver definido
                            if(TabelaDeSimbolos[palavra].definido == true){
                                //cout << "Label ja foi definido antes" << endl;
                                //cout << "Linha:" << LinhasArquivo << endl;
                                cout << "Label ja definido anteriormente -Linha: " << LinhasArquivo << endl;
                            }
                            //Se o label ainda nao estiver definido
                            else{
                                //Verifica se o label que foi definido agora era publico
                                if(TabelaDeSimbolos[palavra].publico == true){
                                    TabelaDefinicoes[palavra].Valor = ContadorLinhas;
                                }
                                TabelaDeSimbolos[palavra].definido = true;
                                TabelaDeSimbolos[palavra].Valor = ContadorLinhas;

                            }
                        }
                        else {
                            if(TabelaDeSimbolos[palavra].publico == true){
                                    TabelaDefinicoes[palavra].Valor = ContadorLinhas;
                                }
                            TabelaDeSimbolos[palavra].definido = true;
                            TabelaDeSimbolos[palavra].Valor = ContadorLinhas;
                        }
                    }
                    else{
                        //cout << "Linha:" << LinhasArquivo << endl;
                        cout << "TOken invalido -Linha: " << LinhasArquivo << endl;
                    
                    }
                }
                // o END do programa sempre fica na section data
                else if(palavra != "END"){
                    //cout << " Comandos na Section Data devem comecar com um label" << endl;
                    //cout << "Linha:" << LinhasArquivo << endl;
                    cout << "Sem label na section data -Linha: " << LinhasArquivo << endl;
                }
                i++;
                if(palavra != "END")
                    palavra = v[i];
                
                // Verifica a diretiva presente na linha 
                if (palavra.compare("SPACE") == 0){
                    TabelaDeSimbolos[Label].Tipo = 2; 
                    int QuantidadeSpaces = 1;
                    //Se houver um numero em seguida da palavra SPACE
                    if(v.size() == 3){
                        QuantidadeSpaces = stoi(v[2]);
                        if(TabelaDeSimbolos[Label].QuantidadeSpace >= QuantidadeSpaces){
                            //cout << "Quantidade do Vetor errada ";
                            //cout << "-Linha:" << LinhasArquivo << endl; 
                            cout << "Quantidade do Vetor errada -Linha: " << LinhasArquivo << endl;
                        }
                    }
                    else if (v.size() > 3){
                        cout << "quantidade de argumentos errada -Linha: " << LinhasArquivo << endl;
                    }    
                    for(int i = 0 ; i < QuantidadeSpaces;i++)
                        VetorObjeto.push_back("OO"); 
                    ContadorLinhas = ContadorLinhas + QuantidadeSpaces;
                }
                else if (palavra.compare("CONST") == 0){
                    string numero;
                    TabelaDeSimbolos[Label].Tipo = 1;
                    bool FlagNegativo = false;
                    if (v.size() != 3){
                        //cout << "Numero de argumentos para CONST invalido!" << endl;
                        //cout << "Linha:" << LinhasArquivo << endl;
                        cout << "numero de argumentos para const invalido -Linha: " << LinhasArquivo << endl;
                    }
                    int ValorFinal = 0,ValorHexa;
                    numero = v[2]; 
                    if(numero[0] == '-'){
                        FlagNegativo = true;
                        numero.erase(0,1);
                    } 
                    if(VerificaHexa(numero)){
                        stringstream stream;
                        stream << numero;
                        stream >> std::hex >> ValorFinal;
                    }
                    else{
                        ValorFinal = stoi(numero);

                    }
                    if (FlagNegativo)
                        ValorFinal = ValorFinal*(-1);
                    TabelaDeSimbolos[Label].constante = ValorFinal;
                    // Mostrar o valor do const
                    //cout << ValorFinal << endl;
                    VetorObjeto.push_back(to_string(ValorFinal));
                    
                    ContadorLinhas++;


                }
                else if (palavra.compare("END") != 0){
                    //cout << "Diretiva inexistente" << endl;
                    //cout << "Linha:" << LinhasArquivo <<  endl;
                    cout << "Diretiva inexistente -Linha: " << LinhasArquivo << endl;
                }
            }
        }
        else{
            if(Arquivo.peek() != EOF){
                //cout << "Secao invalida ou ja definida:" << linha << endl;
                //cout << "Linha:" << LinhasArquivo << endl;
                cout << "secao invalida ou ja definida -Linha: " << LinhasArquivo << endl;
                break;
            }
        }
    }
    if(FlagText == false){
        //cout << "Linha:"<< LinhasArquivo << endl;
        cout << "Nao apresenta section text -Linha: " << LinhasArquivo << endl;
    
    }
    //ArquivoObjeto.close();
    //Essa parte do codigo coloca os valores dos labels que faltam no codigo
    for(auto& Simbolo : TabelaDeSimbolos){
	    vector<int> ListaUsos;
        /*if (Simbolo.second.definido == false && Simbolo.second.externo == false){
            //cout << "Simbolo nao definido ";
            //cout << Simbolo.first << endl;
            //cout << "Linha:"<<  Simbolo.second.LinhasUsadas[0] << endl;
            cout << "Simbolo nao definido -Linha: " << Simbolo.second.LinhasUsadas[0] << endl;
        }*/
        // Se todos os simbolos estiverem definidos
        
        
        /*else */if (Simbolo.second.externo == false)
        {
            //Se tiver local em que ele nao foi definido corretamente
            if(!Simbolo.second.LugaresUsados.empty()){
                int j = 0;
                while(j < Simbolo.second.LugaresUsados.size()) {
                    int PosicaoUsada = Simbolo.second.LugaresUsados[j];
                    //Procura no VetorObjeto o local a ser substituido
                    for(int i = 0 ; i < VetorObjeto.size() ; i++){
                        
                        if(PosicaoUsada == i){
                            //cout << "Simbolo:" << Simbolo.first << " " ;
                            //cout << "Lugar usado: " << Simbolo.second.LugaresUsados[j] << endl;
                            //cout << "VetorObjeto["<< i<<"]"<<"="<< VetorObjeto[i] <<"+"<<Simbolo.second.Valor << endl;
                            
                            // Verifica se a instrucao é um jump e se o endereco é o correto
                            int Instrucao = stoi (VetorObjeto[i-1]);
                                /*
                                if ( Instrucao >=1 && Instrucao <= 4 && Simbolo.second.Tipo == 0){
                                    //cout << "Linha:" << Simbolo.second.LinhasUsadas[j] << endl;
                                    //cout << "Operacao com operando invalido" << endl;
                                    cout << "Operacao com operando invalido -Linha: " << Simbolo.second.LinhasUsadas[j] << endl;
                                }
                                else if((Instrucao >= 5 && Instrucao <= 8) && Simbolo.second.Tipo != 0){
                                    //cout << "Linha:" << Simbolo.second.LinhasUsadas[j] << endl;
                                    //cout << "Jump para label invalido" << endl;
                                    cout << "Operacao com operando invalido2 -Linha: " << Simbolo.second.LinhasUsadas[j] << endl;
                                }
                                if( Instrucao == 4 && Simbolo.second.Tipo == 1 && Simbolo.second.constante == 0){
                                    //cout << "Linha:" << Simbolo.second.LinhasUsadas[j] << endl;
                                    //cout << "Divisao por 0" << endl;
                                    cout << "Operacao com operando invalido3 -Linha: " << Simbolo.second.LinhasUsadas[j] << endl;
                                }
                                
                                // Verifica se o simbolo é uma constante
                                if(Simbolo.second.Tipo == 1){
                                    //Verifica se a instrucao é um load em uma constante
                                    if (Instrucao == 12){
                                        //cout << "Linha:" << Simbolo.second.LinhasUsadas[j] << endl;
                                        //cout << "Modificacao do valor de uma constante" << endl;
                                        cout << "ERRO SEMANTICO -Linha: " << Simbolo.second.LinhasUsadas[j] << endl;
                                    
                                    }
                                    // Verifica se a instrucao é um copy e se o segundo operando é uma constante
                                    if( i >= 2){
                                        Instrucao = stoi(VetorObjeto[i-2]);
                                        if( Instrucao == 9 ){
                                            //cout << "Linha:" << Simbolo.second.LinhasUsadas[j] << endl;
                                            //cout << "Modificacao do valor de uma constante" << endl;
                                            cout << "ERRO SEMANTICO -Linha: " << Simbolo.second.LinhasUsadas[j] << endl;
                                        }
                                    }
                                }
                                */
                            VetorObjeto[i] = to_string(stoi(VetorObjeto[i]) + Simbolo.second.Valor);
                            //cout << VetorObjeto[i] << endl;
                            break;
                        }
                    }
                    j++;
                }
            }   
        }
        
    
    }
    
    
        ArquivoObjeto << "H: " << NomeArquivo.substr(0, NomeArquivo.size()-4) << endl;
        ArquivoObjeto << "H: " << VetorObjeto.size() << endl;
        ArquivoObjeto << "H: ";
        for ( int i = 0 ; i < VetorRealocacoes.size() ; i++){
            ArquivoObjeto << VetorRealocacoes[i] << " ";

        }
        ArquivoObjeto << endl;
        if ( DoisArquivos == true){
            for(auto& Simbolo : TabelaUso){
                ArquivoObjeto << "U: " ;
                //Pega todos os lugares em que o simbolo externo foi utilizado
                ArquivoObjeto << Simbolo.first << " ";
                for(int i = 0; i < Simbolo.second.LugaresUsados.size(); i++)
                    ArquivoObjeto << Simbolo.second.LugaresUsados[i] << " "; 


                ArquivoObjeto << endl;
            }
            for(auto& Simbolo : TabelaDefinicoes){
                ArquivoObjeto << "D: ";
                //Pega todos as definicoes dos labels public
                ArquivoObjeto << Simbolo.first << " " << Simbolo.second.Valor << endl;
            }
        }
        ArquivoObjeto << "T: ";
    
    for (int i = 0 ; i < VetorObjeto.size() ; i++){
        //cout << VetorObjeto[i] << " ";
        ArquivoObjeto << VetorObjeto[i] << " ";
    }
    ArquivoObjeto.close();
    Arquivo.close();
    return NomeArquivoObjeto;
}

int ValidaInstrucao(string instrucao){
    if (instrucao.compare("ADD") == 0)
        return 1;
    else if (instrucao.compare("SUB") == 0)
        return 2;
    else if (instrucao.compare("MULT") == 0)
        return 3;
    else if (instrucao.compare("DIV") == 0)
        return 4;
    else if (instrucao.compare("JMP") == 0)
        return 5;
    else if (instrucao.compare("JMPN") == 0)
        return 6;
    else if (instrucao.compare("JMPP") == 0)
        return 7;
    else if (instrucao.compare("JMPZ") == 0)
        return 8;
    else if (instrucao.compare("COPY") == 0)
        return 9;
    else if (instrucao.compare("LOAD") == 0)
        return 10;
    else if (instrucao.compare("STORE") == 0)
        return 11;
    else if (instrucao.compare("INPUT") == 0)
        return 12;
    else if (instrucao.compare("OUTPUT") == 0)
        return 13;
    else if (instrucao.compare("STOP") == 0)
        return 14;
    else if(instrucao.compare("EXTERN") == 0 || instrucao.compare("BEGIN") == 0)
        return 15;
    else if(instrucao.compare("PUBLIC") == 0)
        return 16;
    return -1;
}
bool ValidaToken(string token){
    if (token.size() > 50){
        //cout << " Tamanho da variavel ou rotulo " << token << " ultrapassa 50 caracteres" << endl;
        return false;
    }
    else if (isdigit(token[0])){
        //cout << "A variavel ou rotulo " << token << " possui numero no primeiro caractere" << endl;
        return false;
    }
    if (token.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_") != std::string::npos)
    {
        //cout << "Foi utilizado um caractere invalido no token " << token << endl;
        return false;
    }
    return true;



}
bool VerificaHexa(string s){
  return s.compare(0, 2, "0X") == 0
      && s.size() > 2
      && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}

string PadronizaSection(string NomeArquivo,bool DoisArquivos){
    ifstream Arquivo;
    ofstream ArquivoNovo;
    Arquivo.open(NomeArquivo);
    string linha,label;
    bool FlagText = false;
    vector<string> VetorText,VetorArquivo;
    
    if (!Arquivo.is_open()){
        cout << "Não foi possível abrir o arquivo pre-processado " << NomeArquivo << "\n";
        return "-1";
    }
    //pega a primeira linha se tiver MODULOS
    if(DoisArquivos == true){
        getline(Arquivo, linha);
        istringstream buf(linha);
        vector<string> v;
        //Separa todas as palavras da linha e coloca elas em um vector
        for(string palavra; buf >> palavra; ){
            v.push_back(palavra);
            // imprime todas as palavras da linha cout << palavra << endl;
        }
        label = v[0];
        VetorText.push_back(linha);
    }         
    



    while(getline(Arquivo, linha)){
        
        if (linha.compare("SECTION TEXT") == 0){
            FlagText = true;
            if(linha.compare("END") != 0 || DoisArquivos == false)
                VetorText.push_back(linha);
            while(getline(Arquivo, linha))
                if(linha.compare("END") != 0 || DoisArquivos == false)
                    VetorText.push_back(linha);
            VetorText.insert(std::end(VetorText), std::begin(VetorArquivo), std::end(VetorArquivo));
        }
        if(linha.compare("END") != 0 || DoisArquivos == false)
            VetorArquivo.push_back(linha);

    }
    Arquivo.close();
    ArquivoNovo.open(NomeArquivo,std::ofstream::out | std::ofstream::trunc);
    if (!FlagText)
        cout << "ERRO SEMANTICO" << endl;
    
    for(int i = 0 ; i < VetorText.size() ; i++){
        ArquivoNovo << VetorText[i] << endl;
    }
    if(DoisArquivos)
        ArquivoNovo << "END";
    ArquivoNovo.close();
    return label;
}