From any folder in terminal
1. Generate build tree with `cmake -B build -S /path/to/source/root`
2. Build target calculator with `make all -C build`
3. Call calculator server `./build/servercalculator`