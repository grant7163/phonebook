#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("orig.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (!fp) {
        printf("ERROR opening input file orig.txt\n");
        exit(0);
    }
    int i = 0;
    char append[50], find[50];
    double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a, orig_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &orig_a, &orig_f);
        orig_sum_a += orig_a;
        orig_sum_f += orig_f;
    }
    fclose(fp);

    fp = fopen("opt.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double opt_sum_a = 0.0, opt_sum_f = 0.0, opt_a, opt_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &opt_a, &opt_f);
        opt_sum_a += opt_a;
        opt_sum_f += opt_f;
    }
    fclose(fp); 

    fp = fopen("hash_opt.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double hash_opt_sum_a = 0.0, hash_opt_sum_f = 0.0, hash_opt_a, hash_opt_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &hash_opt_a, &hash_opt_f);
        hash_opt_sum_a += hash_opt_a;
        hash_opt_sum_f += hash_opt_f;
    }
    fclose(fp); 

    fp = fopen("bst_opt.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double bst_opt_sum_a = 0.0, bst_opt_sum_f = 0.0, bst_opt_a, bst_opt_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &bst_opt_a, &bst_opt_f);
        bst_opt_sum_a += bst_opt_a;
        bst_opt_sum_f += bst_opt_f;
    }


    fprintf(output, "append() %.8lf %.8lf %.8lf %.8lf\n",orig_sum_a / 100.0, opt_sum_a / 100.0, hash_opt_sum_a / 100.0, bst_opt_sum_a / 100.0);
    fprintf(output, "findName() %.8lf %.8lf %.8lf %.8lf", orig_sum_f / 100.0, opt_sum_f / 100.0, hash_opt_sum_f / 100.0, bst_opt_sum_f / 100.0);
    fclose(output);
    fclose(fp);
    return 0;
}