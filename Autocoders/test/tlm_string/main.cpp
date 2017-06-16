#include <Autocoders/test/tlm_string/TestTelemImpl.hpp>
#include <Autocoders/test/tlm_string/TestTelemRecvImpl.hpp>
#include <Autocoders/test/time_tester/TestTimeImpl.hpp>
#include <Fw/Obj/SimpleObjRegistry.hpp>

int main(int argc, char* argv[]) {

#if FW_PORT_TRACING
    Fw::PortBase::setTrace(true);
#endif

#if FW_OBJECT_REGISTRATION == 1
    Fw::SimpleObjRegistry objReg;
#endif

	TestTlmImpl testImpl("TestTlmImpl");
	testImpl.init();
	TestTelemRecvImpl tlmRecv("TestTlmRecv");
	tlmRecv.init();
	TestTimeImpl timeSource("TimeComp");
	timeSource.init();

    testImpl.set_Tlm_OutputPort(0,tlmRecv.get_tlmRecvPort_InputPort(0));
    testImpl.set_Time_OutputPort(0,timeSource.get_timeGetPort_InputPort(0));

    timeSource.setTime(Fw::Time(TB_NONE,2,3));
#if FW_OBJECT_REGISTRATION == 1
	objReg.dump();
#endif
	Fw::TlmString str(argv[1]);
	testImpl.genTlm(str);


}
