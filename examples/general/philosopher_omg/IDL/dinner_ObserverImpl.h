//
// generated by Qedo
//

#ifndef _dinner_ObserverImpl_H_
#define _dinner_ObserverImpl_H_


// BEGIN USER INSERT SECTION file_pre
#ifdef WIN32
#include "PhilosophersExecutors.h"
#include "ObserverGUI.h"
#else
#include "philo_gui.h"
#endif
// END USER INSERT SECTION file_pre


#include <OB/CORBA.h>
#include "DiningPhilosophers_BUSINESS.h"
#include "RefCountLocalObject.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include <string>
#include <vector>
#include <sstream>
#include "Output.h"
#include "Cookie.h"


using namespace std;
// END USER INSERT SECTION file_post


namespace dinner
{
    
    //
    // executor
    //
    class ObserverSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::dinner::CCM_ObserverSessionImpl
// BEGIN USER INSERT SECTION INHERITANCE_ObserverSessionImpl
#ifdef OBSERVER_WITH_GUI
, public JTCThread
, public JTCMonitor
#endif
// END USER INSERT SECTION INHERITANCE_ObserverSessionImpl
    {
    
    private:
    
        ::DiningPhilosophers::CCM_Observer_Context_var context_;
        
    public:
    
        ObserverSessionImpl();
        ~ObserverSessionImpl();
        
        void set_context(::DiningPhilosophers::CCM_Observer_Context_ptr context);
        void configuration_complete();
        void stop();
        void remove();
    
// BEGIN USER INSERT SECTION ObserverSessionImpl
private:
       bool running_;
       JTCInitialize *initialize_;
       vector < string > philoNames_;

#ifdef OBSERVER_WITH_GUI
#ifdef WIN32
       ObserverGUI* gui_;
#endif

public:
       void run();
       void finish();
#endif
// END USER INSERT SECTION ObserverSessionImpl

    };
    
    
    //
    // executor locator
    //
    class ObserverImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
// BEGIN USER INSERT SECTION INHERITANCE_ObserverImpl
// END USER INSERT SECTION INHERITANCE_ObserverImpl
    {
    
    private:
    
        ::DiningPhilosophers::CCM_Observer_Context_var context_;
        
        ObserverSessionImpl* component_;
        
    public:
    
        ObserverImpl();
        ~ObserverImpl();
        
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
    
// BEGIN USER INSERT SECTION ObserverImpl
private:
       Components::EnterpriseComponent_var component_executor_;
       
       HU_CCM_Container::Monitor monitor_;
// END USER INSERT SECTION ObserverImpl

    };
    
    
    //
    // home executor
    //
    class ObserverHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::DiningPhilosophers::CCM_ObserverHome
// BEGIN USER INSERT SECTION INHERITANCE_ObserverHomeImpl
// END USER INSERT SECTION INHERITANCE_ObserverHomeImpl
    {
    
    private:
    
        Components::CCMContext_ptr context_;
        
    public:
        ObserverHomeImpl();
        ~ObserverHomeImpl();
        
        //
        // IDL:Components/HomeExecutorBase/set_context:1.0
        //
        virtual void set_context (Components::CCMContext_ptr ctx);
        
        //
        // IDL:.../create:1.0
        //
        virtual ::Components::ExecutorLocator_ptr create();
    
// BEGIN USER INSERT SECTION ObserverHomeImpl
// END USER INSERT SECTION ObserverHomeImpl

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
::Components::HomeExecutorBase_ptr create_ObserverHomeE(void);
}

#endif