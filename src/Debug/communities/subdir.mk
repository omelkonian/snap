################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../communities/Communities.cpp \
../communities/Community.cpp \
../communities/_communities.cpp \
../communities/cliquePercolationMethod.cpp \
../communities/findCliques.cpp \
../communities/girvanNewman.cpp 

OBJS += \
./communities/Communities.o \
./communities/Community.o \
./communities/_communities.o \
./communities/cliquePercolationMethod.o \
./communities/findCliques.o \
./communities/girvanNewman.o 

CPP_DEPS += \
./communities/Communities.d \
./communities/Community.d \
./communities/_communities.d \
./communities/cliquePercolationMethod.d \
./communities/findCliques.d \
./communities/girvanNewman.d 


# Each subdirectory must supply rules for building sources it contributes
communities/%.o: ../communities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


