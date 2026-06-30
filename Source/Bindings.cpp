#include <pybind11/pybind11.h>
#include "Value.h"
#include "Engine.h"
#include <string>

namespace py = pybind11;

PYBIND11_MODULE(micrograd_cpp, m) {
    m.doc() = "High-Performance C++ Scalar Autograd Engine Backend";

    // Bind the Value class, explicitly stating it's managed via std::shared_ptr
    py::class_<Value, std::shared_ptr<Value>>(m, "Value")
        .def(py::init<double>())
        .def_readwrite("data", &Value::data)
        .def_readwrite("grad", &Value::grad)

        .def("__add__", [](const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {return lhs + rhs;})
        .def("__add__", [](const std::shared_ptr<Value>& lhs, double rhs) {return lhs + rhs;})
        .def("__radd__", [](double lhs, const std::shared_ptr<Value>& rhs) {return lhs + rhs;})

        .def("__mul__", [](const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {return lhs * rhs;})
        .def("__mul__", [](const std::shared_ptr<Value>& lhs, double rhs) {return lhs * rhs;})
        .def("__rmul__", [](double lhs, const std::shared_ptr<Value>& rhs) {return lhs * rhs;})

        .def("__sub__", [](const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {return lhs - rhs;})
        .def("__sub__", [](const std::shared_ptr<Value>& lhs, double rhs) {return lhs - rhs;})
        .def("__rsub__", [](double lhs, const std::shared_ptr<Value>& rhs) {return lhs - rhs;})

        .def("__truediv__", [](const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {return lhs / rhs;})
        .def("__truediv__", [](const std::shared_ptr<Value>& lhs, double rhs) {return lhs / rhs;})
        .def("__rtruediv__", [](double lhs, const std::shared_ptr<Value>& rhs) {return lhs / rhs;})

        .def("__neg__", [](const std::shared_ptr<Value>& val) {return -val;})

        .def("__repr__", [](const std::shared_ptr<Value>& v){
            if (v) {
                return "Value(data=" + std::to_string(v->data) + ", grad=" + std::to_string(v->grad) + ")";
            }
            return std::string("Value(nullptr)");
        });
    m.def("backward", &Autograd::backward, "Run backpropagation to compute gradients");
}