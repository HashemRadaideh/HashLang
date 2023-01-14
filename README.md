# Hash

Just another avarage programming language.

### Features:

1. dynamicly typed
2. strongly typed
3. interpreted
4. JIT
5. Virtual enviroment

### Primitive types:

1. boolean
2. number
3. string

### Complex types:

**Single complex type hash-tables**

# Build from source

> It's best to build the project before starting to work, to remove all warnings and file path problems (diagnostics).

```bash
git clone https://github.com/HashemRadaideh/Hash
cd ./Hash
cmake -B ./build && cmake --build ./build --config Release --target all --
./build/hash
```

# Debuging

```bash
cmake -B ./build && cmake --build ./build --config Debug --target all -j 6 --
```
