# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

# intro.o : intro.cpp intro.h
# 	clang++ -c intro.cpp
    
# main.o : main.cpp
# 	clang++ -c main.cpp

intro : main.o intro.o PNG.o HSLAPixel.o lodepng.o output_msg
	clang++ main.o intro.o PNG.o HSLAPixel.o lodepng.o -o intro

main.o : main.cpp #intro.h cs225/PNG.h cs225/HSLAPixel.h
	clang++ -c main.cpp


intro.o : intro.cpp intro.h #cs225/PNG.h #cs225/HSLAPixel.h
	clang++ -c intro.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h #cs225/HSLAPixel.h #cs225/lodepng/lodepng.h
	clang++ -c cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	clang++ -c cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	clang++ -c cs225/lodepng/lodepng.cpp



# intro : intro.o main.o output_msg
# 	clang++ intro.o main.o -o intro

# intro.o : intro.cpp intro.h
# 	clang++ -c intro.cpp
    
# main.o : main.cpp
# 	clang++ -c main.cpp

clean :
	rm intro *.o




output_msg: ; $(CLANG_VERSION_MSG)

# Be sure to add output_msg as dependency target for your `intro` binary

test: output_msg intro.o PNG.o HSLAPixel.o lodepng.o tests.o 
	clang++ intro.o PNG.o HSLAPixel.o lodepng.o tests.o -o test

tests.o: tests/tests.cpp tests/catch.hpp cs225/PNG.h cs225/HSLAPixel.h
	clang++ -c tests/tests.cpp
    
.PHONY: output_msg