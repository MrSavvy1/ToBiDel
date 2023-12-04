#include <stdio.h>
#include <unistd.h>

int main() {
		int c = 0;
		char *d = "Savvy($) ";
	 int p = printf("%s", d);
	while( p && (c = getline()) !=EOF){
	
			putchar(c);
		if (c == '\n' || c == '\t' || c == '\0'){
			printf("Savvy($) ");
		}

		
	}
	c = 1;
	return 0;
}