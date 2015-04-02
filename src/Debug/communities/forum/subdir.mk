################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../communities/forum/Forum.cpp \
../communities/forum/ForumList.cpp 

OBJS += \
./communities/forum/Forum.o \
./communities/forum/ForumList.o 

CPP_DEPS += \
./communities/forum/Forum.d \
./communities/forum/ForumList.d 


# Each subdirectory must supply rules for building sources it contributes
communities/forum/%.o: ../communities/forum/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


