#include <iostream>
#include <format>
#include "Tools.h"
#define gamma 1

int main()
{
	float* p = new float []{ 1 };
	delete[] p;
	p = new float[] {2};
	std::cout << *p;
	//float s[] = {
	//	2,  2,  2,  2,  2,  2,
	//	2,  0,  0,  0,  1,  2,
	//	2,  0,  2,  0, -1,  2,
	//	2,  0,  0,  0,  0,  2,
	//	2,  2,  2,  2,  2,  2
	//};
	//float ls[] = {
	//	2,  2,  2,  2,  2,  2,
	//	2,  0,  0,  0,  1,  2,
	//	2,  0,  2,  0, -1,  2,
	//	2,  0,  0,  0,  0,  2,
	//	2,  2,  2,  2,  2,  2
	//};
	//for (int cnt = 1; cnt < 6; cnt++) {
	//	for (int i = 1; i < 4; i++) {
	//		for (int j = 1; j < 5; j++) {
	//			float l = ls[i * 6 + j];
	//			if (l == 2 or l == 1 or l == -1)continue;
	//			float lq = 0, uq = 0, rq = 0, dq = 0;
	//			float ll = ls[i * 6 + j - 1], lu = ls[i * 6 + j - 6], lr = ls[i * 6 + j + 1], ld = ls[i * 6 + j + 6];

	//			//left is wall
	//			if (ll == 2) {
	//				lq += l * 0.8;
	//				uq += l * 0.1;
	//				dq += l * 0.1;
	//			}
	//			else {
	//				lq += ll * 0.8;
	//				uq += ll * 0.1;
	//				dq += ll * 0.1;
	//			}

	//			//right is wall
	//			if (lr == 2) {
	//				rq += l * 0.8;
	//				uq += l * 0.1;
	//				dq += l * 0.1;
	//			}
	//			else {
	//				rq += lr * 0.8;
	//				uq += lr * 0.1;
	//				dq += lr * 0.1;
	//			}

	//			//up is wall
	//			if (lu == 2) {
	//				uq += l * 0.8;
	//				lq += l * 0.1;
	//				rq += l * 0.1;
	//			}
	//			else {
	//				uq += lu * 0.8;
	//				lq += lu * 0.1;
	//				rq += lu * 0.1;
	//			}

	//			//down is wall
	//			if (ld == 2) {
	//				dq += l * 0.8;
	//				lq += l * 0.1;
	//				rq += l * 0.1;
	//			}
	//			else {
	//				dq += ld * 0.8;
	//				lq += ld * 0.1;
	//				rq += ld * 0.1;
	//			}

	//			lq *= gamma;
	//			uq *= gamma;
	//			rq *= gamma;
	//			dq *= gamma;

	//			std::cout << std::format("q-state at ({},{}) is: (left, up, right, down) ({},{},{},{})", i, j, lq, uq, rq, dq) << std::endl;
	//			//std::cout << "q-state:" << lq << " " << uq << " " << rq << " " << dq << " " << std::endl;
	//			s[i * 6 + j] = std::max(lq, std::max(uq, std::max(rq, dq)));
	//		}
	//	}
	//	std::cout << std::format("round {}, Value table is:", cnt) << std::endl;
	//	for (int i = 1; i < 4; i++) {
	//		for (int j = 1; j < 5; j++) {
	//			std::cout << s[i * 6 + j] << " ";
	//		}
	//		std::cout << std::endl;
	//	}
	//	memcpy(ls, s, 30 * sizeof(float));
	//}
}
