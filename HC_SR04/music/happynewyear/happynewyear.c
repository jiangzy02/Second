#include <happynewyear.h>
#include <tone.h>
#include <delay_by_systick.h>
void happynewyear(void)
{
	while(1)
	{
		middle_do();
		delay_ms(250);
		middle_do();
		delay_ms(350);
		middle_do();
		delay_ms(350);
		low_so();
		delay_ms(350);
		
		middle_mi();
		delay_ms(250);
		middle_mi();
		delay_ms(350);
		middle_mi();
		delay_ms(350);
		middle_do();
		delay_ms(350);
		
		middle_do();
		delay_ms(250);
		middle_mi();
		delay_ms(350);
		middle_so();
		delay_ms(350);
		middle_so();
		delay_ms(350);
		
		middle_fa();
		delay_ms(250);
		middle_mi();
		delay_ms(350);
		middle_re();
		delay_ms(500);
		
		middle_re();
		delay_ms(250);
		middle_mi();
		delay_ms(350);
		middle_fa();
		delay_ms(350);
		middle_re();
		delay_ms(350);
		
		middle_mi();
		delay_ms(250);
		middle_re();
		delay_ms(350);
		middle_mi();
		delay_ms(350);
		middle_do();
		delay_ms(350);
		
		middle_do();
		delay_ms(250);
		middle_mi();
		delay_ms(350);
		middle_re();
		delay_ms(350);
		low_so();
		delay_ms(350);
		
		low_si();
		delay_ms(250);
		middle_re();
		delay_ms(250);
		middle_do();
		delay_ms(500);		
	}
}
