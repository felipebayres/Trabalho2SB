# Trabalho1-SB

Felipe Brito Ayres - 16/0119537
Vítor Ribas Bandeira - 16/0148421
 
 O trabalho foi feito no ambiente do Linux(Ubuntu) e foi utilizado o MakeFile.
  
  Para compilar o montador do trabalho: 
      1.Entre na pasta \Montador\src pelo terminal
      2. Digite make no terminal;
      3. Digite ./montador -NomeArquivo-.asm e aperte enter

-Atenção- : 
  Optamos por deixar o simulador em uma pasta diferente da do compilador para ficar mais organizado.
  Então se quiser usar o arquivo criado pelo montador , é preciso colocar o caminho dele ao chamar o simulador no passo 3 abaixo(ex: ../../Montador/src/Fibonacci.obj):
  
  Para compilar o simulador do trabalho:
      1.Entre na pasta \Simulador\src pelo terminal
      2. Digite make no terminal;
      3. Digite ./simulador -NomeArquivo-.obj e aperte enter
