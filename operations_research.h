#ifndef __OR_UTILS_INTERFACE_H__
#define __OR_UTILS_INTERFACE_H__


// Preprocessors for user interface with library
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

// Definitions for the interface


// Interface for creating objects
Inequality inequality_create(int nvars);

void inequality_add_to_list(InequalityType ineq, InequalityType* list, int index, 
                            int nvars);

ObjFuncType objective_function_get(int nvars);

SimplexTable simplex_table_create(ObjFuncType objfunc, InequalityType* list, 
                                  int neqs, int nvars);

DualSimplexTable dual_simplex_table_create(ObjFuncType objfunc, 
                                            InequalityType* list, int neqs, 
                                            int nvars);

TransportationTable transportation_table_create();

CuttingPlaneTable cutting_plane_table_create(); 


// Interface for algorithms

void simplex_solve(SimplexTable table, int nvars, int neqs);

void dual_simplex_solve(DualSimplexTable table, int nvars, int neqs);

void transportation_solve(TransportationTable table, int nvars, int neqs);

#endif
