#include <stm32f10x_map.h>

#define GPIOA_ODR_A (GPIOA_BASE+0x0C)
#define GPIOA_IDR_A (GPIOA_BASE+0x08)

#define GPIOB_ODR_B (GPIOB_BASE+0x0C)
#define GPIOB_IDR_B (GPIOB_BASE+0x08)

#define GPIOC_ODR_C (GPIOC_BASE+0x0C)
#define GPIOC_IDR_C (GPIOC_BASE+0x08)

#define GPIOD_ODR_D (GPIOD_BASE+0x0C)
#define GPIOD_IDR_D (GPIOD_BASE+0x08)

#define GPIOE_ODR_E (GPIOE_BASE+0x0C)
#define GPIOE_IDR_E (GPIOE_BASE+0x08)

#define GPIOF_ODR_F (GPIOF_BASE+0x0C)
#define GPIOF_IDR_F (GPIOF_BASE+0x08)

#define GPIOG_ODR_G (GPIOG_BASE+0x0C)
#define GPIOG_IDR_G (GPIOG_BASE+0x08)

#define Bitband(Addr,BitNum)  *((volatile unsigned long *)(((Addr&0xF0000000)+0x2000000)+((Addr&0xfffff)<<5)+(BitNum<<2)))

#define PAO(n)	Bitband(GPIOA_ODR_A,n)
#define PAI(n)  Bitband(GPIOA_IDR_A,n)

#define PBO(n)	Bitband(GPIOB_ODR_B,n)
#define PBI(n)  Bitband(GPIOB_IDR_B,n)

#define PCO(n)	Bitband(GPIOC_ODR_C,n)
#define PCI(n)  Bitband(GPIOC_IDR_C,n)

#define PDO(n)	Bitband(GPIOD_ODR_D,n)
#define PDI(n)  Bitband(GPIOD_IDR_D,n)

#define PEO(n)	Bitband(GPIOE_ODR_E,n)
#define PEI(n)  Bitband(GPIOE_IDR_E,n)

#define PFO(n)	Bitband(GPIOF_ODR_F,n)
#define PFI(n)  Bitband(GPIOF_IDR_F,n)

#define PGO(n)	Bitband(GPIOG_ODR_G,n)
#define PGI(n)  Bitband(GPIOG_IDR_G,n)
