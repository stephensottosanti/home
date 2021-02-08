#include <stdio.h>

int main(void) {
	
	char p1[10];
	char p2[10];
	
	printf("Enter player 1's move: ");
	scanf("%s", p1);

	printf("Enter player 2's move: ");

	if (strcmp(p1,p2)==0)
		printf("You tied\n");
	else
		if(strcmp(p1,"rock") == 0 && strcmp(p2,"scissors") == 0
				printf("p1 won");




	return 0;
}
