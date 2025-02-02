#pragma once
#pragma once
#include "repository.h"
#include "domain.h"

int get_next_id();
void sort_medicines_ascending(Dynamic_array* medicines);
void sort_medicines_descendending(Dynamic_array* medicines);
Dynamic_array* sort_medicines_by_concentration(Dynamic_array* repository);
Dynamic_array* get_all_medicines(Dynamic_array* repository);
void add_medicine_services(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, int quantity, int price);
void delete_medicine_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration);
void update_medicine_name_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, char* new_name);
void update_medicine_concentration_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, int new_concentration);
void update_medicine_quantity_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, int new_quantity);
void update_medicine_price_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, int new_price);
Dynamic_array* get_medicines_by_name_service(Dynamic_array* repository, char* given_name);
Dynamic_array* get_short_supply_service(Dynamic_array* repository, int quantity); //int sorted
int Undo(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array);
int Redo(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array);
void init_service(Dynamic_array* repository);

