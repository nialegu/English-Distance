#include <iostream>

using namespace std;

class Distance {
private:
	int feet;
	float inches;
public:
	Distance() : feet(0), inches(0.0) {}
	Distance(int ft, float inch) : feet(ft), inches(inch) {}
	void get_dist() {
		cout << "Enter feet: "; cin >> feet;
		cout << "Enter inches: "; cin >> inches;
		cout << endl;
	}
	void show_dist() {
		cout << feet << "\'-" << inches << "\"" << endl;
	}
	Distance operator+ (Distance) const;
	bool operator< (Distance) const;
	void operator+=(Distance);
};

void Distance::operator+=(Distance d2) {
	feet += d2.feet;
	inches += d2.inches;
	if (inches >= 12) {
		feet++;
		inches -= 12;
	}
}

bool Distance::operator<(Distance d2) const {
	float bf1 = feet + inches / 12;
	float bf2 = d2.feet + d2.inches / 12;
	return(bf1 < bf2) ? true : false;
}

Distance Distance::operator+(Distance d2) const {
	int f = feet + d2.feet;
	float i = inches + d2.inches;
	if (i >= 12) {
		f++; i -= 12;
	}
	return Distance(f, i);
}

int main() {
	Distance d1, d3, d4;
	d1.get_dist();
	Distance d2(11, 6.25);
	d3 = d1 + d2;
	d4 = d1 + d2 + d3;
	cout << "d1 = "; d1.show_dist();
	cout << "d2 = "; d2.show_dist();
	cout << "d3 = "; d3.show_dist();
	cout << "d4 = "; d4.show_dist();

	if (d1 < d2) cout << "\nd1 is smaller than d2" << endl;
	else cout << "\nd1 is bigger or equal to d2" << endl;

	d1 += d2;
	cout << "\nd1 now: "; d1.show_dist();
	return 0;
}

