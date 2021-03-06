/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#ifndef __CONTAINER_INTERFACE_IMPL_H__
#define __CONTAINER_INTERFACE_IMPL_H__

#include <CORBA.h>
#ifdef MICO_ORB
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif
#include <QedoComponents_skel.h>
#include "HomeServantBase.h"
#include "ComponentInstance.h"
#include "Util.h"
#include <vector>
#include <string>
#include <sstream>


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * entry in a list of homes
 */
class HomeEntry
{
public:
	/** the servant of the home */
	Qedo::HomeServantBase*						home_servant_;
	/** id for registration in home finder */
	Components::Cookie*							home_cookie_;

	/** handle of the servant module dynamic library */
#ifdef _WIN32
	HINSTANCE servant_module_;
#else
	void* servant_module_;
#endif

	/** handle of the executor module dynamic library */
#ifdef _WIN32
	HINSTANCE executor_module_;
#else
	void* executor_module_;
#endif

	/**
	 * constructor
	 */
	HomeEntry (Qedo::HomeServantBase*, 
			   Components::Cookie* c,
#ifdef _WIN32
			   HINSTANCE servant_module,
			   HINSTANCE executor_module
#else
			   void* servant_module,
			   void* executor_module
#endif
			   );

	/**
	 * constructor
	 */
	HomeEntry();

	/**
	 * copy constructor
	 */
	HomeEntry (const HomeEntry&);

	/**
	 * assignment operator
	 */
	HomeEntry& operator= (const HomeEntry&);

	/**
	 * destructor
	 */
	~HomeEntry();
};


/**
 * entry in a list of service references
 * the entry is part of the list of service references in the container interface class
 */
class CONTAINERDLL_API ServiceReferenceEntry
{
public:
	/** the service id */
	std::string				_service_id;

	/** the initial service reference */
	CORBA::Object_var		_service_ref;

	/**
	 * constructor
	 * \param service_id The service id.
	 * \param service_ref The initial reference of the service.
	 */
	ServiceReferenceEntry(const char* service_id, CORBA::Object_ptr service_ref);

	/**
	 * copy constructor
	 */
	ServiceReferenceEntry (const ServiceReferenceEntry&);

	/**
	 * destructor
	 */
	~ServiceReferenceEntry();
};


/** the container type */
enum ContainerType {CT_EMPTY, CT_SERVICE, CT_SESSION, CT_PROCESS, CT_ENTITY, CT_EXTENSION};


class ComponentServerImpl;


/**
 * implementation of IDL:omg.org/Components/Deployment/Container
 */
