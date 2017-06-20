################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MultipleTCPSocketListenerTest.cpp \
../src/TCPSocketTest.cpp \
../src/UdpSocketTest.cpp \
../src/main.cpp 

OBJS += \
./src/MultipleTCPSocketListenerTest.o \
./src/TCPSocketTest.o \
./src/UdpSocketTest.o \
./src/main.o 

CPP_DEPS += \
./src/MultipleTCPSocketListenerTest.d \
./src/TCPSocketTest.d \
./src/UdpSocketTest.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/project/lab7/finish/lab7 /SocketUtils2/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


