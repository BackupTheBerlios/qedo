dnl autoconf macroses for detecting Visibroker (http://www.borland.com)
dnl (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 2000
dnl $Id: RSSH_CHECK_VISIBROKER.m4,v 1.1 2002/10/07 07:17:02 tom Exp $
dnl
AC_DEFUN(RSSH_CHECK_VISIBROKER,[
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_CPP])dnl
AC_REQUIRE([AC_PROG_CXXCPP])dnl
AC_REQUIRE([AC_CXX_NAMESPACES])dnl

AC_CHECKING(for VISIBROKER)

visibroker=no

AC_ARG_WITH(visi, [visi: prefix to Visibroker installation (default: /usr/inprise/vbroker) ],\
            VISI_PREFIX=${with_visi} , VISI_PREFIX=/usr/inprise/vbroker )

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

if test ! $VISI_PREFIX = no
then

svCPPFLAGS=$CPPFLAGS
svCXXFLAGS=$CXXFLAGS
svCXXCPPFLAGS=$CXXCPPFLAGS
svLIBS=$LIBS
svRSSH_ROLLBACK=$rssh_rollback
rssh_rollback=true

CXXCPPFLAGS="$CXXCPPFLAGS  -I$VISI_PREFIX/include"
CPPFLAGS="$CPPFLAGS  -I$VISI_PREFIX/include"

AC_CHECK_HEADER( corba.h, visibroker=yes , visibroker=no )
else
 visibroker=no
fi

AC_CHECK_PROG(have_vbj, vbj, yes, no)


if test "x$visibroker" = xyes -a  "x$have_vbj" = "xyes"
then

RSSH_ENABLE_PTHREADS

AC_CHECK_LIB(socket,socket, LIBS="-lsocket $LIBS",,)
AC_CHECK_LIB(nsl,gethostbyname, LIBS="-lnsl $LIBS",,)

ORB_LIBS="-lorb_r -lvport_r"
ORB_LIBDIR="-L$VISI_PREFIX/lib"
LIBS="$ORB_LIBDIR $ORB_LIBS $LIBS"
         
AC_SUBST(VISI_PREFIX)

ORB_PREFIX=$VISI_PREFIX
AC_SUBST(VISI_PREFIX)

ORB=VisiBroker
AC_SUBST(ORB)


IDL=$VISI_PREFIX/bin/idl2cpp
AC_SUBST(IDL,$IDL)
IDLCXX=$VISI_PREFIX/bin/idl2cpp
AC_SUBST(IDLCXX,$IDLCXX)

IDLFLAGS="$IDLFLAGS -I$VISI_PREFIX/idl "
if test "$ac_cv_cxx_namespaces" = yes
then
  IDLFLAGS="$IDLFLAGS -namespace"
  AC_DEFINE(CORBA_MODULE_NAMESPACE_MAPPING,1,[Define if we use namespaces with visibroker])
  AC_DEFINE(CORBA_IS_CLASS,1,[Define if we use classes for CORBA under visibroker])
else
  AC_DEFINE(CORBA_MODULE_CLASS_MAPPING,1,[Define if we use classes for namespaces under visibroker])
fi

AC_SUBST(IDLFLAGS)

ORB_INCLUDE_PREFIX=$OB_PREFIX/include
AC_SUBST(ORB_INCLUDE_PREFIX)


IDL_CLN_H=_c.hh
IDL_CLN_H_SUFFIX=_c.hh
IDL_CLN_H1_SUFFIX=no
AC_SUBST(IDL_CLN_H,$IDL_CLN_H)
AC_SUBST(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)
AC_SUBST(IDL_CLN_H1_SUFFIX,$IDL_CLN_H1_SUFFIX)
AC_DEFINE_UNQUOTED(IDL_CLN_H,$IDL_CLN_H,[Define the suffix for c++ client include files])
AC_DEFINE_UNQUOTED(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX,[Define the suffix for c++ client include files])

IDL_CLN_CPP=_c.cc
IDL_CLN_CPP_SUFFIX=_c.cc
AC_SUBST(IDL_CLN_CPP,$IDL_CLN_CPP)
AC_SUBST(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP)
AC_DEFINE_UNQUOTED(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP,[Define the suffix for c++ client implementation  files])

IDL_CLN_O=_c.o 
IDL_CLN_OBJ_SUFFIX=_c.o 
AC_SUBST(IDL_CLN_O,$IDL_CLN_O)
AC_SUBST(IDL_CLN_OBJ_SUFFIX,$IDL_CLN_OBJ_SUFFIX)

IDL_SRV_H=_s.hh 
IDL_SRV_H_SUFFIX=_s.hh 
IDL_SRV_H1_SUFFIX=no 
AC_SUBST(IDL_SRV_H,$IDL_SRV_H)
AC_SUBST(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)
AC_SUBST(IDL_SRV_H1_SUFFIX,$IDL_SRV_H_SUFFIX)
AC_DEFINE_UNQUOTED(IDL_SRV_H_SUFFIX,$IDL_SRV_H,[Define the suffix for c++ server include files])

IDL_SRV_CPP=_s.cc
IDL_SRV_CPP_SUFFIX=_s.cc
AC_SUBST(IDL_SRV_CPP,$IDL_SRV_CPP)
AC_SUBST(IDL_SRV_CPP_SUFFIX,$IDL_SRV_CPP)

IDL_SRV_O=_s.o
IDL_SRV_OBJ_SUFFIX=_s.o
AC_SUBST(IDL_SRV_O,$IDL_SRV_O)
AC_SUBST(IDL_SRV_OBJ_SUFFIX,$IDL_SRV_O)

IDL_TIE_H_SUFFIX=no
IDL_TIE_H1_SUFFIX=no
IDL_TIE_CPP_SUFFIX=no
AC_SUBST(IDL_TIE_H_SUFFIX,$IDL_TIE_H_SUFFIX)
AC_SUBST(IDL_TIE_H1_SUFFIX,$IDL_TIE_H1_SUFFIX)
AC_SUBST(IDL_TIE_CPP_SUFFIX,$IDL_TIE_CPP_SUFFIX)


CORBA_H='corba.h'
AC_DEFINE_UNQUOTED(CORBA_H,<$CORBA_H>,[Define the name of the CORBA include file])

COSNAMING_H='CosNaming_c.h'
AC_DEFINE_UNQUOTED(COSNAMING_H,<$COSNAMING_H>,[Define the name of the COSNaming include file])
ORB_COSNAMING_LIB="-lcosnm_r"
AC_SUBST(ORB_COSNAMING_LIB)

AC_DEFINE(CORBA_HAVE_POA,1,[Defined if the ORB implements POA])
AC_DEFINE(CORBA_SYSTEM_EXCEPTION_IS_STREAMBLE,1,[Defined if exeception could be pass to cout])
AC_DEFINE(CORBA_ORB_HAVE_NO_DESTROY,1,[Defined if the ORB has no destroy operation])
HAVE_ORB_IDL=1
AC_SUBST(HAVE_ORB_IDL)
  
AC_DEFINE(VISIBROKER,1,[Defined if visibroker is present])

else

visibroker=no
CPPFLAGS=$svCPPFLAGS
CXXCPPFLAGS=$svCXXCPPFLAGS
CXXFLAGS=$svCXXFLAGS
LIBS=$svLIBS
eval $rssh_rollback
rssh_rollback=$svRSSH_ROLLBACK

fi

AC_LANG_RESTORE

AC_MSG_RESULT(Visibroker check result: $visibroker)

])dnl
dnl
