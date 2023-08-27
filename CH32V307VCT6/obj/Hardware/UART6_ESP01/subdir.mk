################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/UART6_ESP01/UART6.c 

OBJS += \
./Hardware/UART6_ESP01/UART6.o 

C_DEPS += \
./Hardware/UART6_ESP01/UART6.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/UART6_ESP01/%.o: ../Hardware/UART6_ESP01/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\Emd_2023728\CH32V307VCT6\Hardware\UART6_ESP01" -I"E:\Emd_2023728\CH32V307VCT6\Hardware\IWDG" -I"E:\Emd_2023728\CH32V307VCT6\Hardware\USART2_TWAsr" -I"E:\Emd_2023728\CH32V307VCT6\Hardware\USART3_DMA" -I"E:\Emd_2023728\CH32V307VCT6\Debug" -I"E:\Emd_2023728\CH32V307VCT6\Hardware\esp8266" -I"E:\Emd_2023728\CH32V307VCT6\Hardware\JQ8900" -I"E:\Emd_2023728\CH32V307VCT6\Hardware\MqttKit" -I"E:\Emd_2023728\CH32V307VCT6\Hardware\onenet" -I"E:\Emd_2023728\CH32V307VCT6\Hardware\WS2812" -I"E:\Emd_2023728\CH32V307VCT6\Core" -I"E:\Emd_2023728\CH32V307VCT6\User" -I"E:\Emd_2023728\CH32V307VCT6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

