################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Dispatcher.cpp \
../src/MThread.cpp \
../src/MultipleTCPSocketsListener.cpp \
../src/TCPMessengerServer.cpp \
../src/TCPSocket.cpp \
../src/main.cpp 

OBJS += \
./src/Dispatcher.o \
./src/MThread.o \
./src/MultipleTCPSocketsListener.o \
./src/TCPMessengerServer.o \
./src/TCPSocket.o \
./src/main.o 

CPP_DEPS += \
./src/Dispatcher.d \
./src/MThread.d \
./src/MultipleTCPSocketsListener.d \
./src/TCPMessengerServer.d \
./src/TCPSocket.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


