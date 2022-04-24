#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int t_mat[3][3];

t_mat* matice(t_mat* A, t_mat* B, char operation)
{
    t_mat* result = malloc(sizeof(t_mat));

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(operation == '+')
                (*result)[i][j] = (*A)[i][j] + (*B)[i][j];
            else if(operation == '-')
                (*result)[i][j] = (*A)[i][j] - (*B)[i][j];
            else return NULL;
        }

    return result;
}


int gen_random_int(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

t_mat* gen_matrix(int lower, int upper)
{
    t_mat* matrix = malloc(sizeof(t_mat));

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            (*matrix)[i][j] = gen_random_int(lower, upper);

    return matrix;
}

void print_matrix(t_mat* matrix)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            printf("%5d", (*matrix)[i][j]);

        printf("\n");
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));

    t_mat** matrices = malloc(5 * sizeof(t_mat*));

    // Generovani matic
    for(int i = 0; i < 5; i++)
        matrices[i] = gen_matrix(0, 50);

    // Zapis matic do binarniho souboru
    FILE* fp = fopen("output.bin", "w");

    for(int i = 0; i < 5; i++)
        fwrite(matrices[i], sizeof(t_mat), 1, fp);

    fclose(fp);

    // Uvolneni pameti
    for(int i = 0; i < 5; i++)
        free(matrices[i]);


    matrices = malloc(5 * sizeof(t_mat*));

    // Nacteni matic z binarniho souboru
    fp = fopen("output.bin", "r");

    for(int i = 0; i < 5; i++)
    {
        matrices[i] = malloc(sizeof(t_mat));
        fread(matrices[i], sizeof(t_mat), 1, fp);
    }

    fclose(fp);

    // Nacteni operace a operandu
    int matrix_a, matrix_b;
    char operation;

    do {
        printf("Zadejte rovnici (napr. 1 + 2): ");
        scanf("%d %c %d", &matrix_a, &operation, &matrix_b);
        printf("\n");
    }
    while(operation != '+' && operation != '-' && printf("Nedefinovana operace!\n\n"));

    // Vypocet
    t_mat *matrix = matice(matrices[matrix_a-1], matrices[matrix_b-1], operation);

    // Vypis operandu a vysledku
    if(matrix != NULL)
    {
        printf("Matice %d:\n", matrix_a);
        print_matrix(matrices[matrix_a-1]);

        // Pokud jsou operandy dve ruzne matice
        if(matrices[matrix_a-1] != matrices[matrix_b-1])
        {
            printf("Matice %d:\n", matrix_b);
            print_matrix(matrices[matrix_b-1]);
        }

        printf("Výsledná matice:\n");
        print_matrix(matrix);
    }
    else
        printf("Nedefinovaná operace\n");

    // Uvolneni pameti
    for(int i = 0; i < 5; i++)
        free(matrices[i]);

    return 0;
}
