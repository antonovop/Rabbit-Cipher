#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int first_state_counter(int, int);

int *x_zero_massive(const int *);

int *c_zero_massive(const int *);

int *c_next(const int *, int *, int *);

int f_next(const int *, int *, int, int *);

int main() {
    int f = 0;
    int first_f = 0;
    int *k_mas = calloc(8, sizeof(int));

    //getting keys version_1
    for (int j = 0; j <= 7; j++) {
        char key[] = "";
        scanf("%s", key);
        k_mas[j] = (int) strtoul(key, 0, 16);
    }

    // for x_zero_state and c_zero_state
    int *x_zero_state = x_zero_massive(k_mas);
    int *c_zero_state = c_zero_massive(k_mas);

    // output for x_zero_state
    for (int j = 0; j <= 7; j++) {
        printf("%d ", x_zero_state[j]);
    }
    printf("\n");

    // output of c_zero_state
    for (int j = 0; j <= 7; j++) {
        printf("%d ", c_zero_state[j]);
    }
    printf("\n");

//    int *c_next_state = c_next(c_zero_state, &f, &first_f);
//    for (int o = 0; o <= 7; o++) {
//        printf("%x ",c_next_state[o]);
//    }
//    printf("\n");

    //next state for c
    for (int j = 0; j <= 4; j++) {
        int *c_next_state = c_next(c_zero_state, &f, &first_f);
        for (int o = 0; o <= 7; o++) {
            printf("%x ",c_next_state[o]);
        }
        printf("\n");
        for (int l = 0; l <= 7; l++) {
            c_zero_state[l] = c_next_state[l];
        }
    }

    return 0;
}

//state variables and counters setup
int first_state_counter(int k_1, int k_2) {
    int var_or_counter = (k_1 << 8) | k_2;
    return var_or_counter;
}


//function for x_zero_mas
int *x_zero_massive(const int *k_mas) {
    int k1;
    int k2;
    int *x_mas = calloc(8, sizeof(int));
    for (int j = 0; j <= 7; j++) {
        if (j % 2 == 1) {
            k1 = k_mas[(j + 5) % 8];
            k2 = k_mas[(j + 4) % 8];
        } else {
            k1 = k_mas[(j + 1) % 8];
            k2 = k_mas[j];
        }
        x_mas[j] = first_state_counter(k1, k2);
    }
    return x_mas;
}

// function for c_zero_mas
int *c_zero_massive(const int *k_mas) {
    int k1;
    int k2;
    int *c_mas = calloc(8, sizeof(int));
    for (int j = 0; j <= 7; j++) {
        if (j % 2 == 1) {
            k1 = k_mas[j];
            k2 = k_mas[(j + 1) % 8];
        } else {
            k1 = k_mas[(j + 4) % 8];
            k2 = k_mas[(j + 5) % 8];
        }
        c_mas[j] = first_state_counter(k1, k2);
    }
    return c_mas;
}

//next c_state
int *c_next(const int *c_zero, int *f, int *first_f) {
    int a[8] = {(int) 0x4D34D34D, (int) 0xD34D34D3, (int) 0x34D34D34, (int) 0x4D34D34D, (int) 0xD34D34D3,
                (int) 0x34D34D34, (int) 0x4D34D34D, (int) 0xD34D34D3};
    int *c_i_next = calloc(8, sizeof(int));
    for (int j = 0; j <= 7; j++) {
        c_i_next[j] = (a[j] + c_zero[j] + f_next(c_zero, f, j, first_f)) % (int)pow(2,32);
    }
    return c_i_next;
}

// next f_state
int f_next(const int *c_zero, int *f, int j, int *first_f) {
    int a[8] = {(int) 0x4D34D34D, (int) 0xD34D34D3, (int) 0x34D34D34, (int) 0x4D34D34D, (int) 0xD34D34D3,
                (int) 0x34D34D34, (int) 0x4D34D34D, (int) 0xD34D34D3};
    if (*first_f == 0) {
        *f = 0;
        *first_f = 1;
    } else if (j == 1 && ((c_zero[0] + a[0] + *f) >= pow(2, 32))) {
        *f = 1;
    } else if (j != 1 && ((c_zero[j - 1] + a[j - 1] + *f) >= pow(2, 32))) {
        *f = 1;
    } else {
        *f = 0;
    }
    return *f;
}