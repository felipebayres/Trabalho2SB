# Trabalho2-SB

Felipe Brito Ayres - 16/0119537
Vítor Ribas Bandeira - 16/0148421
 
 O trabalho foi feito no ambiente do Linux(Ubuntu) e foi utilizado o MakeFile.
  
  Para compilar o montador do trabalho: 
      1.Entre na pasta \Montador\src ou na \Ligador\src pelo terminal
      2. Digite make no terminal;
      3. Digite ./montador -NomeArquivo-.asm e aperte enter
      3.5 Digite ./ligador -NomeArquivo.obj- -NomeArquivo2.obj- e aperte enter		

-Atenção- : 
  Optamos por deixar o simulador em uma pasta diferente da do compilador para ficar mais organizado.
  Então se quiser usar o arquivo criado pelo ligador , é preciso colocar o caminho dele ao chamar o simulador no passo 3 abaixo(ex: ../../Ligador/src/Fibonacci):
  
  Para compilar o simulador do trabalho:
      1.Entre na pasta \Simulador\src pelo terminal
      2. Digite make no terminal;
      3. Digite ./simulador -NomeArquivo- e aperte enter
