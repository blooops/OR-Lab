#ifndef __OR_UTILS_INTERFACE_H__
#define __OR_UTILS_INTERFACE_H__


// Preprocessors for user interface with library
#define Fraction                    struct fraction
#define StandardDataType            double
#define IntegerStrictType           Fraction
#define SimplexTableDataType        StandardDataType
#define DualSimplexTableDataType    StandardDataType
#define TransportationTableDataType StandardDataType
#define CuttingPlaneTableDataType   IntegerStrictType
#define SimplexTable                SimplexTableDataType**
#define DualSimplexTable            DualSimplexTableDataType**
#define TransportationTable         TransportationTableDataType**
#define CuttingPlaneTable           CuttingPlaneTableDataType**
#define InequalityType              StandardDataType*
#define ObjFuncType                 StandardDataType*
#define Solution                    StandardDataType*
#define InequalityList              InequalityType*


/*
*   STRUCTURE DEFINITIONS FOR INTERFACE
*   ->  Fraction
*/

struct fraction {
    StandardDataType num;
    StandardDataType den;
};

/*
 *  USER INTERFACE FOR USING THIS LIBRARY
 *  ->  object creation interface
 *  ->  data input interface
 *  ->  solver function interface
 */


// Interface for creating objects


InequalityList inequality_list_create(int nvars, int neqs);

void inequality_list_destroy(InequalityList list, int neqs);

void inequality_add_to_list(InequalityType ineq, InequalityList list, int index);

ObjFuncType objective_function_create(int nvars);

void objective_function_destroy(ObjFuncType objfunc);

SimplexTable simplex_table_create(ObjFuncType objfunc, InequalityList list, 
        int neqs, int nvars);

void simplex_table_destroy(SimplexTable table, int neqs, int nvars);

DualSimplexTable dual_simplex_table_create(ObjFuncType objfunc, 
        InequalityType list, int neqs, int nvars);

void dual_simplex_table_destroy(DualSimplexTable table, int neqs, int nvars);

TransportationTable transportation_table_create();

void transportation_table_destroy(TransportationTable table);

CuttingPlaneTable cutting_plane_table_create(); 

void cutting_plane_table_destroy(CuttingPlaneTable table);


// Interface for taking data inputs


void inequality_input(InequalityType in, int nvars);

void objective_function_input(ObjFuncType objfunc, int nvars);

void data_validate(ObjFuncType objfunc, InequalityList list, int nvars,
        int neqs);

int remove_degeneracy(InequalityList list, int nvars, int neqs);


// Interface for algorithms


void simplex_solve(SimplexTable table, int nvars, int neqs);

void dual_simplex_solve(DualSimplexTable table, int nvars, int neqs);

void transportation_solve(TransportationTable table, int nvars, int neqs);

#endif
