#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<sys/types.h>

#include <sys/socket.h>
#include <sys/types.h>

//to store address information
#include <netinet/in.h>
#include <arpa/inet.h>
int main (int argc, char *argv[]) {
    int port, relay_socket, newsocket, status, pid, i = 0;
    char check = ' ', buffer[50], IPbuffer[100];
    struct sockaddr_in relay_address, node_address, client_address;
    socklen_t address_len;
    FILE *fp;
        if( argc != 2 ){
            fprintf(stderr, "usage %s port\n", argv[0]);
            return -1;
        }      
    sscanf( argv[1], "%d" "%c", &port, &check);
    port = atoi(argv[1]);
        if( check != ' ' | port == 0 ){
            fprintf(stderr, "improper port\n");
            return -1;
        }
    relay_socket = socket(AF_INET, SOCK_STREAM, 0);
	    if( relay_socket <0 ){
	    	perror("[-] Error opening socket");
	    	exit(EXIT_FAILURE);
	    }
    bzero(IPbuffer, sizeof(IPbuffer));
	//specify address family, i.e, domain
	relay_address.sin_family = AF_INET;
	relay_address.sin_port = htons(port);
	//htons converts the int port no. to appropriate type
	relay_address.sin_addr.s_addr = INADDR_ANY;
    status = bind(relay_socket, (struct sockaddr *) &relay_address, sizeof(relay_address));
        if( status <0 ){
            perror("[-] Error on binding");
            exit(EXIT_FAILURE);
        }
        printf("Bind to the port : %d\n", port);
    //listen for connection(request)
    status = listen(relay_socket, 4);
        if( status != 0 )
            perror("[-] Error on listening");
        else
            printf("Listening......\n");
    //system("rm in.txt");
    while(1){
        address_len = sizeof(node_address);
        newsocket= accept( relay_socket, (struct sockaddr *)&node_address, &address_len );
            if( newsocket < 0 ){
                perror("[-] ERROR on accepting");
                exit(EXIT_FAILURE);
            }
        if ( (pid = fork()) < 0 ){
            close(newsocket);
            exit(EXIT_FAILURE);
        }
        if( pid == 0 ){
            close(relay_socket);
            relay_socket = -1;
            bzero(buffer, sizeof(buffer));
            status = recv(newsocket, buffer, sizeof(buffer), 0);
            if( status < 0 )
                perror("[-] Error on recieving IP information");
            //STAGE 1
            else if( strcmp(buffer, "node's information") != 0 ){
                printf( "Connection accepted from node : %s:%d\n", inet_ntoa(node_address.sin_addr), ntohs(node_address.sin_port) );
                printf("Recivied node IP:PORT - %s\n", buffer);
                fp = fopen("a","a+");
                fprintf(fp, "%s", buffer);
                fclose(fp);
                printf("Closes the %s:%d node connection gracefully\n", inet_ntoa(node_address.sin_addr), ntohs(node_address.sin_port) );
            }
            //STAGE 2
            else{
                printf( "Connection accepted from client : %s:%d\n", inet_ntoa(node_address.sin_addr), ntohs(node_address.sin_port) );
                printf("RECIEVED - REQUEST client : SEND %s\n", buffer);
                //printf("%s\n", buffer);
                fp = fopen("a", "rb");
        		fseek(fp, 0, SEEK_END);
        	    long fsize = ftell(fp);
        	    rewind(fp);//send the pointer to beginning of the file
        	    char *string = malloc(fsize + 1);
        	    fread(string, fsize, 1, fp);
        	    fclose(fp);
            	string[fsize] = 0;
                status = send( newsocket, string, strlen(string), 0 );
                    if( status < 0 )
                        perror("[-] Error sending node info to client");
                    else
                        printf("Node's info is sent to client : %s\n",string);
                system("rm a");
                close(newsocket);
                printf("Closes the connection gracefully : %s:%d\n", inet_ntoa(node_address.sin_addr), ntohs(node_address.sin_port) );
                exit(EXIT_SUCCESS);
            }//STAGE 3 end
            exit(EXIT_SUCCESS);
        }//pid 0 end
        else
            close(newsocket);
    }//while(1) end
    return 0;
}