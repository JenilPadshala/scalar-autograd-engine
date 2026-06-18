#include <iostream>
#include <memory>

#include "Engine.h"
#include "Value.h"

int main() {
  std::cout << "--- Initializing Autograd Engine Test ---" << std::endl;

  // L = (x * y) + bias
  auto x = std::make_shared<Value>(2.0);
  auto y = std::make_shared<Value>(3.0);
  auto bias = std::make_shared<Value>(10.0);

  auto L = (x * y) + bias;

  std::cout << "Forward Pass Output (L): " << L->data << std::endl;

  Autograd::backward(L);

  std::cout << "\n--- Gradient Verification ---" << std::endl;
  std::cout << "dL / dBias : " << bias->grad << " (Expected: 1.0)" << std::endl;
  std::cout << "dL / dY    : " << y->grad << " (Expected: 2.0)" << std::endl;
  std::cout << "dL / dX    : " << x->grad << " (Expected: 3.0)" << std::endl;

  return 0;
}