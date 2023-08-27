################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/ADC_SMOKE/ADC.c 

OBJS += \
./hardware/ADC_SMOKE/ADC.o 

C_DEPS += \
./hardware/ADC_SMOKE/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/ADC_SMOKE/%.o: ../hardware/ADC_SMOKE/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART6_K2102" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\KEY" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART4_MPU" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART5_DMA" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\USART2_K2101" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\USART3_Screen" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART_show" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\RTC" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\DHT11" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\Speed" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Debug" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\ADC_SMOKE" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\HC-SR04" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Core" -I"E:\Emd_2023728\CH32V307VCT6_EVT\User" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

