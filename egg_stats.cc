// Autogenerated file
#include "egg_stats.h"

std::array<MultivariateNormal<4>, EGG_TYPE_COUNT> egg_stats::expectations = {
	// none
	(MultivariateNormal<4>) {
		(Matrix<float,4,1>() << 76.95, 104.15, 139.8, 66.0).finished(),
		(Matrix<float,4,4>() << 43.5236842105, 28.85, 11.4631578947, 50.8947368421,
		                        28.85, 19.3973684211, 7.71578947368, 34.1052631579,
		                        11.4631578947, 7.71578947368, 3.32631578947, 13.5789473684,
		                        50.8947368421, 34.1052631579, 13.5789473684, 61.2631578947).finished()
	},
	// white
	(MultivariateNormal<4>) {
		(Matrix<float,4,1>() << 98.8, 153.15, 187.9, 75.15).finished(),
		(Matrix<float,4,4>() << 62.9052631579, 43.9263157895, 21.1894736842, 76.3473684211,
		                        43.9263157895, 84.9763157895, 63.5947368421, 26.1868421053,
		                        21.1894736842, 63.5947368421, 55.7789473684, 4.43684210526,
		                        76.3473684211, 26.1868421053, 4.43684210526, 128.028947368).finished()
	},
	// brown
	(MultivariateNormal<4>) {
		(Matrix<float,4,1>() << 88.25, 128.95, 174.7, 66.35).finished(),
		(Matrix<float,4,4>() << 112.828947368, 81.1184210526, 39.0789473684, 132.802631579,
		                        81.1184210526, 76.3657894737, 49.0368421053, 82.8605263158,
		                        39.0789473684, 49.0368421053, 41.8, 31.7947368421,
		                        132.802631579, 82.8605263158, 31.7947368421, 176.028947368).finished()
	},
	// cream
	(MultivariateNormal<4>) {
		(Matrix<float,4,1>() << 78.5, 118.1, 159.85, 63.6).finished(),
		(Matrix<float,4,4>() << 26.4736842105, 27.6315789474, 10.8157894737, 30.5789473684,
		                        27.6315789474, 73.4631578947, 26.3315789474, 38.9368421053,
		                        10.8157894737, 26.3315789474, 28.2394736842, 15.7789473684,
		                        30.5789473684, 38.9368421053, 15.7789473684, 44.6736842105).finished()
	}
};

