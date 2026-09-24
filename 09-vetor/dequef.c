#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"


/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) {
   dequef* D = (dequef*) malloc(sizeof(dequef));
   if (D == NULL) { // retorna NULL se a alocação der errada
      return NULL;
   }
   D->data = (float*) malloc(capacity*sizeof(float));
   D->first = 0;
   D->size = 0;
   D->cap = capacity;
   D->mincap = capacity;
   D->factor = factor;
   if (D->data == NULL) { // retorna NULL se a alocação der errada
      return NULL;
   }
   return D;
}

/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
   free(D->data);
   free(D);
}



/**
   The size of the deque.
**/
long df_size(dequef* D) {
   return D->size;
}



/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
   int fim;
   float *temp;
   if (D->size == D->cap) {
      temp = (float*) realloc(D->data, D->cap*D->factor*sizeof(float));
      if (temp == NULL) {
         return 0;
      }
      for (int i = 0; i < D->size; ++i) {
         fim = (D->first + i)%D->cap;
         temp[i] = D->data[fim];
      }
      D->first = 0;
      D->cap *= D->factor;
      free(D->data);
   }
      temp[++fim]= x;
      D->data = temp;
      return 1;
}



/**
   Remove a float from the end of D and return it.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_pop(dequef* D) {
}



/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
}



/**
   Remove a float from the beginning of D and return it.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_eject(dequef* D) {
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] what happens then?
**/
float df_get(dequef* D, long i) {
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] what happens then?
**/
void df_set(dequef* D, long i, float x) {
}



/**
   Print the elements of D in a single line.
**/
void df_print(dequef* D) {
   printf("deque (%ld):", D->size);
   for (int i = 0; i < D->size; ++i) {
      printf(" %.1f");
   }
   printf("\n");
}
