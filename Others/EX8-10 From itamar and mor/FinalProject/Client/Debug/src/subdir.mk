################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TCPMessengerClient.cpp \
../src/UDPHandeler.cpp \
../src/UDPSocket.cpp \
../src/main.cpp 

OBJS += \
./src/TCPMessengerClient.o \
./src/UDPHandeler.o \
./src/UDPSocket.o \
./src/main.o 

CPP_DEPS += \
./src/TCPMessengerClient.d \
./src/UDPHandeler.d \
./src/UDPSocket.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

