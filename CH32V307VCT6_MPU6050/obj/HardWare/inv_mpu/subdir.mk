################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HardWare/inv_mpu/inv_mpu.c 

OBJS += \
./HardWare/inv_mpu/inv_mpu.o 

C_DEPS += \
./HardWare/inv_mpu/inv_mpu.d 


# Each subdirectory must supply rules for building sources it contributes
HardWare/inv_mpu/%.o: ../HardWare/inv_mpu/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\UART4" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\IWDG" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\nmswj" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\MPU6050IIC" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\TIM2" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\USART2" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\Debug" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\MPU6050" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\Core" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\User" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\Peripheral\inc" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\inv_mpu" -I"C:\Users\JIANGZHIYU\Desktop\CH32V307VCT6_MPU6050\CH32V307VCT6_MPU6050\HardWare\inv_mpu_dmp_motion_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

