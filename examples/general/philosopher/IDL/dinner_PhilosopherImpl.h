//
// generated by Qedo
//

#ifndef _dinner_PhilosopherImpl_H_
#define _dinner_PhilosopherImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <OB/CORBA.h>
#include "dinner_BUSINESS.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include "RefCountLocalObject.h"
#include "ExecutorValuetypes.h"

using namespace std;

namespace dinner {

class JTCThreadWithTimer : public virtual JTCThread, public virtual JTCMonitor
{
protected:
	void timer_sleep (long millis);

public:
	JTCThreadWithTimer();
	~JTCThreadWithTimer();
	void wake_up ();
};

}
// END USER INSERT SECTION file_post


namespace dinner
{
    
    //
    // executor
    //
    class PhilosopherSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::dinner::CCM_PhilosopherSessionImpl
// BEGIN USER INSERT SECTION INHERITANCE_PhilosopherSessionImpl
		, public RefCountLocalObject
		, JTCThreadWithTimer
// END USER INSERT SECTION INHERITANCE_PhilosopherSessionImpl
    {
    
    private:
    
        ::dinner::CCM_Philosopher_Context_var context_;
        
    public:
    
        PhilosopherSessionImpl();
        ~PhilosopherSessionImpl();
        
        void set_context(::dinner::CCM_Philosopher_Context_ptr context);
        void configuration_complete();
        void stop();
        void remove();
        
        //
        // IDL:dinner/Philosopher/thinking_seconds:1.0
        //
        void thinking_seconds(CORBA::ULong param)
        	throw(CORBA::SystemException);
        CORBA::ULong thinking_seconds()
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/Philosopher/eating_seconds:1.0
        //
        void eating_seconds(CORBA::ULong param)
        	throw(CORBA::SystemException);
        CORBA::ULong eating_seconds()
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/Philosopher/sleeping_seconds:1.0
        //
        void sleeping_seconds(CORBA::ULong param)
        	throw(CORBA::SystemException);
        CORBA::ULong sleeping_seconds()
        	throw(CORBA::SystemException);
        
        //
        // IDL:dinner/Named/name:1.0
        //
        void name(const char* param)
        	throw(CORBA::SystemException);
        char* name()
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION PhilosopherSessionImpl
	private:
		JTCThreadHandle my_thread_handle_;
		string id_;
		long tsec_, esec_, ssec_;
		bool stopped_;

	public:
		// This is the run function of the thread
		void run();
// END USER INSERT SECTION PhilosopherSessionImpl

    };
    
    
    //
    // executor locator
    //
    class PhilosopherImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
// BEGIN USER INSERT SECTION INHERITANCE_PhilosopherImpl
		, public RefCountLocalObject
// END USER INSERT SECTION INHERITANCE_PhilosopherImpl
    {
    
    private:
    
        ::dinner::CCM_Philosopher_Context_var context_;
        
        PhilosopherSessionImpl* component_;
        
    public:
    
        PhilosopherImpl();
        ~PhilosopherImpl();
        
        //
        // IDL:Components/ExecutorLocator/obtain_executor:1.0
        //
        virtual CORBA::Object_ptr obtain_executor(const char* name)
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/ExecutorLocator/release_executor:1.0
        //
        virtual void release_executor(CORBA::Object_ptr exc)
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/ExecutorLocator/configuration_complete:1.0
        //
        virtual void configuration_complete()
        	throw(CORBA::SystemException, ::Components::InvalidConfiguration);
        
        //
        // IDL:Components/SessionComponent/set_session_context:1.0
        //
        virtual void set_session_context(Components::SessionContext_ptr ctx)
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_activate:1.0
        //
        virtual void ccm_activate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_passivate:1.0
        //
        virtual void ccm_passivate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/SessionComponent/ccm_remove:1.0
        //
        virtual void ccm_remove()
        	throw(CORBA::SystemException, ::Components::CCMException);
    
// BEGIN USER INSERT SECTION PhilosopherImpl
// END USER INSERT SECTION PhilosopherImpl

    };
    
    
    //
    // home executor
    //
    class PhilosopherHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::dinner::CCM_PhilosopherHome
// BEGIN USER INSERT SECTION INHERITANCE_PhilosopherHomeImpl
		, public RefCountLocalObject
// END USER INSERT SECTION INHERITANCE_PhilosopherHomeImpl
    {
    
    private:
    
        Components::CCMContext_ptr context_;
        
    public:
        PhilosopherHomeImpl();
        ~PhilosopherHomeImpl();
        
        //
        // IDL:Components/HomeExecutorBase/set_context:1.0
        //
        virtual void set_context (Components::CCMContext_ptr ctx);
        
        //
        // IDL:.../create:1.0
        //
        virtual ::Components::EnterpriseComponent_ptr create();
    
// BEGIN USER INSERT SECTION PhilosopherHomeImpl
// END USER INSERT SECTION PhilosopherHomeImpl

    };
    
};

//
// entry point
//
extern "C" {
#ifdef _WIN32
__declspec(dllexport)
#else
#endif
::Components::HomeExecutorBase_ptr create_PhilosopherHomeE(void);
}

#endif