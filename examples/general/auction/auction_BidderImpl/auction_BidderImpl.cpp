//
// generated by Qedo
//

#include "auction_BidderImpl.h"


// BEGIN USER INSERT SECTION file
// END USER INSERT SECTION file


namespace auction {


// BEGIN USER INSERT SECTION BidderSessionImpl
void*
BidderSessionImpl::run(void *p)
{
	BidderSessionImpl* impl;

	impl = static_cast<BidderSessionImpl*>(p);

	unsigned long my_price;

	while (! impl->stopped)
	{
		std::cout << "Your bid is: " << std::endl;
		std::cin >> my_price;
		if ( impl->stopped ) break;
		impl->do_bid(my_price);
	}

	return 0;
}

void
BidderSessionImpl::stop()
{
	stopped = true;
	bidder_thread->join();
}

void
BidderSessionImpl::do_bid(unsigned long price)
{
	CORBA::Object_ptr obj;
	auction::BidderForAuctioneer_var me;

	obj = context_->get_CCM_object();

	me = auction::BidderForAuctioneer::_narrow(obj);

	auction::Bid *bid = new auction::BidImpl;
	bid->price(price);
	bid->bidder(me);

	context_->push_my_bid(bid);

	std::cout << "Do a bid for " << bidder_item << " with price " << price << std::endl;
}
// END USER INSERT SECTION BidderSessionImpl


BidderSessionImpl::BidderSessionImpl()
{
// BEGIN USER INSERT SECTION BidderSessionImpl::BidderSessionImpl
	stopped = false;
	bidder_amount = 0;
// END USER INSERT SECTION BidderSessionImpl::BidderSessionImpl
}


BidderSessionImpl::~BidderSessionImpl()
{
// BEGIN USER INSERT SECTION BidderSessionImpl::~BidderSessionImpl
// END USER INSERT SECTION BidderSessionImpl::~BidderSessionImpl

}


void
BidderSessionImpl::set_context(::auction::CCM_Bidder_ContextImpl_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = ::auction::CCM_Bidder_ContextImpl::_duplicate(context);
}


void
BidderSessionImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::configuration_complete
	bidder_thread = context_->start_thread(run,this);
// END USER INSERT SECTION BidderSessionImpl::configuration_complete
}


void
BidderSessionImpl::remove()
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::remove
// END USER INSERT SECTION BidderSessionImpl::remove
}


void
BidderSessionImpl::amount(CORBA::Long param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::_amount
	bidder_amount = param;
// END USER INSERT SECTION BidderSessionImpl::_amount
}


CORBA::Long
BidderSessionImpl::amount()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::amount
	return bidder_amount;
// END USER INSERT SECTION BidderSessionImpl::amount
}


void
BidderSessionImpl::item(const char* param)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::_item
	bidder_item = param;
// END USER INSERT SECTION BidderSessionImpl::_item
}


char*
BidderSessionImpl::item()
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::item
	return const_cast<char*>(bidder_item.c_str());
// END USER INSERT SECTION BidderSessionImpl::item
}


void
BidderSessionImpl::sold(CORBA::Long amount)
	throw(CORBA::SystemException)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::sold
	std::cout << "You got item '" << bidder_item << "' for " << amount << std::endl;
	bidder_amount = bidder_amount - amount;
// END USER INSERT SECTION BidderSessionImpl::sold
}


void
BidderSessionImpl::push_event (Components::EventBase* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::push_event
// END USER INSERT SECTION BidderSessionImpl::push_event
}


void
BidderSessionImpl::push_GiveBid(::auction::GiveBid* ev)
    throw (CORBA::SystemException)
{
// BEGIN USER INSERT SECTION BidderSessionImpl::push_GiveBid
	bidder_item = ev->item();
	bidder_current_price = ev->current_bid();
	std::cout << "Bid for " << ev->item() << " price is " << ev->current_bid() << std::endl;
// END USER INSERT SECTION BidderSessionImpl::push_GiveBid
}


// BEGIN USER INSERT SECTION BidderImpl
// END USER INSERT SECTION BidderImpl


BidderImpl::BidderImpl()
:component_(new BidderSessionImpl())
{
// BEGIN USER INSERT SECTION BidderImpl::BidderImpl
// END USER INSERT SECTION BidderImpl::BidderImpl
}


BidderImpl::~BidderImpl()
{
// BEGIN USER INSERT SECTION BidderImpl::~BidderImpl
// END USER INSERT SECTION BidderImpl::~BidderImpl

    component_->_remove_ref();
}


::CORBA::Object*
BidderImpl::obtain_executor(const char* name)
    throw (CORBA::SystemException)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
BidderImpl::release_executor(::CORBA::Object_ptr executor)
    throw (CORBA::SystemException)
{
    CORBA::release (executor);
}


void
BidderImpl::configuration_complete()
    throw (CORBA::SystemException, Components::InvalidConfiguration)
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION BidderImpl::configuration_complete
// END USER INSERT SECTION BidderImpl::configuration_complete
}


void
BidderImpl::set_session_context(::Components::SessionContext_ptr context)
    throw (CORBA::SystemException, Components::CCMException)
{
    #ifdef TAO_ORB
    ::auction::CCM_Bidder_Context_ptr tmp_context;
    
    tmp_context = dynamic_cast<::auction::CCM_Bidder_ContextImpl*>(context);
    
    if (tmp_context)
        context_ = ::auction::CCM_Bidder_ContextImpl::_duplicate(tmp_context);
    else
        context_ = ::auction::CCM_Bidder_ContextImpl::_nil();
        
    #else
    context_ = ::auction::CCM_Bidder_ContextImpl::_narrow(context);
    
    #endif
    component_->set_context(context_);
}


void
BidderImpl::ccm_activate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION BidderImpl::ccm_activate
// END USER INSERT SECTION BidderImpl::ccm_activate
}


void
BidderImpl::ccm_passivate()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION BidderImpl::ccm_passivate
// END USER INSERT SECTION BidderImpl::ccm_passivate
}


void
BidderImpl::ccm_remove()
    throw (CORBA::SystemException, Components::CCMException)
{
// BEGIN USER INSERT SECTION BidderImpl::ccm_remove
// END USER INSERT SECTION BidderImpl::ccm_remove
}


// BEGIN USER INSERT SECTION BidderHomeImpl
// END USER INSERT SECTION BidderHomeImpl


BidderHomeImpl::BidderHomeImpl()
{
// BEGIN USER INSERT SECTION BidderHomeImpl::BidderHomeImpl
// END USER INSERT SECTION BidderHomeImpl::BidderHomeImpl
}


BidderHomeImpl::~BidderHomeImpl()
{
// BEGIN USER INSERT SECTION BidderHomeImpl::~BidderHomeImpl
// END USER INSERT SECTION BidderHomeImpl::~BidderHomeImpl

}


void
BidderHomeImpl::set_context(Components::HomeContext_ptr ctx)
    throw (CORBA::SystemException, Components::CCMException)
{
    context_ = Components::HomeContext::_duplicate(ctx);
    
}


::Components::EnterpriseComponent_ptr
BidderHomeImpl::create ()
    throw (CORBA::SystemException, Components::CreateFailure)
{
// BEGIN USER INSERT SECTION BidderHomeImpl::create
// END USER INSERT SECTION BidderHomeImpl::create
    return new BidderImpl();
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_BiddersE(void)
{
// BEGIN USER INSERT SECTION create_Bidders
// END USER INSERT SECTION create_Bidders

    return new ::auction::BidderHomeImpl();
}

