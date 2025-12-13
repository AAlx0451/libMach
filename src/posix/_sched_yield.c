#include <mach/mach_syscall.h>

int _sched_yield(void) {
    return (int)mach_syscall(SYS_swtch_pri, 0);
}
