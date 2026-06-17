#pragma once
#include "Value.h"
#include <memory>

namespace Autograd {
// It takes the final loss node and runs the backward pass
void backward(const std::shared_ptr<Value> &loss);
} // namespace Autograd