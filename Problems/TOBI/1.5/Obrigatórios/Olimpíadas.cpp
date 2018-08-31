#include <cstdio>
#include <algorithm>

using namespace std;

typedef struct medals {
	int country_id, total;
} Medals;

bool condition(Medals countryA, Medals countryB) {
	if(countryA.total == countryB.total) return (countryA.country_id < countryB.country_id);
	else return (countryA.total > countryB.total);
}

int main() {
	int n_participants, modalities, medal;
	scanf("%d %d", &n_participants, &modalities);
	Medals participant[n_participants];
	for(int i = 0; i < n_participants; i++) participant[i].country_id = i, participant[i].total = 0;

	for(int i = 0; i < modalities; i++) {
		scanf("%d", &medal);
		--medal;
		if(medal >= 0 && medal < n_participants) ++participant[medal].total;
		scanf("%d", &medal);
		--medal;
		if(medal >= 0 && medal < n_participants) ++participant[medal].total;
		scanf("%d", &medal);
		--medal;
		if(medal >= 0 && medal < n_participants) ++participant[medal].total;
	}
	sort(participant, participant+n_participants, condition);
	for(int i = 0; i < n_participants; i++) {
		if(i+1 != n_participants) printf("%d ", participant[i].country_id+1);
		else printf("%d", participant[i].country_id+1);
	}
	return 0;
}
