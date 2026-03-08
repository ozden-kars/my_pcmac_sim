//
// Generated file, do not edit! Created by opp_msgtool 6.2 from src/pcmac/PCMACMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "PCMACMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(PCMACMessage)

PCMACMessage::PCMACMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

PCMACMessage::PCMACMessage(const PCMACMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

PCMACMessage::~PCMACMessage()
{
}

PCMACMessage& PCMACMessage::operator=(const PCMACMessage& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void PCMACMessage::copy(const PCMACMessage& other)
{
    this->isEmergency_ = other.isEmergency_;
    this->priority = other.priority;
    this->senderX = other.senderX;
    this->senderY = other.senderY;
    this->senderSpeed = other.senderSpeed;
    this->platoonSize = other.platoonSize;
    this->platoonAvgVelocity = other.platoonAvgVelocity;
    this->vehiclesBehind = other.vehiclesBehind;
}

void PCMACMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->isEmergency_);
    doParsimPacking(b,this->priority);
    doParsimPacking(b,this->senderX);
    doParsimPacking(b,this->senderY);
    doParsimPacking(b,this->senderSpeed);
    doParsimPacking(b,this->platoonSize);
    doParsimPacking(b,this->platoonAvgVelocity);
    doParsimPacking(b,this->vehiclesBehind);
}

void PCMACMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->isEmergency_);
    doParsimUnpacking(b,this->priority);
    doParsimUnpacking(b,this->senderX);
    doParsimUnpacking(b,this->senderY);
    doParsimUnpacking(b,this->senderSpeed);
    doParsimUnpacking(b,this->platoonSize);
    doParsimUnpacking(b,this->platoonAvgVelocity);
    doParsimUnpacking(b,this->vehiclesBehind);
}

bool PCMACMessage::isEmergency() const
{
    return this->isEmergency_;
}

void PCMACMessage::setIsEmergency(bool isEmergency)
{
    this->isEmergency_ = isEmergency;
}

double PCMACMessage::getPriority() const
{
    return this->priority;
}

void PCMACMessage::setPriority(double priority)
{
    this->priority = priority;
}

double PCMACMessage::getSenderX() const
{
    return this->senderX;
}

void PCMACMessage::setSenderX(double senderX)
{
    this->senderX = senderX;
}

double PCMACMessage::getSenderY() const
{
    return this->senderY;
}

void PCMACMessage::setSenderY(double senderY)
{
    this->senderY = senderY;
}

double PCMACMessage::getSenderSpeed() const
{
    return this->senderSpeed;
}

void PCMACMessage::setSenderSpeed(double senderSpeed)
{
    this->senderSpeed = senderSpeed;
}

int PCMACMessage::getPlatoonSize() const
{
    return this->platoonSize;
}

void PCMACMessage::setPlatoonSize(int platoonSize)
{
    this->platoonSize = platoonSize;
}

double PCMACMessage::getPlatoonAvgVelocity() const
{
    return this->platoonAvgVelocity;
}

void PCMACMessage::setPlatoonAvgVelocity(double platoonAvgVelocity)
{
    this->platoonAvgVelocity = platoonAvgVelocity;
}

int PCMACMessage::getVehiclesBehind() const
{
    return this->vehiclesBehind;
}

void PCMACMessage::setVehiclesBehind(int vehiclesBehind)
{
    this->vehiclesBehind = vehiclesBehind;
}

class PCMACMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_isEmergency,
        FIELD_priority,
        FIELD_senderX,
        FIELD_senderY,
        FIELD_senderSpeed,
        FIELD_platoonSize,
        FIELD_platoonAvgVelocity,
        FIELD_vehiclesBehind,
    };
  public:
    PCMACMessageDescriptor();
    virtual ~PCMACMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(PCMACMessageDescriptor)

PCMACMessageDescriptor::PCMACMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(PCMACMessage)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

PCMACMessageDescriptor::~PCMACMessageDescriptor()
{
    delete[] propertyNames;
}

bool PCMACMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PCMACMessage *>(obj)!=nullptr;
}

