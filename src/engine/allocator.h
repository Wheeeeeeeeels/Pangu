//
// Created by wheels on 2022/9/16.
// 空间配置器实现: 内存开辟与释放，对象构造与析构
#include <cstdio>
#include "pangu.h"


#ifndef PANGU_ALLOCATOR_H
#define PANGU_ALLOCATOR_H

#define PANGU_NEW(allocator, ...) new (PANGU::NewPlaceholder(), (allocator).allocate_aligned(sizeof(__VA_ARGS__), alignof(__VA_ARGS__))) __VA_ARGS__
#define PANGU_DELETE(allocator,var) (allocator).deleteObject(var);
namespace Pangu{struct NewPlaceHolder{};}
// void* 可以指向任意类型的地址,void* 只有强制类型转换之后才可以取值
// 重载 new运算符
inline void* operator new(size_t,Pangu::NewPlaceHolder,void* where){return where;}
// 重载delete运算符
inline void operator delete(void*,Pangu::NewPlaceHolder,void*){}

namespace Pangu{

struct  PANGU_ENGINE_API IAllocator{
       virtual ~IAllocator(){}
	   virtual  bool isDebug() const {return false;}

	   virtual void* allocate(size_t size) = 0;
	   virtual void deallocate(void* ptr) = 0;
	   virtual void* reallocate(void* ptr,size_t size) = 0;

	   virtual void* allocate_aligned(size_t size,size_t align) = 0;
	   virtual void deallocate_aligned(void* ptr) = 0;
	   virtual void* reallocate_aligned(void* ptr,size_t size) = 0;

	   template <class T> void deleteObjects(T* ptr){
		   if(ptr){
			   ptr->~T();
			   deallocate_aligned(ptr);
		   }
	   }
};

template<typename T>
struct Local{
	~Local(){
		if(obj) obj->~T();
	}
    void operator=(const Local&) = delete;

    template<typename... Args>
    void create(Args&&... args){
        ASSERT(!obj);
        obj = new (NewPlaceHolder(),mem) T(static_cast<Args&&>(args)...);
    }
    void destroy(){
        ASSERT(obj);
        obj->~T();
        obj = nullptr;
    }
    T& operator*() {ASSERT(obj); return *obj; }
    T* operator->() {ASSERT(obj); return obj; }
    T* get() {return obj;}
private:
	alignas(T) pangu::u8 mem[sizeof (T)];
	T* obj = nullptr;
};
// re-implementation the UniquePtr
template<typename T>
struct UniquePtr{
    UniquePtr() : m_ptr(nullptr),m_allocator(nullptr){}
    UniquePtr(T* obj,IAllocator* allocator):m_ptr(obj),m_allocator(allocator){}

    template<typename T2>
    UniquePtr( UniquePtr<T2>&& rhs){
        *this = static_cast<UniquePtr<T2>&&>(rhs);
    }
    ~UniquePtr(){
        if(m_ptr){
           // PANGU_DELETE(*m_allocator,m_prt);
        }
    }

private:
    T* m_ptr = nullptr;
    IAllocator* m_allocator = nullptr;
};

}


#endif // PANGU_ALLOCATOR_H
