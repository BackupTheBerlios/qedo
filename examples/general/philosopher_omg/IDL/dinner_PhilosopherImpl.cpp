//
// generated by Qedo
//

#include "dinner_PhilosopherImpl.h"


// BEGIN USER INSERT SECTION file
#include "PhilosopherState.h"

#ifndef WIN32
static GUI gui;
#endif
namespace dinner {

//
// A Thread class with interruptable sleep()
//
ThreadWithTimer::ThreadWithTimer ()
{
}


ThreadWithTimer::~ThreadWithTimer ()
{
}

#if defined (HAVE_JTC) || defined (WIN32)
void
ThreadWithTimer::timer_sleep (long millis)
{
	JTCSynchronized synchronized(*this);	

	bool done_ = false;

	while (!done_)
	{
		try
		{ 
			this->wait(millis);
			done_ = true;
		}
		catch (JTCInterruptedException&)
		{
		}
	}
}


void
ThreadWithTimer::wake_up ()
{
	JTCSynchronized synchronized ( *this );	

	this -> notify ();
}
#else
#ifdef HAVE_PTHREAD_H
void
ThreadWithTimer::timer_sleep (long millis)
{
}


void
ThreadWithTimer::wake_up ()
{
}


void
ThreadWithTimer::_run (void *)
{
	run();
}
#else
#error No threads configured
#endif
#endif


#ifdef WIN32
//
// A GUI thread for the WIN32 Philosopher
//
GUIThread::GUIThread ()
{
	gui_ = 0;
	stopped_ = false;
}


GUIThread::~GUIThread ()
{
}


void
GUIThread::run ()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	
	gui_ = new PhilosopherGUI ( NULL, philo );

	{
		// notify philospher to go on
		HU_CCM_Container::Synchronized synchronized ( *philo );
		philo -> notify ();
	}

	// event main loop
	MSG msg;
	BOOL bRet;
	while (!stopped_ && ( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)) { 

		if (bRet == -1)
		{ 
			WITH_PID_ERR( "Error from GetMessage()" );
		}
		else
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

	if(gui_) delete gui_;
}
#endif

}
// END USER INSERT SECTION file


