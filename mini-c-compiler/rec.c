int func(int x);
int func(int x){
	if(x <= 1) {
		return x;
	}
	return func(x-1)+func(x-2);
}
int main(){
	int x;
	int a[3];
	a[2]=5;
	x=*(a+2);
	x=x+func(5);
	print x*2;
	print ' ';
	print x;
	print endl;
	print x;

	print ' ';
	print '-';
	print ' ';

	char c;
	c = 'r';
	print c+1;
	print endl;

	x=6;
	x++;
	print x;
	print endl;

	char arr[10];
	for(x=0;x<10;++x){
		arr[x] = 'a'+x;
		print arr[x];
		print ' ';
	}
	print endl;
	
	return 0;
}