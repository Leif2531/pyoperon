// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright 2019-2021 Heal Research

#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <type_traits>

#include <operon/algorithms/gp.hpp>
#include <operon/algorithms/nsga2.hpp>
#include <operon/core/constants.hpp>
#include <operon/core/dataset.hpp>
#include <operon/core/format.hpp>
#include <operon/core/individual.hpp>
#include <operon/core/node.hpp>
#include <operon/core/pset.hpp>
#include <operon/core/metrics.hpp>
#include <operon/core/operator.hpp>

#include <operon/operators/creator.hpp>
#include <operon/operators/crossover.hpp>
#include <operon/operators/generator.hpp>
#include <operon/operators/initializer.hpp>
#include <operon/operators/mutation.hpp>
#include <operon/operators/non_dominated_sorter.hpp>
#include <operon/operators/selection.hpp>
#include <operon/operators/reinserter.hpp>

namespace py = pybind11;

// enable pass-by-reference semantics for this vector type
PYBIND11_MAKE_OPAQUE(std::vector<Operon::Variable>);
PYBIND11_MAKE_OPAQUE(std::vector<Operon::Individual>);

using GeneticProgrammingAlgorithm = Operon::GeneticProgrammingAlgorithm<Operon::UniformInitializer>;
using NSGA2Algorithm              = Operon::NSGA2<Operon::UniformInitializer>;

template<typename T>
py::array_t<T const> MakeView(Operon::Span<T const> view)
{
    auto sz = static_cast<pybind11::ssize_t>(view.size());
    py::array_t<T const> arr(sz, view.data(), py::capsule(view.data()));
    ENSURE(arr.owndata() == false);
    ENSURE(arr.data() == view.data());
    return arr;
}

template<typename T>
Operon::Span<T> MakeSpan(py::array_t<T> arr)
{
    py::buffer_info info = arr.request();
    using size_type = typename Operon::Span<T>::size_type;
    return Operon::Span<T>(static_cast<T*>(info.ptr), static_cast<size_type>(info.size));
}

void init_algorithm(py::module_&);
void init_creator(py::module_&);
void init_crossover(py::module_&);
void init_dataset(py::module_&);
void init_eval(py::module_&);
void init_generator(py::module_&);
void init_mutation(py::module_&);
void init_non_dominated_sorter(py::module_&);
void init_node(py::module_&);
void init_problem(py::module_&);
void init_pset(py::module_&);
void init_reinserter(py::module_&m);
void init_selection(py::module_&m);
void init_tree(py::module_&);
