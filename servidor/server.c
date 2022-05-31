#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#define SIZE 1024

void write_file(char recvBuffer[SIZE], int sockfd, char *filename)
{
	int n;
	FILE *fp;
	char buffer[SIZE];

	fp = fopen(filename, "w");
	fprintf(fp, "%s", recvBuffer);
	while (1)
	{
		n = recv(sockfd, buffer, SIZE, 0);
		if (n <= 0)
		{
			break;
			return;
		}
		fprintf(fp, "%s", buffer);
		bzero(buffer, SIZE);
	}
	return;
}

int main()
{
	int welcomeSocket, newSocket, fileSocket;
	char recvBuffer[SIZE], sendBuffer[SIZE];
	struct sockaddr_in serverAddr;

	socklen_t addr_size;

	char *ip = "127.0.0.1";
	char *port = "7891";

	char ip_port[strlen(ip) + strlen(port) + 2];
	strcpy(ip_port, ip);
	strcat(ip_port, ":");
	strcat(ip_port, port);

	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;

	serverAddr.sin_port = htons(atoi(port));

	serverAddr.sin_addr.s_addr = inet_addr(ip);

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	bind(welcomeSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

	time_t ticks;

	if (listen(welcomeSocket, 5) == 0)
	{
		printf("Server listening on %s\n", ip_port);
	}
	else
		printf("Error\n");

	newSocket = accept(welcomeSocket, (struct sockaddr *)NULL, NULL);
	printf("Cliente conectou.\n");
	char filename[255] = "arquivo_recebido";

	do
	{

		printf("Esperando Mensagem do cliente...\n");

		recv(newSocket, recvBuffer, sizeof(recvBuffer), 0);

		printf("Mensagem recebida do cliente:\n\t %s\n", recvBuffer);

		if (strcmp(recvBuffer, "server_ip") == 0)
		{
			strcpy(sendBuffer, ip_port);
			send(newSocket, sendBuffer, sizeof(sendBuffer), 0);
		}
		else
		{
			printf("Upando arquivo...\n");
			write_file(recvBuffer, newSocket, filename);
			printf("Upload concluido.\n");
			break;
		}
	} while (1);

	printf("fechando conexao...\n");
	close(newSocket);

	return 0;
}
