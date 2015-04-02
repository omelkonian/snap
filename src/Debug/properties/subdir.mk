################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../properties/DoubleProperty.cpp \
../properties/IntegerProperty.cpp \
../properties/Properties.cpp \
../properties/Property.cpp \
../properties/StringProperty.cpp 

OBJS += \
./properties/DoubleProperty.o \
./properties/IntegerProperty.o \
./properties/Properties.o \
./properties/Property.o \
./properties/StringProperty.o 

CPP_DEPS += \
./properties/DoubleProperty.d \
./properties/IntegerProperty.d \
./properties/Properties.d \
./properties/Property.d \
./properties/StringProperty.d 


# Each subdirectory must supply rules for building sources it contributes
properties/%.o: ../properties/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


