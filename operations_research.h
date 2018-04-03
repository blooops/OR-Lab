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

// Definitions for the interface
void inequality_add_to_list(InequalityType* list, int index);
ObjFuncType objective_function_get();
SimplexTable simplex_table_create();
DualSimplexTable dual_simplex_table_create();
TransportationTable transportation_table_create()
CuttingPlaneTable cutting_plane_table_create();

#endif
