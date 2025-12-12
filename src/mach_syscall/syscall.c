#if defined(__GNUC__) || defined(__clang__)
# define FORCE_ARM 
#else
# define FORCE_ARM
#endif

#ifdef __arm__
# ifdef __APPLE__

#define REG(name, val) register long name __asm__(#name) = val

#define _MSYS_GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define _MSYS_COUNT_ARGS(...) _MSYS_GET_NTH_ARG(0, ##__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define _MSYS_CONCAT_IMPL(name, count) name##count
#define _MSYS_CONCAT(name, count) _MSYS_CONCAT_IMPL(name, count)

#define mach_syscall(number, ...) \
    _MSYS_CONCAT(_mach_syscall, _MSYS_COUNT_ARGS(__VA_ARGS__))(number, ##__VA_ARGS__)

#define DEFINE_MACH_SYSCALL(n, args, regs, stack_setup, ...) \
FORCE_ARM \
long _mach_syscall##n args \
{ \
    regs \
    \
    __asm__ volatile ( \
        stack_setup \
        "svc #0x80\n\t" \
        : "+r" (r0) \
        : __VA_ARGS__ \
        : "memory", "r4", "r5", "r6", "r8" \
    ); \
    \
    return r0; \
}

DEFINE_MACH_SYSCALL(0, (long number),
    REG(r0, 0); REG(r12, number);,
    "",
    "r" (r12)
)

DEFINE_MACH_SYSCALL(1, (long number, long arg1),
    REG(r0, arg1); REG(r12, number);,
    "",
    "r" (r12)
)

DEFINE_MACH_SYSCALL(2, (long number, long arg1, long arg2),
    REG(r0, arg1); REG(r1, arg2); REG(r12, number);,
    "",
    "r" (r1), "r" (r12)
)

DEFINE_MACH_SYSCALL(3, (long number, long arg1, long arg2, long arg3),
    REG(r0, arg1); REG(r1, arg2); REG(r2, arg3); REG(r12, number);,
    "",
    "r" (r1), "r" (r2), "r" (r12)
)

DEFINE_MACH_SYSCALL(4, (long number, long arg1, long arg2, long arg3, long arg4),
    REG(r0, arg1); REG(r1, arg2); REG(r2, arg3); REG(r3, arg4); REG(r12, number);,
    "",
    "r" (r1), "r" (r2), "r" (r3), "r" (r12)
)

DEFINE_MACH_SYSCALL(5, (long number, long arg1, long arg2, long arg3, long arg4, long arg5),
    REG(r0, arg1); REG(r1, arg2); REG(r2, arg3); REG(r3, arg4); REG(r12, number);,
    "push {r4}\n\t"
    "mov r4, %[a5]\n\t"
    "push {r4}\n\t"
    "svc #0x80\n\t"
    "pop {r4}\n\t"
    "pop {r4}\n\t",
    "r" (r1), "r" (r2), "r" (r3), "r" (r12), [a5] "r" (arg5)
)

DEFINE_MACH_SYSCALL(6, (long number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6),
    REG(r0, arg1); REG(r1, arg2); REG(r2, arg3); REG(r3, arg4); REG(r12, number);,
    "push {r5}\n\t"
    "push {r4}\n\t"
    "mov r5, %[a6]\n\t"
    "mov r4, %[a5]\n\t"
    "push {r5}\n\t"
    "push {r4}\n\t"
    "svc #0x80\n\t"
    "pop {r4}\n\t"
    "pop {r5}\n\t"
    "pop {r4}\n\t"
    "pop {r5}\n\t",
    "r" (r1), "r" (r2), "r" (r3), "r" (r12), [a5] "r" (arg5), [a6] "r" (arg6)
)

DEFINE_MACH_SYSCALL(7, (long number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, long arg7),
    REG(r0, arg1); REG(r1, arg2); REG(r2, arg3); REG(r3, arg4); REG(r12, number);,
    "push {r6}\n\t"
    "push {r5}\n\t"
    "push {r4}\n\t"
    "mov r6, %[a7]\n\t"
    "mov r5, %[a6]\n\t"
    "mov r4, %[a5]\n\t"
    "push {r6}\n\t"
    "push {r5}\n\t"
    "push {r4}\n\t"
    "svc #0x80\n\t"
    "pop {r4}\n\t"
    "pop {r5}\n\t"
    "pop {r6}\n\t"
    "pop {r4}\n\t"
    "pop {r5}\n\t"
    "pop {r6}\n\t",
    "r" (r1), "r" (r2), "r" (r3), "r" (r12), [a5] "r" (arg5), [a6] "r" (arg6), [a7] "r" (arg7)
)

DEFINE_MACH_SYSCALL(8, (long number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, long arg7, long arg8),
    REG(r0, arg1); REG(r1, arg2); REG(r2, arg3); REG(r3, arg4); REG(r12, number);,
    "push {r8}\n\t"
    "push {r6}\n\t"
    "push {r5}\n\t"
    "push {r4}\n\t"
    "mov r8, %[a8]\n\t"
    "mov r6, %[a7]\n\t"
    "mov r5, %[a6]\n\t"
    "mov r4, %[a5]\n\t"
    "push {r8}\n\t"
    "push {r6}\n\t"
    "push {r5}\n\t"
    "push {r4}\n\t"
    "svc #0x80\n\t"
    "pop {r4}\n\t"
    "pop {r5}\n\t"
    "pop {r6}\n\t"
    "pop {r8}\n\t"
    "pop {r4}\n\t"
    "pop {r5}\n\t"
    "pop {r6}\n\t"
    "pop {r8}\n\t",
    "r" (r1), "r" (r2), "r" (r3), "r" (r12), [a5] "r" (arg5), [a6] "r" (arg6), [a7] "r" (arg7), [a8] "r" (arg8)
)

# endif
#endif
