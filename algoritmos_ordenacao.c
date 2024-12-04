#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int * a, int n){

	int i;

	printf("array:");

	for(i = 0; i < n; i++) printf(" %d", a[i]);
	
	printf("\n");
}

void print2(int * a, int ini, int fim){

	int i;

	printf("array:");

	for(i = ini; i <= fim; i++) printf(" %d", a[i]);
	
	printf("\n");
}

void troca(int * a, int i, int j){

	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

// =================================================================================================== //
// =================================================================================================== //

void selection_sort(int * a, int n, int ini, int * n_calls){

	int i;
	int min = ini;

	(*n_calls)++;

	if(ini < n - 1){

		for(i = ini + 1; i < n; i++) if(a[i] < a[min]) min = i;
		
		troca(a, ini, min);
		selection_sort(a, n, ini + 1, n_calls);		
	}
}

// =================================================================================================== //
// =================================================================================================== //

void insertion_sort(int * a, int n){

	int fim, i, valor;
	
	for(fim = 1; fim < n; fim++){

		valor = a[fim];

		for(i = fim; i > 0 && a[i - 1] > valor; i--){ 

			a[i] = a[i - 1];
		}

		a[i] = valor;
	}
}

// =================================================================================================== //
// =================================================================================================== //

void bubble_sort(int * a, int n, int * n_calls){
	
	int i, trocas;

	(*n_calls)++;

	for(trocas = 0, i = 0; i < n - 1; i++){

		if(a[i] > a[i + 1]) {

			troca(a, i, i + 1);
			trocas++;
		}		
	}

	if(trocas > 0) bubble_sort(a, n, n_calls);
}

// =================================================================================================== //
// =================================================================================================== //

int particiona(int * a, int ini, int fim){

	int i, x, q, k;

	int * b = malloc((fim - ini + 1) * sizeof(int));

	for(x = a[ini], i = ini, q = 0; i <= fim; i++) if(a[i] < x) b[q++] = a[i];
	for(i = ini, k = q; i <= fim; i++) if(a[i] >= x) b[k++] = a[i];
	for(i = ini, k = 0; i <= fim; i++, k++) a[i] = b[k];

	free(b);

	return (ini + (q == 0 ? 0 : q - 1));
}

void quick_sort(int * a, int ini, int fim){

	int q;

	if(ini < fim){

		q = particiona(a, ini, fim);
		quick_sort(a, ini, q);
		quick_sort(a, q + 1, fim); 
	}
}

// =================================================================================================== //
// =================================================================================================== //

void merge(int * a, int ini, int med, int fim){

	int i = ini;
	int j = med + 1;
	int k = 0;
	
	int * b = malloc((fim - ini + 1) * sizeof(int));

	while(i <= med && j <= fim) b[k++] = a[i] < a[j] ? a[i++] : a[j++];
	while(i <= med) b[k++] = a[i++];
	while(j <= fim) b[k++] = a[j++];
	for(i = ini, k = 0; i <= fim; i++, k++) a[i] = b[k];

	free(b);
}

void merge_sort(int * a, int ini, int fim){

	if(ini < fim){

		int med = (ini + fim) / 2;

		merge_sort(a, ini, med);
		merge_sort(a, med + 1, fim);
		merge(a, ini, med, fim);
	}
}

// =================================================================================================== //
// =================================================================================================== //

typedef struct {

	int * a;
	int n;

} Heap;

void heapfy(Heap * heap, int i){

	int esq = 2 * i + 1;
	int dir = 2 * i + 2;

	int max = i;

	if(esq < heap->n && heap->a[esq] > heap->a[max]) max = esq;
	if(dir < heap->n && heap->a[dir] > heap->a[max]) max = dir;

	if(max != i){ 
		
		troca(heap->a, i, max);
		heapfy(heap, max);
	}
}

Heap * cria_heap(int * a, int n){

	int i;
	Heap * heap = malloc(sizeof(Heap));

	heap->n = n;
	heap->a = malloc(heap->n * sizeof(int));

	memcpy(heap->a, a, heap->n * sizeof(int));
	
	for(i = n - 1; i >= 0; i--){
		
		heapfy(heap, i);
	}

	return heap;
}

int extrai_maximo(Heap * heap){

	int max = heap->a[0];

	heap->a[0] = heap->a[heap->n - 1];
	heap->n--;
	heapfy(heap, 0);

	return max;
}

void heapsort(int * a, int n){

	int i;
	Heap * heap = cria_heap(a, n);

	for(i = n - 1; i >= 0; i--) a[i] = extrai_maximo(heap);
}

// =================================================================================================== //
// =================================================================================================== //

int main(){

	int a[] = { 5, 8, 4, 7, 3, 6, 1, 2 };
	//int a[] = { 1, 2, 3, 4, 6, 5, 7, 8 };
	
	int n = 8;
	int n_calls = 0;

	print(a, n);

	//bubble_sort(a, n, &n_calls);
	//selection_sort(a, n, 0, &n_calls);
	//insertion_sort(a, n);

	//heapsort(a, n);
	//merge_sort(a, 0, n - 1);
	//quick_sort(a, 0, n - 1);

	print(a, n);
	printf("n_calls: %d\n", n_calls);

	return 0;
}
