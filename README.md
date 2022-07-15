# gnucob-ffi

## compile and run

    ./build.sh && LD_LIBRARY_PATH=. COB_LIBRARY_PATH=. ./main


## Introduction

The repo was used to recreate an issue with FFI linkage into GNUCOBOL 3 programs from c.

The issue is that on first link from C to COBOL, both Linkage areas were passed to COBOL
but on the second pass (that is C->COBOL->C->COBOL) the following error was receieved:

    libcob: ./cob2.cob:21: error: LINKAGE item 'LINKAGE2' (accessed by 'LINKAGE2-DATA') not passed by caller

This indicating that the C program has not passed the second linkage area, but the call
parameters were the same for both calls.

Thanks to Simon Sobisch (@GitMensch) from the GNUCOBOL project for resolving.
See https://sourceforge.net/p/gnucobol/discussion/help/thread/7ce4211af8/

The issue was related to an GNUCOBOL linkage counter not being set.

```c
// Tell the runtime about the numbers of parameters passed
// (necessary for GnuCOBOL < 4) to support IF param OMITTED
cob_get_global_ptr()->cob_call_params = num_linkage_areas;
```

## Program explanation

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

