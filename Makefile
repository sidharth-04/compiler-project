CC=clang
CFLAGS=-g -w -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include `llvm-config --cflags`
LD=clang++
LDFLAGS=`llvm-config --cxxflags --ldflags --libs core executionengine mcjit interpreter analysis native bitwriter --system-libs` -L/usr/local/opt/llvm/lib/c++ -Wl,-syslibroot,/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk

# Define the build directory
BUILD_DIR=build

# Define the output executable
OUTPUT_EXECUTABLE=compiler

# Define the paths for intermediate files
OBJECT_FILES=$(BUILD_DIR)/compiler.o
BITCODE_FILE=$(BUILD_DIR)/compiler.bc
LLVM_FILE=$(BUILD_DIR)/compiler.ll

# Default target
all: clean compile
compile: $(BUILD_DIR) $(OUTPUT_EXECUTABLE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJECT_FILES): $(BUILD_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT_EXECUTABLE): $(OBJECT_FILES)
	$(LD) $^ $(LDFLAGS) -o $@

clean:
	-rm -rf $(BUILD_DIR) $(OUTPUT_EXECUTABLE)

# LDFLAGS="-L/usr/local/opt/llvm/lib/c++ -Wl,-rpath,/usr/local/opt/llvm/lib/c++"

# llvm is keg-only, which means it was not symlinked into /usr/local,
# because macOS already provides this software and installing another version in
# parallel can cause all kinds of trouble.

# If you need to have llvm first in your PATH, run:
#   echo 'export PATH="/usr/local/opt/llvm/bin:$PATH"' >> ~/.zshrc

# For compilers to find llvm you may need to set:
#   export LDFLAGS="-L/usr/local/opt/llvm/lib"
#   export CPPFLAGS="-I/usr/local/opt/llvm/include"

# /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
