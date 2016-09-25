void BI_imvcopy(int, int, int*, int, char*);
void BI_ivmcopy(int, int, int*, int, char*);
void BI_dmvcopy(int, int, double*, int, char*);
void BI_dvmcopy(int, int, double*, int, char*);
void BI_TransDist(BLACSCONTEXT*, char, int, int, int*,
                  int*, int, BI_DistType*, int, int);

void Cblacs_pinfo(int*, int*);
F_VOID_FUNC blacs_pinfo_(int*, int*);

void Cblacs_gridmap(int*, int*, int, int, int);
F_VOID_FUNC blacs_gridmap_(int*, int*, int*, int*, int*);

void Cblacs_abort(int, int);
void Cblacs_get(int, int, int*);
void Cblacs_gridmap(int*, int*, int, int, int);
