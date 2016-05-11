# Models for ROSS

These models originally shipped with [ROSS](http://github.com/carothersc/ROSS).
Use the models in the [legacy]() branch with the [ROSS-Legacy version](https://github.com/carothersc/ROSS/releases/tag/Legacy).
Or, use any of the models in the master branch with regular ROSS.

# Installation

This repository is automatically linked with ROSS and can be downloaded using the following commands:
```
git clone http://github.com/carothers/ROSS.git
cd ROSS
git submodule init
git submodule update
```

# Current Status

A small subset of these models are maintained by the ROSS development team.
These models are use by ROSS's continuous integration tests.
These models are:

- wifi
- phold-delta
- srw
- suspend_test

Some models herein are included only for historical purposes.
They are currently considered *deprecated* and should not be used for future development.
These models are:

- dragonfly (please see the dragonfly model which exists within the CODES repository)

The remaining models are no longer under active development.
While they have not been deprecated, they are not guaranteed to work with the latest version of ROSS.
