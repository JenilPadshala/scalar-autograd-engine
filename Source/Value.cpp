#include "Value.h"
#include "Function.h"

// Overloading the '+' operator
std::shared_ptr<Value> operator+(const std::shared_ptr<Value> &lhs,
                                 const std::shared_ptr<Value> &rhs) {
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
std::shared_ptr<Value> operator*(const std::shared_ptr<Value> &lhs,
                                 const std::shared_ptr<Value> &rhs) {
  double out_data = lhs->data * rhs->data;

  // Create the MulNode context wrapper
  auto ctx = std::make_shared<MulNode>(lhs, rhs);
  // Create the output Value node and set its creator to the MulNode context
  auto out_val = std::make_shared<Value>(out_data, ctx);
  ctx->output = out_val;
  // Return the new Value node pointing to its creator (MulNode)
  return out_val;
}

// Overloading the '-' operator for negation
std::shared_ptr<Value> operator-(const std::shared_ptr<Value> &val) {
  double out_data = -val->data;

  auto ctx = std::make_shared<NegNode>(val);
  auto out_val = std::make_shared<Value>(out_data, ctx);
  ctx->output = out_val;
  return out_val;
}

// Overloading the '-' operator for subtraction
std::shared_ptr<Value> operator-(const std::shared_ptr<Value> &lhs,
                                 const std::shared_ptr<Value> &rhs) {
  return lhs + (-rhs);
}

// Overloading the '/' operator for division
std::shared_ptr<Value> operator/(const std::shared_ptr<Value> &lhs,
                                 const std::shared_ptr<Value> &rhs) {
  double out_data = std::pow(rhs->data, -1.0);
  auto ctx = std::make_shared<PowNode>(rhs, -1.0);
  auto inverse_rhs = std::make_shared<Value>(out_data, ctx);
  ctx->output = inverse_rhs;
  return lhs * inverse_rhs;
}