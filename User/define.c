#include "define.h"

void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
