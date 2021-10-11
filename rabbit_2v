#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int first_state_counter(int, int);

int *x_zero_massive(const int *);

int *c_zero_massive(const int *);

int *c_next(const int *, int *, int *);

int *x_next(const int *, const int *);

int f_next(const int *, int *, int, int *);

int *s_next(const int *);

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

    // output of x_zero_state
    for (int j = 0; j <= 7; j++) {
        printf("%x ", x_zero_state[j]);
    }
    printf("\n");

    // output of c_zero_state
    for (int j = 0; j <= 7; j++) {
        printf("%x ", c_zero_state[j]);
    }
    printf("\n");

    //next states for c and x
    for (int j = 0; j <= 4; j++) {
        int *c_next_state = c_next(c_zero_state, &f, &first_f);
        for (int l = 0; l <= 7; l++) {
            c_zero_state[l] = c_next_state[l];
        }
        int *x_next_state = x_next(x_zero_state, c_zero_state);
        for (int p = 0; p <= 7; p++) {
            x_zero_state[p] = x_next_state[p];
        }
        int *s_next_state = s_next(x_zero_state);
        // далее - XOR с частями текста по 16 бит
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
        c_i_next[j] = (a[j] + c_zero[j] + f_next(c_zero, f, j, first_f)) % (int) pow(2, 32);
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

// next x_state
// !!! NOT WORKING !!!
int *x_next(const int *x_zero, const int *c_zero) {
    int *x_i_next = calloc(8, sizeof(int));
    int *g = calloc(8, sizeof(int));
    for (int j = 0; j <= 7; j++) {
        int for_g = (int) pow((x_zero[j] + c_zero[j]), 2) % (int) pow(2, 32);
        g[j] = (for_g ^ ((for_g) >> 32)) % (int) pow(2, 32);
    }
    x_i_next[0] = (g[0] + ((g[7] << 16) | (g[7] >> 16)) + ((g[6] << 16) | (g[6] >> 16))) % (int) pow(2, 32);;
    x_i_next[1] = (g[1] + ((g[0] << 8) | (g[0] >> 24)) + g[7]) % (int) pow(2, 32);;
    x_i_next[2] = (g[2] + ((g[1] << 16) | (g[1] >> 16)) + ((g[0] << 16) | (g[0] >> 16))) % (int) pow(2, 32);;
    x_i_next[3] = (g[3] + ((g[2] << 8) | (g[2] >> 24)) + g[1]) % (int) pow(2, 32);;
    x_i_next[4] = (g[4] + ((g[3] << 16) | (g[3] >> 16)) + ((g[2] << 16) | (g[2] >> 16))) % (int) pow(2, 32);;
    x_i_next[5] = (g[5] + ((g[4] << 8) | (g[4] >> 24)) + g[3]) % (int) pow(2, 32);;
    x_i_next[6] = (g[6] + ((g[5] << 16) | (g[5] >> 16)) + ((g[4] << 16) | (g[4] >> 16))) % (int) pow(2, 32);;
    x_i_next[7] = (g[7] + ((g[6] << 8) | (g[6] >> 24)) + g[5]) % (int) pow(2, 32);;
    return x_i_next;
}

// s_next
int *s_next(const int *x_state)
{
    int *s_next_state = calloc(8, sizeof(int));
    s_next_state[0] = (x_state[0] >> 16) ^ (x_state[5] & ((1 << x_state[5]) - 1));
    s_next_state[1] = (x_state[0] & ((1 << x_state[0]) - 1)) ^ (x_state[3] >> 16);
    s_next_state[2] = (x_state[2] >> 16) ^ (x_state[7] & ((1 << x_state[7]) - 1));
    s_next_state[3] = (x_state[2] & ((1 << x_state[1]) - 1)) ^ (x_state[5] >> 16);
    s_next_state[4] = (x_state[4] >> 16) ^ (x_state[1] & ((1 << x_state[1]) - 1));
    s_next_state[5] = (x_state[4] & ((1 << x_state[5]) - 1)) ^ (x_state[5] >> 16);
    s_next_state[6] = (x_state[6] >> 16) ^ (x_state[3] & ((1 << x_state[3]) - 1));
    s_next_state[7] = (x_state[6] & ((1 << x_state[6]) - 1)) ^ (x_state[1] >> 16);
    return s_next_state;
}


// Issues :
// 1. mod 2^32 (all state variables functions)
// 2. a[i] - negative or positive? (f_next and c_next)
// 3. >> 32 not working (x_next)
// 4. for_g XOR (^) not working [long long int type] (x_next)
// 5. how to get [0,15] and [16,31] bites correctly? (s_next)
