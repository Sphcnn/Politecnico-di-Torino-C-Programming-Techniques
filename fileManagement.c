#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *fptr, *fptrcopy ;
    int  make_it_uppercase, line_length;
    fptr = fopen("P1_input.txt","r");
    fptrcopy = fopen("P1_output.txt","w");
    if (fptr == NULL) {
        printf("Error opening file");
    }
    else {
        if (fptrcopy == NULL) {
            printf("Error opening file");
        }
        else {
            char myletter;
            line_length = 0;
            do {
                myletter = fgetc(fptr);
                line_length++;
                if (line_length > 25) {
                    fprintf(fptrcopy,"\t|%d",line_length-1);
                    fputc('\n', fptrcopy);
                    line_length = 0;
                }
                if (isdigit(myletter)) {
                    myletter = '*';
                    fputc(myletter, fptrcopy);
                }

                else if (isalpha(myletter)) {
                    if (make_it_uppercase != 0) {
                        myletter = toupper(myletter);
                        make_it_uppercase = 0;
                    }
                    fputc(myletter, fptrcopy);
                }

                else if (ispunct(myletter)) {
                    if (myletter == '.' || myletter == '?' || myletter=='!') {
                            make_it_uppercase = 1;
                    }
                    fputc(myletter, fptrcopy);
                    fputc(' ', fptrcopy);
                }

                else if (isspace(myletter)) {
                    fputc(myletter, fptrcopy);
                }


            }while(myletter!=EOF);
        }
    }

    fclose(fptrcopy);
    fclose(fptr);


}