//
// generated by Qedo
//

#include "CCMGenerator_CSDBackEnd_compo.h"


// BEGIN USER INSERT SECTION file
#include <iostream>
#include "Exceptions.h"
#include "HelpFunctions.h"
// END USER INSERT SECTION file


namespace CCMGenerator {


// BEGIN USER INSERT SECTION CSDBackendSessionImpl
void CSDBackendSessionImpl::connect_the_whole_repository ()
{
	M2C::MOFRepository::RepositoryRoot_var repository_root = 
		M2C::MOFRepository::RepositoryRoot::_narrow ( _root );

	if( CORBA::is_nil ( repository_root ) )
	{
		std::cerr << "I got a nil reference for the repository root reference" << std::endl;
		exit (1);
	}
	::Reflective::RefPackageSet* package_set = repository_root -> get_root_packages();
	_repconnector.set_package_set (package_set); 
	_repconnector.connectRepository();
	_base_idl_pkg_ref =		_repconnector._base_idl_pkg_ref;
	_cif_ref  =				_repconnector._cif_ref;
	_component_idl_ref =	_repconnector._component_idl_ref ;
	_deployment_ref =		_repconnector._deployment_ref;
}

void CSDBackendSessionImpl::begin ( ostream& out )
{
	out << "<?xml version = '1.0' ?>";
	HelpFunctions::new_line ( out, 0 );
	out << "<!DOCTYPE softpkg PUBLIC \"-//OMG//DTD Software Package Descriptor\" \"http://qedo.berlios.de/softpkg.dtd\">";
	HelpFunctions::new_line ( out, 0 );
}
void CSDBackendSessionImpl::_generate_deployment_unit_element ( MDE::Deployment::DeploymentUnit_ptr unit, ostream& out, unsigned long & indent_level )
{
	out << "<implementation id=\"" << unit->uuid() << "\">";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	MDE::Deployment::DeploymentRequirementSet_var reqs_ = unit->req();
	MDE::Deployment::ContainedFileSet_var contained_ = unit->contained_file();

	// generate os element	
	std::string unit_name_ = unit->identifier();
	std::string req_name_ = unit_name_ + "_os";
	this->_generate_os_element( unit, req_name_, out, indent_level );
	// generate processor element
	HelpFunctions::new_line ( out, indent_level );
	req_name_ = unit_name_ + "_processor";
	this->_generate_processor_element( unit, req_name_, out, indent_level );
	// generate compiler element
	HelpFunctions::new_line ( out, indent_level );
	req_name_ = unit_name_ + "_compiler";
	this->_generate_compiler_element( unit, req_name_, out, indent_level );
	// generate programminglanguage element
	HelpFunctions::new_line ( out, indent_level );
	req_name_ = unit_name_ + "_programmlanguage";
	this->_generate_prog_language_element( unit, req_name_, out, indent_level );
	// generate descriptorfile element
	HelpFunctions::new_line ( out, indent_level );
	req_name_ = unit_name_ + "_descriptorfile_link";
	std::string str_ = get_req_value( unit, req_name_ );
	if ( ! str_.empty() )
		this->_generate_descriptor_element( unit, req_name_, out, indent_level );
	// generate code elements
	HelpFunctions::new_line ( out, indent_level );
	if ( contained_->length() > 0 )
	{
		for (CORBA::ULong i = 0; i < contained_->length (); i++)
		{
			HelpFunctions::new_line ( out, indent_level );
			this->_generate_code_element ( contained_[i], out, indent_level );
		}
	}

	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</implementation>";
}

void CSDBackendSessionImpl::_generate_os_element 
	( MDE::Deployment::DeploymentUnit_ptr unit, std::string req_name, ostream& out, unsigned long & indent_level )
{
	out << "<os name=\"" << get_req_value( unit, req_name);
	if ( get_req_version (unit, req_name) == "" )
		out << "\"/>";
	else
		out << "\" version=\"" << get_req_version (unit, req_name) << "/>";
}

void CSDBackendSessionImpl::_generate_processor_element 
	( MDE::Deployment::DeploymentUnit_ptr unit, std::string req_name, ostream& out, unsigned long & indent_level )
{
	out << "<processor name=\"" << get_req_value( unit, req_name) << "\"/>";
}

void CSDBackendSessionImpl::_generate_compiler_element 
	( MDE::Deployment::DeploymentUnit_ptr unit, std::string req_name, ostream& out, unsigned long & indent_level )
{
	out << "<compiler name=\"" << get_req_value( unit, req_name);
	if ( get_req_version (unit, req_name) == "" )
		out << "\"/>";
	else
		out << "\" version=\"" << get_req_version (unit, req_name) << "/>";
}

void CSDBackendSessionImpl::_generate_prog_language_element 
	( MDE::Deployment::DeploymentUnit_ptr unit, std::string req_name, ostream& out, unsigned long & indent_level )
{
	out << "<programminglanguage name=\"" << get_req_value( unit, req_name);
	if ( get_req_version (unit, req_name) == "" )
		out << "\"/>";
	else
		out << "\" version=\"" << get_req_version (unit, req_name) << "/>";
}

void CSDBackendSessionImpl::_generate_descriptor_element
	( MDE::Deployment::DeploymentUnit_ptr unit, std::string req_name, ostream& out, unsigned long & indent_level )
{
	out << "<descriptor type=\"CORBA-Component\">";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<fileinarchive name=\"" << get_req_value( unit, req_name ) << "\" />";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<descriptor>";
}

void CSDBackendSessionImpl::_generate_code_element
( MDE::Deployment::ContainedFile_ptr contained, ostream& out, unsigned long & indent_level )
{
	out << "<code type=\"" << contained->codetype() << "\">";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<fileinarchive name=\"" << contained->filename();
	if ( contained->location() != "" )
	{
		out << "\">";
		HelpFunctions::inc_indent_level ( indent_level );
		HelpFunctions::new_line ( out, indent_level );
		out << "<link href=\"" << contained->location() << "\"/>";
		HelpFunctions::dec_indent_level ( indent_level );
	}
	else 
		out << "\"/>";
	HelpFunctions::new_line ( out, indent_level );
	out << "<entrypoint>" << contained->entrypoint() << "</entrypoint>";
	HelpFunctions::new_line ( out, indent_level );
	out << "<usage>" << contained->entrypointusage () << "</usage>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</code>";

}

std::string CSDBackendSessionImpl::get_req_value ( MDE::Deployment::DeploymentUnit_ptr unit, std::string req_name )
{
	std::string ret_ = "";
	MDE::Deployment::DeploymentRequirementSet_var all_reqs_ = unit->req();
	for (CORBA::ULong i = 0; i < all_reqs_->length (); i++)
	{
		if ( all_reqs_[i]->identifier() == req_name)
		{
			ret_ = all_reqs_[i]->kind();
			return ret_;
		}
	}
	return ret_;
}

std::string CSDBackendSessionImpl::get_req_version ( MDE::Deployment::DeploymentUnit_ptr unit, std::string req_name )
{
	std::string ret_ = "";
	MDE::Deployment::DeploymentRequirementSet_var all_reqs_ = unit->req();
	for (CORBA::ULong i = 0; i < all_reqs_->length (); i++)
	{
		if ( all_reqs_[i]->identifier() == req_name)
		{
			ret_ = all_reqs_[i]->req_version();
			return ret_;
		}
	}
	return ret_;
}

// END USER INSERT SECTION CSDBackendSessionImpl


CSDBackendSessionImpl::CSDBackendSessionImpl()
{
// BEGIN USER INSERT SECTION CSDBackendSessionImpl::CSDBackendSessionImpl
// END USER INSERT SECTION CSDBackendSessionImpl::CSDBackendSessionImpl
}


CSDBackendSessionImpl::~CSDBackendSessionImpl()
{
// BEGIN USER INSERT SECTION CSDBackendSessionImpl::~CSDBackendSessionImpl
// END USER INSERT SECTION CSDBackendSessionImpl::~CSDBackendSessionImpl

}


void
CSDBackendSessionImpl::set_context(::CCMGenerator::CCM_CSDBackend_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::CCMGenerator::CCM_CSDBackend_ContextImpl::_duplicate(context);
}


void
CSDBackendSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION CSDBackendSessionImpl::configuration_complete
	cout << "configuration_complete() by CSDBackEnd was called!!! " <<  endl;
// END USER INSERT SECTION CSDBackendSessionImpl::configuration_complete
}


