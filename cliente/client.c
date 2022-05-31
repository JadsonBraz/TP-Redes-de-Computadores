#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define SIZE 1024

void send_file(FILE *fp, int clientSocket)
{
	int n;
	char data[SIZE] = {0};

	while (fgets(data, SIZE, fp) != NULL)
	{
		if (send(clientSocket, data, sizeof(data), 0) == -1)
		{
			perror("[-]Error in sending file.");
			exit(1);
		}
		bzero(data, SIZE);
	}
}

int main()
{
	int clientSocket;
	char buffer[SIZE];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	char *ip = "127.0.0.1";
	char *port = "7891";

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(port));
	serverAddr.sin_addr.s_addr = inet_addr(ip);

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

	send(clientSocket, "server_ip", sizeof(buffer), 0);
	recv(clientSocket, buffer, sizeof(buffer), 0);

	printf("IP e porta do servidor: %s\n", buffer);

	FILE *fp;
	fp = NULL;
	char filename[255];
	while (fp == NULL)
	{
		printf("Digite o nome do arquivo que será enviado: ");
		scanf("%s", filename);

		fp = fopen(filename, "r");

		if (fp == NULL)
		{
			perror("Erro ao ler arquivo");
		}
	}
	send_file(fp, clientSocket);
	printf("Arquivo enviado com sucesso!\n");

	printf("Fechando Conexao e encerrando o programa...\n");
	close(clientSocket);

	return 0;
}
