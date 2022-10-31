use std::env;

#[link(name = "simpfun", kind = "static")]
extern "C" {
    pub fn simpstart(m: cty::c_int);
    pub fn simpfun(i: cty::c_int, j: cty::c_int, k: cty::c_int);
    pub fn dumpfin();
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let m: i32 = args[1].parse().unwrap();
    let I: i32 = args[2].parse().unwrap();
    let J: i32 = args[3].parse().unwrap();
    let K: i32 = args[4].parse().unwrap();
    unsafe {
        simpstart(m);
        for i in 0..I {
            for j in 0..J {
                for k in 0..K {
                    simpfun(i, j, k);
                }
            }
        }
        dumpfin();
    }
}
