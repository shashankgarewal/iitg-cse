int main(){
	int i;
	i=0;
	int j;
	for(j=0;j<5;j++){
		if(j == 3) {
			i=i+7;
		}
		int k;
		k=0;
		while(k<3){
			i = i + k;
			k=k+1;
		}
		i = i+j*j;
	}
	print i;
	print endl;

}