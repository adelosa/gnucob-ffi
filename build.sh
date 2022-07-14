rm *.so 
rm main
cobc -d -x `pkg-config --libs libffi` -o ./main ./main.c
cobc -d -m -o ./cob1.so ./cob1.cob
cobc -d -m -o ./cob2.so ./cob2.cob
cobc -d -m `pkg-config --libs libffi` -o ./ccall.so ./ccall.c