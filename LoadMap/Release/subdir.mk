################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AStarAlgorithm.cpp \
../ConfigurationManager.cpp \
../Graph.cpp \
../Main.cpp \
../Map.cpp \
../Node.cpp \
../Robot.cpp \
../lodepng.cpp 

OBJS += \
./AStarAlgorithm.o \
./ConfigurationManager.o \
./Graph.o \
./Main.o \
./Map.o \
./Node.o \
./Robot.o \
./lodepng.o 

CPP_DEPS += \
./AStarAlgorithm.d \
./ConfigurationManager.d \
./Graph.d \
./Main.d \
./Map.d \
./Node.d \
./Robot.d \
./lodepng.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


