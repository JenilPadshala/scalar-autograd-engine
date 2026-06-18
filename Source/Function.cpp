#include "Function.h"
#include <cmath>

// AddNode Implementation
AddNode::AddNode(std::shared_ptr<Value> a, std::shared_ptr<Value> b)
    : Function({a, b}) {}

void AddNode::backward(double output_grad) {
  inputs[0]->grad += output_grad * 1.0;
  inputs[1]->grad += output_grad * 1.0;
}

// MulNode Implementation
MulNode::MulNode(std::shared_ptr<Value> a, std::shared_ptr<Value> b)
    : Function({a, b}) {}

void MulNode::backward(double output_grad) {
  inputs[0]->grad += output_grad * inputs[1]->data;
  inputs[1]->grad += output_grad * inputs[0]->data;
}

// NegNode Implementation
NegNode::NegNode(std::shared_ptr<Value> a) : Function({a}) {}

void NegNode::backward(double output_grad) {
  inputs[0]->grad += output_grad * -1.0;
}

// PowNode Implementation
PowNode::PowNode(std::shared_ptr<Value> a, double exp)
    : Function({a}), exponent(exp) {}

void PowNode::backward(double output_grad) {
  double base_data = inputs[0]->data;
  double local_derivative = exponent * std::pow(base_data, exponent - 1);
  inputs[0]->grad += output_grad * local_derivative;
}