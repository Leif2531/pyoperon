# pyoperon

[![License](https://img.shields.io/github/license/heal-research/pyoperon?style=flat)](https://github.com/heal-research/pyoperon/blob/master/LICENSE)
[![build-linux](https://github.com/heal-research/pyoperon/actions/workflows/build-linux.yml/badge.svg)](https://github.com/heal-research/pyoperon/actions/workflows/build-linux.yml)
[![Gitter chat](https://badges.gitter.im/operongp/gitter.png)](https://gitter.im/operongp/community)

**pyoperon** is the python bindings library of [**Operon**](https://github.com/heal-research/operon), a modern C++ framework for symbolic regression developed by [Heal-Research](https://github.com/heal-research) at the University of Applied Sciences Upper Austria.

A scikit-learn regressor is also available:
```python
from operon.sklearn import SymbolicRegressor
```

The [examples](https://github.com/heal-research/pyoperon/examples) folder contains sample code for using either the Python bindings directly or the operon.sklearn module.

# Building and installing

Currently, the easiest way to consume **pyoperon** is via the [nix package manager](https://nixos.org/). Nix can be installed on other Linux distributions in a few easy steps:

1. [Install nix](https://nixos.org/manual/nix/stable/installation/installing-binary.html) and enable flake support in `~/.config/nix/nix.conf`:
   ```
   experimental-features = nix-command flakes
   ```
2. Install **pyoperon**:
   ```
   nix develop github:heal-research/pyoperon --no-write-lock-file
   ```

Upon completion of the last command, the `$PYTHONPATH` will be updated and **pyoperon** will pe available for use.

Alternatively, one can also clone this repo and run `nix develop` from within the cloned path.

# Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.
