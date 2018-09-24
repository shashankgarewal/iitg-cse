int print_star(int n);
int print_star(int n){
	int sp;
	sp = n / 2;
	int st;
	st = 1;
	int i;
    for (i = 1; i <= n; i++) {
    	int j;
        for (j = 1; j <= sp; j++) {
            print ' ';
        }
         
        int count;
        count = 1;
        int k;
        for (k = 1; k <= st; k++) {
        	int tem;
        	tem = k;
        	while(tem >= 0){
        		tem = tem-2;
        	}
        	tem = tem+2;
            if (tem == 0){
                print '*';
            }
            else{
                print count++;
            }
        }
 
 		print endl;
 
        if (i <= n / 2) {
             
            sp = sp - 1;
            st = st + 2;
        }
        else {
            sp = sp + 1;
            st = st - 2;
        }
    }

	return 0;
}
int main(){
	int i;
	i=0;
	int j;
	for(j=0;j<5;j++){

		if(j == 2){
			continue;
		}

		while(1){
			if(i == 10) {
				break;
			}
			print j;
			print '*';
			print i;
			print ' ';

			i = i+1;
		}
		print endl;
		i = 0;
	}
	i=9;
	print_star(i);

}