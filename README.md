# Trabalho final de Redes 

## Autores

ANTONIO ALEX GOMES RODRIGUES

JADSON BRAZ MUNIZ


## Descrição: 

Seja um servidor e um cliente em execução. 
Ao executar o cliente, pede-se o IP e porta do servidor. 
Em seguida, o programa irá pedir o nome do arquivo que que está armazenado no cliente e que será enviado para o servidor. 
Então, o programa cliente realiza uma conexão TCP com o servidor e envia o arquivo. 
O arquivo pode possuir qualquer tamanho e extensão.

## Compilar

Para compilar os arquivos, entre na pasta do projeto e digite:

	gcc cliente/client.c -o cliente/client

	gcc servidor/server.c -o servidor/server

## Executar:

Abra um terminal, navegue para a pasta `servidor` e digite: 
	
	./server

Abra um segundo terminal, navegue para a pasta `cliente` e digite: 

	./client

