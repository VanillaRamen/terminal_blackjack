#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


char gethitstand();
void hit(int*, int*);
char playagain();


int main() {
    /* START */
    start:
    int hand = 0;
    int aces = 0;
    srand(time(NULL));
    char hitstand;

    /* INITIAL DRAW TWO*/
    hit(&hand, &aces); hit(&hand, &aces);

    /* HITSTAND LOOP */
    while (1) {
        printf("hand:   (%d)\naces:   (%d)\n", hand, aces);
        hitstand = gethitstand();

        if (hitstand == 'h') {
            hit(&hand, &aces);
        } else break; // stand

        if (hand >= 21) break; // blackjack or bust
    }

    /* STAND OR BUST */
    if (hand > 21) {
        printf("bust! %d\n", hand);
    } else {
        if (hand == 21) printf("super!! ");
        printf("you made %d!\n", hand);
    }

    /* PLAY AGAIN? */
    if (playagain() == 'Y') goto start;
    return 0;
}


/* HIT ME */
void hit(int* h, int* a) {
    int v = rand() % 13 + 1;
    if (v == 1) {
        printf("+11 (ace!)\n");
        *a += 1;
        *h += 11;
    } else {
        if (v > 10) v = 10;
        printf("+%d\n", v);
        *h += v;
    }

    while (*h > 21 && *a) {
        printf("-10 (used ace)\n");
        *h -= 10;
        *a -= 1;
    }
}

/* PROMPT A HITSTAND */
char gethitstand() {
    char uselect[1024];
    while (1) { // getting user input
        printf("hit     [h]\nstand   [s]\nselection: ");
        scanf(" %[^\n]s", uselect);
        if (strlen(uselect) > 1) uselect[0] = 'a';
        switch (uselect[0]) {
            case 'h':
            case 's':
                goto end_hitstand;
            default:
                break;
        }
        printf("invalid selection\n");
    } end_hitstand:
    printf("\n");
    return uselect[0];
}

/* PLAY AGAIN? */
char playagain() {
    char playagain[1024];

    while (1) {
        printf("play again? (Y/n) > ");
        scanf(" %[^\n]s", playagain);
        if (strlen(playagain) > 1) playagain[0] = 'a';
        switch (playagain[0]) {
            case 'Y':
            case 'n':
            case 'N':
                goto end_playagain;
            default:
                break;
        }
        printf("invalid input\n");
    } end_playagain:

    return playagain[0];
}