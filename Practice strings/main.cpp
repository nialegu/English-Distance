#include <iostream>

using namespace std;

class Distance {
protected:
	const float mtf;
	int feet;
	float inches;
public:
	Distance() : feet(0), inches(0.0), mtf(3.280833F) {}
	explicit Distance(float meters) : mtf(3.280833F) {
		float fltfeet = mtf * meters;
		feet = int(fltfeet);
		inches = 12 * (fltfeet - feet);
	}
	Distance(int ft, float inch) : feet(ft), inches(inch), mtf(3.280833F) {}

	void get_dist() {
		cout << "Enter feet: "; cin >> feet;
		cout << "Enter inches: "; cin >> inches;
	}

	void show_dist() {
		cout << feet << "\'-" << inches << "\"" << endl;
	}

	Distance operator+ (Distance) const;
	Distance operator- (Distance) const;
	bool operator< (Distance) const;
	void operator+=(Distance);
	operator float()const;
	void operator= (Distance dd) {
		feet = dd.feet;
		inches = dd.inches;
	}
};

class DistSign : public Distance {
private:
	char sign;
public:
	DistSign() : Distance() {
		sign = '+';
	}
	DistSign(int ft, float in) : Distance(ft, in) {
		sign = '+';
	}
	DistSign(int ft, float in, char sg) : Distance(ft, in) {
		sign = sg;
	}

	void get_dist() {
		Distance::get_dist();
		cout << "Enter the sign (+ or -): "; cin >> sign;
	}
	void show_dist() {
		cout << sign;
		Distance::show_dist();
	}
};

int main() {
	DistSign alpha;
	alpha.get_dist();

	DistSign beta(11, 6.25);
	DistSign gamma(100, 5.5, '-');

	alpha.show_dist();
	beta.show_dist();
	gamma.show_dist();
	
	//void fancyDist(Distance);
	//Distance d1, d3, d4;
	//d1.get_dist();
	//Distance d2(11, 6.25);

	//d3 = d1 + d2;
	//d4 = d1 + d2 + d3;
	//cout << "d1 = "; d1.show_dist();
	//cout << "d2 = "; d2.show_dist();
	//cout << "d3 = "; d3.show_dist();
	//cout << "d4 = "; d4.show_dist();

	//if (d1 < d2) cout << "\nd1 is smaller than d2" << endl;
	//else cout << "\nd1 is bigger or equal to d2" << endl;
	//d1 += d2;
	//cout << "\nd1 now: "; d1.show_dist();

	//float mtrs;
	//Distance d5(2.35F);
	////Distance d5 = 2.35F; - it's incorrect now cause we added "explicit"
	//cout << "\nd5 = "; d5.show_dist();
	//mtrs = static_cast<float>(d5);
	//cout << "d5 = " << mtrs << " meters " << endl;
	//mtrs = d1;
	//cout << "d1 = " << mtrs << " meters " << endl;
	////fancyDist(mtrs); - without "explicit" this thing works
	//cout << endl;
	//Distance d6, d7, d8;
	//d6.get_dist();
	//d7.get_dist();
	//d8 = d7 - d6;
	//d8.show_dist();

	return 0;
}

void fancyDist(Distance d) {
	cout << "In feet and inches: ";
	d.show_dist();
	cout << endl;
}

//transform to meters
Distance::operator float()const {
	float fracfeet = inches / 12;
	fracfeet += static_cast<float>(feet);
	return fracfeet / mtf;
}

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

Distance Distance::operator-(Distance d2) const {
	int f; float i;
	if ((feet - d2.feet) < 0 || ( (feet - d2.feet) == 0 && (inches - d2.inches) < 0 )) {
		cout << "Getting negative value! ";
		return Distance(0, 0);
	}
	else {
		f = feet - d2.feet;
		i = inches - d2.inches;
		if (i < 0) {
			i = 12 - i * (-1);
			f--;
		}
		return Distance(f, i);
	}
}

Distance Distance::operator+(Distance d2) const {
	int f = feet + d2.feet;
	float i = inches + d2.inches;
	if (i >= 12) {
		f++; i -= 12;
	}
	return Distance(f, i);
}