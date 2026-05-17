module Svc {
module Ccsds {
    @ Deframer for the TC Space Data Link Protocol (CCSDS Standard)
    passive component TcDeframer {

        import Deframer

        @ Port to notify of a deframing error
        output port errorNotify: Ccsds.ErrorNotify

        @ Synchronous ProcessSecurity call (CCSDS 355.0-B-2 §3.3, TC). When
        @ connected, the provider authenticates the frame and returns the
        @ cleared Data Field slice. When unconnected, the deframer falls back
        @ to its legacy behavior: strip Primary Header + FECF and forward.
        output port processSecurityOut: Ccsds.ProcessSecurity

        @ Notification of a security verification failure. Optional; only
        @ fired if connected.
        output port securityErrorNotify: Ccsds.SecurityErrorNotify

        @ Deframing received an invalid SCID
        event InvalidSpacecraftId(transmitted: U16, configured: U16) \
            severity warning low \ 
            format "Invalid Spacecraft ID Received. Received: {} | Deframer configured with: {}"

        @ Deframing received an invalid frame length
        event InvalidFrameLength(transmitted: U16, actual: FwSizeType) \
            severity warning high \
            format "Not enough data received. Header length specified: {} | Received data length: {}"

        @ Deframing received an invalid VCID
        event InvalidVcId(transmitted: U16, configured: U16) \
            severity activity low \
            format "Invalid Virtual Channel ID Received. Header token specified: {} | Deframer configured with: {}"

        @ Deframing received an invalid checksum
        event InvalidCrc(transmitted: U16, computed: U16) \
            severity warning high \
            format "Invalid checksum received. Trailer specified: {} | Computed on board: {}"

        # @ Security verification recieved an invalid SPI
        # event SecurityInvalidSpi(transmitted: U16) \
        #     severity warning high \
        #     format "Invalid Security Parameter Index received. SPI specified: {}"

        # @ Security verification received an mismatched MAC
        # event SecurityMacFailure(transmitted: Mac) \
        #     severity warning high \
        #     format "Invalid Message Authentication Code received. MAC specified: {}"

        # @ Security verification received a replayed sequence number
        # event SecurityAntiReplayFailure(transmitted: U32, expected: U32) \
        #     severity warning high \
        #     format "Anti-replay sequence number reuse detected. Received: {} | Expected: {}"

        # @ Security verification received a padding error
        # event SecurityPaddingError() \
        #     severity warning high \
        #     format "Invalid padding received."

        @ Security verification encountered an internal error
        event SecurityError(statusCode: U8) \
            severity warning high \
            format "Error during security verification. Status code: {}"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}
}