class CONTAINERDLL_API ContainerInterfaceImpl : public virtual POA_Components::Deployment::Container,
												public virtual PortableServer::RefCountServantBase,
												public virtual CreateDestructCORBAObjectCounter
{
	class EventEntry
	{
	public:
		EventEntry (Components::EventConsumerBase_ptr c, Components::EventBase* e);
		EventEntry (const EventEntry& e);
		~EventEntry();
		Components::EventConsumerBase_var consumer_;
		Components::EventBase* event_;
		EventEntry& operator= (const EventEntry&);
	};

	/** to add services */
	friend class PrimaryServant;
	/** to access services */
	friend class ServantLocator;

#ifndef _QEDO_NO_QOS
	/** to access the component server */
	friend class ExtensionContext;
	friend class CCMContext;
	friend class ServerInterceptorDispatcher;
	friend class HomeServantBase;
#endif
private:
	/** the orb */
	CORBA::ORB_var											orb_;
	/** the poa */
	PortableServer::POA_var									root_poa_;

	/** the conatiner type */
	ContainerType											container_type_;
	/** the component server */
	ComponentServerImpl*									component_server_;
	/** the component installer */
	Components::Deployment::ComponentInstallation_var		component_installer_;
	/** the home finder */
	Qedo_Components::HomeFinder_var							home_finder_;
	/** the list of installed homes */
	std::vector <HomeEntry>									installed_homes_;
	/** the mutex �for installed_homes_ */
	QedoMutex												installed_homes_mutex_;

	/** the list of service references */
	std::vector <ServiceReferenceEntry>						service_references_;
	/** the mutex for service_references_ */
	QedoMutex												service_references_mutex_;

	/** the list of service components for preinvoke*/
	//std::vector <Qedo::ComponentInstance>					services_preinvoke_;
	/** the list of service components for postinvoke*/
	//std::vector <Qedo::ComponentInstance>					services_postinvoke_;

	/** the list of pending events to be dispatched*/
	std::vector<EventEntry>									event_list;

	/** the mutex for accessing the event_list member*/
	QedoMutex												event_queue_mutex_;

	/** this condition is signaled when a new entry is added to the event_list member*/
	QedoCond												event_queue_cond_;

	/* this bool indicates to the events thread the hi should stop */
	QedoThread*											event_queue_thread_;
	/* this bool indicates to the events thread the hi should stop */
	bool													event_queue_stopping_;

	/** Configuration values */
	enum EventCommunicationMode {EVENT_COMMUNICATION_ASYNCHRONOUS,
								 EVENT_COMMUNICATION_SYNCHRONOUS};

	EventCommunicationMode									event_communication_mode_;

	/**
	 * The event dispatcher thread
	 */
	static void* event_dispatcher_thread (void*);

	/**
	 * register the required valuetype factories if not already done
	 */
	void loadValuetypeFactories(std::string, std::string)
		throw (Components::CCMException);

#ifndef _QEDO_NO_QOS
	Components::Extension::ServantInterceptorRegistration_var servant_reg;
	Components::Extension::StubInterceptorRegistration_var stub_reg;

#endif 

public:
	/**
	 * constructor
	 */
	ContainerInterfaceImpl (CORBA::ORB_ptr, 
							PortableServer::POA_ptr, 
							ContainerType,
							ComponentServerImpl*,
							Components::Deployment::ComponentInstallation_ptr);

	/**
	 * destructor
	 */
	~ContainerInterfaceImpl();

	/**
	 * provide the initial service reference of the specified service
	 * \param service_id The service id.
	 * \return The initial reference of the service.
	 */
	CORBA::Object_ptr resolve_service_reference(const char*)
		throw (Components::CCMException);

	/**
	 * removes any homes that are still running
	 * */
	void prepare_remove();

	/**
	 * qeue events for delivering
	 * \param consumer The consumer is the receiver of the event.
	 * \param ev The ev is the event to be deliver.
	 */
	void queue_event(Components::EventConsumerBase_ptr, Components::EventBase*, CORBA::Long);

	/**
	 * qeue events for delivering
	 * \param consumers The consumers are the receivers of the event.
	 * \param ev The ev is the event to be deliver.
	 */
	void queue_event(const SubscribedConsumerVector&, Components::EventBase*, CORBA::Long);

	/**
	 * implements IDL:omg.org/Components/Deployment/Container/configuration:1.0
	 * not implemented yet
	 */
    virtual Components::ConfigValues* configuration()
        throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Deployment/Container/get_component_server:1.0
	 * not implemented yet
	 */
    virtual Components::Deployment::ComponentServer_ptr get_component_server()
        throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Deployment/Container/install_home:1.0
	 * The ConfigValue named "HOMEFINDERNAME" is used to provide a name for home registration in a HomeFinder,
	 * if available. Currently each home is registered automatically anyway by repository ids of home and
	 * managed component.
	 * The ConfigValue named "CCMSERVICE" could be used to indicate that a component of this home is a container
	 * service. This is still under development!
	 * \param id The uuid of the home implementation.
	 * \param entrypt The name of the entry point.
	 * \param config The list of config values.
	 * \return The object of the created home.
	 */
    virtual Components::CCMHome_ptr install_home(const char* id,
												 const char* entrypt,
												 const Components::ConfigValues& config)
        throw (Components::Deployment::UnknownImplId,
               Components::Deployment::ImplEntryPointNotFound,
               Components::Deployment::InstallationFailure,
               Components::Deployment::InvalidConfiguration,
               CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Deployment/Container/remove_home:1.0
	 * removes the home
	 * \param href The reference of the home.
	 */
    virtual void remove_home(Components::CCMHome_ptr href)
        throw (Components::RemoveFailure, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Deployment/Container/get_homes:1.0
	 * provides the list of all homes
	 * \return The list of all homes.
	 */
    virtual Components::CCMHomes* get_homes()
        throw (CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/Deployment/Container/remove:1.0
	 * not implemented
	 */
    virtual void remove()
        throw (Components::RemoveFailure, CORBA::SystemException);

	/**
     * implements IDL:omg.org/Components/Deployment/Container/install_service_reference:1.0
     * Qedo extension!
	 * register an initial reference of a service
	 * \param id The id of the service.
	 * \param ref The reference of the service.
	 */
    virtual void install_service_reference(const char* id, CORBA::Object_ptr ref)
		throw (Components::CCMException, CORBA::SystemException);
};

/** @} */

} // namespace Qedo

#endif

