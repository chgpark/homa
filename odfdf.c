#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


int going_back(int** tmp, int plrows, int plcols, int maxdia) {
    int *maxdia_dir = (int*)malloc(2*sizeof(int));
        
printf("%d\t%d\t%d\n", plrows, plcols, tmp[plrows][plcols]);
    //Is it start.
    if (plrows == 0 && plcols == 0)
        return maxdia;
    //Is there dia.
    if (tmp[plrows][plcols])
    {
        maxdia += 1;
        tmp[plrows][plcols] -= 1;
    }
    if ((plcols == 0 || tmp[plrows][plcols-1] < 0) && (plrows == 0 || tmp[plrows-1][plcols] < 0))
        return 0;
    //Go to next.
    if (plcols > 0 && tmp[plrows][plcols-1] >= 0)
        maxdia_dir[0] = going_back(tmp, plrows, plcols-1, maxdia);
    if (plrows > 0 && tmp[plrows-1][plcols] >= 0)
        maxdia_dir[1] = going_back(tmp, plrows-1, plcols, maxdia);
    return maxdia_dir[0] > maxdia_dir[1] ? maxdia_dir[0] : maxdia_dir[1];
}

int check_dest(int n, int** mat, int plrows, int plcols, int maxdia) {
    
    int* maxdia_dir = (int*)malloc(2*sizeof(int));
    int** tmp = (int**)malloc(n*sizeof(int*));
    int ii= -1;
    while (++ii < n)
        tmp[ii] = (int*)malloc(n*sizeof(int));
    ii = -1;
    while (++ii < n)
        memcpy(tmp[ii], mat[ii], n*sizeof(int));
    
printf("%d\t%d\t%d\n", plrows, plcols, tmp[plrows][plcols]);
    int flag = 0;
    //Is it dest
    if (plrows == n-1 && plcols == n-1)
        return maxdia;
    //Is there dia
    if (tmp[plrows][plcols])
    {
        flag = 1;
        maxdia += 1;
        tmp[plrows][plcols] -= 1;
    }
    if ((plcols == n-1 || tmp[plrows][plcols+1] < 0) && (plrows == n-1 || tmp[plrows+1][plcols] < 0))
        return -1;
    //Go to next
    if (plcols < n-1 && tmp[plrows][plcols+1] >= 0)
        maxdia_dir[0] = check_dest(n, tmp, plrows, plcols+1, maxdia);
    if (plrows < n-1 && tmp[plrows+1][plcols] >= 0)
        maxdia_dir[1] = check_dest(n, tmp, plrows+1, plcols, maxdia);
    
    if (maxdia_dir[0] < 0 && maxdia_dir[1] < 0 && flag)
        tmp[plrows][plcols] += 1;
    
    ii = -1;
    while (++ii < n)
        memcpy(mat[ii], tmp[ii], n*sizeof(int));
    return maxdia_dir[0] > maxdia_dir[1] ? maxdia_dir[0] : maxdia_dir[1];
}

int collect_max(int rows, int cols, int** mat) {
    int maxdia;
    maxdia = check_dest(rows, mat, 0, 0, 0);
printf("%d\n", maxdia);
    if (maxdia < 0)
        return 0;
    else
        maxdia = going_back(mat, rows-1, cols-1, maxdia);
    if (maxdia < 0)
        return 0;
    return maxdia;
}

int main()
{
    FILE *f = stdout;
    char *output_path = getenv("OUTPUT_PATH");
    if (output_path) {
        f = fopen(output_path, "w");
    }

    int res;
    int mat_rows = 0;
    int mat_cols = 0;
    scanf("%d", &mat_rows);
    scanf("%d", &mat_cols);

    int** mat = (int**)malloc(mat_rows*sizeof(int*));
    int mat_init_i = 0;
    for (mat_init_i = 0; mat_init_i < mat_rows; ++mat_init_i) {
        mat[mat_init_i] = (int*)malloc(mat_cols*(sizeof(int)));
    }

    int mat_i, mat_j;
    for (mat_i = 0; mat_i < mat_rows; mat_i++) {
        for (mat_j = 0; mat_j < mat_cols; mat_j++) {
            int mat_item;
            scanf("%d", &mat_item);

            mat[mat_i][mat_j] = mat_item;
        }
    }

    res = collect_max(mat_rows, mat_cols, mat);
    fprintf(f, "%d\n", res);

    fclose(f);
    return 0;
}

