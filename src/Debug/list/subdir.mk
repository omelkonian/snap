################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../list/BucketItemListItem.cpp \
../list/BucketListItem.cpp \
../list/CommunityListItem.cpp \
../list/EdgeListItem.cpp \
../list/ExtendedQueueItem.cpp \
../list/ForumListItem.cpp \
../list/GraphListItem.cpp \
../list/IntegerListItem.cpp \
../list/List.cpp \
../list/ListItem.cpp \
../list/ListListItem.cpp \
../list/Queue.cpp \
../list/ThreadListItem.cpp 

OBJS += \
./list/BucketItemListItem.o \
./list/BucketListItem.o \
./list/CommunityListItem.o \
./list/EdgeListItem.o \
./list/ExtendedQueueItem.o \
./list/ForumListItem.o \
./list/GraphListItem.o \
./list/IntegerListItem.o \
./list/List.o \
./list/ListItem.o \
./list/ListListItem.o \
./list/Queue.o \
./list/ThreadListItem.o 

CPP_DEPS += \
./list/BucketItemListItem.d \
./list/BucketListItem.d \
./list/CommunityListItem.d \
./list/EdgeListItem.d \
./list/ExtendedQueueItem.d \
./list/ForumListItem.d \
./list/GraphListItem.d \
./list/IntegerListItem.d \
./list/List.d \
./list/ListItem.d \
./list/ListListItem.d \
./list/Queue.d \
./list/ThreadListItem.d 


# Each subdirectory must supply rules for building sources it contributes
list/%.o: ../list/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -Os -g3 -Wall -c -fmessage-length=0 -lpthread -fstack-check -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


