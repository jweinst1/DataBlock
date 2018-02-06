#include <stdio.h>
#include "DataBlock.h"
#include "TestMacro.h"


void DataBlockTest_1(void)
{
        struct DataBlock* tester = DataBlock_new(50);
        DataBlock_EXPAND(tester, 5);
        TESTCASE_IS_EQ(tester->cap, 60, 1);

}


int main(int argc, char const *argv[]) {
        DataBlockTest_1();
        return 0;
}
