#pragma once
#include "IHandleEntity.h"
#define NUM_ENT_ENTRY_BITS         (11 + 2)
#define NUM_ENT_ENTRIES            (1 << NUM_ENT_ENTRY_BITS)
#define INVALID_EHANDLE_INDEX 0xffffffff
#define NUM_SERIAL_NUM_BITS        16 // (32 - num_ent_entry_bits)
#define NUM_SERIAL_NUM_SHIFT_BITS (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK             (( 1 << NUM_SERIAL_NUM_BITS) - 1)

class CBaseHandle {
public:
	CBaseHandle();
	CBaseHandle(const CBaseHandle& other);
	CBaseHandle(unsigned long value);
	CBaseHandle(int entry, int serial_number);

	void init(int entry, int serial_number);
	void term();

	// Even if this returns true, Get() still can return return a non-null value.
	// This just tells if the handle has been initted with any values.
	[[nodiscard]] bool is_valid() const;

	[[nodiscard]] int get_entry_index() const;
	[[nodiscard]] int get_serial_number() const;

	[[nodiscard]] int to_int() const;
	bool operator !=(const CBaseHandle& other) const;
	bool operator ==(const CBaseHandle& other) const;
	bool operator ==(const IHandleEntity* ent) const;
	bool operator !=(const IHandleEntity* ent) const;
	bool operator <(const CBaseHandle& other) const;

	// Assign a value to the handle.
	const CBaseHandle& operator=(const IHandleEntity* entity);
	const CBaseHandle& set(const IHandleEntity* entity);

	[[nodiscard]] IHandleEntity* get() const;
protected:
	unsigned long  m_index;
};

inline CBaseHandle::CBaseHandle() {
	m_index = INVALID_EHANDLE_INDEX;
}

inline CBaseHandle::CBaseHandle(const CBaseHandle& other) {
	m_index = other.m_index;
}

inline CBaseHandle::CBaseHandle(const unsigned long value) {
	m_index = value;
}

inline CBaseHandle::CBaseHandle(const int entry, const int serial_number) {
	init(entry, serial_number);
}

inline void CBaseHandle::init(const int entry, const int serial_number) {
	m_index = static_cast<unsigned long>(entry | serial_number << NUM_SERIAL_NUM_SHIFT_BITS);
}

inline void CBaseHandle::term() {
	m_index = INVALID_EHANDLE_INDEX;
}

inline bool CBaseHandle::is_valid() const {
	return m_index != INVALID_EHANDLE_INDEX;
}

inline int CBaseHandle::get_entry_index() const {
	// There is a hack here: due to a bug in the original implementation of the 
	// entity handle system, an attempt to look up an invalid entity index in 
	// certain cirumstances might fall through to the the mask operation below.
	// This would mask an invalid index to be in fact a lookup of entity number
	// NUM_ENT_ENTRIES, so invalid ent indexes end up actually looking up the
	// last slot in the entities array. Since this slot is always empty, the 
	// lookup returns NULL and the expected behavior occurs through this unexpected
	// route.
	// A lot of code actually depends on this behavior, and the bug was only exposed
	// after a change to NUM_SERIAL_NUM_BITS increased the number of allowable
	// static props in the world. So the if-stanza below detects this case and 
	// retains the prior (bug-submarining) behavior.
	if (!is_valid())
		return NUM_ENT_ENTRIES - 1;
	return m_index & ENT_ENTRY_MASK;
}

inline int CBaseHandle::get_serial_number() const {
	return m_index >> NUM_SERIAL_NUM_SHIFT_BITS;
}

inline int CBaseHandle::to_int() const {
	return static_cast<int>(m_index);
}

inline bool CBaseHandle::operator !=(const CBaseHandle& other) const {
	return m_index != other.m_index;
}

inline bool CBaseHandle::operator ==(const CBaseHandle& other) const {
	return m_index == other.m_index;
}

inline bool CBaseHandle::operator ==(const IHandleEntity* ent) const {
	return get() == ent;
}

inline bool CBaseHandle::operator !=(const IHandleEntity* ent) const {
	return get() != ent;
}

inline bool CBaseHandle::operator <(const CBaseHandle& other) const {
	return m_index < other.m_index;
}

inline const CBaseHandle& CBaseHandle::operator=(const IHandleEntity* entity) {
	return set(entity);
}

inline const CBaseHandle& CBaseHandle::set(const IHandleEntity* entity) {
	if (entity)
		*this = entity->GetRefEhandle();
	else
		m_index = INVALID_EHANDLE_INDEX;

	return *this;
}

template< class T >
class c_handle : public CBaseHandle {
public:

	c_handle();
	c_handle(int entry, int serial_number);
	c_handle(const CBaseHandle& handle);
	c_handle(T* pval);

	// The index should have come from a call to ToInt(). If it hasn't, you're in trouble.
	static c_handle<T> from_index(int index);

	T* get() const;
	void	set(const T* pval);

	operator T* ();
	operator T* () const;

	bool	operator !() const;
	bool	operator==(T* val) const;
	bool	operator!=(T* val) const;
	const CBaseHandle& operator=(const T* val);

	T* operator->() const;
};


// ----------------------------------------------------------------------- //
// Inlines.
// ----------------------------------------------------------------------- //

template<class T>
c_handle<T>::c_handle() {
}

template<class T>
c_handle<T>::c_handle(const int entry, const int serial_number) {
	init(entry, serial_number);
}

template<class T>
c_handle<T>::c_handle(const CBaseHandle& handle)
	: CBaseHandle(handle) {
}

template<class T>
c_handle<T>::c_handle(T* pObj) {
	term();
	Set(pObj);
}

template<class T>
c_handle<T> c_handle<T>::from_index(int index) {
	c_handle<T> ret;
	ret.m_index = index;
	return ret;
}


template<class T>
T* c_handle<T>::get() const {
	return (T*)CBaseHandle::get();
}

template<class T>
c_handle<T>::operator T* () {
	return get();
}

template<class T>
c_handle<T>::operator T* () const {
	return get();
}

template<class T>
bool c_handle<T>::operator !() const {
	return !get();
}

template<class T>
bool c_handle<T>::operator==(T* val) const {
	return get() == val;
}

template<class T>
bool c_handle<T>::operator!=(T* val) const {
	return get() != val;
}

template<class T>
void c_handle<T>::set(const T* pVal) {
	CBaseHandle::set(reinterpret_cast<const IHandleEntity*>(pVal));
}

template<class T>
const CBaseHandle& c_handle<T>::operator=(const T* val) {
	set(val);
	return *this;
}

template<class T>
T* c_handle<T>::operator -> () const {
	return get();
}