module Svc {
module Ccsds {

    @ Port for requesting a sequence count for a given APID
    port ApidSequenceCount (apid: ComCfg.Apid, sequenceCount: U16) -> U16

    @ Port for notifying of an error in framing/deframing
    port ErrorNotify (errorCode: Ccsds.FrameError)

    @ Synchronous ProcessSecurity call (CCSDS 355.0-B-2 §3.3, TC).
    @ Implementations own SA semantics: SPI lookup, anti-replay window, MAC
    @ verification, and any decryption. The payload buffer is passed by ref
    @ so that providers may decrypt in-place if the SA includes encryption.
    @ When invoked from Svc.Ccsds.TcDeframer, payload covers the full Transfer
    @ Frame minus the 2-byte FECF (Primary Header through Security Trailer),
    @ matching CCSDS 355.0-B-2 §3.3.2.3 exactly. The provider returns the
    @ offset/size of the cleared Data Field slice within that buffer.
    port ProcessSecurity (globalVcId: U16, globalMapId: U16, ref payload: Fw.Buffer) -> Ccsds.ProcessSecurityResult

    @ Port for notifying of a security verification failure
    port SecurityErrorNotify (statusCode: U8)

}
}
