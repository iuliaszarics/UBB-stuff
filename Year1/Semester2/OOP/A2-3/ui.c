#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ui.h"
#include "controller.h"

void print_menu()
{
    printf("This is a console-based application meant to help organizing the medicines./n");
    printf("These are it's functionalities:/n");
    printf("1.Add a medicine./n");
    printf("2.Delete a medicine./n");
    printf("3.Update a medicine./n");
    printf("4.Search for a medicine given a string./n");
    printf("5.Show medicines short in supply./n");
    printf("6.Undo./n");
    printf("7.Redo./n");
    printf("8.Print all medicines./n");
    printf("9.Exit./n");
}

void ui_add_medicine(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array)
{
    char name[50];
    int concentration, quantity, price;
    printf("Enter the name of the medicine you want to add: /n");
    if (scanf("%49s", name) != 1)
    {
        printf("Invalid input for name!\n");
        return;
    }
    printf("Enter the concentration: ");
    if (scanf("%d", &concentration) != 1)
    {
        printf("Invalid input for concentration!\n");
        return;
    }
    printf("Enter the quantity: ");
    if(scanf("%d", &quantity)!=1)
    {
        printf("Invalid input for quantity!\n");
        return;
    }
    printf("Enter the price: ");
    if (scanf("%d", &price) != 1) {
        printf("Invalid input for price!\n");
        return;
    }
    add_medicine_services(repository, undo_array, redo_array, &name, &concentration, &quantity, &price);

}

void ui_delete_medicine(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array)
{
    char name[50];
    int concentration;
    printf("Enter the name of the medicine you want to delete: /n");
    if (scanf("%49s", name) != 1) {
        printf("Invalid input for name!\n");
        return;
    }
    printf("Enter the concentration: ");
    if (scanf("%d", &concentration) != 1)
    {
        printf("Invalid input for concentration!\n");
        return;
    }
    delete_medicine_service(repository, undo_array, redo_array, &name, &concentration);
}


void ui_update_medicine(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array) {
    char name[50];
    int concentration, new_concentration, new_quantity, new_price;
    char new_name[50];

    printf("Enter the name of the medicine you want to update: \n");
    if (scanf("%49s", name) != 1) {
        printf("Invalid input for name!\n");
        return;
    }

    printf("Enter the concentration: \n");
    if (scanf("%d", &concentration) != 1) {
        printf("Invalid input for concentration!\n");
        return;
    }

    printf("Enter the new name of the medicine: \n");
    if (scanf("%49s", new_name) != 1) {
        printf("Invalid input for new name!\n");
        return;
    }

    update_medicine_name_service(repository, undo_array, redo_array, name, &concentration, new_name);

    printf("Enter the new concentration: \n");
    if (scanf("%d", &new_concentration) != 1) {
        printf("Invalid input for new concentration!\n");
        return;
    }

    update_medicine_concentration_service(repository, undo_array, redo_array, name, &concentration, &new_concentration);

    printf("Enter the new quantity: \n");
    if (scanf("%d", &new_quantity) != 1) {
        printf("Invalid input for new quantity!\n");
        return;
    }

    update_medicine_quantity_service(repository, undo_array, redo_array, name, &concentration, &new_quantity);

    printf("Enter the new price: \n");
    if (scanf("%d", &new_price) != 1) {
        printf("Invalid input for new price!\n");
        return;
    }

    update_medicine_price_service(repository, undo_array, redo_array, name, &concentration, &new_price);
}


void show_medicines_short_in_supply(Dynamic_array* repository)
{
    int quantity;
    printf("Enter the quantity: /n");
    if (scanf("%d", &quantity) != 1)
    {
        printf("Invalid input for quantity!\n");
        return;
    }
    get_short_supply_service(repository, &quantity);
}

void print_dynamic(Dynamic_array* medicines)
{
    for (int i = 0;i < medicines->size;i++)
    {
        printf("%d. Name = %s ", i + 1, get_name(medicines->medicines[i]));
        printf("Concentration = %d ", get_concentration(medicines->medicines[i]));
        printf("Quantity = %d ", get_quantity(medicines->medicines[i]));
        printf("Price = %d\n", get_price(medicines->medicines[i]));
    }
}

void print_all_medicines(Dynamic_array* repository)
{
    Dynamic_array* all_medicines = get_all_medicines(repository);
    printf("The list of the medicines is: /n");
    print_dynamic(all_medicines);
    destroy_dynamic(all_medicines);
}

int get_the_command()
{
    int command;
    printf("Please choose what you want to do (1-9): /n");
    if (scanf("%d", &command) != 1)
    {
        printf("Invalid input for command!\n");
        return;
    }
    return command;
}

int use_the_command(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array, int selected_command)
{
    switch (selected_command)
    {
    case 1:
        ui_add_medicine(repository, undo_array, redo_array);
        break;
    case 2:
        ui_delete_medicine(repository, undo_array, redo_array);
        break;
    case 3:
        ui_update_medicine(repository, undo_array, redo_array);
        break;
    case 4:
        break;
    case 5:
        show_medicines_short_in_supply(repository);
    case 6:
        break;
    case 7:
        break;
    case 8:
        print_all_medicines(repository);
    case 9:
        return 1;
    }
    return 0;
}

void run(Dynamic_array* repository, Operation_dynamic* undo_array, Operation_dynamic* redo_array)
{
    do
    {
        print_menu();
        int command = get_the_command();
        int result = use_the_command(repository, undo_array, redo_array, command);
        if (result) break;
    } while (1);
}