#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repository.h"
#include "domain.h"
#include "controller.h"

void sort_medicines_ascending(Dynamic_array* dynamic_array)
{
    for (int i = 0;i < dynamic_array->size - 1;i++)
        for (int j = i + 1;j < dynamic_array->size;j++)
        {
            if (strcmp(dynamic_array->medicines[i].name, dynamic_array->medicines[j].name) > 0)
            {
                Medicine aux = dynamic_array->medicines[i];
                dynamic_array->medicines[i] = dynamic_array->medicines[j];
                dynamic_array->medicines[j] = aux;
            }
        }
}

void sort_medicines_descending(Dynamic_array* dynamic_array)
{
    for (int i = 0;i < get_dynamic_size(dynamic_array) - 1;i++)
        for (int j = i + 1;j < get_dynamic_size(dynamic_array);j++)
        {
            if (strcmp(dynamic_array->medicines[i].name, dynamic_array->medicines[j].name) < 0)
            {
                Medicine aux = dynamic_array->medicines[i];
                dynamic_array->medicines[i] = dynamic_array->medicines[j];
                dynamic_array->medicines[j] = aux;
            }
        }
}

Dynamic_array*sort_medicines_by_concentration(Dynamic_array*repository)
{
    Dynamic_array*medicines_sorted_concentration=create_dynamic_array(2);
    for (int i = 0;i < get_dynamic_size(repository);i++) add_new_medicine_dynamic(medicines_sorted_concentration, repository->medicines[i]);
    for (int i=0;i<get_dynamic_size(medicines_sorted_concentration)-1;i++)
        for (int j = i + 1;j < get_dynamic_size(medicines_sorted_concentration);j++)
        {
            if (medicines_sorted_concentration->medicines[i].concentration > medicines_sorted_concentration->medicines[j].concentration)
            {
                Medicine aux = medicines_sorted_concentration->medicines[i];
                medicines_sorted_concentration->medicines[i] = medicines_sorted_concentration->medicines[j];
                medicines_sorted_concentration->medicines[j] = aux;
            }
        }
}

Dynamic_array* get_all_medicines(Dynamic_array* repository)
{
    Dynamic_array* all_medicines = create_dynamic_array(2);
    for (int i = 0;i < get_dynamic_size(repository);i++)
    {
        add_new_medicine_dynamic(all_medicines, repository->medicines[i]);
    }
    return all_medicines;
    free(all_medicines);
}

void add_medicine_services(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, int quantity, int price)
{
    //redo_array->size = 0;
    Dynamic_array* allMedicines = create_dynamic_array(2);
    for (int i = 0;i < get_dynamic_size(repository);i++)
    {
        add_new_medicine_dynamic(allMedicines, repository->medicines[i]);
    }
    int exists = 0;
    for (int i = 0;i < get_dynamic_size(allMedicines);i++)
    {
        if (!strcmp(get_name(allMedicines->medicines[i]), name) && get_concentration(allMedicines->medicines[i]) == concentration)
        {
            repository->medicines[i].quantity += quantity;
            exists = 1;
        }
        if (!exists)
        {
            Medicine added_medicine = add_new_medicine_repository(repository, name, concentration, quantity, price);
            Operation undo_operation;
            strcpy(undo_operation.operation, "add");
            undo_operation.medicine = added_medicine;
            add_to_operation(undo_array, undo_operation);
        }
        return allMedicines;
        destroy_dynamic(allMedicines);
    }
}

void delete_medicine_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration)
{
    redo_array->size = 0;
    Medicine deleted_medicines = delete_from_repository(repository, name, concentration);
    Operation undo_operation;
    strcpy(undo_operation.operation, "delete");
    undo_operation.medicine = deleted_medicines;
    add_to_operation(undo_array, undo_operation);
}

void update_medicine_name_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, char* new_name)
{
    redo_array->size = 0;
    Medicine updated_medicine = update_name_to_repository(repository, name, concentration, new_name);
    Operation undo_operation;
    strcpy(undo_operation.operation, "update");
    undo_operation.medicine = updated_medicine;
    add_to_operation(undo_array, undo_operation);
}

