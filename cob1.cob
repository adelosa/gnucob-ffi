000000 IDENTIFICATION DIVISION.
       PROGRAM-ID. cob1.
       ENVIRONMENT DIVISION.
       DATA DIVISION.
       LINKAGE SECTION.
       01  LINKAGE1.
           05 LINKAGE-AREA              USAGE POINTER.
           05 LINKAGE1-DATA             PIC X(20).
       01  LINKAGE2.
           05 LINKAGE2-DATA             PIC X(20).

       PROCEDURE DIVISION 
           USING 
               LINKAGE1
               LINKAGE2
               .
       
       AA000-MAINLINE SECTION.
           DISPLAY 'IN COB1'.
           MOVE 'COB1-LINKAGE1' TO LINKAGE1-DATA.
           DISPLAY LINKAGE1-DATA.
           MOVE 'COB1-LINKAGE2' TO LINKAGE2-DATA.
           DISPLAY LINKAGE2-DATA.
           CALL 'ccall' USING LINKAGE1.
           GOBACK
           .

       AA000-EXIT.
           EXIT.
