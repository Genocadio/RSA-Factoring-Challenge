#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void factorize(mpz_t number)
{
    mpz_t i, quotient;
    mpz_inits(i, quotient, NULL);

    mpz_set_ui(i, 2);

    while (mpz_cmp(i, number) <= 0)
    {
        mpz_mod(quotient, number, i);

        if (mpz_cmp_ui(quotient, 0) == 0)
        {
            gmp_printf("%Zd=%Zd*%Zd\n", number, i, quotient);
            break;
        }

        mpz_add_ui(i, i, 1);
    }

    mpz_clears(i, quotient, NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./factorize <file>\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    mpz_t number;
    mpz_init(number);

    while (gmp_fscanf(file, "%Zd", number) == 1)
    {
        factorize(number);
    }

    mpz_clear(number);
    fclose(file);

    return 0;
}
