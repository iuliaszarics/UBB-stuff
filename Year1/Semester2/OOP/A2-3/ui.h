#pragma once
#pragma once
#include "domain.h"

int command();
void print_menu();
void ui_add_medicine(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array);
void ui_delete_medicine(Dynamic_array* repository, Operation_dynamic* undo_array, Operation* redo_array);
void ui_update_medicine(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array);
// void ui_update_medicine_concentration(Dynamic_array*repository,Operation_dynamic*undo_array,Operation_dynamic*redo_array);
// void ui_update_medicine_quantity(Dynamic_array*repository,Operation_dynamic*undo_array,Operation_dynamic*redo_array);
// void ui_update_medicine_price(Dynamic_array*repository,Operation_dynamic*undo_array,Operation_dynamic*redo_array);
void ui_undo(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array);
void ui_redo(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array);
void print_all_medicines(Dynamic_array* repository);
void show_medicines_short_in_supply(Dynamic_array* repository);
int get_the_command();
int use_the_command(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, int selected_command);
void run(Dynamic_array* repostiory, Operation_dynamic* undo_array, Operation_dynamic* redo_array);