Building
--------

```
mkdir build/
cd build/
cmake ..
make
```

Generating .clang_complete file (for Vim autocompletion)
--------------------------------------------------------

1. Clean build files
```
cd build/
rm -rf *
```
2. Run `CC='../cc_args.py gcc' CXX='../cc_args.py g++' cmake ..`
3. The .clang_complete file will be in build/, just move it to the src/ folder.
