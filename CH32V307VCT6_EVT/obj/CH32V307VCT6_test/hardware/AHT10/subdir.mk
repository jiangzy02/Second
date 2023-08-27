################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CH32V307VCT6_test/hardware/AHT10/AHT10.c 

OBJS += \
./CH32V307VCT6_test/hardware/AHT10/AHT10.o 

C_DEPS += \
./CH32V307VCT6_test/hardware/AHT10/AHT10.d 


# Each subdirectory must supply rules for building sources it contributes
CH32V307VCT6_test/hardware/AHT10/%.o: ../CH32V307VCT6_test/hardware/AHT10/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\UART_show" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\KEY_Pwm" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\WS2812" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\RTC" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\DHT11" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\Speed" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\Debug" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\LED" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\ADC_SMOKE" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\USART2" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\USART3" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\HC-SR04" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\hardware\JQ8900" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\Core" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\User" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_test\CH32V307VCT6_test\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

