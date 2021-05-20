
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Used for randon seed
#include <math.h> // Used for 'sqrt'

#define MAXX 81
#define MAXY 81
#define CENTREX 40
#define CENTREY 40
#define MAXSTEPS 40

char data[MAXY][MAXX];

// Clear data from one step
void clear_step(int step) {
    int i,j;

    for (j=0; j<MAXY; j++){
        for(i=0;i<MAXX;i++){
            if((j+i+step)%2 == 0) {
                data[j][i] = ' ';
            }
        }
    }
}

// Clear all data
void clear_data() {
    int i,j;

    for (j=0; j<MAXY; j++){
        for(i=0;i<MAXX;i++){
            data[j][i] = ' ';
        }
    }
}

// Random cell generator
char cell_create() {
    char r;
    if (rand() %2 == 0) {
        r = '|';
    } else {
        r = '-';
    }
    return r;
}

// Create data step
void data_step(int step) {
    int i,j;

    for (j=0; j<MAXY; j++){
        for(i=0;i<MAXX;i++){
            // Only operate on diagonal checkerboard squares
            if ((j+i+step)%2 == 0) {
                int t = 0;
                char r = ' '; // Result character
                char da = ' ';
                char db = ' ';
                char dc = ' ';
                char dd = ' ';
                //        da
                //         |
                // dd - data[j][i] - db
                //         |
                //         dc

                // Edge conditions
                if (j-1 >= 0)    { da = data[j-1][i]; };
                if (j+1 < MAXY) { dc = data[j+1][i]; };
                if (i-1 >= 0)    { dd = data[j][i-1]; };
                if (i+1 < MAXX) { db = data[j][i+1]; };

                if ((da == 'v') || (da == '|')) { r = 'v'; t++; }
                if ((db == '<') || (db == '-')) { r = '<'; t++; }
                if ((dc == '^') || (dc == '|')) { r = '^'; t++; }
                if ((dd == '>') || (dd == '-')) { r = '>'; t++; }

                if (t > 0) {
                    // Incoming momentum
                    // If t = 1, r already set to same character.
                    if (t > 1) { r = '*'; }
                } else {
                    // Adjacent momentum
                    t = 0;
                    if (da != ' ') { t++; }
                    if (db != ' ') { t++; }
                    if (dc != ' ') { t++; }
                    if (dd != ' ') { t++; }
                    if (t > 0) { r = '*'; }
                }

                if (r == '*') r = cell_create();
                data[j][i] = r;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// Draw Circle
void draw_circle(int radius) {
    int i,j;
    int sq_x, sq_y;
    for(i=0; i<MAXX; i++){
        sq_y = pow(1.0*radius,2) - pow(1.0*CENTREX-i,2);
        if (sq_y >= 0){
            j = CENTREY + floor(sqrt(sq_y));
            data[j][i] = '#';
            j = CENTREY - floor(sqrt(sq_y));
            data[j][i] = '#';
        };
    }

    for(j=0; j<MAXX; j++){
        sq_x = pow(1.0*radius,2) - pow(1.0*CENTREY-j,2);
        if (sq_x >= 0){
            i = CENTREX + floor(sqrt(sq_x));
            data[j][i] = '#';
            i = CENTREX - floor(sqrt(sq_x));
            data[j][i] = '#';
        };
    }
}

//////////////////////////////////////////////////////////////////////////////
// Print data array
void print_data() {
    int i,j;

    // printf("\033[1;31m"); printf("Hello world\n"); printf("\033[0m");

    for (j=0; j<MAXY; j++){
        for(i=0;i<MAXX;i++){
            switch (data[j][i]) {
            case '^':
                printf("\033[1;31m%c\033[0m", data[j][i]);
                break;
            case '>':
                printf("\033[0;32m%c\033[0m", data[j][i]);
                break;
            case 'v':
                printf("\033[0;33m%c\033[0m", data[j][i]);
                break;
            case '<':
                printf("\033[0;34m%c\033[0m", data[j][i]);
                break;
            case '#':
                printf("\033[1;107m%c\033[0m", data[j][i]);
                break;
            default:
                printf("%c", data[j][i]);
            }
        }
        printf("\n");
    }
}

//////////////////////////////////////////////////////////////////////////////
int main() {
    int i,j;
    int step = 0;

    // Set random seed from current time.
    srand(time(0));

    // printf() displays the string inside quotation
    printf("Arctic Circle!\n");
    printf("--------------\n");
    printf("maxx: %d,  maxy: %d\n", MAXX, MAXY);
    printf("maxsteps: %d", MAXSTEPS);

    for (j=0; j<MAXY; j++){
        for(i=0;i<MAXX;i++){
            data[j][i] = ' ';
        }
    }

    //    print_data();
    clear_data();

    // Set initial condition
    data[CENTREY][CENTREX] = '|';

    for (step = 1; step <= 40; step++){
        clear_step(step);
        data_step(step);
    }

    printf("Step: %d\n", step);
    clear_step(step);

    // Draw circle around centre.
    // draw_circle(MAXSTEPS);
    print_data();
    return 0;
    }
