//
// generated by Qedo
//

#ifndef _auction_BidderImpl_H_
#define _auction_BidderImpl_H_


// BEGIN USER INSERT SECTION file_pre
// END USER INSERT SECTION file_pre


#include <CORBA.h>
#include "auction_BidderImpl_BUSINESS.h"
#include "valuetypes.h"
#include "RefCountBase.h"
#include <string>


// BEGIN USER INSERT SECTION file_post
// END USER INSERT SECTION file_post


namespace auction
{
    
    //
    // executor
    //
    class BidderSessionImpl
        : public virtual CORBA::LocalObject
        , public virtual ::auction::CCM_BidderSessionImpl
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_BidderSessionImpl
// END USER INSERT SECTION INHERITANCE_BidderSessionImpl
    {
    
    private:
    
        ::auction::CCM_Bidder_ContextImpl_var context_;
        
    public:
    
        BidderSessionImpl();
        virtual ~BidderSessionImpl();
        
        void set_context(::auction::CCM_Bidder_ContextImpl_ptr context)
            throw (CORBA::SystemException, Components::CCMException);
        
        void configuration_complete()
            throw (CORBA::SystemException, Components::InvalidConfiguration);
        
        void remove()
            throw (CORBA::SystemException);
        
        
        //
        // IDL:auction/Bidder/amount:1.0
        //
        void amount(CORBA::Long param)
        	throw(CORBA::SystemException);
        CORBA::Long amount()
        	throw(CORBA::SystemException);
        
        //
        // IDL:auction/Bidder/item:1.0
        //
        void item(const char* param)
        	throw(CORBA::SystemException);
        char* item()
        	throw(CORBA::SystemException);
        
        //
        // IDL:auction/BidderForAuctioneer/sold:1.0
        //
        virtual void sold(CORBA::Long amount)
        	throw(CORBA::SystemException);
        
        //
        // IDL:Components/EventConsumerBase/push_event:1.0
        //
        virtual void push_event (Components::EventBase* ev)
            throw (CORBA::SystemException);
        
        
        //
        // IDL:auction/Bidder/current_bid:1.0
        //
        void push_GiveBid(::auction::GiveBid* ev)
            throw (CORBA::SystemException);
        
    
// BEGIN USER INSERT SECTION BidderSessionImpl
      Components::Thread_var bidder_thread;
      bool stopped;
		CORBA::Long            bidder_amount;
		CORBA::Long            bidder_current_price;
		std::string            bidder_item;
	public:
		static void* run(void*);
		void stop();
		void do_bid(unsigned long);
// END USER INSERT SECTION BidderSessionImpl

    };
    
    
    //
    // executor locator
    //
    class BidderImpl
        : public virtual CORBA::LocalObject
        , public virtual Components::SessionExecutorLocator
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_BidderImpl
// END USER INSERT SECTION INHERITANCE_BidderImpl
    {
    
    private:
    
        ::auction::CCM_Bidder_ContextImpl_var context_;
        
        BidderSessionImpl* component_;
        
    public:
    
        BidderImpl();
        virtual ~BidderImpl();
        
        
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
    
// BEGIN USER INSERT SECTION BidderImpl
// END USER INSERT SECTION BidderImpl

    };
    
    
    //
    // home executor
    //
    class BidderHomeImpl
        : public virtual CORBA::LocalObject
        , public virtual ::auction::CCM_Bidders
#ifndef MICO_ORB
        , public virtual Qedo::RefCountLocalObject
#endif
// BEGIN USER INSERT SECTION INHERITANCE_BidderHomeImpl
// END USER INSERT SECTION INHERITANCE_BidderHomeImpl
    {
    
    private:
    
        Components::HomeContext_var context_;
        
    public:
        BidderHomeImpl();
        virtual ~BidderHomeImpl();
        
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
    
// BEGIN USER INSERT SECTION BidderHomeImpl
// END USER INSERT SECTION BidderHomeImpl

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
::Components::HomeExecutorBase_ptr create_BiddersE(void);
}

#endif
