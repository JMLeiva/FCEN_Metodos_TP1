################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Matriz.cpp \
../src/MatrizDOD.cpp \
../src/MatrizDOK.cpp \
../src/MatrizStandard.cpp \
../src/Vector.cpp \
../src/main.cpp 

OBJS += \
./src/Matriz.o \
./src/MatrizDOD.o \
./src/MatrizDOK.o \
./src/MatrizStandard.o \
./src/Vector.o \
./src/main.o 

CPP_DEPS += \
./src/Matriz.d \
./src/MatrizDOD.d \
./src/MatrizDOK.d \
./src/MatrizStandard.d \
./src/Vector.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -p -pg -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