namespace dinner {


// BEGIN USER INSERT SECTION PhilosopherSessionImpl
PhilosopherSessionImpl::PhilosopherSessionImpl (string name, int tick, bool right_hander = true) 
: right_hander_(right_hander), stopped_(false), id_(name), tickTime_(tick)
{
	status = DiningPhilosophers::THINKING;
}


void 
PhilosopherSessionImpl::run 
()
{
	string thread_name = "(";
	thread_name.append(JTCThread::currentThread()->getName());
	thread_name.append(")");

	bool have_left=false, have_right=false;
	PhilosopherState_impl* report;

	DiningPhilosophers::Fork_var left_hand = context_ -> get_connection_left();
	DiningPhilosophers::Fork_var right_hand = context_ -> get_connection_right();

#ifdef WIN32
	// start GUI thread and wait until the GUI is created
	{
		JTCSynchronized synchronized ( *this );
		
		gui_thread -> philo = this;
		gui_thread -> start ();
		
		while ( !gui_thread -> gui_ )
		{
			try
			{
				wait ();
			}
			catch ( const JTCInterruptedException& )
			{
			}
		}
	}
#else
	philosopher_gui = gui.new_gui(id_.c_str());
#endif

    // start thinking
    status = DiningPhilosophers::THINKING;
    long tickCount = 0;
    long holdFork = 0;
    bool haveLeft = false;
    bool haveRight = false;
	
    while (!stopped_)
	{
        //
        // update gui
        //
#ifdef WIN32
		gui_thread->gui_->InvalidateRect(0);
#else
		switch (status)
        {
        case DiningPhilosophers::THINKING : gui.thinking(philosopher_gui);
            break;
        case DiningPhilosophers::STARVING : gui.sleeping(philosopher_gui);
            break;
        case DiningPhilosophers::HUNGRY : gui.hungry(philosopher_gui);
            break;
        case DiningPhilosophers::EATING : gui.eating(philosopher_gui);
            break;
        case DiningPhilosophers::DEAD : gui.sleeping(philosopher_gui);
            break;
        }
#endif

        //
        // push info
        //
        report = new PhilosopherState_impl(id_.c_str(), status, tickCount, haveLeft, haveRight);
		try
		{
//			context_->push_info(report);
		}
		catch(CORBA::SystemException& ex)
		{
			WITH_PID_ERR2 ( "PhilosopherSessionImpl: CORBA system exception during reporting : ", ex );
		}

        // sleep
		timer_sleep(tickTime_);
        tickCount++;

        //
        // THINKING
        //
        if (status == DiningPhilosophers::THINKING && (tickCount > 2))
        {
            status = DiningPhilosophers::HUNGRY;
        }
        
        //
        // HUNGRY
        //
        if (status == DiningPhilosophers::HUNGRY)
        {
            if (tickCount > 9)
            {
                status = DiningPhilosophers::STARVING;
            }
            else
            {
                // try to get a fork for the strong hand
			    try
			    {
				    if (right_hander_)
				    {
					    right_hand->get();
					    haveRight = true;
    					WITH_PID_OUT3(id_, " got right fork ", thread_name);
    				}
	    			else
		    		{
			    		left_hand->get();
				    	haveLeft = true;
					    WITH_PID_OUT3(id_, " got left fork ", thread_name);
				    }
			    }
			    catch (DiningPhilosophers::InUse& )
			    {
				    if (right_hander_)
				    {
					    WITH_PID_OUT3(id_, " can't get right fork ", thread_name);
				    }
				    else
				    {
					    WITH_PID_OUT3(id_, " can't get left fork ", thread_name);
				    }
				    continue;
			    }
			    catch ( CORBA::SystemException& )
			    {
				    WITH_PID_ERR("PhilosopherSessionImpl: CORBA system exception during obtain_fork(). continue...");
    				continue;
	    		}

    			// try to get a fork for the weak hand
			    try {
				    if (right_hander_)
				    {
					    left_hand->get();
					    haveLeft = true;
    					WITH_PID_OUT3(id_, " got left fork ", thread_name);
	    			}
		    		else
			    	{
				    	right_hand->get();
					    haveRight = true;
    					WITH_PID_OUT3(id_, " got right fork ", thread_name);
	    			}
		    	}
			    catch (DiningPhilosophers::InUse&)
			    {
				    try
				    {
					    if (right_hander_)
					    {
		    				right_hand->release();
			    			haveRight = false;
    						WITH_PID_OUT3(id_, " doesn't need right fork anymore ", thread_name);
	    				} 
		    			else 
			    		{
				    		left_hand->release();
					    	haveLeft = false;
					    	WITH_PID_OUT3(id_, " doesn't need left fork anymore ", thread_name);
					    }
					    continue;
	    			}
		    		catch (CORBA::SystemException&)
			    	{
				    	WITH_PID_ERR3("PhilosopherSessionImpl: CORBA system exception during release_fork(). I'm in hell, aborting -> ", id_, thread_name );
    					continue;
	    			}
		    	}
			    catch (CORBA::SystemException&)
			    {
	    			try
		    		{
			    		WITH_PID_ERR3("PhilosopherSessionImpl: CORBA system exception during obtain_fork() -> ", id_, thread_name );
			
				    	if (right_hander_)
					    {
						    right_hand->release();
		    				haveRight = false;
			    		}
	    				else
		    			{
			    			left_hand->release();
				    		haveLeft = false;
					    }
					    continue;
			    	}
	    			catch (CORBA::SystemException&)
		    		{
			    		WITH_PID_ERR3("PhilosopherSessionImpl: CORBA system exception during release_fork(). I'm in hell, aborting -> ", id_, thread_name );
					    continue;
	    			}
		    	}

                tickCount = 0;
                status = DiningPhilosophers::EATING;
            }
        }

        //
        // STARVING
        //
        if (status == DiningPhilosophers::STARVING)
        {
            if (tickCount > 39)
            {
                status = DiningPhilosophers::DEAD;
            }
            else
            {
                // try to get a fork for the strong hand
			    try
			    {
				    if (right_hander_ && !haveRight)
				    {
					    right_hand->get();
					    haveRight = true;
    					WITH_PID_OUT3(id_, " got right fork ", thread_name);
    				}
	    			if (!right_hander_ && !haveLeft)
		    		{
			    		left_hand->get();
				    	haveLeft = true;
					    WITH_PID_OUT3(id_, " got left fork ", thread_name);
				    }
			    }
			    catch (DiningPhilosophers::InUse&)
			    {
				    if (right_hander_)
				    {
					    WITH_PID_OUT3(id_, " can't get right fork ", thread_name);
				    }
				    else
				    {
					    WITH_PID_OUT3(id_, " can't get left fork ", thread_name);
				    }
				    continue;
			    }
			    catch (CORBA::SystemException&)
			    {
				    WITH_PID_ERR("PhilosopherSessionImpl: CORBA system exception during obtain_fork(). continue...");
    				continue;
	    		}

                holdFork++;
    			// try to get a fork for the weak hand
			    try {
				    if (right_hander_)
				    {
					    left_hand->get();
					    haveLeft = true;
    					WITH_PID_OUT3(id_, " got left fork ", thread_name);
	    			}
		    		else
			    	{
				    	right_hand->get();
					    haveRight = true;
    					WITH_PID_OUT3(id_, " got right fork ", thread_name);
	    			}
		    	}
			    catch (DiningPhilosophers::InUse&)
			    {
				    try
				    {
					    if (right_hander_ && (holdFork > 5))
					    {
		    				right_hand->release();
			    			haveRight = false;
    						DEBUG_WITH_PID_OUT3(id_, " doesn't need right fork anymore ", thread_name);
                            holdFork = 0;
	    				} 
		    			if (!right_hander_ && (holdFork > 5)) 
			    		{
				    		left_hand->release();
					    	haveLeft = false;
					    	DEBUG_WITH_PID_OUT3(id_, " doesn't need right fork anymore ", thread_name);
                            holdFork = 0;
					    }
					    continue;
	    			}
		    		catch (CORBA::SystemException&)
			    	{
				    	WITH_PID_ERR3("PhilosopherSessionImpl: CORBA system exception during release_fork(). I'm in hell, aborting -> ", id_, thread_name );
    					continue;
	    			}
		    	}
			    catch (CORBA::SystemException&)
			    {
	    			try
		    		{
			    		WITH_PID_ERR3("PhilosopherSessionImpl: CORBA system exception during obtain_fork() -> ", id_, thread_name );
			
				    	if (right_hander_)
					    {
						    right_hand->release();
		    				haveRight = false;
			    		}
	    				else
		    			{
			    			left_hand->release();
				    		haveLeft = false;
					    }
					    continue;
			    	}
	    			catch (CORBA::SystemException&)
		    		{
			    		WITH_PID_ERR3("PhilosopherSessionImpl: CORBA system exception during release_fork(). I'm in hell, aborting -> ", id_, thread_name );
					    continue;
	    			}
		    	}

                tickCount = 0;
                status = DiningPhilosophers::EATING;
            }
        }

        //
        // EATING
        //
        if (status == DiningPhilosophers::EATING && (tickCount > 3))
        {
            tickCount = 0;
            status = DiningPhilosophers::THINKING;

            // release the used forks
			try
			{
				right_hand->release();
				haveRight = false;
				left_hand->release();
				haveLeft = false;
			}
            catch (CORBA::SystemException&)
			{
				WITH_PID_ERR3("PhilosopherSessionImpl: Unexpected CORBA system exception. I'm in hell, aborting... -> ", id_, thread_name );
				continue;
			}
        }

        //
        // DEAD
        //
        if (status == DiningPhilosophers::DEAD)
        {
            try
	        {
        		if (haveLeft)
                {
	    		    left_hand->release();
                    haveLeft = false;
                }

    	    	if (haveRight)
                {
		        	right_hand->release();
                    haveRight = false;
                }
        	}
	        catch (CORBA::SystemException&)
        	{
	        	WITH_PID_ERR3("PhilosopherSessionImpl: CORBA system exception during release_fork(). Doesn't matter, I'm finishing anyway -> ", id_, thread_name );
        	}
        	WITH_PID_OUT3(id_, " is dead ", thread_name );
            
            // respawn
            if (tickCount > 50)
            {
                id_ = id_.append("'s son");
                tickCount = 0;
                status = DiningPhilosophers::THINKING;
            }
        }
    }
}
// END USER INSERT SECTION PhilosopherSessionImpl


PhilosopherSessionImpl::PhilosopherSessionImpl()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::PhilosopherSessionImpl
// END USER INSERT SECTION PhilosopherSessionImpl::PhilosopherSessionImpl
}


