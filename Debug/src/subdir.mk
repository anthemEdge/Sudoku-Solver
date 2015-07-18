################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Game.cpp \
../src/Grid.cpp \
../src/Pos.cpp \
../src/PossibleGird.cpp \
../src/Sudoku\ Solver.cpp 

OBJS += \
./src/Game.o \
./src/Grid.o \
./src/Pos.o \
./src/PossibleGird.o \
./src/Sudoku\ Solver.o 

CPP_DEPS += \
./src/Game.d \
./src/Grid.d \
./src/Pos.d \
./src/PossibleGird.d \
./src/Sudoku\ Solver.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Sudoku\ Solver.o: ../src/Sudoku\ Solver.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Sudoku Solver.d" -MT"src/Sudoku\ Solver.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


