//
// Created by Administrator on 2022/9/15.
//

#pragma once

// 方便移植，当前系统位于windows操作系统时
#ifndef _WIN32
	// 处理信号
	#include <signal.h>
#endif

// 自定义ASSERT宏，方便对错误信息进行分析
#ifndef ASSERT
	#ifdef PANGU_DEBUG
		#ifdef _WIN32
			// 可以对程序添加断点进行调试
			#define PANGU_DEBUG_BREAK() __debugbreak()
		#else
			#define PANGU_DEBUG_BREAK()  raise(SIGTRAP)
		#endif
		#define ASSERT(x) do { const volatile bool lumix_assert_b____ = !(x); if(lumix_assert_b____) PANGU_DEBUG_BREAK(); } while (false)
	#else
		#if defined _MSC_VER && !defined __clang__
			#define ASSERT(x) __assume(x)
		#else
			#define ASSERT(x) { false ? (void)(x) : (void)0; }
		#endif
	#endif
#endif

enum { PANGU_MAX_PATH = 260 };

namespace pangu {

// primitive_alias 重新命名
using i8 = char;
using u8 = unsigned char;
using i16 = short;
using u16 = unsigned short;
using i32 = int;
using u32 = unsigned int;
#ifdef _WIN32
using i64 = long long;
using u64 = unsigned long long;
#else
using i64 = long;
using u64 = unsigned long;
#endif
// (void*)的大小
using uintptr = u64;
// 编译时断言
static_assert(sizeof(uintptr) == 8, "Incorrect size of uintptr");
static_assert(sizeof(i64) == 8, "Incorrect sizeof i64");
static_assert(sizeof(i32) == 4, "Incorrect sizeof i32");
static_assert(sizeof(i16) == 2, "Incorrect sizeof i16");
static_assert(sizeof(i8) == 1, "Incorrect sizeof i8");

struct EntityRef;

struct EntityPtr {
	i32 index;
	EntityPtr() : index(-1) {}
	explicit EntityPtr(i32 index) : index(index){};
	bool operator==(const EntityPtr& rhs) const { return rhs.index == index; }
	bool operator<(const EntityPtr& rhs) const { return rhs.index < index; }
	bool operator>(const EntityPtr& rhs) const { return rhs.index > index; }
	bool operator!=(const EntityPtr& rhs) const { return rhs.index != index; }
	bool isValid() const { return index > 0; }
	// TODO
	inline explicit operator EntityRef() const;
	inline EntityRef operator*() const;
};

struct EntityRef {
	i32 index;
	bool operator==(const EntityRef& rhs) const { return rhs.index == index; }
	bool operator<(const EntityRef& rhs) const { return rhs.index < index; }
	bool operator>(const EntityRef& rhs) const { return rhs.index > index; }
	bool operator!=(const EntityRef& rhs) const { return rhs.index != index; }
	operator EntityRef() { return EntityRef{index}; }
};

struct ComponentType {
	enum { MAX_TYPES_COUNT = 64 };
	i32 index;
	bool operator==(const ComponentType& rhs) const {
		return rhs.index == index;
	}
	bool operator<(const ComponentType& rhs) const { return rhs.index < index; }
	bool operator>(const ComponentType& rhs) const { return rhs.index > index; }
	bool operator!=(const ComponentType& rhs) const {
		return rhs.index != index;
	}
};

const ComponentType INVALID_COMPONENT_TYPE = {-1};
const EntityPtr INVALID_ENTITY = EntityPtr{-1};
// TODO
template <typename T, u32 count>
constexpr u32 lengthOf(const T (&)[count]) {
	return count;
};

enum {
	RED = 0xff0000ff,
	GREEN = 0xff00ff00,
	BLUE = 0xffff0000,
	BLACK = 0xff000000,
	WHITE = 0xffffffff
};

#pragma pack()

#ifdef _WIN32
	// 将dll内部类进行导出,表明这些东西可以被外部函数使用
	#define PANGU_LIBRARY_EXPORT __declspec(dllexport)
	// 将dll内部类进行导入
	#define PANGU_LIBRARY_IMPORT __declspec(dllimport)
	// __forceinline 代替inline
	#define PANGU_FORCE_INLINE __forceinline
// 只用于限定指针，表明本指针是访问一个数据对象的惟一且初始的方式
	#define PANGU_RESTRICT __restrict
#else
	// GCC中的visibility属性
	#define PANGU_LIBRARY_EXPORT __attribute__((visibility("default")))
	#define PANGU_LIBRARY_IMPORT
	// 强制内联
	#define PANGU_FORCE_INLINE __attribute__((always_inline)) inline
	#define PANGU_RESTRICT __restrict__
#endif

#ifdef STATIC_PLUGINS
	#define PANGU_ENGINE_API
#elif defined BUILDING_ENGINE
	#define PANGU_ENGINE_API PANGU_LIBRARY_EXPORT
#else
	#define PANGU_ENGINE_API PANGU_LIBRARY_IMPORT
#endif

#ifdef STATIC_PLUGINS
	#define PANGU_EDITOR_API
#elif defined BUILDING_EDITOR
	#define PANGU_EDITOR_API PANGU_LIBRARY_EXPORT
#else
	#define PANGU_EDITOR_API PANGU_LIBRARY_IMPORT
#endif

#ifdef STATIC_PLUGINS
	#define PANGU_RENDERER_API
#elif defined BUILDING_RENDERER
	#define PANGU_RENDERER_API PANGU_LIBRARY_EXPORT
#else
	#define PANGU_RENDERER_API PANGU_LIBRARY_IMPORT
#endif


inline EntityPtr::operator EntityRef() const {
	ASSERT(isValid());
	return {index};
}
// TODO
inline EntityRef EntityPtr::operator*() const {
	ASSERT(isValid());
	return {index};
}

namespace reflection {
PANGU_ENGINE_API ComponentType getCommponentType(const char* id);
}

#ifdef _MSC_VER
	#pragma warning(disable : 4251)
	// this is disabled because VS19 16.5.0 has false positives :(
	#pragma warning(disable : 4724)
	#if _MSC_VER == 1900
		#pragma warning(disable : 4091)
	#endif
#endif

}  // namespace pangu