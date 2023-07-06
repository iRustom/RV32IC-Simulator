#include "services.h"

int main() {
    char s[] = "Programming is fun";
    int i;

    for (i = 0; s[i] != '\0'; ++i);
    
    printString("Length of the string: ");
    
    printInt(i);

    return 0;
}