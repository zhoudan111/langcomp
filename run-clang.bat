@echo off
md src
copy RUST.rs src\main.rs
cargo clean
del *.s
del *.cod
del *.o
del *.obj
del *.a
del *.lib
del *.exe
del C
del CPP
echo "----simpfun-----"
clang -O2 -S simpfun.c
clang -O2 -c simpfun.c
lib simpfun.o
echo "----build c-----"
clang -O2 -S C.c
clang -O2 -o C.exe C.c simpfun.o
echo "---build cpp----"
clang++ -O2 -S CPP.cpp
clang++ -O2 -o CPP.exe CPP.cpp simpfun.o
echo "---build rust---"
cargo rustc --release -- --emit asm
cargo build --release
echo "-------C--------"
for /L %%i in (1, 1, 10) do C.exe 64 1000 1000 1000
echo "------CPP-------"
for /L %%i in (1, 1, 10) do CPP.exe 64 1000 1000 1000
echo "------RUST------"
for /L %%i in (1, 1, 10) do target\release\RUST.exe 64 1000 1000 1000
echo "------done------"