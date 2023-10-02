#include <iostream>
#include <string>

using namespace std;
void one_line();

class Type {
private:
	string dimensions;
	string grade;
public:
	Type() : dimensions("N/A"), grade("N/A") {}
	Type(string di, string gr) : dimensions(di), grade(gr) {}
	
	void get_type() {
		cout << "Enter nominal sizes (for example 2x4): "; getline(cin, dimensions);
		cout << "Enter a grade: "; getline(cin, grade);
	}
	void show_type() const {
		cout << "Nominal sizes: " << dimensions << endl;
		cout << "Grade: " << grade << endl;
	}
};

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

class Lumber : public Type, public Distance {
private:
	int quantity;
	double price;
public:
	Lumber() : Type(), Distance(), quantity(0), price(0.0) {}
	Lumber(string di, string gr,
			int ft, float in,
			int qu, double pr) :
		Type(di, gr), Distance(ft, in), quantity(qu), price(pr) {}

	void get_lumber() {
		Type::get_type(); Distance::get_dist();
		cout << "Enter quantity: "; cin >> quantity;
		cout << "Enter price: "; cin >> price;
		one_line();
	}
	void show_lumber() {
		Type::show_type(); 
		cout << "Size: "; Distance::show_dist();
		cout << "Price of " << quantity << " pieces: " << price*quantity << " dollars" << endl;
		one_line();
	}
};

int main() {
	Lumber siding;
	siding.get_lumber();
	Lumber studs("2x4", "const", 8, 0.0, 200, 4.45);
	cout << "First\n\n"; siding.show_lumber();
	cout << "Second\n\n"; studs.show_lumber();

	return 0;
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

void one_line() {
	for (int i = 0; i < 45; i++) {
		cout << "-";
	}
	cout << endl;
}