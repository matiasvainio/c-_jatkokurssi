/*

  Harjoitus 3

  Optimoi suorien tunnistus. Älä muuta kääntäjäoptioita.
  Pidä ohjelma yksisäikeisenä.

  Vertaa alkuperäistä ja optimoitua versiota:

  - kuinka paljon enemmän muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?

  Käännös: gcc straight.c -o straight

*/

#include <stdint.h>
#include <stdio.h>
#include <time.h>

const int NUM_OF_CARDS = 5;
uint16_t bit_vector = 0;

int straight_lookup_table[1228800];

inline int is_straight(int *k);
inline int is_straight2(int *k);
inline void sort(int *k);
inline void create_lookup_table();
inline int is_quadsorfullhouse(int *k);

#define SET_BIT(BF, N) BF |= ((uint16_t)0x0000000000000001 << (N))
#define CLR_BIT(BF, N) BF &= ~((uint16_t)0x0000000000000001 << (N))
#define IS_BIT_SET(BF, N) (((BF) >> (N)) & 0x1)

int main() {
    create_lookup_table();
    printf("Taulu luotu\n");
    /*
      Käydään läpi kaikki viiden kortin permutaatiot, ja lasketaan
      kuin monta suoraa (värisuoraa tai tavallista) löytyy.

      Ks. Wikipedia http://en.wikipedia.org/wiki/Poker_probability :

      Royal flush     4      combinations
      Straight flush  36     combinations
      Straight        10,200 combinations

      Koska 5 korttia voi olla 5 x 4 x 3 x 2 x 1 = 120 järjestyksessä,
      pitäisi suoria löytyä (10200 + 36 + 4) x 120 = 1228800 kappaletta.

    */
    int k0, k1, k2, k3, k4;      /* Pakan kortit, 0..51*/
    int k[5];                    /* Korttien numeroarvot, 2..14*/
    int suoria, quads_fullhouse; /* Suorien lkm*/
    clock_t t1, t2;

    t1 = clock();
    suoria = 0;
    for (k0 = 0; k0 < 52; ++k0) {
        for (k1 = 0; k1 < 52; ++k1) {
            if (k1 == k0) continue;
            for (k2 = 0; k2 < 52; ++k2) {
                if (k2 == k0 || k2 == k1) continue;
                for (k3 = 0; k3 < 52; ++k3) {
                    if (k3 == k0 || k3 == k1 || k3 == k2) continue;
                    for (k4 = 0; k4 < 52; ++k4) {
                        if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3) continue;

                        /*
                          Lasketaan korttien numeroarvot ja
                          tarkistetaan onko suora.
                        */
                        k[0] = (k0 % 13) + 2;
                        k[1] = (k1 % 13) + 2;
                        k[2] = (k2 % 13) + 2;
                        k[3] = (k3 % 13) + 2;
                        k[4] = (k4 % 13) + 2;
                        if (is_straight(k) == 1)
                            ++suoria;
                    }
                }
            }
        }
    }
    t2 = clock();
    printf("Suoria     : %d kpl (oikea arvo 1228800)\n", suoria);
    printf("Aikaa kului (ilman hakutaulua): %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

    t1 = clock();
    suoria = 0;
    for (k0 = 0; k0 < 52; ++k0) {
        for (k1 = 0; k1 < 52; ++k1) {
            if (k1 == k0) continue;
            for (k2 = 0; k2 < 52; ++k2) {
                if (k2 == k0 || k2 == k1) continue;
                for (k3 = 0; k3 < 52; ++k3) {
                    if (k3 == k0 || k3 == k1 || k3 == k2) continue;
                    for (k4 = 0; k4 < 52; ++k4) {
                        if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3) continue;

                        /*
                          Lasketaan korttien numeroarvot ja
                          tarkistetaan onko suora.
                        */
                        k[0] = (k0 % 13) + 2;
                        k[1] = (k1 % 13) + 2;
                        k[2] = (k2 % 13) + 2;
                        k[3] = (k3 % 13) + 2;
                        k[4] = (k4 % 13) + 2;
                        if (is_straight2(k))
                            ++suoria;
                    }
                }
            }
        }
    }
    t2 = clock();
    printf("Suoria     : %d kpl (oikea arvo 1228800)\n", suoria);
    printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

    t1 = clock();
    quads_fullhouse = 0;
    for (k0 = 0; k0 < 52; ++k0) {
        for (k1 = 0; k1 < 52; ++k1) {
            if (k1 == k0) continue;
            for (k2 = 0; k2 < 52; ++k2) {
                if (k2 == k0 || k2 == k1) continue;
                for (k3 = 0; k3 < 52; ++k3) {
                    if (k3 == k0 || k3 == k1 || k3 == k2) continue;
                    for (k4 = 0; k4 < 52; ++k4) {
                        if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3) continue;

                        /*
                          Lasketaan korttien numeroarvot ja
                          tarkistetaan onko suora.
                        */
                        k[0] = (k0 % 13) + 2;
                        k[1] = (k1 % 13) + 2;
                        k[2] = (k2 % 13) + 2;
                        k[3] = (k3 % 13) + 2;
                        k[4] = (k4 % 13) + 2;
                        if (is_quadsorfullhouse(k))
                            ++quads_fullhouse;
                    }
                }
            }
        }
    }
    t2 = clock();
    printf("Nelosia ja täyskäsiä     : %d kpl (oikea arvo 524160)\n", quads_fullhouse);
    printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

    return 0;
}

