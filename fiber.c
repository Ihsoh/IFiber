#include "fiber.h"

int InitMainFiber(FiberPtr fiber)
{
	if(fiber == (FiberPtr)0)
		return -1;
	fiber->first = 0;
	return 0;
}

int InitFiber(FiberPtr fiber, FiberFunction func)
{
	if(fiber == (FiberPtr)0 || func == (FiberFunction)0)
		return -1;
	fiber->eip = (unsigned int)func;
	fiber->esp = (unsigned int)fiber->stack + FIBER_STACK_SIZE - 0x10;
	fiber->first = 1;
	return 0;
}

int SwitchFiber(FiberPtr current, FiberPtr target)
{
	if(current == (FiberPtr)0 || target == (FiberPtr)0)
		return -1;
	
	asm volatile(	"pushal\n\t");
	
	// Store current context.
	asm volatile(	"pushl		%%eax\n\t"
					"pushl		%%ebx\n\t"
					"pushl		%%ecx\n\t"
					"pushl		%%edx\n\t"
					"pushl		%%esi\n\t"
					"pushl		%%edi\n\t"
					"pushl		%%ebp\n\t"
					"pushfl\n\t"
					"movl		%%esp, %0\n\t"
					"movl		$__SwitchFiber_Return, %1\n\t"
					"fnsave		%2\n\t"
					"fxsave		%3\n\t"
					:	"=m"(current->esp),
						"=m"(current->eip),
						"=m"(current->i387_status),
						"=m"(current->sse_status));
	
	// Resume target context and jump to target.
	if(target->first)
	{
		target->first = 0;
		asm volatile(	"fninit\n\t"
						"movl		%0, %%esp\n\t"
						"pushl		%%eax\n\t"
						"movl		%1, %%eax\n\t"
						"movl		%%eax, -4(%%esp)\n\t"
						"popl		%%eax\n\t"
						"jmp		*2*-4(%%esp)\n\t"
						:
						:	"m"(target->esp),
							"m"(target->eip));
	}
	else
		asm volatile(	"movl		%0, %%esp\n\t"
						"frstor		%2\n\t"
						"fxrstor	%3\n\t"
						"pushl		%%eax\n\t"
						"movl		%1, %%eax\n\t"
						"movl		%%eax, -4(%%esp)\n\t"
						"popl		%%eax\n\t"
						"popfl\n\t"
						"popl		%%ebp\n\t"
						"popl		%%edi\n\t"
						"popl		%%esi\n\t"
						"popl		%%edx\n\t"
						"popl		%%ecx\n\t"
						"popl		%%ebx\n\t"
						"popl		%%eax\n\t"
						"jmp		*10*-4(%%esp)\n\t"
						:
						:	"m"(target->esp),
							"m"(target->eip),
							"m"(target->i387_status),
							"m"(target->sse_status));
	
	asm volatile(	"__SwitchFiber_Return:");
	
	asm volatile(	"popal\n\t");
	
	return 0;
}
