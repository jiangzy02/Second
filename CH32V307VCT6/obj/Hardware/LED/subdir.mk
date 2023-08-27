################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/LED/LED.c 

OBJS += \
./Hardware/LED/LED.o 

C_DEPS += \
./Hardware/LED/LED.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/LED/%.o: ../Hardware/LED/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Debug" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Hardware\esp8266" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Hardware\JQ8900" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Hardware\LED" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Hardware\MqttKit" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Hardware\onenet" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Hardware\UART6" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Hardware\USART3" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Hardware\WS2812" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Core" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\User" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

