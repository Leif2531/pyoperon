// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2019-2021 Heal Research

#include "pyoperon/pyoperon.hpp"

#include <pybind11/detail/common.h>

void init_algorithm(py::module_ &m)
{
    py::class_<GeneticProgrammingAlgorithm>(m, "GeneticProgrammingAlgorithm")
        .def(py::init<Operon::Problem const&, Operon::GeneticAlgorithmConfig const&, Operon::UniformInitializer&,
                Operon::OffspringGeneratorBase const&, Operon::ReinserterBase const&>())
        .def("Run", py::overload_cast<Operon::RandomGenerator&, std::function<void()>, size_t>(&GeneticProgrammingAlgorithm::Run),
                py::call_guard<py::gil_scoped_release>(), py::arg("rng"), py::arg("callback") = nullptr, py::arg("threads") = 0)
        .def("Reset", &GeneticProgrammingAlgorithm::Reset)
        .def("BestModel", [](GeneticProgrammingAlgorithm const& self, Operon::Comparison const& comparison) {
                    auto min_elem = std::min_element(self.Parents().begin(), self.Parents().end(), [&](auto const& a, auto const& b) { return comparison(a, b);});
                    return *min_elem;
                })
        .def_property_readonly("Generation", &GeneticProgrammingAlgorithm::Generation)
        .def_property_readonly("Parents", static_cast<Operon::Span<Operon::Individual const> (GeneticProgrammingAlgorithm::*)() const>(&GeneticProgrammingAlgorithm::Parents))
        .def_property_readonly("Offspring", static_cast<Operon::Span<Operon::Individual const> (GeneticProgrammingAlgorithm::*)() const>(&GeneticProgrammingAlgorithm::Offspring))
        .def_property_readonly("Config", &GeneticProgrammingAlgorithm::GetConfig);

    py::class_<NSGA2Algorithm>(m, "NSGA2Algorithm")
        .def(py::init<Operon::Problem const&, Operon::GeneticAlgorithmConfig const&, Operon::UniformInitializer&,
                Operon::OffspringGeneratorBase const&, Operon::ReinserterBase const&, Operon::NondominatedSorterBase const&>())
        .def("Run", py::overload_cast<Operon::RandomGenerator&, std::function<void()>, size_t>(&NSGA2Algorithm::Run),
                py::call_guard<py::gil_scoped_release>(), py::arg("rng"), py::arg("callback") = nullptr, py::arg("threads") = 0)
        .def("Reset", &NSGA2Algorithm::Reset)
        .def("BestModel", [](NSGA2Algorithm const& self, Operon::Comparison const& comparison) {
                    auto min_elem = std::min_element(self.Best().begin(), self.Best().end(), [&](auto const& a, auto const& b) { return comparison(a, b);});
                    return *min_elem;
                })
        .def_property_readonly("Generation", &NSGA2Algorithm::Generation)
        .def_property_readonly("Parents", static_cast<Operon::Span<Operon::Individual const> (NSGA2Algorithm::*)() const>(&NSGA2Algorithm::Parents))
        .def_property_readonly("Offspring", static_cast<Operon::Span<Operon::Individual const> (NSGA2Algorithm::*)() const>(&NSGA2Algorithm::Offspring))
        .def_property_readonly("BestFront", [](NSGA2Algorithm const& self) {
                auto best = self.Best();
                return std::vector<Operon::Individual>(best.begin(), best.end());
                })
        .def_property_readonly("Config", &NSGA2Algorithm::GetConfig);
}
