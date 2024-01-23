#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>

#define TAMANHO_BUFFER  1024
#define MAXIMO_EVENTOS 10

char buffer_principal[TAMANHO_BUFFER];
char buffer_executar[TAMANHO_BUFFER];
int conectar_socket(void){


        struct sockaddr_in s1_socket, s1_addr;
        struct epoll_event evento, events[MAXIMO_EVENTOS];
        int yes = 1;
        int epo;
        int executar, contagem = 1;
        int retorno_socket, retorno_bind, retorno_listen, retorno_accept;
        char buffer_teste[] = "bem vindo ao servidor\n";
        socklen_t s1_addr_len;
        s1_socket.sin_family = AF_INET;
        s1_socket.sin_port  = htons(8811);
        inet_aton("192.168.0.91", &s1_socket.sin_addr);

        retorno_socket = socket(AF_INET, SOCK_STREAM, 0);

        /* Inicio do socket */
        if(retorno_socket == -1){
                printf("Error file descriptor socket!!");
                exit(1);
        }

        retorno_bind = bind(retorno_socket, (const struct sockaddr *)&s1_socket, sizeof(s1_socket));

        /*Bind da porta com o file  */
        if(retorno_bind < 0){
                printf("Error no bind %d", retorno_bind);
                exit(1);
        }

        retorno_listen = listen(retorno_socket, 10);

        /*ouvir conexao */
        if(retorno_listen == -1) {
                printf("Error no listen");
        }

        if(setsockopt(retorno_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1){
                printf("Error!! porta em uso!");
        }

        epo = epoll_create1(0);
        if(epo == -1){
                puts("Erro ao criar epoll");
                return 1;
        }

        evento.events = EPOLLIN;
        evento.data.fd = retorno_socket;


        if(epoll_ctl(epo, EPOLL_CTL_ADD, retorno_socket, &evento) == -1){
                puts("Error epoll_ctl");
                close(retorno_socket);
                return 1;
        }

        fflush(stdout);
        while(executar){
                contagem = epoll_wait(epo, &events, MAXIMO_EVENTOS, 40000);
                if(contagem == -1){
                        puts("Error epoll esperar");
                        return 1;
                }
                for(int valor_file=0;valor_file < contagem; valor_file++){
                        if(events[i].data.fd == retorno_socket){
                                retorno_accept = accept(retorno_socket, (struct sockaddr *)&s1_addr, &s1_addr_len);
                                if(retorno_accept == -1){
                                        puts("Error in accept");
                                }
                        }

                        while(recv(retorno_accept, buffer_principal, sizeof buffer_principal, 0) > 0){
                                printf("Dados clientes:%s\n", buffer_principal);
                                if(memcmp(buffer_principal, "Exit", 4)==0){
                                        memset(buffer_principal,0,sizeof buffer_principal);
                                        close(retorno_accept);
                                }
                        }
                        close(retorno_accept);
                }

        }
                close(retorno_socket);

}

int main(void) {

        conectar_socket();

return 0;
}