void
CSDBackendSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CSDBackendSessionImpl::remove
// END USER INSERT SECTION CSDBackendSessionImpl::remove
}


void
CSDBackendSessionImpl::rep_ref(CORBA::Object_ptr param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CSDBackendSessionImpl::_rep_ref
	_root = CORBA::Object::_duplicate(param);
	if( CORBA::is_nil ( _root ) ) 
	{
		throw NilObjectRef ( "Repository root is NIL: narrow problem!" );
	}
// END USER INSERT SECTION CSDBackendSessionImpl::_rep_ref
}


CORBA::Object_ptr
CSDBackendSessionImpl::rep_ref()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION CSDBackendSessionImpl::rep_ref
	return _root._retn();
// END USER INSERT SECTION CSDBackendSessionImpl::rep_ref
}


void
CSDBackendSessionImpl::generate(const char* name, const char* vers, const char* a_name, const char* a_comp, const char* a_web, const char* title, const char* description, const char* lisence, const char* idl_id, const char* idl_file, const char* output, const CCMGenerator::DeploymentUnitIDList& units)
	throw(CORBA::SystemException, ::CCMGenerator::OutputError)
{
// BEGIN USER INSERT SECTION CSDBackendSessionImpl::generate
	//this->_generate_deployment_unit_element ();
 try
 {
	this->connect_the_whole_repository ();

	ofstream out;
	out.open ( output );
	unsigned long indent_level = 0;
	begin(out);
	HelpFunctions::new_line ( out, indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<softpkg name=\"" << name << "\" " << "version=\"" << vers << "\">";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<title> " << title << " <title>";
	HelpFunctions::new_line ( out, indent_level );
	out << "<autor>";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<name>" << a_name << "</name>";
	HelpFunctions::new_line ( out, indent_level );
	out << "<company>" << a_comp << "</company>";
	HelpFunctions::new_line ( out, indent_level );
	out << "<webpage href=\"" << a_web << "\"/>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</autor>";
	HelpFunctions::new_line ( out, indent_level );
	out << "<description>" << description << "</description>";
	HelpFunctions::new_line ( out, indent_level );
	out << "<license href=\"" << lisence << "\"/>";
	HelpFunctions::new_line ( out, indent_level );
	out << "<idl id=\"" << idl_id << "\">";
	HelpFunctions::inc_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<fileinarchive name=\"" << idl_file << "\"/>";
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "<idl>";
	HelpFunctions::new_line ( out, indent_level );
	
	MDE::Deployment::DeploymentUnitSet_var all_units_= 
		_repconnector._deployment_unit_ref->all_of_class_deployment_unit();
	
	MDE::Deployment::DeploymentUnit_var unit_;
	std::string unit_rep_id_;
	CORBA::ULong  i;
	for (i = 0; i < units.length(); i++)
	{
		for (CORBA::ULong j = 0; j < all_units_->length (); j++)
		{
			unit_rep_id_ = all_units_[j]->repository_id();
			if ( !strcmp ( unit_rep_id_.c_str(), units[i] ) )
			{
				unit_ = all_units_[j];
				if ( ! CORBA::is_nil ( unit_ ))
				{
					HelpFunctions::new_line ( out, indent_level );
					this->_generate_deployment_unit_element( unit_, out, indent_level );
				}
			}
		}
	
	}
	HelpFunctions::dec_indent_level ( indent_level );
	HelpFunctions::new_line ( out, indent_level );
	out << "</softpkg>" ;
	out.close();
}
	
catch (CORBA::SystemException& e)
{
	throw e;
}
// END USER INSERT SECTION CSDBackendSessionImpl::generate
}


// BEGIN USER INSERT SECTION CSDBackEnd_compo
// END USER INSERT SECTION CSDBackEnd_compo


CSDBackEnd_compo::CSDBackEnd_compo()
:component_(new CSDBackendSessionImpl())
{
// BEGIN USER INSERT SECTION CSDBackEnd_compo::CSDBackEnd_compo
// END USER INSERT SECTION CSDBackEnd_compo::CSDBackEnd_compo
}


CSDBackEnd_compo::~CSDBackEnd_compo()
{
// BEGIN USER INSERT SECTION CSDBackEnd_compo::~CSDBackEnd_compo
// END USER INSERT SECTION CSDBackEnd_compo::~CSDBackEnd_compo

    component_->_remove_ref();
}


::CORBA::Object*
CSDBackEnd_compo::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    else if (! strcmp (name, "control")) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
CSDBackEnd_compo::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
CSDBackEnd_compo::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION CSDBackEnd_compo::configuration_complete
// END USER INSERT SECTION CSDBackEnd_compo::configuration_complete
}


