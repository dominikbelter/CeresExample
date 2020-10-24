/** @file main.cpp
 *
 * This example shows how to use Ceres library
 *
 */
#include <ceres/ceres.h>

#include <iostream>
#include <memory>

using ceres::NumericDiffCostFunction;
using ceres::CENTRAL;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;

using namespace std;

struct CostFunctor {
   template <typename T>
   bool operator()(const T* const x, T* residual) const {
     residual[0] = pow(T(10.0) - x[0],2.0);// cost function
     return true;
   }
};

int main()
{
    try {

        // The variable to solve for with its initial value.
        double initial_x = 5.0;
        double x = initial_x;

        // Build the problem.
        Problem problem;

        // Set up the only cost function (also known as residual). This uses
        // auto-differentiation to obtain the derivative (jacobian).
        CostFunction* cost_function =
                new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
        problem.AddResidualBlock(cost_function, NULL, &x);

        // Run the solver!
        Solver::Options options;
        options.linear_solver_type = ceres::DENSE_QR;
        options.minimizer_progress_to_stdout = true;
        Solver::Summary summary;
        Solve(options, &problem, &summary);

        std::cout << summary.BriefReport() << "\n";
        std::cout << "x_init: " << initial_x << "\n";
        std::cout << "x_final: " << x << "\n";
        return 0;
    }
	catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
