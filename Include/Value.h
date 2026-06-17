#pragma once
#include <iostream>
#include <memory>

class Function;

class Value : public std::enable_shared_from_this<Value> {
public:
  double data;
  double grad;
  std::shared_ptr<Function> creator;

  // Constructor for Leaf Node / user inputs
  explicit Value(double val) : data(val), grad(0.0), creator(nullptr) {}

  // Constructor for Internal Nodes
  Value(double val, std::shared_ptr<Function> op_creator)
      : data(val), grad(0.0), creator(op_creator) {}
};

// Global operator overload for easy std::cout printing
inline std::ostream &operator<<(std::ostream &os,
                                const std::shared_ptr<Value> &val) {
  if (val) {
    os << "Value(data=" << val->data << ", grad=" << val->grad << ")";
  } else {
    os << "Value(nullptr)";
  }
  return os;
}



// Declarations
std::shared_ptr<Value> operator+(const std::shared_ptr<Value> &lhs, const std::shared_ptr<Value> &rhs);
std::shared_ptr<Value> operator*(const std::shared_ptr<Value> &lhs, const std::shared_ptr<Value> &rhs);