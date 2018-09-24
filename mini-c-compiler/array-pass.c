int func(int* a);
int func2(int b[3]);

int func(int* a)
{
	int v;
	v = *a;
	return v+5;
}
int func2(int b[3]){
	return b[0]*b[1]*b[2];
}


int main(){
	int i;
	i = 3;
	int j;
	int b[3];
	b[0] = 4;
	b[1] = 5;
	b[2] = 6;

	j =	func(&i) + func2(b);

	print j;
	print endl;
}