PhilosopherSessionImpl::~PhilosopherSessionImpl()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::~PhilosopherSessionImpl
// END USER INSERT SECTION PhilosopherSessionImpl::~PhilosopherSessionImpl
}


void
PhilosopherSessionImpl::set_context(::DiningPhilosophers::CCM_Philosopher_Context_ptr context)
{
    context_ = ::DiningPhilosophers::CCM_Philosopher_Context::_duplicate(context);
}


void
PhilosopherSessionImpl::configuration_complete()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::configuration_complete
#ifdef WIN32
	gui_thread = new GUIThread;
#endif
    
    start ();
// END USER INSERT SECTION PhilosopherSessionImpl::configuration_complete
}


void
PhilosopherSessionImpl::stop()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::stop
// END USER INSERT SECTION PhilosopherSessionImpl::stop
}


void
PhilosopherSessionImpl::remove()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::remove
    JTCThreadHandle my_handle = this;
	
	DEBUG_WITH_PID_OUT2 ( "PhilosopherSessionImpl: Removing thread ", id_ );
	
	stopped_ = true;

	this -> wake_up();

	do 
	{
		try
		{
			DEBUG_WITH_PID_OUT2 ( "PhilosopherSessionImpl: Try join ", id_ );
			my_handle -> join ();
		}
		catch(const JTCInterruptedException&)
		{
		}
	} while( my_handle -> isAlive() );

	DEBUG_WITH_PID_OUT2 ( "PhilosopherSessionImpl: Removed thread ", id_ );
	
