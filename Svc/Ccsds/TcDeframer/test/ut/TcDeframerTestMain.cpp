// ======================================================================
// \title  TcDeframerTestMain.cpp
// \author thomas-bc
// \brief  cpp file for TcDeframer component test main function
// ======================================================================

#include "TcDeframerTester.hpp"

TEST(TcDeframer, testDataReturn) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testDataReturn();
}

TEST(TcDeframer, testNominalDeframing) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testNominalDeframing();
}

TEST(TcDeframer, testInvalidScId) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testInvalidScId();
}

TEST(TcDeframer, testInvalidVcId) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testInvalidVcId();
}

TEST(TcDeframer, testInvalidLengthToken) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testInvalidLengthToken();
}

TEST(TcDeframer, testInvalidCrc) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testInvalidCrc();
}

TEST(TcDeframer, testSecurityAcceptForwardsReturnSlice) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testSecurityAcceptForwardsReturnSlice();
}

TEST(TcDeframer, testSecurityInvalidSpiRejects) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testSecurityInvalidSpiRejects();
}

TEST(TcDeframer, testSecurityMacFailureRejects) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testSecurityMacFailureRejects();
}

TEST(TcDeframer, testSecurityAntiReplayRejects) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testSecurityAntiReplayRejects();
}

TEST(TcDeframer, testSecurityPaddingErrorRejects) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testSecurityPaddingErrorRejects();
}

TEST(TcDeframer, testSecurityOutOfBoundsReturnSliceTriggersInternalError) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testSecurityOutOfBoundsReturnSliceTriggersInternalError();
}

TEST(TcDeframer, testSecurityGvcidPopulated) {
    Svc::Ccsds::TcDeframerTester tester;
    tester.testSecurityGvcidPopulated();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
