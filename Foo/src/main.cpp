// Copyright 2021 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

#include "scip/cons_indicator.h"
#include "scip/prob.h"
#include "scip/scip.h"
#include "scip/scip_prob.h"
#include "scip/scipdefplugins.h"
#include "scip/struct_scip.h"

const double inf = std::numeric_limits<double>::infinity();

int main(int /*argc*/, char** /*argv*/) {
  SCIP* scip_ = nullptr;

  // Init
  std::cerr << "Init...\n";
  SCIPcreate(&scip_);
  SCIPincludeDefaultPlugins(scip_);

  SCIPsetIntParam(scip_, "timing/clocktype", 2);
  SCIPsetRealParam(scip_, "limits/memory", 6.59407790080000000e+10);

  //SCIPcreateProb(scip_, "", NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  SCIPcreateProbBasic(scip_, "");

  SCIPsetObjsense(scip_, (SCIP_OBJSENSE)1);  // Minimization
  SCIPsetObjsense(scip_, (SCIP_OBJSENSE)-1);  // Maximization

  // Add Variables
  std::cerr << "Add variables...\n";

  SCIP_VAR* x_ = nullptr;
  SCIPcreateVar(scip_, &x_, "x", 0.00000000000000000e+00, inf,
                0.00000000000000000e+00, (SCIP_VARTYPE)1, 1, 0, NULL, NULL,
                NULL, NULL, NULL);
  SCIPaddVar(scip_, x_);

  SCIP_VAR* y_ = nullptr;
  SCIPcreateVar(scip_, &y_, "y", 0.00000000000000000e+00, inf,
                0.00000000000000000e+00, (SCIP_VARTYPE)1, 1, 0, NULL, NULL,
                NULL, NULL, NULL);
  SCIPaddVar(scip_, y_);

  SCIP_VAR* z_ = nullptr;
  SCIPcreateVar(scip_, &z_, "z", 0.00000000000000000e+00, inf,
                0.00000000000000000e+00, (SCIP_VARTYPE)1, 1, 0, NULL, NULL,
                NULL, NULL, NULL);
  SCIPaddVar(scip_, z_);
  SCIPfreeTransform(scip_);

  // Add Constraints
  std::cerr << "Add constraints...\n";

  std::cerr << "Constraint 0...\n";
  // 2*x + 7*y + 3*z <= 50
  SCIP_CONS* constraint_0_ = nullptr;
  SCIP_VAR* vars_0[] = {y_, z_, x_};
  SCIP_Real vals_0[] = {7.00000000000000000e+00, 3.00000000000000000e+00,
                        2.00000000000000000e+00};
  SCIPcreateConsLinear(scip_, &constraint_0_, "auto_c_000000000", 3, vars_0,
                       vals_0, -inf, 5.00000000000000000e+01, 1, 1, 1, 1, 1, 0,
                       0, 0, 0, 0);
  SCIPaddCons(scip_, constraint_0_);

  std::cerr << "Constraint 1...\n";
  // 3*x - 5*y + 7*z <= 45
  SCIP_CONS* constraint_1_ = nullptr;
  SCIP_VAR* vars_1[] = {y_, z_, x_};
  SCIP_Real vals_1[] = {-5.00000000000000000e+00, 7.00000000000000000e+00,
                        3.00000000000000000e+00};
  SCIPcreateConsLinear(scip_, &constraint_1_, "auto_c_000000001", 3, vars_1,
                       vals_1, -inf, 4.50000000000000000e+01, 1, 1, 1, 1, 1, 0,
                       0, 0, 0, 0);
  SCIPaddCons(scip_, constraint_1_);

  std::cerr << "Constraint 2...\n";
  // 5*x + 2*y - 6*z <= 37
  SCIP_CONS* constraint_2_ = nullptr;
  SCIP_VAR* vars_2[] = {y_, z_, x_};
  SCIP_Real vals_2[] = {2.00000000000000000e+00, -6.00000000000000000e+00,
                        5.00000000000000000e+00};
  SCIPcreateConsLinear(scip_, &constraint_2_, "auto_c_000000002", 3, vars_2,
                       vals_2, -inf, 3.70000000000000000e+01, 1, 1, 1, 1, 1, 0,
                       0, 0, 0, 0);
  SCIPaddCons(scip_, constraint_2_);

  std::cerr << "Objective...\n";
  // Maximize 2*x + 2*y + 3*z
  SCIPfreeTransform(scip_);
  SCIPchgVarObj(scip_, x_, 2.00000000000000000e+00);
  SCIPchgVarObj(scip_, y_, 2.00000000000000000e+00);
  SCIPchgVarObj(scip_, z_, 3.00000000000000000e+00);
  SCIPaddOrigObjoffset(scip_, 0.00000000000000000e+00);

  SCIPresetParam(scip_, "limits/time");
  SCIPsetRealParam(scip_, "numerics/feastol", 9.99999999999999955e-08);
  SCIPsetRealParam(scip_, "numerics/dualfeastol", 9.99999999999999955e-08);
  SCIPsetIntParam(scip_, "presolving/maxrounds", -1);
  SCIPsetRealParam(scip_, "limits/gap", 1.00000000000000005e-04);

  // Solve
  std::cerr << "Solve...\n";

  SCIPsetIntParam(scip_, "parallel/maxnthreads", 8);
  SCIPsolveConcurrent(scip_);
  //SCIPsolve(scip_);

  // Check the stage.
  std::cerr << "Check stage...\n";
  const SCIP_STAGE stage = SCIPgetStage(scip_);
  std::cerr << "stage: ";
  switch(stage) {
    case SCIP_STAGE_PRESOLVING:
      std::cerr << "PRESOLVING\n";
      break;
    case SCIP_STAGE_SOLVING:
      std::cerr << "SOLVING\n";
      break;
    case SCIP_STAGE_SOLVED:
      std::cerr << "SOLVED\n";
      break;
    default:
      std::cerr << "UNKNOWN !!!\n";
      break;
  }

  // Check the status: optimal, infeasible, etc.
  std::cerr << "Check status...\n";
  SCIP_STATUS scip_status = SCIPgetStatus(scip_);
  std::cerr << "status: ";
  switch (scip_status) {
    case SCIP_STATUS_OPTIMAL:
      std::cerr << "OPTIMAL\n";
      break;
    case SCIP_STATUS_GAPLIMIT:
      std::cerr << "GAPLIMIT\n";
      break;
    case SCIP_STATUS_INFEASIBLE:
      std::cerr << "INFEASIBLE\n";
      break;
    case SCIP_STATUS_UNBOUNDED:
      std::cerr << "UNBOUNDED\n";
      break;
    case SCIP_STATUS_INFORUNBD:
      std::cerr << "INFORUNBD\n";
      break;
    case SCIP_STATUS_TIMELIMIT:
      std::cerr << "TIMELIMIT\n";
      break;
    case SCIP_STATUS_TOTALNODELIMIT:
      std::cerr << "TOTALNODELIMIT\n";
      break;
    default:
      std::cerr << "UNKNOWN !!!\n";
      break;
  }

  // Get the results.
  int solution_number_ = SCIPgetNSols(scip_);
  std::cerr << "Solutions: " << std::to_string(solution_number_) << std::endl;

  //std::cerr << "freeSols...\n";
  //SCIP_EXPORT SCIP_SOL** solutions_ = SCIPgetSols(scip_);
  //for (int i=0; i < solution_number_; ++i) {
  // SCIPclearSol(scip_, solutions_[i]);
  // SCIPfreeSol(scip_, &solutions_[i]);
  //}

  //SCIP_SOL* solution = SCIPgetBestSol(scip_);
  //SCIPfreeSol(scip_, &solution);

  //solution_number_ = SCIPgetNSols(scip_);
  //std::cerr << "Solutions: " << std::to_string(solution_number_) << std::endl;

  // Cleanup
  std::cerr << "Cleanup...\n";

  std::cerr << "freeSolve...\n";
  SCIPfreeSolve(scip_, /*Restart=*/false);

  std::cerr << "resetParam...\n";
  SCIPresetParams(scip_);

  std::cerr << "freeTransform...\n";
  SCIPfreeTransform(scip_);

  std::cerr << "releaseConstraints...\n";
  SCIPreleaseCons(scip_, &constraint_0_);
  SCIPreleaseCons(scip_, &constraint_1_);
  SCIPreleaseCons(scip_, &constraint_2_);

  std::cerr << "releaseVar...\n";
  SCIPreleaseVar(scip_, &x_);
  SCIPreleaseVar(scip_, &y_);
  SCIPreleaseVar(scip_, &z_);

  solution_number_ = SCIPgetNSols(scip_);
  std::cerr << "Solutions: " << std::to_string(solution_number_) << std::endl;

  std::cerr << "freeProb...\n";
  SCIPfreeProb(scip_);

  std::cerr << "free...\n";
  SCIPfree(&scip_);

  std::cerr << "Done\n";
  return 0;
}
