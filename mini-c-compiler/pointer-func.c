int func(int* a);

int func(int* a)
{
	int v;
	v = *a;
	return v+5;
}


int main(){
	int i;
	i = 3;
	int j;
	j =	func(&i);
	print j;
	print endl;
}