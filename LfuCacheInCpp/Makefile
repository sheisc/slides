####################################################################################
# 				How to Use
# 
# (1) Build the project
#   make
#	make CXX=clang++	
#
# (2) Run the executable
#   ./main
# (3) Clean the project
#   make clean
#
# If you want to know more about makefile, please refer to:
#
#    https://www.gnu.org/software/make/manual/html_node/Rule-Syntax.html
#
####################################################################################
PROJ_ROOT_PATH = $(shell pwd)

TARGET_EXE = main
BUILD_DIR = build

CPP_SRC_FILES = $(shell find ./src -name "*.cpp")
H_SRC_FILES = $(shell find ./src -name "*.h")

# src/*.cpp  --->  src/*.o ---> build/*.o
TMP_OBJ_FILES = $(CPP_SRC_FILES:.cpp=.o)
OBJ_FILES_IN_BUILD =$(subst src/,$(BUILD_DIR)/,$(TMP_OBJ_FILES))

# src/*.cpp  --->  src/*.o ---> build/*.o
TMP_LLVM_LL_FILES = $(CPP_SRC_FILES:.cpp=.ll)
LLVM_LL_FILES_IN_BUILD =$(subst src/,$(BUILD_DIR)/,$(TMP_LLVM_LL_FILES))

CXX= g++
#CPPFLAGS = -m32 -g -no-pie --save-temps -I $(PROJ_ROOT_PATH)/src
#CPPFLAGS = -g --save-temps -I $(PROJ_ROOT_PATH)/src
#CPPFLAGS = -no-pie --save-temps -fno-asynchronous-unwind-tables -I $(PROJ_ROOT_PATH)/src 
CPPFLAGS = -g -Wall -I $(PROJ_ROOT_PATH)/src 

# create a directory  
$(shell mkdir -p $(BUILD_DIR))

# the default target
all: 
	make $(TARGET_EXE)
ifeq ($(CXX),clang++)	
	make gen_llvm
endif

# generate the target, which depends on the "build/*.o" files
$(TARGET_EXE):  $(OBJ_FILES_IN_BUILD) 	
	$(CXX) $(CPPFLAGS) -o $(TARGET_EXE) $(OBJ_FILES_IN_BUILD)

gen_llvm:  $(LLVM_LL_FILES_IN_BUILD)


# How to generate a "build/*.o" from a "src/*.cpp"
# To generate prerequisites automatically, please see COMP9024/C/HowToMake/Makefile.V2
# https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html
$(BUILD_DIR)/%.o: src/%.cpp $(H_SRC_FILES)
	@mkdir -p $(shell dirname $@)
	${CXX} ${CPPFLAGS} -c $< -o $@

$(BUILD_DIR)/%.ll: src/%.cpp $(H_SRC_FILES)
	@mkdir -p $(shell dirname $@)
	${CXX} -c -S -emit-llvm ${CPPFLAGS} -c $< -o $@


view:
	find ./images -name "*.png" | sort | xargs feh -g 1024x768  &

# clean all the files generated	
clean:
	rm -rf $(TARGET_EXE) $(BUILD_DIR) 
	find . -name "*.o" | xargs rm -f
	find . -name "*.s" | xargs rm -f
	find . -name "*.i" | xargs rm -f
	find . -name "*.d" | xargs rm -f
	find . -name "*.bc" | xargs rm -f
	find ./images -name "*.dot" | xargs rm -f

