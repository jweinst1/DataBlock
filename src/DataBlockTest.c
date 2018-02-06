#include <stdio.h>
#include "DataBlock.h"
#include "TestMacro.h"


void DataBlockTest_1(void)
{
        struct DataBlock* tester = DataBlock_new(50);
        DataBlock_EXPAND(tester, 5);
        TESTCASE_IS_EQ(tester->cap, 60, 1);

}

void DataBlockTest_2(void)
{
        struct DataBlock* tester = DataBlock_new(50);
        unsigned char newData[] = {3, 4, 5, 6};
        DataBlock_write(tester, newData, 4);
        TESTCASE_IS_EQ(tester->data[1], 4, 2);
}


int main(int argc, char const *argv[]) {
        DataBlockTest_1();
        DataBlockTest_2();
        return 0;
}
