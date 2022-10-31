@echo off
md src
copy RUST.rs src\main.rs
cargo clean
del *.cod
del *.obj
del *.lib
del *.exe
echo "----simpfun-----"
cl /O2 /FAcs /c simpfun.c
lib simpfun.obj
echo "----build c-----"
cl /O2 /FAcs C.c simpfun.obj
echo "---build cpp----"
cl /O2 /EHsc /FAcs CPP.cpp simpfun.obj
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