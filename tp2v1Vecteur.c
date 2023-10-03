#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

struct vecfloat {
  int nbele;
  float * v;
} ;
typedef struct vecfloat vec_t;

vec_t creeretremplir (int nb) {
  vec_t w;
  int i;
  float x, y, z, *pt;
  if (nb < 2)
	nb = 10;
  w.nbele = nb;
  w.v = (float *) malloc (nb * sizeof(float));
  assert(w.v);
  x = 1.0;
  y = 0.13;
  z = 0.021;
  pt = w.v;
  for (i = 0; i < nb; i++) {
	*pt++ = x;
	x += y;
	y += z;
	if (x > 1.5) {
	  x -= 1.01;
	}
	if (x < 0.5) {
	  x += 0.499;
	}
	if (y > 1.) {
	  y = y - 1.01;
	}
	if (x < 0.5) {
	  y += 0.5001;
	}
  }
  return w;
}

void triABullesVec(vec_t *vec) {
    int n = vec->nbele;
    float temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec->v[j] > vec->v[j + 1]) {
                temp = vec->v[j];
                vec->v[j] = vec->v[j + 1];
                vec->v[j + 1] = temp;
            }
        }
    }
}

void triParSelectionVec(vec_t *vec) {
    int n = vec->nbele;
    int i, j, min_index;
    float temp;
    
    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (vec->v[j] < vec->v[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            temp = vec->v[i];
            vec->v[i] = vec->v[min_index];
            vec->v[min_index] = temp;
        }
    }
}

void triParInsertionVec(vec_t *vec) {
    int n = vec->nbele;
    int i, j;
    float key;
    
    for (i = 1; i < n; i++) {
        key = vec->v[i];
        j = i - 1;
        
        while (j >= 0 && vec->v[j] > key) {
            vec->v[j + 1] = vec->v[j];
            j = j - 1;
        }
        
        vec->v[j + 1] = key;
    }
}

int partition(vec_t *vec, int low, int high) {
    float pivot = vec->v[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (vec->v[j] < pivot) {
            i++;
            float temp = vec->v[i];
            vec->v[i] = vec->v[j];
            vec->v[j] = temp;
        }
    }

    float temp = vec->v[i + 1];
    vec->v[i + 1] = vec->v[high];
    vec->v[high] = temp;

    return (i + 1);
}

void triRapid(vec_t *vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);

        triRapid(vec, low, pi - 1);
        triRapid(vec, pi + 1, high);
    }
}

int main() {
    srand(time(NULL));

    int tailles[] = {100, 1000, 10000, 100000};
    int nombreDeTailles = sizeof(tailles) / sizeof(tailles[0]);

    for (int i = 0; i < nombreDeTailles; i++) {
        const int taille = tailles[i];
        if (taille <= 0) {
            printf("La taille du vecteur doit être supérieure à zéro.\n");
            continue;
        }

        vec_t vec = creeretremplir(taille);

        clock_t start_time, end_time;
        double elapsed_time;

        printf("MehdiBook : a.out %d\n", taille);

        start_time = clock();
        triParInsertionVec(&vec);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Tri insertion\t taille %d\t temps %.0lf\n", taille, elapsed_time);

        start_time = clock();
        triABullesVec(&vec);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Tri bulles\t taille %d\t temps %.0lf\n", taille, elapsed_time);

        start_time = clock();
        triParSelectionVec(&vec);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Tri insertion\t taille %d\t temps %.0lf\n", taille, elapsed_time);

        start_time = clock();
        triRapid(&vec, 0, taille - 1);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Quicksort\t taille %d\t temps %.0lf\n", taille, elapsed_time);

        free(vec.v);
    }

    return 0;
}