#include "ParameterManager.h"

int main() {
	ParameterManager * params = PM_create(4);
	PM_manage(params,"studentname",STRING_TYPE,1);
    PM_manage(params,"id",INT_TYPE,1);
    PM_manage(params,"regstat",BOOLEAN_TYPE,1);
    PM_manage(params,"marks",LIST_TYPE,1);
    PM_manage(params,"average",REAL_TYPE,0);
	printf("Success?: %d\n", PM_destroy(params));
}