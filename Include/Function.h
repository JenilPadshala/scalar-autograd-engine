#pragma once
#include "Value.h"
#include <memory>
#include <vector>

class Function {
public:
  // All the Value nodes that are inputs to this operation
  std::vector<std::shared_ptr<Value>> inputs;
  // Weak pointer to the output Value node of this operation (to avoid circular references)
  std::weak_ptr<Value> output;

  // Constructor that accepts the inputs for this operation
  Function(std::vector<std::shared_ptr<Value>> ins) : inputs(ins) {}

  virtual ~Function() = default;

  virtual void backward(double output_grad) = 0;
};


// -- Concrete Operation Declarations --
class AddNode : public Function {
  public:
    AddNode(std::shared_ptr<Value> a, std::shared_ptr<Value> b);
    void backward(double output_grad) override;
};

class MulNode : public Function {
  public:
    MulNode(std::shared_ptr<Value> a, std::shared_ptr<Value> b);
    void backward(double output_grad) override;
};