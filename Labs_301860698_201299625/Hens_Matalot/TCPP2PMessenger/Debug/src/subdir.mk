################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/P2PClient.cpp \
../src/P2PServer.cpp \
../src/TCPP2PMessenger.cpp \
../src/UDPMessenger.cpp \
../src/main.cpp 

OBJS += \
./src/P2PClient.o \
./src/P2PServer.o \
./src/TCPP2PMessenger.o \
./src/UDPMessenger.o \
./src/main.o 

CPP_DEPS += \
./src/P2PClient.d \
./src/P2PServer.d \
./src/TCPP2PMessenger.d \
./src/UDPMessenger.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/project/lab7/finish/lab7 /SocketUtils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


