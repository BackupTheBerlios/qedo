#include "ServerContainerInterceptor.h"
#include <sys/timeb.h>


namespace Qedo {

void 
ServerContainerInterceptor::set_slot_id(PortableInterceptor::SlotId slot_id) {
	slot_id_ = slot_id;

};

ServerContainerInterceptor::ServerContainerInterceptor (container_service::CCM_monitor_Context* context,container_service::MonExec* executor)
{
	executor_ = executor;
	context_ = context;

	char hostname[256];
	gethostname(hostname, 256);
	hostname_ = hostname;

	DWORD pid = GetCurrentProcessId();

	char s[11];

	sprintf (s, "%d", pid);

	process_id_ = s;



}

ServerContainerInterceptor::~ServerContainerInterceptor ()
{
	std::cout << "!!!!!!destructor of ServerContainerInterceptor!!!!!!!!" << std::endl;

}

void
ServerContainerInterceptor::receive_request (Components::Extension::ContainerServerRequestInfo_ptr info)
{

		/* 
		 * Get encoded context information
		 */
	
		std::string trail_id;
		char mess_cnt[11];
		unsigned long event_number = executor_ -> get_new_event_number();
		sprintf (mess_cnt, "__%08x", event_number);	
	 
		IOP::ServiceContext_var sc = 0;
		char *message_data;
		CORBA::Any_var any = new CORBA::Any;

		try {
			sc = info->request_info()->get_request_service_context(100);	
			
		    CORBA::OctetSeq data;

			data.length(sc->context_data.length());
			memcpy(data.get_buffer(), sc->context_data.get_buffer(), sc->context_data.length());
			any = executor_-> get_cdr_codec_ptr() -> decode_value(data, CORBA::_tc_string);


			any >>= message_data;
			
		} catch (CORBA::BAD_PARAM&)
		{
			//no service context for tracing
			message_data = new char[11];
			strcpy(message_data,mess_cnt);		
		} catch (...)
		{
			return;
		}
		
		trail_id = process_id_ + message_data;

		org::coach::tracing::api::TraceEvent_var event = new org::coach::tracing::api::TraceEvent;

		// set time_stamp
		struct _timeb current_time;
		_ftime(&current_time);
		CORBA::LongLong tm = current_time.time;
		tm = tm * 1000 + current_time.millitm;
		event->time_stamp = tm;

		// set ineraction point
		event->interaction_point = org::coach::tracing::api::POA_IN;


		event->trail_label= CORBA::string_dup ("");

		event->message_id = CORBA::string_dup (message_data);

		event->thread_id = CORBA::string_dup (message_data);

		event->trail_id	= CORBA::string_dup ("");
		
		event->event_counter  = event_number;
		event->op_name = CORBA::string_dup (CORBA::string_dup(info->request_info()->operation()));
		event->identity.object_instance_id		= CORBA::string_dup (info->port_id());
		event->identity.object_repository_id	= CORBA::string_dup (info->request_info()->target_most_derived_interface());
		event->identity.cmp_name				= CORBA::string_dup (info->component_id());
		event->identity.cmp_type				= CORBA::string_dup ("UNKNOWN_COMPONENT_TYPE");
		event->identity.cnt_name				= CORBA::string_dup ("UNKNOW_CONTAINER_NAME");
		event->identity.cnt_type				= CORBA::string_dup ("UNKONWN_CONTAINER_TYPE");
		event->identity.node_name				= CORBA::string_dup (hostname_.c_str());
		event->identity.node_ip					= CORBA::string_dup (" e");
		event->identity.process_id				= CORBA::string_dup (process_id_.c_str());

//			Dynamic::ParameterList_var parameters = new Dynamic::ParameterList();
//			parameters->length(0);

		event->parameters.length(0);

		org::coach::tracing::api::TraceEvents_var trace = new org::coach::tracing::api::TraceEvents;
		trace->length(1);
		(*trace)[0] = event;
		context_-> get_connection_to_trace_server() -> receiveEvent(trace.in());
}

void
ServerContainerInterceptor::send_reply (Components::Extension::ContainerServerRequestInfo_ptr info)
{

	org::coach::tracing::api::TraceEvent_var event = new org::coach::tracing::api::TraceEvent;

	// set time_stamp
	struct _timeb current_time;
	_ftime(&current_time);
	CORBA::LongLong tm = current_time.time;
	tm = tm * 1000 + current_time.millitm;
	event->time_stamp = tm;

	// set ineraction point
	event->interaction_point = org::coach::tracing::api::POA_OUT;
	event->trail_label= CORBA::string_dup ("");

	unsigned long event_number = executor_ -> get_new_event_number();
	char cnt[11];
	sprintf (cnt, "__%08x", event_number);
	std::string messageid = process_id_ + cnt;

	event->message_id = CORBA::string_dup (messageid.c_str());

	event->thread_id = CORBA::string_dup ("");
	
	event->trail_id	= CORBA::string_dup (messageid.c_str());
	
	event->event_counter  = event_number;
	event->op_name = CORBA::string_dup (CORBA::string_dup(info->request_info()->operation()));
	event->identity.object_instance_id		= CORBA::string_dup (info->port_id());
	event->identity.object_repository_id	= CORBA::string_dup ("TE");
	event->identity.cmp_name				= CORBA::string_dup (info->component_id());
	event->identity.cmp_type				= CORBA::string_dup ("UNKNOWN_COMPONENT_TYPE");
	event->identity.cnt_name				= CORBA::string_dup ("UNKNOW_CONTAINER_NAME");
	event->identity.cnt_type				= CORBA::string_dup ("UNKONWN_CONTAINER_TYPE");
	event->identity.node_name				= CORBA::string_dup (hostname_.c_str());
	event->identity.node_ip					= CORBA::string_dup (" e");
	event->identity.process_id				= CORBA::string_dup (process_id_.c_str());

//			Dynamic::ParameterList_var parameters = new Dynamic::ParameterList();
//			parameters->length(0);

	event->parameters.length(0);

	org::coach::tracing::api::TraceEvents_var trace = new org::coach::tracing::api::TraceEvents;
	trace->length(1);
	(*trace)[0] = event;
	context_-> get_connection_to_trace_server() -> receiveEvent(trace.in());

	CORBA::Any out_any;
	out_any <<= messageid.c_str();
	CORBA::OctetSeq_var data = executor_ -> get_cdr_codec_ptr() -> encode_value(out_any);

	IOP::ServiceContext out_sc;

	out_sc.context_id = 100;

	out_sc.context_data.length(data->length());

	memcpy(out_sc.context_data.get_buffer(), data->get_buffer(), data->length());

	info->request_info()->add_reply_service_context(out_sc, true);


}

void
ServerContainerInterceptor::send_system_exception (Components::Extension::ContainerServerRequestInfo_ptr info)
{
	std::cout << "COPI: send_system_exception: " << info->request_info()->operation() << "for id: " << std::endl;
	org::coach::tracing::api::TraceEvent_var event = new org::coach::tracing::api::TraceEvent;

	// set time_stamp
	struct _timeb current_time;
	_ftime(&current_time);
	CORBA::LongLong tm = current_time.time;
	tm = tm * 1000 + current_time.millitm;
	event->time_stamp = tm;

	// set ineraction point
	event->interaction_point = org::coach::tracing::api::POA_OUT_EXCEPTION;
	event->trail_label= CORBA::string_dup ("");

	unsigned long event_number = executor_ -> get_new_event_number();
	char cnt[11];
	sprintf (cnt, "__%08x", event_number);
	std::string messageid = process_id_ + cnt;

	event->message_id = CORBA::string_dup (messageid.c_str());

	event->thread_id = CORBA::string_dup ("");
	
	event->trail_id	= CORBA::string_dup (messageid.c_str());
	
	event->event_counter  = event_number;
	event->op_name = CORBA::string_dup (CORBA::string_dup(info->request_info()->operation()));
	event->identity.object_instance_id		= CORBA::string_dup (info->port_id());
	event->identity.object_repository_id	= CORBA::string_dup ("TE");
	event->identity.cmp_name				= CORBA::string_dup (info->component_id());
	event->identity.cmp_type				= CORBA::string_dup ("UNKNOWN_COMPONENT_TYPE");
	event->identity.cnt_name				= CORBA::string_dup ("UNKNOW_CONTAINER_NAME");
	event->identity.cnt_type				= CORBA::string_dup ("UNKONWN_CONTAINER_TYPE");
	event->identity.node_name				= CORBA::string_dup (hostname_.c_str());
	event->identity.node_ip					= CORBA::string_dup (" e");
	event->identity.process_id				= CORBA::string_dup (process_id_.c_str());

//			Dynamic::ParameterList_var parameters = new Dynamic::ParameterList();
//			parameters->length(0);

	event->parameters.length(0);

	org::coach::tracing::api::TraceEvents_var trace = new org::coach::tracing::api::TraceEvents;
	trace->length(1);
	(*trace)[0] = event;
	context_-> get_connection_to_trace_server() -> receiveEvent(trace.in());

	CORBA::Any out_any;
	out_any <<= messageid.c_str();
	CORBA::OctetSeq_var data = executor_ -> get_cdr_codec_ptr() -> encode_value(out_any);

	IOP::ServiceContext out_sc;

	out_sc.context_id = 100;

	out_sc.context_data.length(data->length());

	memcpy(out_sc.context_data.get_buffer(), data->get_buffer(), data->length());

	info->request_info()->add_reply_service_context(out_sc, true);


}

void
ServerContainerInterceptor::send_user_exception (Components::Extension::ContainerServerRequestInfo_ptr info) {
	std::cout << "COPI: send_user_exception: " << info->request_info()->operation() << "for id:" << std::endl;
	std::cout << "COPI: send_system_exception: " << info->request_info()->operation() << "for id: " << std::endl;
	org::coach::tracing::api::TraceEvent_var event = new org::coach::tracing::api::TraceEvent;

	// set time_stamp
	struct _timeb current_time;
	_ftime(&current_time);
	CORBA::LongLong tm = current_time.time;
	tm = tm * 1000 + current_time.millitm;
	event->time_stamp = tm;

	// set ineraction point
	event->interaction_point = org::coach::tracing::api::POA_OUT_EXCEPTION;
	event->trail_label= CORBA::string_dup ("");

	unsigned long event_number = executor_ -> get_new_event_number();
	char cnt[11];
	sprintf (cnt, "__%08x", event_number);
	std::string messageid = process_id_ + cnt;

	event->message_id = CORBA::string_dup (messageid.c_str());

	event->thread_id = CORBA::string_dup ("");
	
	event->trail_id	= CORBA::string_dup (messageid.c_str());
	
	event->event_counter  = event_number;
	event->op_name = CORBA::string_dup (CORBA::string_dup(info->request_info()->operation()));
	event->identity.object_instance_id		= CORBA::string_dup (info->port_id());
	event->identity.object_repository_id	= CORBA::string_dup ("TE");
	event->identity.cmp_name				= CORBA::string_dup (info->component_id());
	event->identity.cmp_type				= CORBA::string_dup ("UNKNOWN_COMPONENT_TYPE");
	event->identity.cnt_name				= CORBA::string_dup ("UNKNOW_CONTAINER_NAME");
	event->identity.cnt_type				= CORBA::string_dup ("UNKONWN_CONTAINER_TYPE");
	event->identity.node_name				= CORBA::string_dup (hostname_.c_str());
	event->identity.node_ip					= CORBA::string_dup (" e");
	event->identity.process_id				= CORBA::string_dup (process_id_.c_str());

//			Dynamic::ParameterList_var parameters = new Dynamic::ParameterList();
//			parameters->length(0);

	event->parameters.length(0);

	org::coach::tracing::api::TraceEvents_var trace = new org::coach::tracing::api::TraceEvents;
	trace->length(1);
	(*trace)[0] = event;
	context_-> get_connection_to_trace_server() -> receiveEvent(trace.in());

	CORBA::Any out_any;
	out_any <<= messageid.c_str();
	CORBA::OctetSeq_var data = executor_ -> get_cdr_codec_ptr() -> encode_value(out_any);

	IOP::ServiceContext out_sc;

	out_sc.context_id = 100;

	out_sc.context_data.length(data->length());

	memcpy(out_sc.context_data.get_buffer(), data->get_buffer(), data->length());

	info->request_info()->add_reply_service_context(out_sc, true);


}

void
ServerContainerInterceptor::rec_request_from_servant_locator(const char * operation)
{
	std::cout << "operation: " << operation << " from servant locator" << std::endl;
}

}; // namespace Qedo