#ifdef WIN32
	JTCThreadHandle my_gui = gui_thread;

	{
		JTCSynchronized synchronized ( *gui_thread );
		gui_thread -> stopped_ = true;
		gui_thread -> gui_ -> InvalidateRect ( 0 );
	}

	do 
	{
		try
		{
			DEBUG_WITH_PID_OUT ( "PhilosopherSessionImpl: Try join with GUI " );
			my_gui -> join ();
		}
		catch(const JTCInterruptedException&)
		{
		}
	} while( my_gui -> isAlive() );

	DEBUG_WITH_PID_OUT ( "PhilosopherSessionImpl: GUI removed" );
#endif
// END USER INSERT SECTION PhilosopherSessionImpl::remove
}


void
PhilosopherSessionImpl::name(const char* param)
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::_name
id_ = CORBA::string_dup(param);	//@@@ (_name);
// END USER INSERT SECTION PhilosopherSessionImpl::_name
}


char*
PhilosopherSessionImpl::name()
{
// BEGIN USER INSERT SECTION PhilosopherSessionImpl::name
    return CORBA::string_dup(id_.c_str());
// END USER INSERT SECTION PhilosopherSessionImpl::name
}


// BEGIN USER INSERT SECTION PhilosopherImpl
PhilosopherImpl::PhilosopherImpl (const char* my_name, int tick, bool right_hander)
: my_name_(my_name), right_hander_ (right_hander), tickTime_(tick)
{
    component_executor_ = 0;
}
// END USER INSERT SECTION PhilosopherImpl


PhilosopherImpl::PhilosopherImpl()
    : component_(new PhilosopherSessionImpl())
{
// BEGIN USER INSERT SECTION PhilosopherImpl::PhilosopherImpl
// END USER INSERT SECTION PhilosopherImpl::PhilosopherImpl
}


