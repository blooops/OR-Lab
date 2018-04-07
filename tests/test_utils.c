#include "../src/operations_research_internal.h"
#include <assert.h>

void test_inequality_list_create_and_destroy() {
   InequalityList list = inequality_list_create(5, 4);
   assert(list != NULL);
   printf("\ninequality_list_create() call success!"); 
   inequality_list_destroy(list, 4);
   printf("\ninequality_list_destroy() call success!");
}

int main() {
    test_inequality_list_create_and_destroy();
    return 0;
}
