#include "KernelException.hpp"

constexpr void KernelException::raise() const {
	while(1);
}