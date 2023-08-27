################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HardWare/USART3/USART3.c 

OBJS += \
./HardWare/USART3/USART3.o 

C_DEPS += \
./HardWare/USART3/USART3.d 


# Each subdirectory must supply rules for building sources it contributes
HardWare/USART3/%.o: ../HardWare/USART3/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\HardWare\MPU6050IIC" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\HardWare\USART3" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\HardWare\TIM2" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\HardWare\USART2" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\Debug" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\HardWare\MPU6050" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\Core" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\User" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\Peripheral\inc" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\HardWare\inv_mpu" -I"C:\MRS_DATA\workspace\CH32V307VCT6_MPU6050\HardWare\inv_mpu_dmp_motion_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

