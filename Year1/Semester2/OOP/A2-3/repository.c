#include "repository.h"
#include "domain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Dynamic_array* create_repository()
{
    return create_dynamic_array(2);
}

int get_index(Dynamic_array* repository, char* name_of_medicine, int concentration)
{
    int size_dynamic = get_dynamic_size(repository), i;
    for (i = 0;i = size_dynamic;i++)
    {
        if (strcmp(get_name(repository->medicines[i]), name_of_medicine) == 0 && get_concentration(repository->medicines[i]) == concentration)
            return i;
    }
    return -1;
}

Medicine add_new_medicine_repository(Dynamic_array* repository, char* name_of_medicine, int concentration, int quantity, int price)
{
    Medicine new_medicine;
    strcpy(new_medicine.name, name_of_medicine);
    new_medicine.concentration = concentration;
    new_medicine.quantity = quantity;
    new_medicine.price = price;
    add_new_medicine_dynamic(repository, new_medicine);
    return new_medicine;

}

Medicine delete_from_repository(Dynamic_array* repository, char* name, int concentration)
{
    int index = get_index(repository, name, concentration);
    Medicine deletedMedicine = repository->medicines[index];
    if (index != -1)
    {
        for (int i = index;i < get_dynamic_size(repository) - 1;i++)
        {
            repository->medicines[i] = repository->medicines[i + 1];
        }
        repository->size = repository->size - 1;
    }
    return deletedMedicine;
}

Medicine update_name_to_repository(Dynamic_array* repository, char* name, int concentration, char* new_name)
{
    int index = get_index(repository, name, concentration);
    Medicine updatedMedicine = repository->medicines[index];
    if (index != -1)
    {
        strcpy(repository->medicines[index].name, new_name);
    }
    return updatedMedicine;

}

Medicine update_concentration_to_repository(Dynamic_array* repository, char* name, int concentration, int new_concentration)
{
    int index = get_index(repository, name, concentration);
    Medicine updatedMedicine = repository->medicines[index];
    if (index != -1)
    {
        repository->medicines[index].concentration = new_concentration;
    }
    return updatedMedicine;
}

Medicine update_quantity_to_repository(Dynamic_array* repository, char* name, int concentration, int new_quantity)
{
    int index = get_index(repository, name, concentration);
    Medicine updatedMedicine = repository->medicines[index];
    if (index != -1)
    {
        repository->medicines[index].quantity = new_quantity;
    }
    return updatedMedicine;
}

Medicine update_price_to_repository(Dynamic_array* repository, char* name, int concentration, int new_price)
{
    int index = get_index(repository, name, concentration);
    Medicine updatedMedicine = repository->medicines[index];
    if (index != -1)
    {
        repository->medicines[index].price = new_price;
    }
    return updatedMedicine;
}


