################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/KEY_Pwm/key_pwm.c 

OBJS += \
./hardware/KEY_Pwm/key_pwm.o 

C_DEPS += \
./hardware/KEY_Pwm/key_pwm.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/KEY_Pwm/%.o: ../hardware/KEY_Pwm/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART_show" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\UART5" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\KEY_Pwm" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\RTC" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\DHT11" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\Speed" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Debug" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\ADC_SMOKE" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\USART2" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\USART3" -I"E:\Emd_2023728\CH32V307VCT6_EVT\hardware\HC-SR04" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Core" -I"E:\Emd_2023728\CH32V307VCT6_EVT\User" -I"E:\Emd_2023728\CH32V307VCT6_EVT\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

