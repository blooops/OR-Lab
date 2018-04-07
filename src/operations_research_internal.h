#ifndef __OR_INTERNAL_H__  // Include only once
#define __OR_INTERNAL_H__

#include <stdio.h>
#include <stdlib.h>
#include "../include/operations_research.h"

#define VariableList        int*
#define VariableValueList   StandardDataType*

VariableList basic_variable_list_create(int nbv);

void basic_variable_list_destroy(VariableList list);

VariableValueList solution_create(int nvars);

void solution_destroy(VariableValueList list);

void gauss_reduction_apply(SimplexTable table, int row, int col, int pivot_row,
        int pivot_col);





#endif