/*
  Parametrina 5 pelikortin numeroarvoa k, 2..14 (ei välttämättä
  numerojärjesteyksessä).

  Palauttaa 1, jos numeroarvot voidaan järjestää siten, että
  ne muodostavat suoran (esim. 4,5,6,7,8).

  Huom! Ässää (arvo 14) voidaan käyttää suorissa myös arvona 1
  (esim. 1,2,3,4,5).
*/
int is_straight(int *k) {
    // TODO
    int straight = 0;
    sort(k);

    if (k[4] == 14 && k[0] == 2) {
        k[4] = 1;
        sort(k);
    }

    for (int i = 0; i < NUM_OF_CARDS; i++) {
        if (k[i - 1] == k[i] - 1) {
            ++straight;
        }
    }

    if (straight == 4) {
        return 1;
    }

    return 0;
}

void sort(int *k) {
    int num_of_cards = 5;

    int i = 1;

    while (i < num_of_cards) {
        int j = i;
        while (j > 0 && k[j - 1] > k[j]) {
            int suora = k[j];
            k[j] = k[j - 1];
            k[j - 1] = suora;

            j = j - 1;
        }
        i = i + 1;
    }
}

int is_straight2(int *k) {
    bit_vector = 0;
    for (int i = 0; i < 5; i++) {
        SET_BIT(bit_vector, k[i]);
    }

    if (IS_BIT_SET(bit_vector, 2) && IS_BIT_SET(bit_vector, 14)) {
        SET_BIT(bit_vector, 1);
        CLR_BIT(bit_vector, 14);
    }

    if (straight_lookup_table[bit_vector] == 1) {
        bit_vector = 0;
        return 1;
    }

    bit_vector = 0;
    return 0;
}

int is_straight_bits(int *k) {
    int suora = 0;
    for (int i = 0; i < NUM_OF_CARDS; i++) {
        SET_BIT(bit_vector, k[i]);
    }

    if (IS_BIT_SET(bit_vector, 2) && IS_BIT_SET(bit_vector, 14)) {
        SET_BIT(bit_vector, 1);
        CLR_BIT(bit_vector, 14);
    }

    for (int i = 0; i < 16; i++) {
        if (IS_BIT_SET(bit_vector, i)) {
            for (int j = i; j < i + 5; j++) {
                if (IS_BIT_SET(bit_vector, j)) {
                    suora++;
                } else {
                    suora--;
                }
            }
        }
    }

    if (suora == 5) {
        straight_lookup_table[bit_vector] = 1;
        bit_vector = 0;
        return 1;
    }

    bit_vector = 0;
    return 0;
}

void create_lookup_table() {
    int k0, k1, k2, k3, k4; /* Pakan kortit, 0..51*/
    int k[5];               /* Korttien numeroarvot, 2..14*/

    for (k0 = 0; k0 < 52; ++k0) {
        for (k1 = 0; k1 < 52; ++k1) {
            if (k1 == k0) continue;
            for (k2 = 0; k2 < 52; ++k2) {
                if (k2 == k0 || k2 == k1) continue;
                for (k3 = 0; k3 < 52; ++k3) {
                    if (k3 == k0 || k3 == k1 || k3 == k2) continue;
                    for (k4 = 0; k4 < 52; ++k4) {
                        if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3) continue;

                        /*
                          Lasketaan korttien numeroarvot ja
                          tarkistetaan onko straight.
                        */
                        k[0] = (k0 % 13) + 2;
                        k[1] = (k1 % 13) + 2;
                        k[2] = (k2 % 13) + 2;
                        k[3] = (k3 % 13) + 2;
                        k[4] = (k4 % 13) + 2;

                        is_straight_bits(k);
                    }
                }
            }
        }
    }
}

int is_quadsorfullhouse(int *k) {
    int faces[15] = {0};

    for (size_t i = 0; i < NUM_OF_CARDS; i++) {
        faces[k[i]]++;
    }

    for (size_t i = 0; i < 15; i++) {
        if (faces[i] == 4) {
            return 1;
        }

        if (faces[i] == 3) {
            for (size_t j = 0; j != i; j++) {
                if (faces[j] == 2) {
                    return 1;
                }
            }
        } else if (faces[i] == 2) {
            for (size_t j = 0; j != i; j++) {
                if (faces[j] == 3) {
                    return 1;
                }
            }
        }
    }

    return 0;
};
