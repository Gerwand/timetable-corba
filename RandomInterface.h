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

#ifndef ___RandomInterface_h__
#define ___RandomInterface_h__


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

class RandomProvider;
typedef RandomProvider* RandomProvider_ptr;
typedef RandomProvider* RandomProviderRef;

extern OB::TypeCodeConst _tc_RandomProvider;

} // End of namespace Genetic

void OBDuplicate(Genetic::RandomProvider_ptr);
void OBRelease(Genetic::RandomProvider_ptr);

void OBMarshal(Genetic::RandomProvider_ptr, OB::OutputStreamImpl*);
void OBUnmarshal(Genetic::RandomProvider_ptr&, OB::InputStreamImpl*);

namespace Genetic
{

typedef OB::ObjVar< RandomProvider > RandomProvider_var;
typedef OB::ObjOut< RandomProvider > RandomProvider_out;

} // End of namespace Genetic

namespace OBStubImpl_Genetic
{

class RandomProvider;
typedef RandomProvider* RandomProvider_ptr;

} // End of namespace OBStubImpl_Genetic

void OBDuplicate(OBStubImpl_Genetic::RandomProvider_ptr);
void OBRelease(OBStubImpl_Genetic::RandomProvider_ptr);

namespace OBStubImpl_Genetic
{

typedef OB::ObjVar< RandomProvider > RandomProvider_var;

} // End of namespace OBStubImpl_Genetic

//
// IDL:Genetic:1.0
//
namespace Genetic
{

//
// IDL:Genetic/RandomSeq:1.0
//
class OBUnique_RandomSeq { };

typedef OB::FixSeq< ::CORBA::Long, OBUnique_RandomSeq > RandomSeq;
typedef OB::SeqVar< OB::FixSeq< ::CORBA::Long, OBUnique_RandomSeq > > RandomSeq_var;
typedef OB::SeqOut< OB::FixSeq< ::CORBA::Long, OBUnique_RandomSeq > > RandomSeq_out;
extern OB::TypeCodeConst _tc_RandomSeq;

struct OBInfo_RandomSeq : public OB::ConstructedInfo
{
    OBInfo_RandomSeq() { }

    virtual void free(void* p) const
    {
        delete (RandomSeq*)p;
    }

    virtual void* dup(const void* p) const
    {
        return new RandomSeq(*(const RandomSeq*)p);
    }

    virtual void marshal(const void*, OB::OutputStreamImpl*) const;
    virtual void unmarshal(void*, OB::InputStreamImpl*) const;
};

//
// IDL:Genetic/RandomProvider:1.0
//
class RandomProvider : virtual public ::CORBA::Object
{
    RandomProvider(const RandomProvider&);
    void operator=(const RandomProvider&);

protected:

    static const char* ids_[];

public:

    RandomProvider() { }
    virtual ~RandomProvider() { }

    typedef RandomProvider_ptr _ptr_type;
    typedef RandomProvider_var _var_type;

    static inline RandomProvider_ptr
    _duplicate(RandomProvider_ptr p)
    {
        if(p)
            p -> _add_ref();
        return p;
    }

    static inline RandomProvider_ptr
    _nil()
    {
        return 0;
    }

    static RandomProvider_ptr _narrow(::CORBA::Object_ptr);
    static RandomProvider_ptr _unchecked_narrow(::CORBA::Object_ptr);

    static RandomProvider_ptr _narrow(::CORBA::AbstractBase_ptr);
    static RandomProvider_ptr _unchecked_narrow(::CORBA::AbstractBase_ptr);

    static const char** _OB_staticIds();

    //
    // IDL:Genetic/RandomProvider/getRandomLong:1.0
    //
    virtual RandomSeq* getRandomLong(::CORBA::Long num) = 0;
};

} // End of namespace Genetic

