################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../CH32V307VCT6_test/Startup/startup_ch32v30x_D8.S \
../CH32V307VCT6_test/Startup/startup_ch32v30x_D8C.S 

OBJS += \
./CH32V307VCT6_test/Startup/startup_ch32v30x_D8.o \
./CH32V307VCT6_test/Startup/startup_ch32v30x_D8C.o 

S_UPPER_DEPS += \
./CH32V307VCT6_test/Startup/startup_ch32v30x_D8.d \
./CH32V307VCT6_test/Startup/startup_ch32v30x_D8C.d 


# Each subdirectory must supply rules for building sources it contributes
CH32V307VCT6_test/Startup/%.o: ../CH32V307VCT6_test/Startup/%.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\Startup" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

