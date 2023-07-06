// Type your code here, or load an example.
#include "services.h"

int nums[]={1, 2, 4, 6, 7, 9, 7, 11, 13, 17};
int dble(int num) {
    return num + num;
} 
main(){
    int volatile sum = 0;
    for(int i=0; i<10; i++)
        sum+=dble(i);
    printInt(sum);
    return 1;
}

