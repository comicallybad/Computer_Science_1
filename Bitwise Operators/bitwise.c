
//this code explaines some bitwise operations
//Then the code also shows how we can iterate
//through subsets of an array

#include <stdio.h>

int sumbits(int n);

int main() {


    int x, y;

    x = 47;
    y = 72;

    int xor  = x ^ y; // xor
    int and = x & y; // and
    int or = x | y; // or
    int not = ~x;

    printf("xor = %d, and = %d, or = %d, not = %d\n", xor, and, or, not);

    int value = 0x13355777; //if a number start with 0x, it means it is a hexadecimal number
    printf("%d\n", value); //equivalent decimal

    int twopower = 1 << 10;
    int half = twopower >> 1;
    printf("twopower = 1 << 10 is %d\n", twopower);
    printf("twopower >> 1  = %d\n", half);

    printf("sum of the bits of %d is %d\n", 47, sumbits(47));

    printf("Starting the process for iterating through subset\n");
    int i, j;
    int n = 5;
    int array[] = {9, 3, 4, 5, 12};
    int target = 22;

    for (i=0; i < (1 << n); i++) { //this loop is eqivalent of for(i=0; i<32; i++)

        int sum = 0;
        // loop through each location in the binary representation of i
        for (j=0; j < n; j++) //n is 5 in our example
        {
            printf(" i =%d, j = %d, 1 << j = %d,(i & (1 << j)) = %d\n", i, j, 1 << j, (i & (1 << j)));
            /*1<<j produces 1 (00001), 2(00010), 4(00100), 8(01000), 16(10000)
            and we use it as mask to extract the bits that are set in i*/
            if ( (i & (1 << j)) != 0 )
                sum += array[j];

        }


        printf("i=%d sum = %d\n", i, sum);
        if (sum == target)
            printf("Can add up to the target!\n");

    }

    // Forming Color Information
    // Extracting Color Information

    system("PAUSE");
    return 0;

}

int sumbits(int n) {

    int sum = 0;
    while (n > 0) {
        sum += (n & 1);// everything cancel out except the right most bit
        n = (n >> 1); //bringing each digit to the right most bit
    }
    return sum;
}
