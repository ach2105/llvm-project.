This project enhances the Clang compiler to automatically generate symbolic string maps for C++ `enum` types. These maps are emitted directly into the compiled object files and enable seamless runtime access to enum names without requiring any manual mapping or macros.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Motivation](#motivation)
- [Demo](#demo)
- [How It Works](#how-it-works)
- [Folder Structure](#folder-structure)
- [Installation & Build](#installation--build)
- [Usage](#usage)
- [Output Verification](#output-verification)
- [Credits](#credits)

---

## 📄 Overview

This project modifies Clang's backend (`CodeGenModule.cpp`) to emit a global array for every enum it encounters. The global variable is named using the convention `__nameof_<EnumName>` and stores the symbolic names of all enum values.

### Example

Given:
```cpp
enum Color { RED, GREEN, BLUE };
```

The compiler automatically generates:
```cpp
const char* __nameof_Color[] = { "RED", "GREEN", "BLUE" };
```

This symbol is embedded in the `.o` file and can be referenced in any other source file.

---

## 💡 Motivation

C++ does not support built-in reflection or runtime access to enum names. Manually writing mapping functions or macros is tedious, error-prone, and not scalable. This project eliminates that need by embedding the mapping during compilation — fully automated and zero-runtime-cost.

---

## 🚀 Demo

### Files:
- `test_enum.cpp` – defines the enum and forces emission
- `use_enum.cpp` – uses the emitted map at runtime

### Build and Run:

```bash
# Compile enum definition
<path-to-clang++> test_enum.cpp -c -o test_enum.o

# Compile and link usage code
<path-to-clang++> use_enum.cpp test_enum.o -o enum_demo \
  -isystem /Library/Developer/CommandLineTools/usr/include/c++/v1 \
  -L /Library/Developer/CommandLineTools/usr/lib -lc++

# Run the demo
./enum_demo
```

### Output:
```
Enum name for value 0: RED
Enum name for value 1: GREEN
Enum name for value 2: BLUE
```

---

## ⚙️ How It Works

1. **Detect Enum**  
   Clang's `EmitTopLevelDecl()` is modified to detect enum declarations (`EnumDecl`).

2. **Generate Strings**  
   Each enum constant is converted into a string using LLVM's `ConstantDataArray`.

3. **Emit Global Array**  
   A global `const char*[]` is generated and inserted into the LLVM IR with external linkage.

4. **Link & Use**  
   The symbol (e.g., `__nameof_Color`) can be used from any other `.cpp` file.

---

## 🗂 Folder Structure

```
clang_integration/
├── llvm-project/           # Cloned and modified LLVM source
│   └── clang/lib/CodeGen/CodeGenModule.cpp  # Contains enum logic
├── test_enum.cpp           # Input enum file
├── use_enum.cpp            # Output demonstration
└── README.md               # This file
```

---

## 🛠 Installation & Build

1. **Clone LLVM**
```bash
git clone https://github.com/llvm/llvm-project.git
cd llvm-project
mkdir build && cd build
```

2. **Build Clang**
```bash
cmake -G Ninja ../llvm -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release
ninja clang
```

3. **Find Clang Binary**
```bash
./bin/clang++
```

---

## 📦 Usage

1. Write any enum in a `.cpp` file:
```cpp
enum Status { SUCCESS, FAILURE };
```

2. Compile using your modified Clang:
```bash
./bin/clang++ your_file.cpp -c -o your_file.o
```

3. Use the generated symbol in another file:
```cpp
extern const char* __nameof_Status[];
```

---

## 🔍 Output Verification

To confirm that the enum map was generated:

```bash
nm your_file.o | grep __nameof
```

Expected:
```
00000000000000XX D __nameof_Status
```

---

## 👥 Credits

- **Achyuta Srivatsa** – Project Author  
- **Based on LLVM + Clang** – https://github.com/llvm/llvm-project

---

## 📜 License

This project is for academic and research purposes, built on top of LLVM's open-source compiler framework (Apache 2.0).

---