//
// IDL:Genetic:1.0
//
namespace OBProxy_Genetic
{

//
// IDL:Genetic/RandomProvider:1.0
//
class RandomProvider : virtual public ::Genetic::RandomProvider,
                       virtual public OBCORBA::Object
{
    RandomProvider(const RandomProvider&);
    void operator=(const RandomProvider&);

protected:

    virtual OB::MarshalStubImpl_ptr _OB_createMarshalStubImpl();

public:

    RandomProvider() { }
    virtual ~RandomProvider() { }

    virtual const char** _OB_ids() const;

    //
    // IDL:Genetic/RandomProvider/getRandomLong:1.0
    //
    ::Genetic::RandomSeq* getRandomLong(::CORBA::Long num);
};

} // End of namespace OBProxy_Genetic

//
// IDL:Genetic:1.0
//
namespace OBStubImpl_Genetic
{

//
// IDL:Genetic/RandomProvider:1.0
//
class RandomProvider : virtual public OB::StubImplBase
{
    RandomProvider(const RandomProvider&);
    void operator=(const RandomProvider&);

protected:

    RandomProvider() { }

public:

    static inline RandomProvider_ptr
    _duplicate(RandomProvider_ptr p)
    {
        if(p)
            p -> _OB_incRef();
        return p;
    }

    static inline RandomProvider_ptr
    _nil()
    {
        return 0;
    }

    //
    // IDL:Genetic/RandomProvider/getRandomLong:1.0
    //
    virtual ::Genetic::RandomSeq* getRandomLong(::CORBA::Long num) = 0;
};

} // End of namespace OBStubImpl_Genetic

//
// IDL:Genetic:1.0
//
namespace OBMarshalStubImpl_Genetic
{

//
// IDL:Genetic/RandomProvider:1.0
//
class RandomProvider : 
    virtual public OBStubImpl_Genetic::RandomProvider,
    virtual public OB::MarshalStubImpl
{
    RandomProvider(const RandomProvider&);
    void operator=(const RandomProvider&);

protected:

    RandomProvider() { }
    friend class OBProxy_Genetic::RandomProvider;

public:

    //
    // IDL:Genetic/RandomProvider/getRandomLong:1.0
    //
    virtual ::Genetic::RandomSeq* getRandomLong(::CORBA::Long num);
};

} // End of namespace OBMarshalStubImpl_Genetic

//
// IDL:Genetic:1.0
//
namespace OBV_Genetic
{

} // End of namespace OBV_Genetic

//
// IDL:Genetic/RandomSeq:1.0
//
void operator<<=(::CORBA::Any&, Genetic::RandomSeq*);
void operator<<=(::CORBA::Any&, const Genetic::RandomSeq&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const Genetic::RandomSeq*&);

inline void
operator<<=(::CORBA::Any_var& any, Genetic::RandomSeq* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const Genetic::RandomSeq& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const Genetic::RandomSeq*& val)
{
    return any.in() >>= val;
}

//
// IDL:Genetic/RandomProvider:1.0
//
namespace CORBA
{

inline void
release(::Genetic::RandomProvider_ptr p)
{
    if(p)
        p -> _remove_ref();
}

inline Boolean
is_nil(::Genetic::RandomProvider_ptr p)
{
    return p == 0;
}

inline void
release(OBStubImpl_Genetic::RandomProvider_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

inline Boolean
is_nil(OBStubImpl_Genetic::RandomProvider_ptr p)
{
    return p == 0;
}

} // End of namespace CORBA

void operator<<=(::CORBA::Any&, Genetic::RandomProvider_ptr*);
void operator<<=(::CORBA::Any&, Genetic::RandomProvider_ptr);
CORBA::Boolean operator>>=(const ::CORBA::Any&, Genetic::RandomProvider_ptr&);

inline void
operator<<=(::CORBA::Any_var& any, Genetic::RandomProvider_ptr* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, Genetic::RandomProvider_ptr val)
{
    any.inout() <<= val;
}

inline CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, Genetic::RandomProvider_ptr& val)
{
    return any.in() >>= val;
}

#endif