################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MThread.cpp \
../src/TCPMessengerClient.cpp \
../src/TCPSocket.cpp \
../src/main.cpp 

OBJS += \
./src/MThread.o \
./src/TCPMessengerClient.o \
./src/TCPSocket.o \
./src/main.o 

CPP_DEPS += \
./src/MThread.d \
./src/TCPMessengerClient.d \
./src/TCPSocket.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


