set -e
mkdir -p src
cp RUST.rs src/main.rs
cargo clean
rm -f *.s *.cod *.o *.obj *.a *.lib C CPP
echo "----simpfun-----"
cc -O2 -S simpfun.c
cc -O2 -c simpfun.c
ar -r libsimpfun.a simpfun.o
echo "----build c-----"
cc -O2 -S C.c
cc -O2 -o C C.c simpfun.o
echo "---build cpp----"
c++ -O2 -S CPP.cpp
c++ -O2 -o CPP CPP.cpp simpfun.o
echo "---build rust---"
cargo rustc --release -- --emit asm
cargo build --release
echo "-------C--------"
for ((i=0; i<10; ++i)); do ./C 64 1000 1000 1000; done
echo "------CPP-------"
for ((i=0; i<10; ++i)); do ./CPP 64 1000 1000 1000; done
echo "------RUST------"
for ((i=0; i<10; ++i)); do target/release/RUST 64 1000 1000 1000; done
echo "------done------"