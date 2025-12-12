cd src;
make -j`nproc`;
mv libmach.a ..;
make clean > /dev/null;
cd ..;
