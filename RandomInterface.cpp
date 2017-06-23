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

#include <OB/CORBAClient.h>
#include <RandomInterface.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

namespace Genetic
{

::OB::TypeCodeConst _tc_RandomSeq(
"017749f01500000048000000017f00001a00000049444c3a47656e657469632f52616e646f6d5"
"365713a312e300000000a00000052616e646f6d536571000000130000000c00000001ffffff03"
"00000000000000"
);

::OB::TypeCodeConst _tc_RandomProvider(
"017749f00e0000003b000000017f00001f00000049444c3a47656e657469632f52616e646f6d5"
"0726f76696465723a312e3000000f00000052616e646f6d50726f766964657200"
);

} // End of namespace Genetic

//
// IDL:Genetic/RandomSeq:1.0
//
void
Genetic::OBInfo_RandomSeq::marshal(const void* _ob_v, OB::OutputStreamImpl* _ob_out) const
{
    const ::Genetic::RandomSeq& _ob_seq = *(const ::Genetic::RandomSeq*)_ob_v;
    ::CORBA::ULong _ob_len0 = _ob_seq.length();
    _ob_out -> write_ulong(_ob_len0);
    _ob_out -> write_long_array(_ob_seq.get_buffer(), _ob_len0);
}

void
Genetic::OBInfo_RandomSeq::unmarshal(void* _ob_v, OB::InputStreamImpl* _ob_in) const
{
    ::Genetic::RandomSeq& _ob_seq = *(::Genetic::RandomSeq*)_ob_v;
    ::CORBA::ULong _ob_len0 = _ob_in -> read_ulong();
    _ob_seq.length(_ob_len0);
    _ob_in -> read_long_array(_ob_seq.get_buffer(), _ob_len0);
}

void
operator<<=(::CORBA::Any& any, Genetic::RandomSeq* v)
{
    static const Genetic::OBInfo_RandomSeq info;
    any.replace(Genetic::_tc_RandomSeq, v, true, &info);
}

void
operator<<=(::CORBA::Any& any, const Genetic::RandomSeq& v)
{
    any <<= new Genetic::RandomSeq(v);
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, const Genetic::RandomSeq*& v)
{
    if(any.check_type(Genetic::_tc_RandomSeq))
    {
        if(!any.info())
        {
            OB::InputStream_var _ob_in = any.create_input_stream();
            Genetic::RandomSeq* val = new Genetic::RandomSeq;
            ::CORBA::ULong _ob_len0 = _ob_in -> read_ulong();
            (*val).length(_ob_len0);
            _ob_in -> read_long_array((*val).get_buffer(), _ob_len0);
            (::CORBA::Any&)any <<= val;
        }

        v = (Genetic::RandomSeq*)any.value();
        return true;
    }
    else
        return false;
}

//
// IDL:Genetic/RandomProvider:1.0
//
const char* Genetic::RandomProvider::ids_[] =
{
    "IDL:Genetic/RandomProvider:1.0",
    0
};

void
OBDuplicate(Genetic::RandomProvider_ptr p)
{
    if(p)
        p -> _add_ref();
}

void
OBRelease(Genetic::RandomProvider_ptr p)
{
    if(p)
        p -> _remove_ref();
}

Genetic::RandomProvider_ptr
Genetic::RandomProvider::_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        RandomProvider_ptr v = 
            dynamic_cast< RandomProvider_ptr >(p);
        if(v)
            return _duplicate(v);

        if(p -> _is_a(ids_[0]))
        {
            OBProxy_Genetic::RandomProvider* val = new OBProxy_Genetic::RandomProvider;
            val -> _OB_copyFrom(p);
            return val;
        }
    }

    return _nil();
}

Genetic::RandomProvider_ptr
Genetic::RandomProvider::_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        RandomProvider_ptr v =
            dynamic_cast< RandomProvider_ptr >(p);
        if(v)
            return _duplicate(v);

        ::CORBA::Object_var obj = p -> _to_object();
        return _narrow(obj);
    }
    return _nil();
}

Genetic::RandomProvider_ptr
Genetic::RandomProvider::_unchecked_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        RandomProvider_ptr v =
            dynamic_cast< RandomProvider_ptr >(p);
        if(v)
            return _duplicate(v);

        OBProxy_Genetic::RandomProvider* val = new OBProxy_Genetic::RandomProvider;
        val -> _OB_copyFrom(p);
        return val;
    }

    return _nil();
}

