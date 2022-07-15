#include <ffi.h>
#include <libcob.h>
#include <stdio.h>

static void (*cobmodule)(void);
int call_cobmodule(char * module, int num_linkage_areas, void ** linkage_areas);

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

int call_cobmodule(char * module, int num_linkage_areas, void ** linkage_areas) {  

    // Link acty, get COBOL function pointer
    cobmodule = cob_resolve(module);
    if(cobmodule == NULL) {
        fprintf(stderr, "call_cobmodule: %s\n", cob_resolve_error());
        return -1;
    }

    // Tell the runtime about the numbers of parameters passed
    // (necessary for GnuCOBOL < 4) to support IF param OMITTED
    cob_get_global_ptr()->cob_call_params = num_linkage_areas;

    // Initialize the datagroup argument vectors
    ffi_cif cif;
    ffi_type *args[num_linkage_areas];
    ffi_arg rc;
  
    int i;
    for (i=0;i<num_linkage_areas;i++) {
        args[i] = &ffi_type_pointer;
    }

    /* Initialize the cif */
    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, num_linkage_areas, &ffi_type_sint, args) == FFI_OK) {
        ffi_call(&cif, cobmodule, &rc, linkage_areas);  
    }
    
    //rc now holds the result of the call
    return rc;
}

