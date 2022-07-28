#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>


int main(void){

	struct addrinfo entrada, *saida;
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int retorno_f, retorno_sock, retorno_bind, retorno_listen, retorno_accept, envio_bytes, envio_msg;
	char *mensagem = "Bem vindo ao nosso servidor...\n";
	int t_mensagem = strlen(mensagem);
	char receber_mensagem[1024];
	int r_mensagem = sizeof receber_mensagem;
	char str[INET_ADDRSTRLEN];

	memset(&entrada, 0, sizeof saida);
	entrada.ai_family = AF_INET;
	entrada.ai_socktype = SOCK_STREAM;
	entrada.ai_protocol = 0;
	



	retorno_f = getaddrinfo("127.0.0.1", "8080", &entrada, &saida);

	if(retorno_f != 0){
		printf("Error na funcao getaddrinfo");
	}
	

	if((retorno_sock = socket(saida->ai_family, saida->ai_socktype, saida->ai_protocol)) == -1){
		printf("Error na criacao de socket!!!\n");
	}else{
		printf(" \n");
	}
	
	addr_size = sizeof their_addr;


	if((retorno_bind = bind(retorno_sock, saida->ai_addr, saida->ai_addrlen)) == -1){
		printf("Error bind %d !!\n", errno);
	}

	if((retorno_listen = listen(retorno_sock, 5)) == -1){
		printf("ERROR: %d\n", errno);
	}


	if((retorno_accept = accept(retorno_sock, (struct sockaddr *)&their_addr, &addr_size)) == -1){
		printf("Error in accept..");
	}

	struct sockaddr_in *ip = (struct sockaddr_in *)&their_addr;

	while(1){
		if((envio_bytes = send(retorno_accept, mensagem, t_mensagem, 0)) < 0){
			printf("Erro...no send");
		}else{
		printf("IP host:%s\n", inet_ntop(AF_INET, &(ip->sin_addr), str, INET_ADDRSTRLEN));
		if((envio_msg =	recv(retorno_accept, receber_mensagem, r_mensagem, 0)) != -1){
			system(receber_mensagem);
			memset(receber_mensagem, 0, sizeof receber_mensagem);
			}else{
				printf("ERRO....");
			}
		
		}
	}
	close(retorno_accept);

return 0;

}
