#pragma once
#include "domain.h"

Dynamic_array* create_repository();

int get_index(Dynamic_array* repository, char* name_of_medicine, int concentration);

Medicine add_new_medicine_repository(Dynamic_array* repository, char* name_of_medicine, int concentration, int quantity, int price);
Medicine delete_from_repository(Dynamic_array* repository, char* name_of_medicine, int concentration);
Medicine update_name_to_repository(Dynamic_array* repository, char* name_of_medicine, int concentration, char* new_name);
Medicine update_concentration_to_repository(Dynamic_array* repository, char* name_of_medicine, int concentration, int new_concentration);
Medicine update_quantity_to_repository(Dynamic_array* repository, char* name_of_medicine, int concentration, int new_quantity);
Medicine update_price_to_repository(Dynamic_array* repository, char* name_of_medicine, int concentration, int new_price);


