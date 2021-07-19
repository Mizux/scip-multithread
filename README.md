# scip-multithread
Test SCIP Multithread

## Building

```sh
cmake -S. -Bbuild
cmake --build build
```

### Running
```sh
./build/bin/Foo
```

### Trace
Here the trace when using `SCIPsolveConcurrent(scip_)`:
```sh
./build/bin/Foo
Init...
Add variables...
Add constraints...
Constraint 0...
Constraint 1...
Constraint 2...
Objective...
Solve...
feasible solution found by trivial heuristic after 0.0 seconds, objective value 0.000000e+00
presolving:
(round 1, fast)       0 del vars, 0 del conss, 0 add conss, 5 chg bounds, 0 chg sides, 0 chg coeffs, 0 upgd conss, 0 impls, 0 clqs
   Deactivated symmetry handling methods, since SCIP was built without symmetry detector (SYM=none).
presolving (2 rounds: 2 fast, 1 medium, 1 exhaustive):
 0 deleted vars, 0 deleted constraints, 0 added constraints, 5 tightened bounds, 0 added holes, 0 changed sides, 0 changed coefficients
 0 implications, 0 cliques
presolved problem has 3 variables (0 bin, 3 int, 0 impl, 0 cont) and 3 constraints
      3 constraints of type <linear>
transformed objective value is always integral (scale: 1)
Presolving Time: 0.00
initializing seeds to 1963210296 in concurrent solver 'scip-2'
initializing seeds to 1332858414 in concurrent solver 'scip-3'
initializing seeds to 1541326760 in concurrent solver 'scip-4'
initializing seeds to 247360965 in concurrent solver 'scip-5'
initializing seeds to 387742462 in concurrent solver 'scip-6'
initializing seeds to 520723434 in concurrent solver 'scip-7'
initializing seeds to 1176648445 in concurrent solver 'scip-8'
transformed 1/1 original solutions to the transformed problem space
starting solve in concurrent solver 'scip-5'
starting solve in concurrent solver 'scip-1'
starting solve in concurrent solver 'scip-4'
starting solve in concurrent solver 'scip-8'
starting solve in concurrent solver 'scip-3'
starting solve in concurrent solver 'scip-2'
starting solve in concurrent solver 'scip-7'
starting solve in concurrent solver 'scip-6'
concurrent solver 'scip-1' stopped with status optimal solution found
concurrent solver 'scip-6' stopped with status optimal solution found
concurrent solver 'scip-4' stopped with status optimal solution found
concurrent solver 'scip-7' stopped with status optimal solution found
concurrent solver 'scip-5' stopped with status optimal solution found
concurrent solver 'scip-2' stopped with status optimal solution found
concurrent solver 'scip-3' stopped with status optimal solution found
concurrent solver 'scip-8' stopped with status optimal solution found
 time | mem |  dualbound   | primalbound  |  gap   
  0.0s| 608k| 3.500000e+01 | 3.500000e+01 |   0.00%
  0.0s| 608k| 3.500000e+01 | 3.500000e+01 |   0.00%

SCIP Status        : problem is solved [optimal solution found]
Solving Time (sec) : 0.03
Solving Nodes      : 16
Primal Bound       : +3.50000000000000e+01 (6 solutions)
Dual Bound         : +3.50000000000000e+01
Gap                : 0.00 %
Check status...
status: OPTIMAL
Solutions: 6
Cleanup...
freeSolve...
resetParam...
releaseVar...
releaseConstraints...
Solutions: 6
free...
Foo: build/_deps/scip-src/src/scip/primal.c:182: SCIPprimalFree: Assertion `(*primal)->nexistingsols == 0' failed.
zsh: abort      ./build/bin/Foo
```

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) for details.

## License

Apache 2.0; see [`LICENSE`](LICENSE) for details.

## Disclaimer

This project is not an official Google project. It is not supported by
Google and Google specifically disclaims all warranties as to its quality,
merchantability, or fitness for a particular purpose.
