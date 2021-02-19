#pragma once
#pragma push_macro("slots")
#undef slots
#include <pybind11/pybind11.h>
#pragma pop_macro("slots")
namespace py = pybind11;

class MouseHook {
public:
	void hook();
private:

}