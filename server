#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

int main(void){


	int socket_descritor, valor_getaddrinfo, return_bind, return_listen, descritor_client, receber_dados;
	struct addrinfo inicio, *saida;
	struct sockaddr_storage their_addr;

	char buffer[1024];


	memset(&inicio, 0, sizeof(struct addrinfo));
	inicio.ai_family = AF_INET;
	inicio.ai_socktype = SOCK_STREAM;
	inicio.ai_protocol = 0;


	

	int valor_estrutura = sizeof their_addr;

	if((valor_getaddrinfo = getaddrinfo("127.0.0.1", "8080", &inicio, &saida)) == 0){
		printf("Funcao getaddrinfo sucess!!\n");

	}


	if((socket_descritor = socket(saida->ai_family, saida->ai_socktype, 0)) == -1){
		printf("Error in socket!! %d \n", errno);
	}

	if((return_bind = bind(socket_descritor, saida->ai_addr, saida->ai_addrlen)) == -1){
		printf("Error - bind %d\n", errno);
	}


	if((return_listen = listen(socket_descritor, 5)) == -1){
		printf("Error Listen: %d\n", errno);
	}
	
	
	while(1){
		
		
		if((descritor_client = accept(socket_descritor, (struct sockaddr *)&their_addr, &valor_estrutura)) < 0){
			printf("Error: %d\n", errno);
		}


		if((receber_dados = recv(descritor_client, buffer, sizeof buffer, 0)) == -1){
			printf("Error recv - %d", errno);
		}else{
			if(receber_dados > 0){
				printf("%s", buffer);
			}
		}
	}

	freeaddrinfo(saida);
return 0;
}
