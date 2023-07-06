#include "services.h"

int sum(int n) {
    if (n != 0)
        // sum() function calls itself
        return n + sum(n-1); 
    else
        return n;
}

main(){
    int x = sum(20);
    printInt(x);
    return 1;
}