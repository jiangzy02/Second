################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/main.c \
../User/system_ch32v30x.c 

OBJS += \
./User/ch32v30x_it.o \
./User/main.o \
./User/system_ch32v30x.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/main.d \
./User/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\KEY" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\IWDG" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART6_K2102" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART4_MPU" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART5_DMA" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\USART2_K2101" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\USART3_Screen" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART_show" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\RTC" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\DHT11" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\Speed" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Debug" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\ADC_SMOKE" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\HC-SR04" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Core" -I"E:\Emd_2023728\CH32V307VCT6_EVT\User" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

