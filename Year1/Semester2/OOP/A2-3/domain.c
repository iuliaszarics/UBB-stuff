#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain.h"

//tre sa facem functii de getters


// int get_id(TElem medicine)
// {
//     return medicine.id;
// }

char* get_name(TElem* medicine)
{
    return medicine->name;
}

int get_concentration(TElem* medicine)
{
    return medicine->concentration;
}

int get_quantity(TElem* medicine)
{
    return medicine->quantity;
}

int get_price(TElem* medicine)
{
    return medicine->price;
}

//setters

void set_name(TElem* medicine, char* new_name)
{
    strcpy(medicine->name, new_name);
}

void set_concentration(TElem* medicine, int new_concentration)
{
    medicine->concentration = new_concentration;
}

void set_quantity(TElem* medicine, int new_quantity)
{
    medicine->quantity = new_quantity;
}

void set_price(TElem* medicine, int new_price)
{
    medicine->price = new_price;
}


//amu si pentru dinamic array

Dynamic_array* create_dynamic_array(int capacity)
{
    Dynamic_array* dynamic_array = malloc(sizeof(Dynamic_array));
    if (dynamic_array == NULL) return NULL;
    dynamic_array->capacity = capacity;
    dynamic_array->size = 0;
    dynamic_array->medicines = malloc(capacity * sizeof(TElem));
    if (dynamic_array->medicines = NULL) return NULL;
    return dynamic_array;
}

int get_dynamic_size(Dynamic_array* dynamic_array)
{
    return dynamic_array->size;
}

int get_dynamic_capacity(Dynamic_array* dynamic_array)
{
    return dynamic_array->capacity;
}

void add_new_medicine_dynamic(Dynamic_array* dynamic_array, Medicine element)
{
    if (dynamic_array == NULL) return;
    if (dynamic_array->size >= dynamic_array->capacity) {
        int new_capacity = dynamic_array->capacity * 2;
        void* temporary_dynamic_array = realloc(dynamic_array->medicines, new_capacity * sizeof(Medicine));
        if (temporary_dynamic_array == NULL) {
            return;
        }
        dynamic_array->medicines = temporary_dynamic_array;
        dynamic_array->capacity = new_capacity;
    }
    dynamic_array->medicines[dynamic_array->size] = element;
    dynamic_array->size++;

}

void destroy_dynamic(Dynamic_array* dynamic_array)
{
    if (dynamic_array == NULL) return;
    free(dynamic_array->medicines);
    free(dynamic_array);
}

Operation_dynamic* create_operations_dynamic(int capacity)
{
    Operation_dynamic* dynamic_array = malloc(sizeof(Operation_dynamic));
    if (dynamic_array == NULL) return NULL;
    dynamic_array->capacity = capacity;
    dynamic_array->size = 0;
    dynamic_array->medicines = malloc(capacity * sizeof(Operation));
    if (dynamic_array->medicines == NULL) return NULL;
    return dynamic_array;
}

void add_to_operation(Operation_dynamic* dynamic_array, Operation element)
{
    if (dynamic_array->size == dynamic_array->capacity);
    resize_operation_dynamic(dynamic_array);
    dynamic_array->medicines[dynamic_array->size] = element;
    dynamic_array->size++;
}

void resize_operation_dynamic(Operation_dynamic* dynamic_array)
{
    if (dynamic_array == NULL) return;
    int new_capacity = dynamic_array->capacity * 2;
    dynamic_array->capacity *= 2;
    void* aux = realloc(dynamic_array->medicines, new_capacity * sizeof(Operation));
    if (aux == NULL) return;
    dynamic_array->capacity = new_capacity;
    dynamic_array->medicines = aux;
}

void destroy_operation_dynamic(Operation_dynamic* dynamic_array)
{
    if (dynamic_array == NULL) return;
    //free(dynamic_array->medicines);
    free(dynamic_array);
}

int get_operation_size(Operation_dynamic* dynamic_array)
{
    return dynamic_array->size;
}

int get_operation_capacity(Operation_dynamic* dynamic_array)
{
    return dynamic_array->capacity;
}

