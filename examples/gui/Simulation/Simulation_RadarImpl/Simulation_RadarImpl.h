//
// generated by Qedo
//

#ifndef _Simulation_RadarImpl_H_
#define _Simulation_RadarImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "Simulation_RadarImpl_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

namespace Simulation {
class RadarSessionImpl;
};

class RadarDisplay : public Fl_Window  {
	void draw();
	Simulation::RadarSessionImpl* impl_;

public:
	
	RadarDisplay(int W,int H, Simulation::RadarSessionImpl* impl
,const char *l=0) : Fl_Window(W,H,l), impl_(impl) {}
};

// END USER INSERT SECTION file_post


namespace Simulation
{
    
    //
    // executor
    //
    class RadarSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::Simulation::CCM_RadarSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_RadarSessionImpl
// END USER INSERT SECTION INHERITANCE_RadarSessionImpl
    {
    
    private:
    
        ::Simulation::CCM_Radar_ContextImpl_var context_;
        
    public:
    
        RadarSessionImpl();
        virtual ~RadarSessionImpl();
        
        void set_context(::Simulation::CCM_Radar_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:Simulation/Radar/radar_identifier:1.0
        //
        void radar_identifier(const char* param)
        	throw(CORBA::SystemException);
        char* radar_identifier()
        	throw(CORBA::SystemException);
        
        //
        // IDL:Simulation/Radar/longitude:1.0
        //
        void longitude(CORBA::Double param)
        	throw(CORBA::SystemException);
        CORBA::Double longitude()
        	throw(CORBA::SystemException);
        
        //
        // IDL:Simulation/Radar/latitude:1.0
        //
        void latitude(CORBA::Double param)
        	throw(CORBA::SystemException);
        CORBA::Double latitude()
        	throw(CORBA::SystemException);
    
// BEGIN USER INSERT SECTION RadarSessionImpl
	private:
		bool data_stopped;
		bool gui_stopped;
        Components::Thread_var data_thread;
        Components::Thread_var gui_thread;
		Fl_Window *window;
	public:
		std::string id_;
		CORBA::Double longitude_;
		CORBA::Double latitude_;
		bool current_data_set_;
		Components::Mutex_ptr current_data_mutex_;
		Simulation::RadarData *current_data;
		static void* run(void*);
		void stop();
		static void* start_gui(void*);
		void stop_gui();
		void scan();


// END USER INSERT SECTION RadarSessionImpl

    };
    
    
    //
    // executor locator
    //
    class RadarImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_RadarImpl
// END USER INSERT SECTION INHERITANCE_RadarImpl
    {
    
    private:
    
        ::Simulation::CCM_Radar_ContextImpl_var context_;
        
        RadarSessionImpl* component_;
        
    public:
    
        RadarImpl();
        virtual ~RadarImpl();
        
        
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
    
// BEGIN USER INSERT SECTION RadarImpl
// END USER INSERT SECTION RadarImpl

    };
    
    
    //
    // home executor
    //
    class RadarHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::Simulation::CCM_RadarHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_RadarHomeImpl
// END USER INSERT SECTION INHERITANCE_RadarHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        RadarHomeImpl();
        virtual ~RadarHomeImpl();
        
        //
        // IDL:Components/HomeExecutorBase/set_context:1.0
        //
        virtual void set_context (Components::HomeContext_ptr ctx)
            throw (CORBA::SystemException, Components::CCMException);
        
        //
        // IDL:.../create:1.0
        //
        virtual ::Components::EnterpriseComponent_ptr create()
            throw (CORBA::SystemException, Components::CreateFailure);
    
// BEGIN USER INSERT SECTION RadarHomeImpl
// END USER INSERT SECTION RadarHomeImpl

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
::Components::HomeExecutorBase_ptr create_RadarHomeE(void);
}

#endif
