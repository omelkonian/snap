################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../graph_metrics/edgeBetweeness.cpp \
../graph_metrics/metrics.cpp 

OBJS += \
./graph_metrics/edgeBetweeness.o \
./graph_metrics/metrics.o 

CPP_DEPS += \
./graph_metrics/edgeBetweeness.d \
./graph_metrics/metrics.d 


# Each subdirectory must supply rules for building sources it contributes
graph_metrics/%.o: ../graph_metrics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


