# gnucob-ffi

## compile and run

    ./build.sh && LD_LIBRARY_PATH=. COB_LIBRARY_PATH=. ./main

## What is this doing?

### main.c  

* Calls `cob1.cob` COBOL module using FFI.
* Passes 2 parameters
    * LINKAGE1 -- pointer + 20 bytes
    * LINKAGE2 -- 20 bytes
* The pointer points to a list of pointers for loc of LINKAGE1 and LINKAGE2.

### cob1.cob
* COBOL module called by `main.c` 
* LINKAGE contains both LINKAGE1 and LINKAGE2
* Program sets and displays values in these two linkage areas
* Call `ccall.c` program passing only LINKAGE1

### ccall.c
* Called by `cob1.cob`
* Gets the pointer in LINKAGE1, and uses list to call `cob2.cob` using list of pointers.

### cob2.cob
* COBOL module called by `ccall.c`
* Same linkage as `cob1.cob`
* Diplays values in LINKAGE1 and LINKAGE2.

## What is the problem?

When COB2 runs, the following error is received:

    libcob: ./cob2.cob:21: error: LINKAGE item 'LINKAGE2' (accessed by 'LINKAGE2-DATA') not passed by caller

LINKAGE1 references works fine.. but LINKAGE2 does not.

