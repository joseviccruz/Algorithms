#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

typedef struct car {
	int id, correct_cps, current_cp;
} Car;

bool condition(Car a, Car b) {
	if(a.correct_cps != b.correct_cps) return (a.correct_cps > b.correct_cps);
	else return (a.current_cp < b.current_cp);
}

int main() {
	int checkpoints, n_cars, sensor_readings, x, y;
	scanf("%d %d %d", &checkpoints, &n_cars, &sensor_readings);
	Car car[n_cars];
	for(int i = 0; i < n_cars; i++) car[i].id = i+1, car[i].correct_cps = 0, car[i].current_cp = INT_MAX;
	for(int i = 0; i < sensor_readings; i++) {
		scanf("%d %d", &x, &y);
		--x;
		if((y-1) == (car[x].correct_cps%checkpoints)) {
			++car[x].correct_cps;
			car[x].current_cp = i;
		}
	}
	sort(car, car+n_cars, condition);
	for(int i = 0; i < n_cars; i++) {
		if(i+1 != n_cars) printf("%d ", car[i].id);
		else printf("%d", car[i].id);
	}
	return 0;
}
