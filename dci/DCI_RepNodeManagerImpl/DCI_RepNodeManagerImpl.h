//
// generated by Qedo
//

#ifndef _DCI_RepNodeManagerImpl_H_
#define _DCI_RepNodeManagerImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "DCI_RepNodeManagerImpl_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
#include "MDE.h"
#include "Output.h"
#include "RepUtils.h"
// END USER INSERT SECTION file_post


namespace DCI
{
    
    //
    // executor
    //
    class RepNodeManagerSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::DCI::CCM_RepNodeManagerSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_RepNodeManagerSessionImpl
// END USER INSERT SECTION INHERITANCE_RepNodeManagerSessionImpl
    {
    
    private:
    
        ::DCI::CCM_RepNodeManager_ContextImpl_var context_;
        
    public:
    
        RepNodeManagerSessionImpl();
        virtual ~RepNodeManagerSessionImpl();
        
        void set_context(::DCI::CCM_RepNodeManager_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:DCI/NodeManager/node_name:1.0
        //
        void node_name(const char* param)
        	throw(CORBA::SystemException);
        char* node_name()
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/Deployment/ServerActivator/create_component_server:1.0
        //
        virtual Components::Deployment::ComponentServer_ptr create_component_server(const Components::ConfigValues& config)
        	throw(CORBA::SystemException, ::Components::CreateFailure, ::Components::Deployment::InvalidConfiguration);
        
        //
        // IDL:Components/Deployment/ServerActivator/remove_component_server:1.0
        //
        virtual void remove_component_server(Components::Deployment::ComponentServer_ptr server)
        	throw(CORBA::SystemException, ::Components::RemoveFailure);
        
        //
        // IDL:Components/Deployment/ServerActivator/get_component_servers:1.0
        //
        virtual Components::Deployment::ComponentServers* get_component_servers()
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/Deployment/ComponentInstallation/install:1.0
        //
        virtual void install(const char* implUUID, const char* component_loc)
        	throw(CORBA::SystemException, ::Components::Deployment::InvalidLocation, ::Components::Deployment::InstallationFailure);
        
        //
        // IDL:Components/Deployment/ComponentInstallation/replace:1.0
        //
        virtual void replace(const char* implUUID, const char* component_loc)
        	throw(CORBA::SystemException, ::Components::Deployment::InvalidLocation, ::Components::Deployment::InstallationFailure);
        
        //
        // IDL:Components/Deployment/ComponentInstallation/remove:1.0
        //
        virtual void remove(const char* implUUID)
        	throw(CORBA::SystemException, ::Components::Deployment::UnknownImplId, ::Components::RemoveFailure);
        
        //
        // IDL:Components/Deployment/ComponentInstallation/get_implementation:1.0
        //
        virtual char* get_implementation(const char* implUUID)
        	throw(CORBA::SystemException, ::Components::Deployment::UnknownImplId, ::Components::Deployment::InstallationFailure);
        
        //
        // IDL:DCI/ExtComponentInstallation/upload:1.0
        //
        virtual char* upload(const char* implUUID, const DCI::ComponentArchive& archive)
        	throw(CORBA::SystemException, ::Components::Deployment::InstallationFailure);
        
        //
        // IDL:DCI/NodeInformation/get_node_properties:1.0
        //
        virtual DCI::DCIDescriptors* get_node_properties()
        	throw(CORBA::SystemException);
        
        //
        // IDL:DCI/NodeInformation/is_property_defined:1.0
        //
        virtual CORBA::Boolean is_property_defined(const char* property_name)
        	throw(CORBA::SystemException, ::Components::InvalidName);
        
        //
        // IDL:DCI/NodeInformation/get_property_value:1.0
        //
        virtual CORBA::Any* get_property_value(const char* property_name)
        	throw(CORBA::SystemException, ::Components::InvalidName);
    
// BEGIN USER INSERT SECTION RepNodeManagerSessionImpl
// END USER INSERT SECTION RepNodeManagerSessionImpl

    };
    
    
    //
    // executor locator
    //
    class RepNodeManagerImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_RepNodeManagerImpl
// END USER INSERT SECTION INHERITANCE_RepNodeManagerImpl
    {
    
    private:
    
        ::DCI::CCM_RepNodeManager_ContextImpl_var context_;
        
        RepNodeManagerSessionImpl* component_;
        
    public:
    
        RepNodeManagerImpl();
        virtual ~RepNodeManagerImpl();
        
        
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
    
// BEGIN USER INSERT SECTION RepNodeManagerImpl
// END USER INSERT SECTION RepNodeManagerImpl

    };
    
    
    //
    // home executor
    //
    class RepNodeManagerHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::DCI::CCM_RepNodeManagerHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_RepNodeManagerHomeImpl
// END USER INSERT SECTION INHERITANCE_RepNodeManagerHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        RepNodeManagerHomeImpl();
        virtual ~RepNodeManagerHomeImpl();
        
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
    
// BEGIN USER INSERT SECTION RepNodeManagerHomeImpl
// END USER INSERT SECTION RepNodeManagerHomeImpl

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
::Components::HomeExecutorBase_ptr create_RepNodeManagerHomeE(void);
}

#endif
