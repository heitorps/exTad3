#include "vector.h"
#include "stdlib.h"

// Aloca espaço para um elemento do tipo vector e inicializa os seus atributos.
Vector *vector_construct(){
    Vector* v = (Vector*)malloc(sizeof(Vector));
    v->size = 0;
    v->allocated = 10;

    v->data = (data_type*)calloc(v->allocated,sizeof(data_type));

    return v;
}

// Libera o espaço reservado para o vector.
void vector_destroy(Vector *v){
    if(v->data != NULL) free(v->data);

    if(v != NULL)   free(v);
}

// Adiciona o item dado ao final do vector e aumenta o tamanho. Aumenta a capacidade alocada se necessário.
void vector_push_back(Vector *v, data_type val){
    v->size++;
    if(v->size > v->allocated){
        v->allocated *= 2;
        v->data = (data_type*)realloc(v->data,v->allocated*sizeof(data_type));
    }
    int i = v->size - 1;
    v->data[i] = val;
}

// Retorna o número de elementos atualmente no vector.
int vector_size(Vector *v){
    return v->size;
}

// Retorna o i-ésimo elemento do vector.
data_type vector_get(Vector *v, int i){
    if(i>=0 && i < v->size)
    return v->data[i];

    else exit(1);
}

// Atualiza o i-ésimo elemento do vector  para que ele passe a ter o valor val.
data_type vector_set(Vector *v, int i, data_type val){
    if(i>=0 && i < v->size){
        data_type previous = v->data[i];
        v->data[i] = val;
        return previous;
    }
    return NULL;
}

// Retorna o índice da primeira ocorrência do item no Vector ou -1 se o elemento não for encontrado.
int vector_find(Vector *v, data_type val, int cmp_fn(data_type val1, data_type val2)){
    for(int i=0; i<v->size; i++){
        if(cmp_fn(v->data[i],val)==0) return i;
    } return -1;
}

// Retorna o maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_max(Vector *v){
    data_type max = v->data[0];

    for(int i=0; i<v->size; i++){
        if(v->data[i] > max) max = v->data[i];
    }
    return max;
}

// Retorna o menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_min(Vector *v){
    data_type min = v->data[0];
    
    for(int i=0; i<v->size; i++){
        if(v->data[i] < min) min = v->data[i];
    }
    return min;
}

// Retorna o índice do maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmax(Vector *v){
    data_type max = v->data[0];
    int idxMax = 0;
    
    for(int i=0; i<v->size; i++){
        if(v->data[i] > max){
            max = v->data[i];
            idxMax = i;
        }
    }
    return idxMax;
}

// Retorna o índice do menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmin(Vector *v){
    data_type min = v->data[0];
    int idxMin = 0;
    
    for(int i=0; i<v->size; i++){
        if(v->data[i] < min){
            min = v->data[i];
            idxMin = i;
        }
    }
    return idxMin;
}

/////////////////////////////////////////////////////////////////////////
// Remove o i-ésimo elemento do vetor.
data_type vector_remove(Vector *v, int i){
    data_type banido = v->data[i];
    for(int j=i+1; j< v->size; j++){
        v->data[j-1] = v->data[j];
    }
    v->size--;
    return banido;
}

// Remove o primeiro elemento
data_type vector_pop_front(Vector *v){
    return vector_remove(v,0);
}

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v){
    return vector_remove(v,v->size-1);
}

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val){
    //aumento de tamanho
    v->size++;
    if(v->size > v->allocated){
        v->allocated *= 2;
        v->data = (data_type*)realloc(v->data,v->allocated*sizeof(data_type));
    }

    //passagem de todos a direita
    for(int j = v->size-1;    j > i;  j--){
        v->data[j] = v->data[j-1];
    }
    v->data[i] = val;
}

// Troca os elementos das posições i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j){
    data_type temp;

    temp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = temp;
}

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v, int cmp_fn(data_type val1, data_type val2)){
    while(1){
        int nSwaps=0;

        for(int i=0; i < v->size-1; i++){
            if(cmp_fn(v->data[i],v->data[i+1])>0){
                vector_swap(v,i,i+1);
                nSwaps++;
            }
        }
        if (!nSwaps) break;
    }
}

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val, int cmp_fn(data_type val1, data_type val2)){
    int minIdx=0, maxIdx = v->size-1;

    int medIdx;
    while (minIdx <= maxIdx)
    {
        medIdx = (minIdx + maxIdx)/2;

        if(cmp_fn(val, v->data[medIdx])==0) return medIdx;
        else if(cmp_fn(val, v->data[medIdx])==1){
            minIdx = medIdx+1;
        }
        else{
            maxIdx = medIdx-1;
        }

    }
    return -1;
    
}

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v){
    for(int i=0; i<(v->size)/2; i++){
        vector_swap(v,i,(v->size-1-i));
    }
}

// Cria uma cópia do vector e dos valores de seus atributos.
Vector *vector_copy(Vector *v);

// Remove todos os elementos de v
void vector_clear(Vector *v);
