# Parallelization in OpenFOAM for HPC Deployment Workshop

## Exercises repository

This repo holds initial code for Hands-on activities planned for the
[Parallelization in OpenFOAM for HPC Deployment](https://www.nhr4ces.de/2022-10-18-training-parallelization-in-openfoam-for-hpc-deployment/) Workshop.

Each activity is associated with an ID and three branches. For example if an activity has `ID=00`, the branches `ex00-fe5`, `ex00-of9` and `ex00-of2206`
are available to ease running the code using the main OpenFOAM forks.

The structure of each activity is as follows (Can be flexible in file naming):

```bash
.
├── exercises
│   ├── serialParallelTests.C              # This is what gets compiled (mentioned in Make/files)
│   ├── testClass.C                        # This is what you modify (Also mentioned in Make/files)
│   └── testClass.H
├── Make
│   ├── files                              # What C++ implementation files to compile
│   └── options                            # Compiler/Linker options
```

> Typically, `Make/options` is the only difference between branches of the same activity, but as you add code, more differences emerge.

I recommend to have no untracked files and nuke everything when hopping branches:

```bash
# Force checkout of the activity's branches
git checkout -f ex01-of9
# Go back to initial version of exercises/testClass.C file
git checkout ex01-of9 -- exercises/testClass.C
```
