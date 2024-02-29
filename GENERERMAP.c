#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 10

void generateMap() {
    char map[HEIGHT][WIDTH];
    int i, j;
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    // Initialiser la carte avec des murs aléatoires
    for(i = 0; i < HEIGHT; i++) {
        for(j = 0; j < WIDTH; j++) {
            if(i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1 || rand() % 4 == 0) {
                map[i][j] = '1'; // Murs
            } else {
                map[i][j] = '0'; // Espaces vides
            }
        }
    }

    // Positionner un P et un E aléatoirement
    int pX, pY, eX, eY;
    do {
        pX = rand() % WIDTH;
        pY = rand() % HEIGHT;
    } while(map[pY][pX] == '1');
    map[pY][pX] = 'P';

    do {
        eX = rand() % WIDTH;
        eY = rand() % HEIGHT;
    } while(map[eY][eX] == '1' || map[eY][eX] == 'P');
    map[eY][eX] = 'E';

    // Remplir le reste des cases avec 0 et 1 aléatoirement
    for(i = 1; i < HEIGHT - 1; i++) {
        for(j = 1; j < WIDTH - 1; j++) {
            if(map[i][j] == '0') {
                map[i][j] = rand() % 2 == 0 ? '0' : '1';
            }
        }
    }

    // Écrire la carte dans un fichier
    FILE *file = fopen("aleatoire.ber", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier pour l'écriture.\n");
        return;
    }

    for(i = 0; i < HEIGHT; i++) {
        for(j = 0; j < WIDTH; j++) {
            fprintf(file, "%c ", map[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    generateMap();
    return 0;
}

