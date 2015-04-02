################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/general.cpp \
../tests/testBucket.cpp \
../tests/tests.cpp 

OBJS += \
./tests/general.o \
./tests/testBucket.o \
./tests/tests.o 

CPP_DEPS += \
./tests/general.d \
./tests/testBucket.d \
./tests/tests.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


