//
// generated by Qedo
//

#ifndef _container_service_MonImpl_H_
#define _container_service_MonImpl_H_


// BEGIN USER INSERT SECTION file_pre
namespace container_service {
class MonExec;
};
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "container_service_MonImpl_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include "ServerContainerInterceptor.h"
#include "ClientContainerInterceptor.h"
// END USER INSERT SECTION file_post


namespace container_service
{
    
    //
    // executor
    //
    class MonExec
        : public virtual CORBA::LocalObject
        , public virtual ::container_service::CCM_MonExec
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_MonExec
// END USER INSERT SECTION INHERITANCE_MonExec
    {
    
    private:
    
        ::container_service::CCM_monitor_ContextImpl_var context_;
        
    public:
    
        MonExec();
        virtual ~MonExec();
        
        void set_context(::container_service::CCM_monitor_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
    
// BEGIN USER INSERT SECTION MonExec
	public:
	Qedo::ServerContainerInterceptor* server_interceptor_;
	Qedo::ClientContainerInterceptor* client_interceptor_;
	unsigned long counter;
	Qedo::QedoMutex counter_mutex;
	IOP::Codec_var m_cdrCodec;
	
	unsigned long 
	get_new_event_number();

	IOP::Codec_ptr
	get_cdr_codec_ptr();

// END USER INSERT SECTION MonExec

    };
    
    
    //
    // executor locator
    //
    class MonImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::ExtensionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_MonImpl
// END USER INSERT SECTION INHERITANCE_MonImpl
    {
    
    private:
    
        ::container_service::CCM_monitor_ContextImpl_var context_;
        
        MonExec* component_;
        
    public:
    
        MonImpl();
        virtual ~MonImpl();
        
        
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
        // IDL:Components/ExtensionComponent/set_extension_context:1.0
        //
        virtual void set_extension_context(Components::ExtensionContext_ptr ctx)
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_activate:1.0
        //
        virtual void ccm_activate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_passivate:1.0
        //
        virtual void ccm_passivate()
        	throw(CORBA::SystemException, ::Components::CCMException);
        
        //
        // IDL:Components/ExtensionComponent/ccm_remove:1.0
        //
        virtual void ccm_remove()
        	throw(CORBA::SystemException, ::Components::CCMException);
    
// BEGIN USER INSERT SECTION MonImpl
// END USER INSERT SECTION MonImpl

    };
    
    
    //
    // home executor
    //
    class HomeMonExec
        : public virtual CORBA::LocalObject
        , public virtual ::container_service::CCM_monitor_home
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_HomeMonExec
// END USER INSERT SECTION INHERITANCE_HomeMonExec
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        HomeMonExec();
        virtual ~HomeMonExec();
        
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
    
// BEGIN USER INSERT SECTION HomeMonExec
// END USER INSERT SECTION HomeMonExec

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
::Components::HomeExecutorBase_ptr create_monitor_homeE(void);
}

#endif
