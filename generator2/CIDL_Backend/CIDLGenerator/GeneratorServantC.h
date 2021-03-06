/*****************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                     */
/*                                                                           */
/* Copyright (c) 2002/2003 by the Qedo Team                                  */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/

#ifndef __GENERATOR_SERVANTC_H__
#define __GENERATOR_SERVANTC_H__

#include "CPPBase.h"
#include "Printer.h"
#include "GeneratorPersistenceC.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>


namespace QEDO_CIDL_Generator 
{


class GeneratorServantC : public virtual CPPBase 
{

private:

	std::string					class_name_;
	std::string					executor_name_;
	std::string					interface_name_;
	std::string					strName_;
	std::string					strAbsHomeName_;
	std::string					strContent_;
	std::string					strNamespace_;
	Printer						out;
	CIDL::CompositionDef_var	composition_;
	IR__::ComponentDef_var		component_;
	IR__::HomeDef_var			home_;
	IR__::StorageHomeDef_var	storagehome_;
	std::set<std::string>		recursion_set_;
	std::list<IR__::ValueDef_var>	lValueTypes_;
	GeneratorPersistenceC*      pc_generator_;

	void check_for_generation(IR__::Contained_ptr item);
	CORBA::ULong calculate_align (CORBA::ULong, CORBA::ULong);
	void generate_marshal_code (IR__::IDLType_ptr, std::string&, CORBA::ULong);
	void generate_unmarshal_code (IR__::IDLType_ptr, std::string&, CORBA::ULong);
	void resolve_atomic_streamtypes(IR__::StreamTypeDef_ptr streamtype, IR__::StreamTypeDefSeq& atomic_streamtypes);

	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doComposition(CIDL::CompositionDef_ptr composition);
	void doComponent(IR__::ComponentDef_ptr component);
	void doProvides(IR__::ProvidesDef_ptr provides, IR__::ComponentDef_ptr component);
	void doUses(IR__::UsesDef_ptr uses, IR__::ComponentDef_ptr component);
	void doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component);
	void doSource(IR__::SourceDef_ptr source, IR__::ComponentDef_ptr component);
	void doEmits(IR__::EmitsDef_ptr emits, IR__::ComponentDef_ptr component);
	void doPublishes(IR__::PublishesDef_ptr publishes, IR__::ComponentDef_ptr component);
	void doConsumes(IR__::ConsumesDef_ptr consumes, IR__::ComponentDef_ptr component);
	void doHome(IR__::HomeDef_ptr home);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);

	void genFacetServants(IR__::ComponentDef_ptr component);
	void genSourceServants(IR__::ComponentDef_ptr component);
	void genConsumerServants(IR__::ComponentDef_ptr component);
	void genContextServantBegin(IR__::ComponentDef_ptr component);
	void genContextServant(IR__::ComponentDef_ptr component,CIDL::LifecycleCategory lc );

	void genProxyStubServantBegin(IR__::ComponentDef_ptr component);
	void genProxyStubServant(IR__::ComponentDef_ptr component);
	void proxyInterface(IR__::UsesDef_ptr uses, IR__::InterfaceDef_ptr intf);
	void proxyOperation(IR__::UsesDef_ptr uses, IR__::OperationDef_ptr operation);
	void proxyAttribute(IR__::UsesDef_ptr uses, IR__::AttributeDef_ptr attribute);

	void genComponentServantBegin(IR__::ComponentDef_ptr component);
	void genComponentServant(IR__::ComponentDef_ptr component);
	void genHomeServantBegin(IR__::HomeDef_ptr home, CIDL::LifecycleCategory lc);
	void genHomeServant(IR__::HomeDef_ptr home, CIDL::LifecycleCategory lc);
	void genFacetRegistration(IR__::ComponentDef_ptr comp);
	void genReceptacleRegistration(IR__::ComponentDef_ptr comp);
	void genEmitterRegistration(IR__::ComponentDef_ptr comp);
	void genPublisherRegistration(IR__::ComponentDef_ptr comp);
	void genConsumerRegistration(IR__::ComponentDef_ptr comp);
	void genSinkRegistration(IR__::ComponentDef_ptr comp);
	void genSourceRegistration(IR__::ComponentDef_ptr comp);
	void gen_supported_home_interface(IR__::InterfaceDef_ptr interf);

	void generate_component(IR__::ComponentDef* a_component,CIDL::LifecycleCategory lc );

	// for persistence
	void genTableForAbsStorageHome();
	void genTableForStorageHome(IR__::StorageHomeDef_ptr storagehome);
	void genTableForHome(IR__::HomeDef_ptr home);
	std::string genSQLLine(std::string strName, std::string strContent, bool end, bool comma, bool space, bool func=false);
	std::string genSQLLine(std::string strContent, bool end, bool comma, bool space, bool func=false);
	
public:

	GeneratorServantC(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorServantC();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
