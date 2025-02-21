### Optimization Flags

```makefile
CFLAGS += -march=native -mtune=native -Ofast -flto -ffast-math -fomit-frame-pointer -funroll-loops -fstrict-aliasing -falign-functions=16 -falign-loops=16 -falign-jumps=16 -DNDEBUG
```

The following flags are used in the Makefile to optimize the compilation process:

- `-march=native -mtune=native`: Optimize for the host CPU.
- `-Ofast`: Faster than `-O3` but breaks strict standards.
- `-flto`: Enables link-time optimizations across files.
- `-ffast-math`: Enables aggressive floating-point optimizations.
- `-fomit-frame-pointer`: Reduces stack overhead for better performance.
- `-funroll-loops`: Expands small loops for better speed.
- `-fstrict-aliasing`: Enables strict aliasing rules for optimization.
- `-falign-functions=16`: Aligns function start addresses to 16-byte boundaries.
- `-falign-loops=16`: Aligns loops to 16-byte boundaries.
- `-falign-jumps=16`: Aligns jump targets to 16-byte boundaries.
- `-DNDEBUG`: Disables debugging macros like `assert()`, improving runtime speed.
