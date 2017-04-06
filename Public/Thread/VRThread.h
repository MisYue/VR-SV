#ifndef _VRTHREAD_H_
#define _VRTHREAD_H_

#include <boost/thread/thread.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/bind.hpp>

#define AUTO_MUTEX_NAME mutex
#define AUTO_MUTEX boost::mutex
#define VR_AUTO_MUTEX mutable boost::recursive_mutex AUTO_MUTEX_NAME;
#define VR_MUTEX_AUTO boost::recursive_mutex::scoped_lock scopedLock(AUTO_MUTEX_NAME);
#define VRSOFT_MUTEX(mutexname) mutable boost::recursive_mutex mutexname
#define VRSOFT_STATIC_MUTEX(mutexname) static boost::recursive_mutex mutexname
#define VRSOFT_LOCK_MUTEX(mutexname) boost::recursive_mutex::scoped_lock autolock(mutexname)
#define VR_MUTEX_AUTO_BOOST boost::recursive_mutex mutexname; boost::recursive_mutex::scoped_lock scopedLock(mutexname)

//#define VR_MUTEX_AUTO VR_MUTEX_AUTO_BOOST

#endif