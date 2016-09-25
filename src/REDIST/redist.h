#ifdef T3D
#define float double
#endif
#ifdef T3E
#define float double
#endif
#ifdef CRAY
#define float double
#endif

//WCC:add
#undef NDEBUG
#include "../BLACS/Bdef.h"
#include "../BLACS/Bdef_wcc.h"
