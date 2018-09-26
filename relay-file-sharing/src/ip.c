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
int f;
int main (int argc, char *argv[]) {
    int port, relay_socket, newsocket, status, pid, i = 0;
    char check = ' ', buffer[50], IPbuffer[100];
    struct sockaddr_in relay_address, node_address, client_address;
    socklen_t address_len;
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
    while(1){
        status = listen(relay_socket, 4);
            if( status != 0 )
                perror("[-] Error on listening");
            else
                printf("Listening......\n");
        address_len = sizeof(node_address);
        newsocket= accept( relay_socket, (struct sockaddr *)&node_address, &address_len );
            if( newsocket < 0 ){
                perror("[-] ERROR on accepting");
                exit(EXIT_FAILURE);
            }
        printf( "Connection accepted from node : %s:%d\n", inet_ntoa(node_address.sin_addr), ntohs(node_address.sin_port) );
            relay_socket = -1;
            bzero(buffer, sizeof(buffer));
            status = recv(newsocket, buffer, sizeof(buffer), 0);
            if( status < 0 )
                perror("[-] Error on recieving IP information");
            else if( strcmp(buffer, "REQUEST : send node information") != 0 ){
                strcat(IPbuffer, buffer);
                printf("IP information received : %s\n", buffer);
                printf("IPbuffer : %s\n", IPbuffer);
            }
            else{
                printf("IPbuffer inside else : %s\n", IPbuffer);
                status = send(newsocket, IPbuffer, strlen(IPbuffer), 0);
                    if( status < 0){
                        perror("[-] Error sending node information");
                    }
                    else
                        printf("node information message sent : %s\n",IPbuffer);
                close(newsocket);
                exit(EXIT_SUCCESS);                
                break;
            }
            printf("buffer outide else : %s\n",buffer);
            printf("IPbuffer before conc outside : %s\n", IPbuffer);
            //strcat(IPbuffer, buffer);
            printf("IPbuffer after conc outside : %s\n", IPbuffer);
            close(newsocket);
            newsocket = -1;
        //}pid 0 end
        printf("IPbuffer inside while, outside pid : %s\n", IPbuffer);
    }//while(1) end
    return 0;
}







    /*        else if( pid > 0 )
        {
            close(newsocket);
            status = recv(newsocket, buffer, sizeof(buffer), 0);
            if( status < 0 )
                perror("[-] Error on recieving IP information");
            else if( strcmp(buffer, "REQUEST : send node information") != 0 ){
                //strcat(IPbuffer, buffer);
                printf("IP information received : %s\n", buffer);
                //printf("IPbuffer : %s\n", IPbuffer);
            }

            continue;
        }
*/

/*                        //STAGE 2
    relay_socket = socket(AF_INET, SOCK_STREAM, 0);
	    if( relay_socket < 0 ){
	    	perror("[-] Error opening socket");
	    	exit(EXIT_FAILURE);
	    }
	//specify address family, i.e, domain
	relay_address.sin_family = AF_INET;
	relay_address.sin_port = htons(port);
	//htons converts the int port no. to appropriate type
	relay_address.sin_addr.s_addr = INADDR_ANY;
    status = bind(relay_socket, (struct sockaddr *) &relay_address, sizeof(relay_address));
        if( status < 0 ){
            perror("[-] Error on binding");
            exit(EXIT_FAILURE);
        }
        printf("Bind to the port : %d", port);
    //listen for connection(request)
    status = listen(relay_socket, 0);
        if( status != 0 )
            perror("[-] Error on listening");
        else
            printf("Listening......\n");
    address_len = sizeof(client_address);
    newsocket= accept( relay_socket, (struct sockaddr *)&client_address, &address_len );
        if( newsocket < 0 ){
            perror("[-] ERROR on accepting");
            exit(EXIT_FAILURE);
        }
        printf( "Connection accepted from client : %s:%d\n", inet_ntoa(node_address.sin_addr), ntohs(node_address.sin_port) );
        bzero(IPbuffer, sizeof(IPbuffer));
        status = recv(relay_socket, PORTbuffer, sizeof(PORTbuffer), 0);
            if( status < 0 )
                perror("[-] Error on recieving request message from client.");
            else{
                printf("REQUEST : message is recieved \n");
                status = send(relay_socket, IPbuffer, strlen(IPbuffer), 0);
                    if( status < 0){
                        perror("[-] Error sending node information");
                    }
                    else
                        printf("node information message sent\n");
            }
        close(newsocket);
        close(relay_socket);
*/











/*
else if( strcmp(buffer, "REQUEST : send node information") != 0 ){
                printf("IP information received : %s\n", buffer);
                printf("buffer : %s", buffer);
                printf("IPbuffer : %s\n", IPbuffer);
                FILE *fp = fopen("in.txt","w+");
                if(fp){
                    fprintf(fp, "%s", buffer);
                    fscanf(fp, "%s", IPbuffer);
                    printf("IPbuffer : %s\n", IPbuffer);
                    fclose(fp);
                }
                else
                    perror("Error! : ");
            }
            else{
                printf("IPbuffer inside else : %s\n", IPbuffer);
                break;
            }
            */