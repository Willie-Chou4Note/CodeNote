#include <stdio.h>
#include <stdlib.h>

/* optimize the factory test due to function pointer array */
uint8_t CMD_Bh = 0xff;
void test1(void)
{
    printf("\n\r1\n\r");
    CMD_Bh = 0xff;
}
void test2(void)
{
    printf("\n\r2\n\r");
    CMD_Bh = 0xff;
}
void test3(void)
{
    printf("\n\r3\n\r");
    CMD_Bh = 0xff;
}
void Factory_test(void)
{
    if (CMD_Bh == 0xff)
    {
        if(htim14_I_Cnt >= 0xfff0)
		  {
			  LL_IWDG_ReloadCounter(IWDG);
			  htim14_I_Cnt = 0;
			  Mode_Timer = 0;
		  }
    }
    else
    {
        func_ptr_arr(CMD_Bh);
    }
}

int main()
{
    void (* func_ptr_arr[3])(void *);
    func_ptr_arr[0] = test1;
    func_ptr_arr[1] = test2;
    func_ptr_arr[2] = test3;
    return 0;
}