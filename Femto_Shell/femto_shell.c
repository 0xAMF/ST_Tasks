#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (100)

int main(void)
{
  char user_input[MAX];
  
  while(1) {
    printf("Alo?! $ ");
    scanf("%s", user_input);
    
    if (!strcmp(user_input, "exit")) { // equal
      printf("Ok, Bye :^)\n");
      break;
    }
    else {
      printf("You entered: %s\n", user_input);
    }
  }
  
 return EXIT_SUCCESS;
}
