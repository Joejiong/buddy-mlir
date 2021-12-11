//====- buddy-opt.cpp - The driver of buddy-mlir --------------------------===//
//
// This file is the dialects and oprimization driver of buddy-mlir project.
//
//===----------------------------------------------------------------------===//

#include "mlir/IR/Dialect.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Support/MlirOptMain.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"

#include "Bud/BudDialect.h"
#include "Bud/BudOps.h"
#include "DIP/DIPDialect.h"
#include "DIP/DIPOps.h"

namespace mlir {
namespace buddy {
void registerConvVectorizationPass();
void registerPointwiseConvVectorizationPass();
void registerLowerBudPass();
void registerLowerDIPPass();
} // namespace buddy
} // namespace mlir

int main(int argc, char **argv) {
  // Register all MLIR passes.
  mlir::registerAllPasses();
  // Register Vectorization of Convolution.
  mlir::buddy::registerConvVectorizationPass();
  mlir::buddy::registerPointwiseConvVectorizationPass();
  mlir::buddy::registerLowerBudPass();
  mlir::buddy::registerLowerDIPPass();

  mlir::DialectRegistry registry;
  // Register all MLIR core dialects.
  registerAllDialects(registry);
  // Register dialects in buddy-mlir project.
  registry.insert<buddy::bud::BudDialect, buddy::dip::DIPDialect>();

  return mlir::failed(
      mlir::MlirOptMain(argc, argv, "buddy-mlir optimizer driver", registry));
}
