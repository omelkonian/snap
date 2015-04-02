################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../project_main/GraphLib.cpp \
../project_main/GraphQueries.cpp \
../project_main/main_part1.cpp \
../project_main/main_part2.cpp \
../project_main/main_part3.cpp 

OBJS += \
./project_main/GraphLib.o \
./project_main/GraphQueries.o \
./project_main/main_part1.o \
./project_main/main_part2.o \
./project_main/main_part3.o 

CPP_DEPS += \
./project_main/GraphLib.d \
./project_main/GraphQueries.d \
./project_main/main_part1.d \
./project_main/main_part2.d \
./project_main/main_part3.d 


# Each subdirectory must supply rules for building sources it contributes
project_main/%.o: ../project_main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


