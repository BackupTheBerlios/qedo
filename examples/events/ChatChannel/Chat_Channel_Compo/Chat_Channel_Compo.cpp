//
// generated by Qedo
//

#include "Chat_Channel_Compo.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace Chat {


// BEGIN USER INSERT SECTION ChatChannelSessionImpl
// END USER INSERT SECTION ChatChannelSessionImpl


ChatChannelSessionImpl::ChatChannelSessionImpl()
{
// BEGIN USER INSERT SECTION ChatChannelSessionImpl::ChatChannelSessionImpl
// END USER INSERT SECTION ChatChannelSessionImpl::ChatChannelSessionImpl
}


ChatChannelSessionImpl::~ChatChannelSessionImpl()
{
// BEGIN USER INSERT SECTION ChatChannelSessionImpl::~ChatChannelSessionImpl
// END USER INSERT SECTION ChatChannelSessionImpl::~ChatChannelSessionImpl

}


void
ChatChannelSessionImpl::set_context(::Chat::CCM_ChatChannel_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::Chat::CCM_ChatChannel_ContextImpl::_duplicate(context);
}


void
ChatChannelSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION ChatChannelSessionImpl::configuration_complete
// END USER INSERT SECTION ChatChannelSessionImpl::configuration_complete
}


void
ChatChannelSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ChatChannelSessionImpl::remove
// END USER INSERT SECTION ChatChannelSessionImpl::remove
}


void
ChatChannelSessionImpl::push_event (Components::EventBase* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ChatChannelSessionImpl::push_event
//	std::cout << "ChatChannel: got message\n";
//	context_->push_event("to_reader",ev);
// END USER INSERT SECTION ChatChannelSessionImpl::push_event
}


void
ChatChannelSessionImpl::push_ChatMessage(::Chat::ChatMessage* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION ChatChannelSessionImpl::push_ChatMessage
	std::cout << "ChatChannel: got message\n";
	context_->push_to_reader(ev);
// END USER INSERT SECTION ChatChannelSessionImpl::push_ChatMessage
}


// BEGIN USER INSERT SECTION Channel_Compo
// END USER INSERT SECTION Channel_Compo


Channel_Compo::Channel_Compo()
:component_(new ChatChannelSessionImpl())
{
// BEGIN USER INSERT SECTION Channel_Compo::Channel_Compo
// END USER INSERT SECTION Channel_Compo::Channel_Compo
}


Channel_Compo::~Channel_Compo()
{
// BEGIN USER INSERT SECTION Channel_Compo::~Channel_Compo
// END USER INSERT SECTION Channel_Compo::~Channel_Compo

    component_->_remove_ref();
}


::CORBA::Object*
Channel_Compo::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
Channel_Compo::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
Channel_Compo::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION Channel_Compo::configuration_complete
// END USER INSERT SECTION Channel_Compo::configuration_complete
}


void
Channel_Compo::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::Chat::CCM_ChatChannel_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::Chat::CCM_ChatChannel_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::Chat::CCM_ChatChannel_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::Chat::CCM_ChatChannel_ContextImpl::_nil();
        
    #else
    context_ = ::Chat::CCM_ChatChannel_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
Channel_Compo::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Channel_Compo::ccm_activate
// END USER INSERT SECTION Channel_Compo::ccm_activate
}


void
Channel_Compo::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Channel_Compo::ccm_passivate
// END USER INSERT SECTION Channel_Compo::ccm_passivate
}


void
Channel_Compo::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION Channel_Compo::ccm_remove
// END USER INSERT SECTION Channel_Compo::ccm_remove
}


// BEGIN USER INSERT SECTION ChatChannelHomeSessionImpl
// END USER INSERT SECTION ChatChannelHomeSessionImpl


ChatChannelHomeSessionImpl::ChatChannelHomeSessionImpl()
{
// BEGIN USER INSERT SECTION ChatChannelHomeSessionImpl::ChatChannelHomeSessionImpl
// END USER INSERT SECTION ChatChannelHomeSessionImpl::ChatChannelHomeSessionImpl
}


ChatChannelHomeSessionImpl::~ChatChannelHomeSessionImpl()
{
// BEGIN USER INSERT SECTION ChatChannelHomeSessionImpl::~ChatChannelHomeSessionImpl
// END USER INSERT SECTION ChatChannelHomeSessionImpl::~ChatChannelHomeSessionImpl

}


void
ChatChannelHomeSessionImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
}


::Components::EnterpriseComponent_ptr
ChatChannelHomeSessionImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION ChatChannelHomeSessionImpl::create
// END USER INSERT SECTION ChatChannelHomeSessionImpl::create
    return new Channel_Compo();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_ChatChannelHomeE(void)
{
// BEGIN USER INSERT SECTION create_ChatChannelHome
// END USER INSERT SECTION create_ChatChannelHome

    return new ::Chat::ChatChannelHomeSessionImpl();
}

