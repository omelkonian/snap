################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Bucket.cpp \
../BucketItem.cpp \
../BucketList.cpp \
../CliqueNode.cpp \
../Edge.cpp \
../Graph.cpp \
../LinearHashTable.cpp \
../Node.cpp \
../Pair.cpp \
../TrustNode.cpp \
../main.cpp 

OBJS += \
./Bucket.o \
./BucketItem.o \
./BucketList.o \
./CliqueNode.o \
./Edge.o \
./Graph.o \
./LinearHashTable.o \
./Node.o \
./Pair.o \
./TrustNode.o \
./main.o 

CPP_DEPS += \
./Bucket.d \
./BucketItem.d \
./BucketList.d \
./CliqueNode.d \
./Edge.d \
./Graph.d \
./LinearHashTable.d \
./Node.d \
./Pair.d \
./TrustNode.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


