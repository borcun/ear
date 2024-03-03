#include "gtest/gtest.h"
#include "ios.h"

TEST(Service, CheckInitialValues) {
    FACE::Service service1("Test Service");
    FACE::Service service2("");
		    
    EXPECT_EQ(service1.getName(), "Test Service");
    EXPECT_EQ(service1.getId(), 0);

    EXPECT_EQ(service2.getName(), "");
    EXPECT_EQ(service2.getId(), 0);
}

TEST(IOService, CheckInitialValues) {
    FACE::IOSS::IOService ios("IO Service");
		    
    EXPECT_EQ(ios.getName(), "IO Service");
    EXPECT_EQ(ios.getId(), 1000);
    EXPECT_EQ(ios.getModel(), "");
    EXPECT_EQ(ios.getVersion(), "");
    EXPECT_EQ(ios.open(), -1);
    EXPECT_EQ(ios.close(), -1);
    EXPECT_EQ(ios.read(nullptr, 0), -1);
    EXPECT_EQ(ios.write(nullptr, 0), -1);
    EXPECT_EQ(ios.ioctl(nullptr, 0), -1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
