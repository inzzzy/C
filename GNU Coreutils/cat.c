#include <stdio.h>
#include <stdlib.h>


/*  Simple implementation of the GNU Coreutils Cat program.
        Inputs from filestream and prints to stdout.      */

void concatenate(FILE *from, FILE *to){
    int c;
    while ( (c = getc(from)) != EOF )
        fprintf(to, "%c", c);
}

int main(int argc, char *argv[]){
    FILE *fp;

    if (argc == 1)
        concatenate(stdin, stdout); // If no arguments are provided, command will simply copy from STDIN to STDOUT
    else
        while(--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL){
                fprintf(stderr, "ERROR: Can not open file %s\n", *argv); 
                exit(1);
            }
            else{
                concatenate(fp, stdout);
                fclose(fp);
            }

    return 0;
}


