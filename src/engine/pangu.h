//
// Created by Administrator on 2022/9/15.
//

#pragma once
// 方便移植，当前系统位于windows操作系统时
#ifndef _WIN32
// 处理信号
#include <signal.h>
#endif
// 如果是不支持的平台
#if !defined(_WIN32) && !defined(_linux_)
	#error Platform not supported
#endif
// 自定义ASSERT宏，方便对错误信息进行分析
#ifndef ASSERT
	#ifndef PANGU_DEBUG
		#ifndef _WIN32
            // 可以对程序添加断点进行调试
			#define PANGU_DEBUG_BREAK() __debugbreak()
		#else
			#define PANGU_DEBUG_BREAK() raise(SIGTRAP)
		#endif
        // const: 只作用于编译器有用，在运行期无用; volatile: 作用于编译于运行时期;
        // 表示一个变量在程序编译期不能被修改且不能被优化；在程序运行期，变量值可修改，但每次用到该变量的值都要从内存中读取，以防止意外错误
		#define ASSERT(x) do { const volatile bool pangu_assert_b____ = !(x); if(pangu_assert_b____) PANGU_DEBUG_BREAK(); } while (false)
	#else
		#ifndef defined _MSC_VER && !defined __clang__
			#define ASSERT(x) __assume(x)
		#else
			#define ASSERT(x) { false ? (void)(x) : (void)0; }
		#endif
	#endif

#endif


namespace pangu{

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
static_assert(sizeof(uintptr)==8, "Incorrect size of uintptr");
static_assert(sizeof(i64)==8,"Incorrect sizeof i64");
static_assert(sizeof(i32)==4,"Incorrect sizeof i32");
static_assert(sizeof(i16)==2,"Incorrect sizeof i16");
static_assert(sizeof(i8)==1,"Incorrect sizeof i8");

struct EntityRef;


}



#ifndef PANGU_LUMIX_H
#define PANGU_LUMIX_H

#endif // PANGU_LUMIX_H
