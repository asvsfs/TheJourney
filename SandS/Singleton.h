#pragma once
#include "stdafx.h"
#include <cstdlib>

class CriticalSection
{
   CRITICAL_SECTION m_cs;
public:
   CriticalSection() 
   {
      ::InitializeCriticalSection(&m_cs);
   }
   ~CriticalSection() 
   {
      ::DeleteCriticalSection(&m_cs);
   }
   void Lock()
   {
      ::EnterCriticalSection(&m_cs);
   }
   void Unlock()
   {
      ::LeaveCriticalSection(&m_cs);
   }
};

template<typename T>
class CSingleton {
public : 
    static T& Instance();
    static void Destroy();
	static CriticalSection _cs;

protected : 
    inline explicit CSingleton() { 
      //  assert(CSingleton::instance_ == 0); 
        CSingleton::instance_ = static_cast<T*>(this); 
    }
    inline ~CSingleton() { 
        CSingleton::instance_ = 0; 
    }

private : 
    static T* CreateInstance();
    static void ScheduleForDestruction(void (*)());
    static void DestroyInstance(T*);

private : 
    static T* instance_;

private : 
    inline explicit CSingleton(CSingleton const&) {}
    inline CSingleton& operator=(CSingleton const&) { return *this; }
};    //    end of class CSingleton


template<typename T>
 T& CSingleton<T>::Instance() {
    if ( CSingleton::instance_ == 0 ) {
		 _cs.Lock();
		 if ( CSingleton::instance_ == 0 ) {
			CSingleton::instance_ = CreateInstance();
			ScheduleForDestruction(CSingleton::Destroy);
		 }
		 _cs.Unlock();
    }
    return *(CSingleton::instance_);
}

template<typename T>
void CSingleton<T>::Destroy() {
    if ( CSingleton::instance_ != 0 ) {
        DestroyInstance(CSingleton::instance_);
        CSingleton::instance_ = 0;
    }
}

template<typename T>
inline  T* CSingleton<T>::CreateInstance() {
    return new T();
}

template<typename T>
inline void CSingleton<T>::ScheduleForDestruction(void (*pFun)()) {
	std::atexit(pFun);
}

template<typename T>
inline void CSingleton<T>::DestroyInstance(T* p) {
    delete p;
}

template<typename T>
 T* CSingleton<T>::instance_ = 0;

 // Static initializing
template <typename T> 
CriticalSection CSingleton<T>::_cs;