#pragma once

#include <CoreFoundation/CoreFoundation.h>

template<class T>
class cfref_ptr
{
public:
	cfref_ptr()
		: obj_(NULL)
	{}

	cfref_ptr(T obj)
		: obj_(obj)
	{
		if (obj_) {
			CFRetain(obj_);
		}
	}

	~cfref_ptr()
	{
		if (obj_) {
			CFRelease(obj_);
		}
	}

	cfref_ptr(cfref_ptr const& other)
		: obj_(other.obj_)
	{
		if (obj_) {
			CFRetain(obj_);
		}
	}

	cfref_ptr(cfref_ptr&& other)
		: obj_(other.obj_)
	{
		other.obj_ = NULL;
	}

	cfref_ptr& operator = (cfref_ptr const& other)
	{
		cfref_ptr tmp(other);
		tmp.swap(*this);
		return *this;
	}

	cfref_ptr& operator = (cfref_ptr&& other)
	{
		obj_ = other.obj_;
		other.obj_ = NULL;
		return *this;
	}

	bool boolean_test() const
	{
		return !!obj_;
	}

	T get()
	{
		return obj_;
	}

	T release()
	{
		T ret = obj_;
		obj_ = NULL;
		return ret;
	}

	void swap(cfref_ptr& other)
	{
		std::swap(obj_, other.obj_);
	}

	void reset(T obj = NULL)
	{
		if (obj_) {
			CFRelease(obj_);
		}
		obj_ = obj;
		if (obj_) {
			CFRetain(obj_);
		}
	}

private:
	T obj_;
};

