#include <stdio.h>
#include <unistd.h>

int main() {
		int c = 0;
		char *d = "Savvy($) ";
	 int p = printf("%s", d);
	while( p && (c = getchar())){
		if (c != EOF){
			putchar(c);
			
		}
		else{
			printf("out already");
		}

		
	}
	c = 1;
	return 0;
}