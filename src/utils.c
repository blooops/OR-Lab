#include "operations_research_internal.h"


//  OBJECT CREATION FUNCTION DEFINITIONS


InequalityList inequality_list_create(int nvars, int neqs) {
    InequalityList list = (InequalityList) malloc(sizeof(InequalityType) * neqs);
    int i;
    for(i = 0; i < neqs; i++)
        list[i] = (InequalityType) malloc(sizeof(StandardDataType) * (nvars+1));

    return list;
}


void inequality_list_destroy(InequalityList list, int neqs) {
    int i;
    for(i = 0; i < neqs; i++)
        free(list[i]);

    free(list);
}


void inequality_add_to_list(InequalityType ineq, InequalityList list, 
        int index) {
    list[index] = ineq; 
}


ObjFuncType objective_function_create(int nvars) {
    ObjFuncType objfunc = (ObjFuncType) malloc(sizeof(StandardDataType) * nvars);
    return objfunc;
}


void objective_function_destroy(ObjFuncType objfunc) {
    free(objfunc);
}


SimplexTable simplex_table_create(ObjFuncType objfunc, InequalityList list, 
        int neqs, int nvars) {
    SimplexTable table = (SimplexTable) malloc(sizeof(StandardDataType*) *
            (neqs + 2));
    int i;
    for(i = 0; i < neqs + 2; i++)
        table[i] = (StandardDataType*) malloc(sizeof(StandardDataType) * 
            (nvars + 2));
}


void simplex_table_destroy(SimplexTable table, int neqs, int nvars) {
    int i;
    for(i = 0; i < neqs + 2; i++) 
        free(table[i]);

    free(table);
}


DualSimplexTable dual_simplex_table_create(ObjFuncType objfunc, 
        InequalityType list, int neqs, int nvars) {

}


TransportationTable transportation_table_create() {

}


CuttingPlaneTable cutting_plane_table_create() {

}


//  DATA INPUT FUNCTION DEFINITIONS


void inequality_input(InequalityType in, int nvars) {
    printf("\nInput Data for Inequality:");
    int i;
    for(i = 0; i < nvars; i++) {
        printf("\nCoefficient of X_%d : ", i + 1);
        scanf("%lf", &in[i]);
    }

    printf("\nValue of RHS :");
    scanf("%lf", &in[i]);
}


void objective_function_input(ObjFuncType objfunc, int nvars) {
    int i;
    printf("\nInput Data for Objective Function:");
    for(i = 0; i < nvars; i++) {
        printf("\nCost Coefficient of X_%d : ", i + 1);
        scanf("%lf", &objfunc[i]);
    }
}


void data_validate(ObjFuncType objfunc, InequalityList list, int nvars,
        int neqs) {

}


int remove_degeneracy(InequalityList list, int nvars, int neqs) {

}


VariableList basic_variable_list_create(int nbv) {
    VariableList list = (VariableList) malloc(sizeof(int) * nbv);
}

void basic_variable_list_destroy(VariableList list) {
    free(list);
}

VariableValueList solution_create(int nvars) {
    VariableValueList list = (VariableValueList) malloc(sizeof(StandardDataType)
            * nvars);
}

void solution_destroy(VariableValueList list) {
    free(list);
}


