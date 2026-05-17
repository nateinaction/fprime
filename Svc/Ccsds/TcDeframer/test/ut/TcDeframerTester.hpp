// ======================================================================
// \title  TcDeframerTester.hpp
// \author thomas-bc
// \brief  hpp file for TcDeframer component test harness implementation class
// ======================================================================

#ifndef Svc_Ccsds_TcDeframerTester_HPP
#define Svc_Ccsds_TcDeframerTester_HPP

#include "Svc/Ccsds/TcDeframer/TcDeframer.hpp"
#include "Svc/Ccsds/TcDeframer/TcDeframerGTestBase.hpp"

namespace Svc {

namespace Ccsds {

class TcDeframerTester final : public TcDeframerGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object TcDeframerTester
    TcDeframerTester();

    //! Destroy object TcDeframerTester
    ~TcDeframerTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    void testDataReturn();
    void testNominalDeframing();
    void testInvalidScId();
    void testInvalidVcId();
    void testInvalidLengthToken();
    void testInvalidCrc();

    // Security path tests (processSecurityOut connected by tester via UT_AUTO_HELPERS).
    void testSecurityAcceptForwardsReturnSlice();
    void testSecurityInvalidSpiRejects();
    void testSecurityMacFailureRejects();
    void testSecurityAntiReplayRejects();
    void testSecurityPaddingErrorRejects();
    void testSecurityOutOfBoundsReturnSliceTriggersInternalError();
    void testSecurityGvcidPopulated();

  private:
    // ----------------------------------------------------------------------
    // Scripted ProcessSecurity provider (overrides auto-generated from_handler)
    // ----------------------------------------------------------------------

    //! Provider mode used by from_processSecurityOut_handler.
    //!   kPassthrough: NO_FAILURE; return slice = [TCHeader size, end of payload].
    //!                 Makes the security path produce the same dataOut buffer
    //!                 as the legacy strip-header-and-FECF path, so the existing
    //!                 framer tests continue to pass with the port now auto-wired.
    //!   kScripted:    Return m_scriptedSecurityResult verbatim.
    enum class SecurityMode { kPassthrough, kScripted };

    Ccsds::ProcessSecurityResult from_processSecurityOut_handler(FwIndexType portNum,
                                                                 const Ccsds::GVCID& gvcid,
                                                                 Fw::Buffer& payload) override;

    SecurityMode m_securityMode = SecurityMode::kPassthrough;
    //! Result returned by the next provider call when in kScripted mode
    Ccsds::ProcessSecurityResult m_scriptedSecurityResult;
    //! Captured GVCID from the most recent call
    Ccsds::GVCID m_capturedGvcid;
    //! Captured payload size from the most recent call
    FwSizeType m_capturedPayloadSize = 0;
    //! Number of provider calls made
    U32 m_providerCalls = 0;

    //! Switch to kScripted mode and set the next result to NO_FAILURE with the given slice.
    void scriptSecurityAccept(FwSizeType returnOffset, FwSizeType returnSize);
    //! Switch to kScripted mode and set the next result to a FAILURE with the given code.
    void scriptSecurityFailure(Ccsds::VerificationStatusCode::T code);

    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

    //! Sets the component state to specific values, helpful for testing
    void setComponentState(U16 scid = 0, U8 vcid = 0, U8 seqNumber = 0, bool acceptAllVcid = true);

    Fw::Buffer assembleFrameBuffer(U8* data, U8 dataLength, U16 scid = 0, U8 vcid = 0, U8 seqNumber = 0);

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    TcDeframer component;

    U8 m_frameData[300];  // data buffer used to produce test frames
};

}  // namespace Ccsds

}  // namespace Svc

#endif
