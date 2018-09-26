#define _OPEN_SYS_ITOA_EXT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include <sys/socket.h>
#include <sys/types.h>

//to store address information
#include <netinet/in.h>
#include <arpa/inet.h>

int main (int argc, char *argv[]) {
    int port, node_socket, newsocket, status;
    unsigned int myPort;
    char check = ' ', buffer[50], IPbuffer[30], temp[10], fname[20];
    socklen_t address_len;
    FILE *fp;
        if (argc != 3) {
            fprintf(stderr, "usage %s hostname port\n", argv[0]);
            return -1;
        }
    sscanf( argv[2], "%d" "%c", &port, &check);
    port = atoi(argv[2]);
        if(check != ' ' | port == 0){
            fprintf(stderr, "Invalid port\n");
            return -1;
        }

    								/*stage 1*/
    //ip address structure for the socket
	struct sockaddr_in relay_address, client_address, node_address;
	//specify address family, i.e, domain
	relay_address.sin_family = AF_INET;
	relay_address.sin_port = htons(port);
	//htons converts the int port no. to appropriate type
	relay_address.sin_addr.s_addr = inet_addr(argv[1]);
	//sin_addr is already a struct, so it have different fields
	//s_addr will give actual server address
    //TCP socket is made
    if( inet_pton(AF_INET, argv[1], &relay_address.sin_addr) <= 0 ){
		fprintf(stderr, "invalid IP address: %s\n", argv[1]);
        return -1;
    }
    node_socket = socket(AF_INET, SOCK_STREAM, 0);
	    if(node_socket <0){
	    	perror("[-] Error creating socket for connecting with relay server\n");
	    	return -1;
	    }
        printf("Node socket is created\n");
    	
    // connect_status=0 everythings okay, -1 there's some error    
	status = connect(node_socket, (struct sockaddr *) &relay_address, sizeof(relay_address));
	    if(status <0){
	    	perror("[-] Error connecting with relay server");
	    	return -1;
	    }
        printf("connected with relay socket\n");
    int addrlen= sizeof(node_address);
    getsockname(node_socket, (struct sockaddr *) &node_address, &addrlen);
    inet_ntop(AF_INET, &node_address.sin_addr, IPbuffer, sizeof(IPbuffer));
    myPort = ntohs(node_address.sin_port);
    strcat(IPbuffer, " ");
    sprintf(temp, "%u", myPort);
    strcat(temp, "\n");
    strcat(IPbuffer, temp);
    //printf("Local ip address & port: %s\n", IPbuffer);
    status = send(node_socket, IPbuffer, strlen(IPbuffer), 0);
        if( status < 0){
            perror("[-] Error sending IP information");
        }
        else
            printf("IP information is sent : %s\n", IPbuffer);
    close(node_socket);



    //stage 3
    node_socket = socket(AF_INET, SOCK_STREAM, 0);
	    if( node_socket <0 ){
	    	perror("[-] Error opening socket");
	    	exit(EXIT_FAILURE);
	    }
	//specify address family, i.e, domain
	node_address.sin_family = AF_INET;
	node_address.sin_port = htons(myPort);
	//htons converts the int port no. to appropriate type
	node_address.sin_addr.s_addr = INADDR_ANY;
    status = bind(node_socket, (struct sockaddr *) &node_address, sizeof(relay_address));
        if( status <0 ){
            perror("[-] Error on binding");
            exit(EXIT_FAILURE);
        }
        printf("Bind to the port : %d\n", myPort);
    //listen for connection(request)
    status = listen(node_socket, 4);
        if( status != 0 )
            perror("[-] Error on listening");
        else
            printf("Listening......\n");
    address_len = sizeof(client_address);
    newsocket= accept( node_socket, (struct sockaddr *)&client_address, &address_len );
        if( newsocket < 0 ){
            perror("[-] ERROR on accepting");
            exit(EXIT_FAILURE);
        }
    bzero(fname, sizeof(fname));
    status = recv(newsocket, fname, sizeof(fname), 0);
        if( status < 0 )
            perror("[-] Error on recieving request message from client.");
        else{
            printf("Search for the %s file\n",fname);
            //find -iname 'relay.c' > a
            bzero(IPbuffer, sizeof(IPbuffer));
            sprintf(IPbuffer, "find -iname \'%s\' > a", fname);
            //location of fname will be stored in file "a"
            system(IPbuffer);
            //reading file 
            fp = fopen("a", "rb");
        	fseek(fp, 0, SEEK_END);
        	long fsize = ftell(fp);
                if(fsize == 0){
                    printf("%s file isn't in with you\n", fname);
                    status = send( newsocket, "0", 1, 0 );
                        if( status < 0 )
                            perror("[-] Error sending node info to client");
                        else
                            printf("SENT RESPOND client : SEND no %s file\n",IPbuffer);
                    close(newsocket);
                    close(node_socket);
                    fclose(fp);
                    exit(EXIT_SUCCESS);
   	             }
                else{
                    status = send( newsocket, "1", 1, 0 );
                        if( status < 0 )
                            perror("[-] Error sending node info to client");
                        else
                            printf("SENT RESPOND client : SEND %s file exist\n",IPbuffer);                    
                    //passing file location info from file to string
        	        char *string = (char *)malloc((fsize + 1)*sizeof(char));
                    rewind(fp);
        	        fread(string, fsize, 1, fp);
        	        fclose(fp);
                    string[fsize] = '\0';            
                    //for knowing file location
                    for(int i = 0; i < fsize; i++){
                        if(string[i] == '\n')
                            string[i] = ' ';
                    }
                    // printf("%s", string);
                    char floc[50];
                    sscanf( string, "%s", floc);
                    bzero(string, sizeof(string));
                    // printf("%s\n", floc);

                    //for sending file
                    fp = fopen( floc , "rb");
        	        fseek(fp, 0, SEEK_END);//send the pointer to beginning of the file
                    fsize = ftell(fp);
        	        char *string1 = malloc(fsize + 1);
                    rewind(fp);
        	        fread(string1, fsize, 1, fp);
        	        fclose(fp);
                    string1[fsize] = 0;
                    char flen[10];
                    sprintf(flen, "%ld", fsize);
                    status = send( newsocket, flen, strlen(flen), 0 );
                        if( status < 0 )
                            perror("[-] Error sending node info to client");
                        else
                            printf("file length is sent : '%s'\n",flen);
                    if(fsize <= 1024){
                        status = send( newsocket, string1, strlen(string1), 0 );
                            if( status < 0 )
                                perror("[-] Error sending node info to client");
                            else
                                printf("file content is sent : '%s'\n",string1);
                    }
                    else{
                        int i = fsize/1024;
                        int j = 0;
                        while(i > 0){
                            status = send( newsocket, string1 + j, 1024, 0 );
                            i--;
                            j = j+1024;
                        }
                        j = i*1024;
                        fsize = fsize - i*1024;
                        status = send( newsocket, string1+j, fsize, 0 );
                    }
                    system("rm a");
	                printf("The file content sent successfully\n");
                }// else end
        }//search for fname end
    return 0;
}