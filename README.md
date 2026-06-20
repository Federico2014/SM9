# SM9 Cryptographic Algorithm Implementation

SM9 (Identity-Based Cryptography) is an identity-based cryptographic algorithm standard issued by the State Cryptography Administration of China.

## Project Structure

```
SM9/
├── include/sm9/
│   ├── core/
│   │   ├── bigint.h          # Big integer arithmetic
│   │   ├── field2.h          # Quadratic extension field (F_p^2)
│   │   ├── field4.h          # Quartic extension field (F_p^4)
│   │   └── field12.h         # Duodecic extension field (F_p^12)
│   ├── curve/
│   │   ├── point.h           # BN curve point arithmetic (G1)
│   │   ├── point2.h          # Twist curve point arithmetic (G2)
│   │   └── pairing.h         # R-ate pairing calculation
│   ├── hash/
│   │   ├── sm3.h             # SM3 hash algorithm
│   │   └── sm4.h             # SM4 block cipher
│   ├── sm9/
│   │   ├── params.h          # SM9 curve parameters
│   │   ├── sm9_dsa.h         # SM9 digital signature
│   │   ├── sm9_ka.h          # SM9 key agreement
│   │   └── sm9_pkc.h         # SM9 public key encryption
│   └── utility.h             # Utility functions
├── src/
│   ├── core/                 # Core mathematical primitives
│   ├── curve/                # Elliptic curve operations
│   ├── hash/                 # Hash and cipher algorithms
│   ├── sm9/                  # SM9 algorithm implementations
│   └── utility.c             # Utility functions implementation
├── tests/
│   └── test_sm9.c            # Test program
├── docs/                     # Documentation
├── CMakeLists.txt            # CMake build configuration
├── Makefile                  # Make build configuration
└── README.md                 # This file
```

## Build Instructions

### Method 1: Using Make (Linux/macOS/MinGW)

```bash
# Build library and test
make

# Clean build artifacts
make clean

# Run test
./bin/sm9_test        # Linux/macOS
./bin/sm9_test.exe    # Windows
```

### Method 2: Using CMake (Cross-platform)

```bash
# Create build directory
mkdir build && cd build

# Configure
cmake ..

# Build
cmake --build .

# Run test
./bin/sm9_test        # Linux/macOS
./bin/sm9_test.exe    # Windows

# Install (optional)
cmake --install .
```

### Method 3: Windows MSVC

```bash
# Using cmake
mkdir build && cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release

# Or open the .sln file directly in Visual Studio
```

## Platform Support

- **Linux**: GCC, Clang
- **macOS**: Apple Clang, GCC
- **Windows**:
  - MinGW/MSYS2
  - Visual Studio 2019+
  - Cygwin

## Dependencies

- C99 compatible compiler
- Math library (libm on Unix-like systems)

## Using SM9 as a Library

After building, you can link against the SM9 library:

```c
#include <sm9/sm9.h>

int main() {
    // Initialize parameters
    SM9Params_init(&BN);

    // Your SM9 operations here...

    return 0;
}
```

Compile with:
```bash
gcc -Iinclude your_program.c -Lbuild -lsm9 -lm
```

## Notes

1. The code contains legacy GB2312 encoded comments. Use an editor that supports multi-byte encoding to view them properly.
2. Pairing operation performance tests may take a long time.
3. Some test cases output long hexadecimal data for verification purposes.

## Algorithm Description

SM9 is an Identity-Based Cryptography (IBC) algorithm with the following features:

- No certificates required: User's public key can be any string (e.g., email, phone number)
- Based on bilinear pairing: Uses BN elliptic curve and R-ate pairing
- Includes three sub-algorithms:
  - **SM9-DS**: Digital signature algorithm
  - **SM9-KA**: Key agreement protocol
  - **SM9-PKC**: Public key encryption algorithm

## Module Dependencies

```
bigint (base)
   └── params
        └── field2
             └── field4
                  └── field12
                       └── point (G1)
                            └── point2 (G2)
                                 └── pairing
                                      └── utility
                                           ├── sm3
                                           └── sm9_dsa
                                                └── sm9_ka
                                                     └── sm9_pkc
                                                          └── sm4
```

## References

- GM/T 0044-2016 SM9 Identity-Based Cryptographic Algorithms
- ISO/IEC 18033-5:2015
