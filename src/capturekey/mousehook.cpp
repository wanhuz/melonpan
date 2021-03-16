#include "mousehook.h"
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#pragma pop_macro("slots")
namespace py = pybind11;


int add(int i, int j) {
	return i + j;
}

void hook() {
	py::scoped_interpreter guard{};
	py::print("Hello, World!");
}

PYBIND11_MODULE(example, m) {
	m.doc() = "pybind11 example plugin"; // optional module docstring

	m.def("add", &add, "A function which adds two numbers");
}