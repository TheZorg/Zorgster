#ifndef ZORGSTER_SINGLETON_HPP
#define ZORGSTER_SINGLETON_HPP
#include <iostream>
#include <cassert>

template <typename T>
class Singleton {
public:
    Singleton()
    {
        assert(!mSingleton);
     	mSingleton = static_cast<T*>(this);
    }

    virtual ~Singleton()
    {
        assert(mSingleton);
        mSingleton = NULL;
    }

    static T& GetSingleton()
    {
        assert(mSingleton);
        return *mSingleton;
    }

    static T* GetSingletonPtr()
    {
        assert(mSingleton);
        return mSingleton;
    }

private:
    static T* mSingleton;
};

template <typename T> T* Singleton<T>::mSingleton = NULL;

#endif