PhilosopherImpl::~PhilosopherImpl()
{
    component_->_remove_ref();

// BEGIN USER INSERT SECTION PhilosopherImpl::~PhilosopherImpl
// END USER INSERT SECTION PhilosopherImpl::~PhilosopherImpl
}


::CORBA::Object*
PhilosopherImpl::obtain_executor(const char* name)
{
    if (! strcmp ( name, "component" ) ) {
        return Components::EnterpriseComponent::_duplicate (component_);
    }
    
    return Components::EnterpriseComponent::_nil();
}


void
PhilosopherImpl::release_executor(::CORBA::Object_ptr executor)
{
    CORBA::release (executor);
}


void
PhilosopherImpl::configuration_complete()
{
    component_->configuration_complete();

// BEGIN USER INSERT SECTION PhilosopherImpl::configuration_complete
    PhilosopherSessionImpl* segment = dynamic_cast<PhilosopherSessionImpl*>(obtain_executor("component"));
    segment->configuration_complete ();
// END USER INSERT SECTION PhilosopherImpl::configuration_complete
}


void
PhilosopherImpl::set_session_context(::Components::SessionContext_ptr context)
{
    context_ = ::DiningPhilosophers::CCM_Philosopher_Context::_narrow(context);
    
    component_->set_context(context_);
}


void
PhilosopherImpl::ccm_activate()
{
// BEGIN USER INSERT SECTION PhilosopherImpl::ccm_activate
// END USER INSERT SECTION PhilosopherImpl::ccm_activate
}


void
PhilosopherImpl::ccm_passivate()
{
// BEGIN USER INSERT SECTION PhilosopherImpl::ccm_passivate
// END USER INSERT SECTION PhilosopherImpl::ccm_passivate
}


void
PhilosopherImpl::ccm_remove()
{
// BEGIN USER INSERT SECTION PhilosopherImpl::ccm_remove
// END USER INSERT SECTION PhilosopherImpl::ccm_remove
}


// BEGIN USER INSERT SECTION PhilosopherHomeImpl
// END USER INSERT SECTION PhilosopherHomeImpl


PhilosopherHomeImpl::PhilosopherHomeImpl()
{
// BEGIN USER INSERT SECTION PhilosopherHomeImpl::PhilosopherHomeImpl
    srand((unsigned)time(NULL));
// END USER INSERT SECTION PhilosopherHomeImpl::PhilosopherHomeImpl
}


PhilosopherHomeImpl::~PhilosopherHomeImpl()
{
// BEGIN USER INSERT SECTION PhilosopherHomeImpl::~PhilosopherHomeImpl
// END USER INSERT SECTION PhilosopherHomeImpl::~PhilosopherHomeImpl
}


void
PhilosopherHomeImpl::set_context(Components::CCMContext_ptr ctx)
{
    context_ = ::DiningPhilosophers::CCM_Philosopher_Context::_narrow(ctx);
}


::Components::ExecutorLocator_ptr
PhilosopherHomeImpl::create ()
{
// BEGIN USER INSERT SECTION PhilosopherHomeImpl::create
    static int right_hander_counter_ = 0;
    bool right_hander = right_hander_counter_++ % 2 ? true : false;

    int tick = 1000 + rand() * 2000 / RAND_MAX;
    return new PhilosopherImpl("give me a name!", tick, right_hander);
// END USER INSERT SECTION PhilosopherHomeImpl::create
    return new PhilosopherImpl();
}


DiningPhilosophers::Philosopher_ptr
PhilosopherHomeImpl::_cxx_new(const char* name)
{
// BEGIN USER INSERT SECTION PhilosopherHomeImpl::new
	return 0;
// END USER INSERT SECTION PhilosopherHomeImpl::new
}


};


//
// entry point
//
::Components::HomeExecutorBase_ptr
create_PhilosopherHomeE(void)
{
// BEGIN USER INSERT SECTION create_PhilosopherHome
// END USER INSERT SECTION create_PhilosopherHome

    return new ::dinner::PhilosopherHomeImpl();
}

