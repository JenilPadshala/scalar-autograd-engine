#include "Function.h"

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
