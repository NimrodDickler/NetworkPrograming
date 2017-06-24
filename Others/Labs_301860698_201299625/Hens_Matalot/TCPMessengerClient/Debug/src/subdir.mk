################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TCPMessengerClient.cpp \
../src/TCPMessengerClientCli.cpp 

OBJS += \
./src/TCPMessengerClient.o \
./src/TCPMessengerClientCli.o 

CPP_DEPS += \
./src/TCPMessengerClient.d \
./src/TCPMessengerClientCli.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/project/lab7/finish/lab7 /SocketUtils2/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


