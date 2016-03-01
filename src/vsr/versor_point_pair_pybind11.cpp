#include <pybind11/pybind11.h>

#include "game/vsr/cga_types.h"
#include "game/vsr/cga_op.h"

namespace vsr {

namespace python {

namespace py = pybind11;
using namespace vsr::cga;

void AddPointPair(py::module &m) {
  py::class_<Par>(m, "Par")
      .def(py::init<double, double, double, double, double, double, double,
                    double, double, double>())
      .def("__init__", [](Par &instance, const Pnt &a,
                          const Pnt &b) { new (&instance) Par(a ^ b); })
      .def("duale", &Par::duale)
      .def("unduale", &Par::unduale)
      .def("dual", &Par::dual)
      .def("undual", &Par::undual)
      .def("unit", &Par::unit)
      .def("rev", &Par::reverse)
      .def("inv", &Par::inverse)
      .def("pnt", [](const Par &self) { return Round::location(self); })
      .def("radius", [](const Par &self) { return Round::radius(self); })
      .def("lin", [](const Par &self) { return Round::carrier(self); })
      .def("pnt_a", [](const Par &self) { return Round::split(self)[0]; })
      .def("pnt_b", [](const Par &self) { return Round::split(self)[1]; })
      .def("spin", (Par (Par::*)(const Mot &) const) & Par::spin)
      .def("__mul__", [](const Par &lhs, double rhs) { return lhs * rhs; })
      .def("__div__", [](const Par &lhs, double rhs) { return lhs / rhs; })
      .def("__repr__",
           [](const Par &arg) {
             std::stringstream ss;
             ss.precision(4);
             ss << "Par: [";
             for (int i = 0; i < arg.Num; ++i) {
               ss << " " << arg[i];
             }
             ss << " ]";
             return ss.str();
           })
      .def_buffer([](Par &arg) -> py::buffer_info {
        return py::buffer_info(
            arg.data(), sizeof(double), py::format_descriptor<double>::value(),
            1, {static_cast<unsigned long>(arg.Num)}, {sizeof(double)});
      });
}

}  // namespace python

}  // namespace vsr