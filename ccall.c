#include <ffi.h>
#include <libcob.h>
#include <stdio.h>

static void (*cobmodule)(void);
int call_cobmodule(char * module, int num_linkage_areas, void ** linkage_areas);  // in main.c

struct linkage1 {
    void * linkage_area;         // pointer linkage_area
    char data[20];              // tran number (FW)
};

void ccall(struct linkage1 * linkage1) {
    
    printf("%s\n", linkage1->data);
    void ** linkage_area = linkage1->linkage_area;
      
    // Setup call to ffi
    void * prog_linkage_ptr[2];           // Alloc list of pointers for prog linkage
    prog_linkage_ptr[0] = &linkage_area[0];
    prog_linkage_ptr[1] = &linkage_area[1];

    call_cobmodule("cob2", 2, prog_linkage_ptr);
}
