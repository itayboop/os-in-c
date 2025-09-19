#pragma once
#include "Utils/Functions/PrintUtils.hpp"

#define THROW(kernel_exception) (kernel_exception.raise())
#define THROW_KERNEL_EXCEPTION() (THROW(KernelException()))

class KernelException final
{
public:
    // TODO: make this get string
	void raise() const
	{
		PrintUtils::printk("KERNEL EXCEPTION!\n");
		while(1);
	}
};