void update_medicine_concentration_service(Dynamic_array* repository, Dynamic_array* undo_array, Dynamic_array* redo_array, char* name, int concentration, int new_concentration)
{
    redo_array->size = 0;
    Medicine updated_medicine = update_concentration_to_repository(repository, name, concentration, new_concentration);
    Operation undo_operation;
    strcpy(undo_operation.operation, "update");
    undo_operation.medicine = updated_medicine;
    add_to_operation(undo_array, undo_operation);
}

void update_medicine_quantity_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, int new_quantity)
{
    redo_array->size = 0;
    Medicine updated_medicine = update_quantity_to_repository(repository, name, concentration, new_quantity);
    Operation undo_operation;
    strcpy(undo_operation.operation, "update");
    undo_operation.medicine = updated_medicine;
    add_to_operation(undo_array, undo_operation);
}

void update_medicine_price_service(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, char* name, int concentration, int new_price)
{
    redo_array->size = 0;
    Medicine updated_medicine = update_price_to_repository(repository, name, concentration, new_price);
    Operation undo_operation;
    strcpy(undo_operation.operation, "update");
    undo_operation.medicine = updated_medicine;
    add_to_operation(undo_array, undo_operation);
}

Dynamic_array* get_medicines_by_name_service(Dynamic_array* repository, char* given_name)
{
    Dynamic_array* all_medicines = create_dynamic_array(2);
    for (int i = 0;i < get_dynamic_size(repository);i++)
    {
        add_new_medicine_dynamic(all_medicines, repository->medicines[i]);
    }
    if (!strcmp(given_name, "") || !strcmp(given_name, "/n"))
    {
        sort_medicines_ascending(all_medicines);
        return all_medicines;
    }
    Dynamic_array* matched_medicines = create_dynamic_array(2);
    for (int i = 0;i < get_dynamic_size(all_medicines);i++)
    {
        if (strstr(repository->medicines[i].name, given_name) != 0)
        {
            add_new_medicine_dynamic(matched_medicines, repository->medicines[i]);
        }
    }
    destroy_dynamic(all_medicines);
    return matched_medicines;
}

Dynamic_array* get_short_supply_service(Dynamic_array* repository, int quantity)
{
    Dynamic_array* all_medicines = create_dynamic_array(2);
    for (int i = 0;i < get_dynamic_size(repository);i++)
    {
        add_new_medicine_dynamic(all_medicines, repository->medicines[i]);
    }
    Dynamic_array* matched_medicines = create_dynamic_array(2);
    for (int i = 0;i < get_dynamic_size(all_medicines);i++)
    {
        if (get_quantity(all_medicines->medicines[i]) < quantity)
            add_new_medicine_dynamic(matched_medicines, all_medicines->medicines[i]);
    }
    destroy_dynamic(all_medicines);
    return matched_medicines;
}

void init_service(Dynamic_array* repository)
{
    Operation_dynamic* undo_array = create_operations_dynamic(2);
    Operation_dynamic* redo_array = create_operations_dynamic(2);
    add_medicine_services(repository, undo_array, redo_array, "Tusocalm", 20, 90, 99);
    add_medicine_services(repository, undo_array, redo_array, "Controloc", 86, 50, 89);
    add_medicine_services(repository, undo_array, redo_array, "Antinevralgic", 60, 290, 90);
    add_medicine_services(repository, undo_array, redo_array, "Parasinus", 90, 120, 55);
    add_medicine_services(repository, undo_array, redo_array, "Betadina", 30, 80, 145);
    add_medicine_services(repository, undo_array, redo_array, "Ibuprofen", 109, 78, 362);
    add_medicine_services(repository, undo_array, redo_array, "Brufen", 20, 1000, 40);
    add_medicine_services(repository, undo_array, redo_array, "Xanax", 80, 50, 30);
    destroy_operation_dynamic(redo_array);
    destroy_operation_dynamic(undo_array);
}



