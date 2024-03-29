// **********************************************************************
//
// Generated by the ORBacus IDL-to-C++ Translator
//
// Copyright (c) 2005
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

// Version: 4.3.3

#include <OB/CORBAServer.h>
#include <RandomInterface_skel.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

//
// IDL:Genetic:1.0
//

//
// IDL:Genetic/RandomProvider/getRandomLong:1.0
//
void
POA_Genetic::RandomProvider::_OB_op_getRandomLong(OB::Upcall_ptr _ob_up)
{
    ::CORBA::Long _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    _ob_a0 = _ob_in -> read_long();
    _OB_postUnmarshal(_ob_up);
    ::Genetic::RandomSeq_var _ob_r = getRandomLong(_ob_a0);
    _OB_postinvoke(_ob_up);
    OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_up);
    ::CORBA::ULong _ob_len0 = _ob_r.in().length();
    _ob_out -> write_ulong(_ob_len0);
    _ob_out -> write_long_array(_ob_r.in().get_buffer(), _ob_len0);
    _OB_postMarshal(_ob_up);
}

//
// IDL:Genetic/RandomProvider:1.0
//
::CORBA::Boolean
POA_Genetic::RandomProvider::_is_a(const char* type)
    throw(::CORBA::SystemException)
{
    const char** _ob_ids = Genetic::RandomProvider::_OB_staticIds();
    for(::CORBA::ULong _ob_i = 0; _ob_ids[_ob_i] != 0; ++_ob_i)
        if(strcmp(type, _ob_ids[_ob_i]) == 0)
            return true;

    return false;
}

::CORBA::RepositoryId
POA_Genetic::RandomProvider::_primary_interface(const PortableServer::ObjectId&,
                                                PortableServer::POA_ptr)
{
    return ::CORBA::string_dup(Genetic::RandomProvider::_OB_staticIds()[0]);
}

Genetic::RandomProvider_ptr
POA_Genetic::RandomProvider::_this()
{
    ::CORBA::Object_var obj = _OB_createReference();
    Genetic::RandomProvider_var result = Genetic::RandomProvider::_narrow(obj);
    return result._retn();
}

OB::DirectStubImpl_ptr
POA_Genetic::RandomProvider::_OB_createDirectStubImpl(PortableServer::POA_ptr poa,
                                                      const PortableServer::ObjectId& oid)
{
    return new OBDirectStubImpl_Genetic::RandomProvider(poa, oid, this);
}

void
POA_Genetic::RandomProvider::_OB_dispatch(OB::Upcall_ptr _ob_up)
{
    static const char* _ob_names[] =
    {
        "getRandomLong"
    };
    static const ::CORBA::ULong _ob_numNames = 1;

    switch(_OB_findOperation(_ob_up, _ob_names, _ob_numNames))
    {
    case 0: // getRandomLong
        _OB_op_getRandomLong(_ob_up);
        return;
    }

    _OB_dispatchBase(_ob_up);
}

//
// IDL:Genetic/RandomProvider:1.0
//
OBDirectStubImpl_Genetic::RandomProvider::RandomProvider(
    PortableServer::POA_ptr poa,
    const PortableServer::ObjectId& oid,
    PortableServer::ServantBase* servant)
#ifdef HAVE_VCPLUSPLUS_BUGS
{
    _ob_initialize(poa, oid, servant);
}
#else
    : OB::DirectStubImpl(poa, oid, servant)
{
}
#endif

//
// IDL:Genetic/RandomProvider/getRandomLong:1.0
//
::Genetic::RandomSeq*
OBDirectStubImpl_Genetic::RandomProvider::getRandomLong(::CORBA::Long _ob_a0)
{
    OB::InvocationHandler _ob_handler(this, "getRandomLong");
    return dynamic_cast<POA_Genetic::RandomProvider*>(_ob_servant_) -> getRandomLong(_ob_a0);
}
