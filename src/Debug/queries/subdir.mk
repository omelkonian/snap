################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../queries/Match.cpp \
../queries/MatchListItem.cpp \
../queries/MatchesList.cpp \
../queries/Stalker.cpp \
../queries/StalkerList.cpp \
../queries/Stalkers.cpp \
../queries/Trend.cpp \
../queries/TrendList.cpp \
../queries/TrendListItem.cpp \
../queries/query1.cpp \
../queries/query2.cpp \
../queries/query3.cpp \
../queries/query4.cpp 

OBJS += \
./queries/Match.o \
./queries/MatchListItem.o \
./queries/MatchesList.o \
./queries/Stalker.o \
./queries/StalkerList.o \
./queries/Stalkers.o \
./queries/Trend.o \
./queries/TrendList.o \
./queries/TrendListItem.o \
./queries/query1.o \
./queries/query2.o \
./queries/query3.o \
./queries/query4.o 

CPP_DEPS += \
./queries/Match.d \
./queries/MatchListItem.d \
./queries/MatchesList.d \
./queries/Stalker.d \
./queries/StalkerList.d \
./queries/Stalkers.d \
./queries/Trend.d \
./queries/TrendList.d \
./queries/TrendListItem.d \
./queries/query1.d \
./queries/query2.d \
./queries/query3.d \
./queries/query4.d 


# Each subdirectory must supply rules for building sources it contributes
queries/%.o: ../queries/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


