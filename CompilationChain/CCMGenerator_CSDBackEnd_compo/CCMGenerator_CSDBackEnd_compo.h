//
// generated by Qedo
//

#ifndef _CCMGenerator_CSDBackEnd_compo_H_
#define _CCMGenerator_CSDBackEnd_compo_H_


// BEGIN USER INSERT SECTION file_pre
#include "RepositoryConnector.h"
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "CCMGenerator_CSDBackEnd_compo_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post

// END USER INSERT SECTION file_post


namespace CCMGenerator
{
    
    //
    // executor
    //
    class CSDBackendSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::CCMGenerator::CCM_CSDBackendSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CSDBackendSessionImpl
// END USER INSERT SECTION INHERITANCE_CSDBackendSessionImpl
    {
    
    private:
    
        ::CCMGenerator::CCM_CSDBackend_ContextImpl_var context_;
        
    public:
    
        CSDBackendSessionImpl();
        virtual ~CSDBackendSessionImpl();
        
        void set_context(::CCMGenerator::CCM_CSDBackend_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:CCMGenerator/CSDBackend/rep_ref:1.0
        //
        void rep_ref(CORBA::Object_ptr param)
        	throw(CORBA::SystemException);
        CORBA::Object_ptr rep_ref()
        	throw(CORBA::SystemException);
        
        //
        // IDL:CCMGenerator/CSDBackEndControl/generate:1.0
        //
        virtual void generate(const char* name, const char* vers, const char* a_name, const char* a_comp, const char* a_web, const char* title, const char* description, const char* lisence, const char* idl_id, const char* idl_file, const char* output, const CCMGenerator::DeploymentUnitIDList& units)
        	throw(CORBA::SystemException, ::CCMGenerator::OutputError);
    
// BEGIN USER INSERT SECTION CSDBackendSessionImpl
		private:
	CORBA::Object_var _root;
	CCMGenerator::CCMRepositoryConnector _repconnector;
	MDE::BaseIDL::BaseIDLPackage_var _base_idl_pkg_ref; 
	MDE::CIF::CIFPackage_var _cif_ref;
	MDE::ComponentIDL::ComponentIDLPackage_var _component_idl_ref;
	MDE::Deployment::DeploymentPackage_var _deployment_ref;
	
	void connect_the_whole_repository ();

	//generate methods
	void _generate_deployment_unit_element ( MDE::Deployment::DeploymentUnit_ptr, ostream& out, unsigned long & indent_level );
	void _generate_os_element ( MDE::Deployment::DeploymentUnit_ptr , std::string, ostream& out, unsigned long & indent_level );
	void _generate_processor_element ( MDE::Deployment::DeploymentUnit_ptr , std::string , ostream& out, unsigned long & indent_level );
	void _generate_compiler_element( MDE::Deployment::DeploymentUnit_ptr , std::string , ostream& out, unsigned long & indent_level );
	void _generate_prog_language_element ( MDE::Deployment::DeploymentUnit_ptr , std::string, ostream& out, unsigned long & indent_level );
	void _generate_descriptor_element ( MDE::Deployment::DeploymentUnit_ptr , std::string , ostream& out, unsigned long & indent_level );
	void _generate_code_element ( MDE::Deployment::ContainedFile_ptr , ostream& out, unsigned long & indent_level );

	// help methods	
	public:
		void begin ( ostream& out );
		std::string get_req_value ( MDE::Deployment::DeploymentUnit_ptr , std::string );
		std::string get_req_version ( MDE::Deployment::DeploymentUnit_ptr , std::string );

// END USER INSERT SECTION CSDBackendSessionImpl

    };
    
    
    //
    // executor locator
    //
    class CSDBackEnd_compo
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CSDBackEnd_compo
// END USER INSERT SECTION INHERITANCE_CSDBackEnd_compo
    {
    
    private:
    
        ::CCMGenerator::CCM_CSDBackend_ContextImpl_var context_;
        
        CSDBackendSessionImpl* component_;
        
    public:
    
        CSDBackEnd_compo();
        virtual ~CSDBackEnd_compo();
        
        
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
    
// BEGIN USER INSERT SECTION CSDBackEnd_compo
// END USER INSERT SECTION CSDBackEnd_compo

    };
    
    
    //
    // home executor
    //
    class CSDBackendHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::CCMGenerator::CCM_CSDBackendHome
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_CSDBackendHomeImpl
// END USER INSERT SECTION INHERITANCE_CSDBackendHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        CSDBackendHomeImpl();
        virtual ~CSDBackendHomeImpl();
        
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
    
// BEGIN USER INSERT SECTION CSDBackendHomeImpl
// END USER INSERT SECTION CSDBackendHomeImpl

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
::Components::HomeExecutorBase_ptr create_CSDBackendHomeE(void);
}

#endif
