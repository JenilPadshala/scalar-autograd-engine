#include "Value.h"
#include "Function.h"

// Function for Addition Operation
class AddNode : public Function
{
public:
  AddNode(std::shared_ptr<Value> a, std::shared_ptr<Value> b)
      : Function({a, b}) {}

  void backward(double output_grad) override
  {
    inputs[0]->grad += output_grad * 1.0;
    inputs[1]->grad += output_grad * 1.0;
  }
};

// Function for Multiplication Operation
class MulNode : public Function
{
public:
  MulNode(std::shared_ptr<Value> a, std::shared_ptr<Value> b)
      : Function({a, b}) {}
  void backward(double output_grad) override
  {
    inputs[0]->grad += output_grad * inputs[1]->data;
    inputs[1]->grad += output_grad * inputs[0]->data;
  }
};

// Overloading the '+' operator
std::shared_ptr<Value> operator+(const std::shared_ptr<Value> &lhs, const std::shared_ptr<Value> &rhs)
{
  double out_data = lhs->data + rhs->data;
  // Create the AddNode context wrapper
  auto ctx = std::make_shared<AddNode>(lhs, rhs);
  // Create the output Value node and set its creator to the AddNode context
  auto out_val = std::make_shared<Value>(out_data, ctx);
  ctx->output = out_val;
  // Return the new Value node
  return out_val;
}

// Overloading the '*' operator
std::shared_ptr<Value> operator*(const std::shared_ptr<Value> &lhs, const std::shared_ptr<Value> &rhs)
{
  double out_data = lhs->data * rhs->data;

  // Create the MulNode context wrapper
  auto ctx = std::make_shared<MulNode>(lhs, rhs);
  // Create the output Value node and set its creator to the MulNode context
  auto out_val = std::make_shared<Value>(out_data, ctx);
  ctx->output = out_val;
  // Return the new Value node pointing to its creator (MulNode)
  return out_val;
}

