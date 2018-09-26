/* strcpy example */
#include <stdio.h>
#include <string.h>

int main ()
{
    FILE* fp = fopen("a", "rb");
        	fseek(fp, 0, SEEK_END);
        	long fsize = ftell(fp);
            printf("%ld", fsize);
  return 0;
}

/*    char IPbuffer[] = "172", NODE[] = "1729\n823928";
    int size_ip = strlen(IPbuffer);
    int size_n = strlen(NODE);
        for(int i = 0; i < (size_n - size_ip); i++){
            NODE[i] = NODE[i + size_ip];
        }
        NODE[size_n - size_ip] = '\0';
        printf("%s\n", NODE);
   return(0);
}
*/