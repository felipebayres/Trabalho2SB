#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <bits/stdc++.h> 
using namespace std;
string PreProcessamento(string NomeArquivo);
string TransformaMaiusculo(string linha);
string RetiraComentarios(string linha);
string RetiraEspacos(string linha);
int VerificaDiretiva(string linha);
void DiretivasEQU(string linha);
bool DiretivasIF(string linha);