Genetic::RandomProvider_ptr
Genetic::RandomProvider::_unchecked_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        ::CORBA::Object_var obj = p -> _to_object();
        return _unchecked_narrow(obj);
    }
    return _nil();
}

const char**
Genetic::RandomProvider::_OB_staticIds()
{
    return ids_;
}

void
OBMarshal(Genetic::RandomProvider_ptr _ob_v, OB::OutputStreamImpl* _ob_out)
{
    _ob_out -> write_Object(_ob_v);
}

void
OBUnmarshal(Genetic::RandomProvider_ptr& _ob_v, OB::InputStreamImpl* _ob_in)
{
    Genetic::RandomProvider_var old = _ob_v;
    ::CORBA::Object_var p = _ob_in -> read_Object();

    if(!::CORBA::is_nil(p))
    {
        OBProxy_Genetic::RandomProvider* _ob_obj = new OBProxy_Genetic::RandomProvider;
        _ob_obj -> _OB_copyFrom(p);
        _ob_v = _ob_obj;
    }
    else
        _ob_v = Genetic::RandomProvider::_nil();
}

void
operator<<=(::CORBA::Any& any, Genetic::RandomProvider_ptr* v)
{
    any.replace(Genetic::_tc_RandomProvider, (::CORBA::Object_ptr)*v, true);
}

void
operator<<=(::CORBA::Any& any, Genetic::RandomProvider_ptr v)
{
    Genetic::RandomProvider_ptr val = Genetic::RandomProvider::_duplicate(v);
    any <<= &val;
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, Genetic::RandomProvider_ptr& v)
{
    if(any.check_type(Genetic::_tc_RandomProvider))
    {
        ::CORBA::Object_ptr val = (::CORBA::Object_ptr)any.value();

        if(!::CORBA::is_nil(val))
        {
            if(!(v = dynamic_cast< Genetic::RandomProvider_ptr >(val)))
            {
                OBProxy_Genetic::RandomProvider* obj = new OBProxy_Genetic::RandomProvider;
                obj -> _OB_copyFrom(val);
                v = obj;
                (::CORBA::Any&)any <<= &v;
            }
        }
        else
            v = Genetic::RandomProvider::_nil();

        return true;
    }
    else
        return false;
}

//
// IDL:Genetic/RandomProvider:1.0
//
OB::MarshalStubImpl_ptr
OBProxy_Genetic::RandomProvider::_OB_createMarshalStubImpl()
{
    return new OBMarshalStubImpl_Genetic::RandomProvider;
}

const char**
OBProxy_Genetic::RandomProvider::_OB_ids() const
{
    return ::Genetic::RandomProvider::ids_;
}

//
// IDL:Genetic/RandomProvider/getRandomLong:1.0
//
::Genetic::RandomSeq*
OBProxy_Genetic::RandomProvider::getRandomLong(::CORBA::Long _ob_a0)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_Genetic::RandomProvider_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_Genetic::RandomProvider_ptr>(_ob_stubImplBase.in());
            return _ob_stubImpl -> getRandomLong(_ob_a0);
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:Genetic/RandomProvider:1.0
//
void
OBDuplicate(OBStubImpl_Genetic::RandomProvider_ptr p)
{
    if(p)
        p -> _OB_incRef();
}

void
OBRelease(OBStubImpl_Genetic::RandomProvider_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

//
// IDL:Genetic/RandomProvider/getRandomLong:1.0
//
::Genetic::RandomSeq*
OBMarshalStubImpl_Genetic::RandomProvider::getRandomLong(::CORBA::Long _ob_a0)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("getRandomLong", true);
        try
        {
            OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_down);
            try
            {
                _ob_out -> write_long(_ob_a0);
            }
            catch(const ::CORBA::SystemException& _ob_ex)
            {
                _OB_marshalEx(_ob_down, _ob_ex);
            }
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            bool _ob_uex;
            OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_down, _ob_uex);
            if(_ob_uex)
            {
                _OB_postUnmarshal(_ob_down);
            }
            else
            {
                ::Genetic::RandomSeq_var _ob_r;
                try
                {
                    _ob_r = new ::Genetic::RandomSeq;
                    ::CORBA::ULong _ob_len0 = _ob_in -> read_ulong();
                    _ob_r -> length(_ob_len0);
                    _ob_in -> read_long_array(_ob_r -> get_buffer(), _ob_len0);
                }
                catch(const ::CORBA::SystemException& _ob_ex)
                {
                    _OB_unmarshalEx(_ob_down, _ob_ex);
                }
                _OB_postUnmarshal(_ob_down);
                return _ob_r._retn();
            }
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}
