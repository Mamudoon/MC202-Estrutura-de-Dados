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
   if (D->size == D->cap) {
      float *temp = D->data;
      D->data = (float*) realloc(D->data, (D->cap*D->factor)*sizeof(float));
      if (D->data == NULL) {
         D->data = temp;
         return 0;
      }
      D->cap *= D->factor;
      for (int i = 0; i < D->first; ++i) {
         D->data[(i + D->size)%D->cap] = D->data[i];
      }
   }
   long fim = (D->first + D->size)%D->cap;
   D->data[fim] = x;
   ++D->size;
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
   long fim = (D->first + D->size - 1)%D->cap;
   float valor = D->data[fim];
   --D->size;
   if (D->size == D->cap/(D->factor*D->factor) && D->cap != D->mincap) {
      long cap_antigo = D->cap;
      if (D->mincap < D->cap/D->factor) {
         D->cap /= D->factor;
      } else {
         D->cap = D->mincap;
      }
      for (int i = 0; i < D->size; ++i) {
         D->data[(i + D->first)%D->cap] = D->data[(i + D->first)%cap_antigo];
      }
      D->data = (float*) realloc(D->data, D->cap*sizeof(float));
   }
   return valor;
}



/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
   if (D->size == D->cap) {
      float *temp = D->data;
      D->data = (float*) realloc(D->data, (D->cap*D->factor)*sizeof(float));
      if (D->data == NULL) {
         D->data = temp;
         return 0;
      }
      D->cap *= D->factor;
      for (int i = 0; i < D->first; ++i) {
         D->data[(i + D->size)%D->cap] = D->data[i];
      }
   }
   D->first = (D->first + D->cap - 1)%D->cap;
   D->data[D->first] = x;
   ++D->size;
   return 1;
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
   float valor = D->data[D->first];
   ++D->first;
   if (D->first == D->cap) {
      D->first = 0;
   }
   --D->size;
   if (D->size == D->cap/(D->factor*D->factor) && D->cap != D->mincap) {
      long cap_antigo = D->cap;
      if (D->mincap < D->cap/D->factor) {
         D->cap /= D->factor;
      } else {
         D->cap = D->mincap;
      }
      for (int i = 0; i < D->size; ++i) {
         D->data[(i + D->first)%D->cap] = D->data[(i + D->first)%cap_antigo];
      }
      D->data = (float*) realloc(D->data, D->cap*sizeof(float));
   }
   return valor;
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] what happens then?
**/
float df_get(dequef* D, long i) {
   for (int k = 0; k < D->size; ++k) {
      if (i == k) {
         return D->data[(D->first + k)%D->cap];
      }
   }
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] what happens then?
**/
void df_set(dequef* D, long i, float x) {
   for (int k = 0; k < D->size; ++k) {
      if (i == k) {
         D->data[(D->first + k)%D->cap] = x;
      }
   }
}



/**
   Print the elements of D in a single line.
**/
void df_print(dequef* D) {
   printf("deque (%ld): ", D->size);
   for (int i = 0; i < D->size; ++i) {
      printf("%.1f ", D->data[(D->first + i)%D->cap]);
   }
   printf("\n");
}
