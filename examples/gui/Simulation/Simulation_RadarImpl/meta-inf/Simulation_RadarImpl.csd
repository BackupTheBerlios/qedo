<?xml version = '1.0' ?>
<!DOCTYPE softpkg PUBLIC "-//OMG//DTD Software Package Descriptor" "http://qedo.berlios.de/softpkg.dtd">

<softpkg name="RadarImpl_softpkg" version="1,0">

    <pkgtype>CORBA Component</pkgtype>
    <title></title>
    <author><name>unknown author</name></author>
    <description></description>
    <license href="" />
    <idl id="IDL:Simulation/RadarHome:1.0">
        <fileinarchive name="simdemo.cidl"/>
    </idl>
    
    <implementation id="UUID-4CDF428E-6542-42A8-A576-4E5358B2D786">
        <os name="WIN" />
        <processor name="x86" />
        <compiler name="VC++" version="7,0" />
        <programminglanguage name="C++" />
        <dependency type="DLL"><localfile name="jtcd.dll"/></dependency>
        <dependency type="DLL"><localfile name="obd.dll"/></dependency>
        <descriptor type="CORBA-Component">
            <fileinarchive name="meta-inf/Simulation_RadarImpl.ccd" />
        </descriptor>
        <code type="DLL">
            <fileinarchive name="Simulation_RadarImpl.dll"/>
            <entrypoint>create_RadarHomeE</entrypoint>
            <usage>executor</usage>
        </code>
        <code type="DLL">
            <fileinarchive name="Simulation_RadarImpl_SERVANT.dll"/>
            <entrypoint>create_RadarHomeS</entrypoint>
            <usage>servant</usage>
        </code>
    </implementation>
</softpkg>
