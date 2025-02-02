#pragma once

typedef struct
{
    char name[50];
    int concentration, quantity, price;
}Medicine;

typedef Medicine TElem;

char* get_name(TElem medicine);
int get_concentration(TElem medicine);
int get_quantity(TElem medicine);
int get_price(TElem medicine);

void set_name(TElem medicine, char* new_name);
void set_concentration(TElem medicine, int new_concentration);
void set_quantity(TElem, int new_quantity);
void set_price(TElem, int new_price);

typedef struct
{
    TElem* medicines;
    int size;
    int capacity;
}Dynamic_array;

typedef Medicine TElem;

Dynamic_array* create_dynamic_array(int capacity);
int get_dynamic_size(Dynamic_array* dynamic_array);
int get_dynamic_capacity(Dynamic_array* dynamic_array);
void add_new_medicine_dynamic(Dynamic_array* dynamic_array, Medicine element);
void resize_dynamic(Dynamic_array* dynamic_array);
void destroy_dynamic(Dynamic_array* dynamic_aray);

typedef struct

{
    char operation[50];
    Medicine medicine;
}Operation;

char* get_undo(Operation* undo_operation);
Medicine get_undo_medicine(Operation undo_operation);

void set_undo(Operation* undo_operation, char* new_undo);
void set_undo_medicine(Operation undo_operation, Medicine new_undo_medicine);

char* get_redo(Operation* redo_operation);
Medicine get_redo_medicine(Operation redo_operation);

void set_redo(Operation* redo_operation, char* new_redo);
void set_redo_medicine(Operation redo_operation, Medicine new_redo_medicine);


typedef struct
{
    Operation* medicines;
    int size, capacity;
}Operation_dynamic;

Operation_dynamic* create_operation_dynamic(int capacity);
void add_to_operation(Operation_dynamic* Dynamic_array, Operation element);
void resize_operation_dynamic(Operation_dynamic* Dynamic_array);
int get_operation_size(Operation_dynamic* Dynamic_array);
int get_operation_capacity(Operation_dynamic* Dynamic_array);
void destroy_operation_dynamic(Operation_dynamic* Dynamic_array);