const char **PCMACMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PCMACMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PCMACMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int PCMACMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_isEmergency
        FD_ISEDITABLE,    // FIELD_priority
        FD_ISEDITABLE,    // FIELD_senderX
        FD_ISEDITABLE,    // FIELD_senderY
        FD_ISEDITABLE,    // FIELD_senderSpeed
        FD_ISEDITABLE,    // FIELD_platoonSize
        FD_ISEDITABLE,    // FIELD_platoonAvgVelocity
        FD_ISEDITABLE,    // FIELD_vehiclesBehind
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *PCMACMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "isEmergency",
        "priority",
        "senderX",
        "senderY",
        "senderSpeed",
        "platoonSize",
        "platoonAvgVelocity",
        "vehiclesBehind",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int PCMACMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "isEmergency") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "senderX") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "senderY") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "senderSpeed") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "platoonSize") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "platoonAvgVelocity") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "vehiclesBehind") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *PCMACMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_isEmergency
        "double",    // FIELD_priority
        "double",    // FIELD_senderX
        "double",    // FIELD_senderY
        "double",    // FIELD_senderSpeed
        "int",    // FIELD_platoonSize
        "double",    // FIELD_platoonAvgVelocity
        "int",    // FIELD_vehiclesBehind
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **PCMACMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PCMACMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PCMACMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PCMACMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PCMACMessage'", field);
    }
}

const char *PCMACMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PCMACMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        case FIELD_isEmergency: return bool2string(pp->isEmergency());
        case FIELD_priority: return double2string(pp->getPriority());
        case FIELD_senderX: return double2string(pp->getSenderX());
        case FIELD_senderY: return double2string(pp->getSenderY());
        case FIELD_senderSpeed: return double2string(pp->getSenderSpeed());
        case FIELD_platoonSize: return long2string(pp->getPlatoonSize());
        case FIELD_platoonAvgVelocity: return double2string(pp->getPlatoonAvgVelocity());
        case FIELD_vehiclesBehind: return long2string(pp->getVehiclesBehind());
        default: return "";
    }
}

void PCMACMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        case FIELD_isEmergency: pp->setIsEmergency(string2bool(value)); break;
        case FIELD_priority: pp->setPriority(string2double(value)); break;
        case FIELD_senderX: pp->setSenderX(string2double(value)); break;
        case FIELD_senderY: pp->setSenderY(string2double(value)); break;
        case FIELD_senderSpeed: pp->setSenderSpeed(string2double(value)); break;
        case FIELD_platoonSize: pp->setPlatoonSize(string2long(value)); break;
        case FIELD_platoonAvgVelocity: pp->setPlatoonAvgVelocity(string2double(value)); break;
        case FIELD_vehiclesBehind: pp->setVehiclesBehind(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PCMACMessage'", field);
    }
}

omnetpp::cValue PCMACMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        case FIELD_isEmergency: return pp->isEmergency();
        case FIELD_priority: return pp->getPriority();
        case FIELD_senderX: return pp->getSenderX();
        case FIELD_senderY: return pp->getSenderY();
        case FIELD_senderSpeed: return pp->getSenderSpeed();
        case FIELD_platoonSize: return pp->getPlatoonSize();
        case FIELD_platoonAvgVelocity: return pp->getPlatoonAvgVelocity();
        case FIELD_vehiclesBehind: return pp->getVehiclesBehind();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PCMACMessage' as cValue -- field index out of range?", field);
    }
}

void PCMACMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        case FIELD_isEmergency: pp->setIsEmergency(value.boolValue()); break;
        case FIELD_priority: pp->setPriority(value.doubleValue()); break;
        case FIELD_senderX: pp->setSenderX(value.doubleValue()); break;
        case FIELD_senderY: pp->setSenderY(value.doubleValue()); break;
        case FIELD_senderSpeed: pp->setSenderSpeed(value.doubleValue()); break;
        case FIELD_platoonSize: pp->setPlatoonSize(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_platoonAvgVelocity: pp->setPlatoonAvgVelocity(value.doubleValue()); break;
        case FIELD_vehiclesBehind: pp->setVehiclesBehind(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PCMACMessage'", field);
    }
}

const char *PCMACMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr PCMACMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PCMACMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PCMACMessage *pp = omnetpp::fromAnyPtr<PCMACMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PCMACMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

