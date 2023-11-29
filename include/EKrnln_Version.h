#pragma once

#define ___VER_1(_major, _minor, _build) L#_major##"_"###_minor##"_"###_build
#define ___VER_2(_major, _minor, _build) L#_major##"."###_minor##"."###_build
#define ___VER_3(_major, _minor, _build) ___VER_1(_major, _minor, _build)
#define ___VER_4(_major, _minor, _build) ___VER_2(_major, _minor, _build)

#define ___VER_1A(_major, _minor, _build) #_major##"_"###_minor##"_"###_build
#define ___VER_2A(_major, _minor, _build) #_major##"."###_minor##"."###_build
#define ___VER_3A(_major, _minor, _build) ___VER_1A(_major, _minor, _build)
#define ___VER_4A(_major, _minor, _build) ___VER_2A(_major, _minor, _build)

// 版本号统一放在一个位置, 用到版本号的cpp文件自己引用这个头文件, 不要在.h文件中引用
// 一行修改版本号就在这修改

#define EKRNLN_MAJORVERSION               2         // 支持库主版本号
#define EKRNLN_MINORVERSION               0         // 支持库次版本号
#define EKRNLN_BUILDVERSION               1         // 支持库编译版本号
#define EKRNLN_VERSION                    ___VER_4(EKRNLN_MAJORVERSION, EKRNLN_MINORVERSION, EKRNLN_BUILDVERSION)    // 支持库版本号
#define EKRNLN_VERSION_                   ___VER_3(EKRNLN_MAJORVERSION, EKRNLN_MINORVERSION, EKRNLN_BUILDVERSION)    // 支持库版本号, 点换成下划线 6_1_101
#define EKRNLN_VERSIONA                   ___VER_4A(EKRNLN_MAJORVERSION, EKRNLN_MINORVERSION, EKRNLN_BUILDVERSION)   // 支持库版本号
#define EKRNLN_VERSIONA_                  ___VER_3A(EKRNLN_MAJORVERSION, EKRNLN_MINORVERSION, EKRNLN_BUILDVERSION)   // 支持库版本号, 点换成下划线 6_1_101

