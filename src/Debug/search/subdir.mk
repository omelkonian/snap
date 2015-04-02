################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../search/BBFS.cpp \
../search/BFS.cpp \
../search/ExtendedBFS.cpp \
../search/ExtendedBFS2.cpp \
../search/ResultSet.cpp \
../search/TidalTrust.cpp 

OBJS += \
./search/BBFS.o \
./search/BFS.o \
./search/ExtendedBFS.o \
./search/ExtendedBFS2.o \
./search/ResultSet.o \
./search/TidalTrust.o 

CPP_DEPS += \
./search/BBFS.d \
./search/BFS.d \
./search/ExtendedBFS.d \
./search/ExtendedBFS2.d \
./search/ResultSet.d \
./search/TidalTrust.d 


# Each subdirectory must supply rules for building sources it contributes
search/%.o: ../search/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


