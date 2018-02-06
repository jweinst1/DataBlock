#include <stdio.h>
#include "DataBlock.h"
#include "TestMacro.h"


void DataBlockTest_1(void)
{
        struct DataBlock* tester = DataBlock_new(50);
        DataBlock_EXPAND(tester, 5);
        TESTCASE_IS_EQ(tester->cap, 60, 1);
        free(tester);

}

void DataBlockTest_2(void)
{
        struct DataBlock* tester = DataBlock_new(50);
        unsigned char newData[] = {3, 4, 5, 6};
        DataBlock_write(tester, newData, 4);
        TESTCASE_IS_EQ(tester->data[1], 4, 2);
        free(tester);
}

void DataBlockTest_3(void)
{
        struct DataBlock* tester = DataBlock_new(50);
        long f = 3000;
        DataBlock_put_long(tester, f);
        TESTCASE_IS_EQ(*(long*)(tester->data), 3000, 3);
        free(tester);
}

void DataBlockTest_4(void)
{
        struct DataBlock* tester = DataBlock_new(50);
        unsigned char newData[] = {3, 4, 5, 6, 66};
        struct DataBlock* writ = DataBlock_from_data(newData, 5);
        DataBlock_put_block(tester, writ);
        TESTCASE_IS_EQ(tester->data[4], 66, 4);
        free(tester);
        free(writ);
}


int main(int argc, char const *argv[]) {
        DataBlockTest_1();
        DataBlockTest_2();
        DataBlockTest_3();
        DataBlockTest_4();
        return 0;
}