void
CSDBackEnd_compo::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::CCMGenerator::CCM_CSDBackend_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::CCMGenerator::CCM_CSDBackend_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::CCMGenerator::CCM_CSDBackend_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::CCMGenerator::CCM_CSDBackend_ContextImpl::_nil();
        
    #else
    context_ = ::CCMGenerator::CCM_CSDBackend_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
CSDBackEnd_compo::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CSDBackEnd_compo::ccm_activate
// END USER INSERT SECTION CSDBackEnd_compo::ccm_activate
}


void
CSDBackEnd_compo::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CSDBackEnd_compo::ccm_passivate
// END USER INSERT SECTION CSDBackEnd_compo::ccm_passivate
}


void
CSDBackEnd_compo::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION CSDBackEnd_compo::ccm_remove
// END USER INSERT SECTION CSDBackEnd_compo::ccm_remove
}


// BEGIN USER INSERT SECTION CSDBackendHomeImpl
// END USER INSERT SECTION CSDBackendHomeImpl


CSDBackendHomeImpl::CSDBackendHomeImpl()
{
// BEGIN USER INSERT SECTION CSDBackendHomeImpl::CSDBackendHomeImpl
// END USER INSERT SECTION CSDBackendHomeImpl::CSDBackendHomeImpl
}


CSDBackendHomeImpl::~CSDBackendHomeImpl()
{
// BEGIN USER INSERT SECTION CSDBackendHomeImpl::~CSDBackendHomeImpl
// END USER INSERT SECTION CSDBackendHomeImpl::~CSDBackendHomeImpl

}


void
CSDBackendHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
CSDBackendHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION CSDBackendHomeImpl::create
// END USER INSERT SECTION CSDBackendHomeImpl::create
    return new CSDBackEnd_compo();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_CSDBackendHomeE(void)
{
// BEGIN USER INSERT SECTION create_CSDBackendHome
// END USER INSERT SECTION create_CSDBackendHome

    return new ::CCMGenerator::CSDBackendHomeImpl();
}

