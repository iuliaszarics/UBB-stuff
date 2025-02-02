#include <stdio.h>
#include "repository.h"
#include "domain.h"
#include "controller.h"
#include "ui.h"

int main(int argc, char** argv)
{
    Dynamic_array* repository = create_repository();
    printf("merge1");
    Operation_dynamic* undo_array = create_operations_dynamic(2);
    printf("merge2");
    Operation_dynamic* redo_array = create_operations_dynamic(2);
    printf("merge3");
    init_service(repository);
    printf("merge4");
    run(repository, undo_array, redo_array);
    printf("merge5");
    destroy_dynamic(repository);
    printf("merge6");
    destroy_operation_dynamic(undo_array);
    printf("merge7");
    destroy_operation_dynamic(redo_array);
    printf("merge8");
    return 0;

}