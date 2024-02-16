#pragma once

#define THROW(kernel_exception) (kernel_exception.raise())
#define THROW_KERNEL_EXCEPTION() (THROW(KernelException()))

class KernelException final
{
public:
	constexpr void raise() const
	{
		while(1);
	}
};
