int func(int x);
int func2(int x);
int func2(int x){
	return func(x)+3;
}
int func(int x){
	if(x <= 1) {
		return x;
	}
	return func(x-1)+func(x-2);
}
int main(){
	int x;
	x=6;
	x=func2(x);
	print x;
}