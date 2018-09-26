#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <sys/types.h>

//to store address information
#include <netinet/in.h>
#include <arpa/inet.h>

int main (int argc, char *argv[]) {
    int port, client_socket, status;
    char check = ' ', IPbuffer[20], PORTbuffer[10], NODE[1000], fname[20];
    FILE *fp;
        if (argc != 3) {
            fprintf(stderr, "usage %s hostname port\n", argv[0]);
            return -1;
        }      
    sscanf( argv[2], "%d" "%c", &port, &check);
    //take integer part of string
    port = atoi(argv[2]);
        if(check != ' ' | port == 0){
            fprintf(stderr, "improper port\n");
            return -1;
        }
    								/*stage 2*/

    //TCP socket is made
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
	    if(client_socket <0){
	    	perror("[-] Error creating socket for connecting with relay server\n");
	    	return -1;
	    }
        printf("Node socket is created for connection with relay\n");
    //ip address structure for the socket
	struct sockaddr_in relay_address, node_address;
	//specify address family, i.e, domain
	relay_address.sin_family = AF_INET;
	relay_address.sin_port = htons(port);
	//htons converts the int port no. to appropriate type
	relay_address.sin_addr.s_addr = inet_addr(argv[1]);
	//sin_addr is already a struct, so it have different fields
	//s_addr will give actual server address
    if( inet_pton(AF_INET, argv[1], &relay_address.sin_addr) <= 0 )
		fprintf(stderr, "invalid IP address: %s\n", argv[1]);
    	
    // connect_status=0 everythings okay, -1 there's some error    
	status = connect(client_socket, (struct sockaddr *) &relay_address, sizeof(relay_address));
	    if(status < 0){
	    	perror("[-] Error connecting with relay server");
	    	return -1;
	    }
        printf("Connected with relay socket\n");
    char* req="node's information";
    /* Send request message to the relay server */
    status = send(client_socket, req, strlen(req), 0);
        if( status < 0){
            perror("[-] Error sending request message");
        }
        else{
            printf("SENT - REQUEST client : SEND %s\n",req);
            /* Now read relay server response */
            bzero(NODE, sizeof(NODE));
            status = recv(client_socket, NODE, sizeof(NODE), 0);
                if( status < 0){
                    perror("[-] Error recieving node information");
                }else
                    printf("RECIEVED - RESPOND node : SEND '%s'\n", NODE);
        }
    close(client_socket);
    //STAGE 2 end

    
    //STAGE 3
    while(1){
        client_socket = socket(AF_INET, SOCK_STREAM, 0);
	    if(client_socket <0){
	    	perror("[-] Error creating socket for connecting with node\n");
	    	return -1;
	    }
        sscanf(NODE, "%s %s", IPbuffer, PORTbuffer);
        port = atoi(PORTbuffer);
        printf("Node socket is created for connecting with node\n");
	    node_address.sin_family = AF_INET;
	    node_address.sin_port = htons(port);
	    //htons converts the int port no. to appropriate type
	    node_address.sin_addr.s_addr = inet_addr(IPbuffer);
        strcat(IPbuffer, PORTbuffer);
        strcat(IPbuffer, "\n");
        printf("%s", IPbuffer);
        int size_ip = strlen(IPbuffer);
        int size_n = strlen(NODE);
            for(int i = 0; i < (size_n - size_ip); i++)
                NODE[i] = NODE[i + size_ip];
            NODE[size_n - size_ip] = '\0';
        if(NODE == '\0')
            break;
	    //sin_addr is already a struct, so it have different fields
	    //s_addr will give actual server address
        if( inet_pton(AF_INET, argv[1], &node_address.sin_addr) <= 0 ){
	    	fprintf(stderr, "invalid IP address: %s\n", argv[1]);
            return -1;
        }
        // connect_status=0 everythings okay, -1 there's some error    
	    status = connect(client_socket, (struct sockaddr *) &node_address, sizeof(node_address));
	        if(status < 0){
	        	perror("[-] Error connecting with node");
	        	return -1;
	        }
            printf("connected with node\n");
        printf("Enter file name : ");
        scanf("%s",fname);
        status = send(client_socket, fname, strlen(fname), 0);
            if( status < 0 ){
                perror("[-] Error sending file name");
                return -1;
            }
            else{
                printf("SENT - REQUEST node : SEND %s file existence \n", fname);
            }
        bzero(IPbuffer, sizeof(IPbuffer));
        status = recv(client_socket, IPbuffer, sizeof(IPbuffer), 0);
            if( status < 0 )
                perror("[-] Error on recieving file content");
            else if(IPbuffer == "0"){
                printf("RECIEVED - RESPONSE node : SEND no %s file\n",fname);
                close(client_socket);
                continue;
            }
            {
                char *req = "content";
                status = send(client_socket, req, strlen(req), 0);
                    if( status < 0 ){
                        perror("[-] Error sending file name");
                        return -1;
                    }
                    else{
                        printf("SENT - REQUEST node : SEND %s file %s\n", fname, req);
                    }
                //file string length
                bzero(IPbuffer, sizeof(IPbuffer));
                status = recv(client_socket, IPbuffer, sizeof(IPbuffer), 0);
                    if( status < 0 ){
                        perror("[-] Error on recieving file length");
                        return -1;
                    }
                long fsize = atol(IPbuffer);
                char buffer[fsize];
                bzero(buffer, sizeof(buffer));
                status = recv(client_socket, buffer, sizeof(buffer), 0);
                    if( status < 0 )
                        perror("[-] Error on recieving file content");
                    else{

                        printf("RECIEVED - RESPONSE node : SEND %s file content\n'%s'\n", fname, buffer);
        /*                printf("Enter file name of saving file : ");      // extra feature - 
                        scanf("%s", fname);                                         saving file 
                        system(fname);                                                
                        fp = fopen("fname", "a");
                        //if(fsize <= 1024){
                            // bzero(buffer, sizeof(buffer));
                            // status = recv(client_socket, buffer, sizeof(buffer), 0);                             
                        fprintf(a, "%s", buffer);                                                                   
                        close(client_socket);   
                        break;
                        }
                        else{
                                int i = fsize/1024;
                                int j = 0;
                                while(i > 0){
                                    status = recv(client_socket, buffer, sizeof(buffer), 0);
                                    printf("%s", buffer);
                                    fprintf(a, "%s", buffer);                                                                   
                                    close(client_socket);
                                    i--;
                                    j = j + 1024;
                                }
                                j = fsize - i*1024;
                                status = recv(client_socket, buffer, sizeof(buffer), 0);
                                printf("%s", buffer);
                            }                                                
        */                break;
                    }
            }
        close(client_socket);
    }//while end
    return 0;
}