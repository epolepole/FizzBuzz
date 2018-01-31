#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <limits>
#include <algorithm>

#include <iostream>
#include <exception>

#include <string>
#include <set>
#include <map>
#include <vector>

#include <memory>

using namespace std;

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

namespace trigonometry {

	struct CurveFit {
		double _a, _b, _c, _d;
		CurveFit(const double& a,const double& b,const double& c, const double& d) :_a(a), _b(b), _c(c), _d(d) {};
		
		double y(const double &x) const
		{
			return _d + (_a - _d) / (1. + pow(x / _c, _b));
		}
	};

	struct Pair {
		double x = 0;
		double y = 0;
		Pair() : x(0), y(0) {};
		Pair(double x, double y) : x(x), y(y) {};
		Pair(const Pair& iOther) : x(iOther.x), y(iOther.y) {};
		Pair operator+(const Pair& iOther) const { return Pair(this->x + iOther.x, this->y + iOther.y); }
		Pair operator-(const Pair& iOther) const { return Pair(this->x - iOther.x, this->y - iOther.y); }
		friend ostream& operator<<(ostream& os, const Pair& iP)
		{
			iP.print(os);
			return os;
		}
		virtual ~Pair() {}
		virtual bool operator==(const Pair& b) const { return x == b.x && y == b.y; }
		virtual bool operator<(const Pair& b) const 
		{ 
			if (x < b.x) return true;
			if (x > b.x) return false;
			if (y < b.y) return true;
			if (y > b.y) return false;
			return false; //Both are equal
		}
		double atan() const {return atan2(y, x); }
		

	private:
		virtual void print(ostream& os) const { os << '(' << x << ',' << y << ')'; }
	};

	struct Point : public Pair
	{
		Point() :Pair() {};
		Point(double x, double y) : Pair(x, y) {};
		Point(const Point& iOther) : Pair(iOther) {};
	} aLandP, aLeftLand, aRightLand;

	struct Speed : public Pair
	{
		Speed() :Pair() {};
		Speed(double x, double y) : Pair(x, y) {};
		Speed(const Speed& iOther) : Pair(iOther) {};
	};
	static double Atan(const Pair& iP){return iP.atan();}
	static double Distance(const Point& a, const Point& b)
	{
		Pair aPair = b - a;
		return sqrt(pow(aPair.x, 2) + pow(aPair.y, 2));
	}

	class Circle {
	protected:
	public:
		double _r = 0;
		Point _c = Point(0, 0);
		Circle() {};
		Circle(const double & ir, const Point& iPoint) : _r(ir), _c(iPoint) {};
		Circle(const Point& iP1, const Point& iP2, const Point& iP3)
		{
			//cerr << "creating circle with " << endl;
			//cerr << "\tP1: " << iP1 << " P2: " << iP2 << " P3: " << iP3 << endl;
			double ma = (iP2.y - iP1.y) / (iP2.x - iP1.x);
			double mb = (iP3.y - iP2.y) / (iP3.x - iP2.x);
			//cerr << "ma = " << ma << endl;
			//cerr << "mb = " << mb << endl;
			_c.x = (ma * mb*(iP1.y - iP3.y) + mb * (iP1.x + iP2.x) - ma * (iP2.x + iP3.x)) / (2. * (mb - ma));
			//cerr << "_c.x = " << _c.x << endl;
			_c.y = -1. / ma * (_c.x - (iP1.x + iP2.x) / 2.) + (iP1.y + iP2.y) / 2.;
			//cerr << "_c.y = " << _c.y << endl;
			_r = Distance(_c, iP1);
			//cerr << "created circle with center: " << _c << " and radius: " << _r << endl;
		}
		bool contains(const Point& iP)
		{
			//cerr << "Checking point " << iP << " on circle with center: " << _c << " and radius: " << _r <<endl;
			//cerr << "error: " << abs(pow(iP.x - _c.x, 2) + pow(iP.y - _c.y, 2) - _r*_r) << endl;
			return abs(pow(iP.x - _c.x, 2) + pow(iP.y - _c.y, 2) - _r * _r) <= 0.001;
		}
		Point pFromAng(const double _ang) { return Point(_c.x + _r * cos(_ang), _c.y + _r * sin(_ang)); }
	};
	class PCircle : public Circle
	{
	public:
		//x - xc = r*cos(ang)
		//y - yc = r*sin(ang)
		//ang = a + b * t
		double _a = 0;
		double _b = 0;
		double _circ = 0;
		PCircle() {};
		PCircle(const double & ir, const Point& iPoint) : Circle(ir, iPoint) {};
		PCircle(const Point& iP1, const Point& iP2, const Point& iP3) :Circle(iP1, iP2, iP3) {};
		void setParams(const Point& iP1, const Point& iP2, const int iDirection)
		{
			if (!contains(iP1)){cerr << "Point 1: " << iP1 << " not in circunference" << endl;}
			if (!contains(iP2)){cerr << "Point 2: " << iP2 << " not in circunference" << endl;}
			double aAng1 = Atan(iP1 - _c);
			double aAng2 = Atan(iP2 - _c);
			//cerr << "aAng1 = " << aAng1 << "rad = " << aAng1 * 180 / M_PI << "deg" << endl;
			//cerr << "aAng2 = " << aAng2 << "rad = " << aAng2 * 180 / M_PI << "deg" << endl;
			if (aAng1 < 0) aAng1 += 2 * M_PI;
			if (aAng2 < 0) aAng2 += 2 * M_PI;
			if (iDirection >= 0 && aAng2<aAng1) aAng2 += 2 * M_PI;
			else if (iDirection < 0 && aAng2>aAng1) aAng2 -= 2*M_PI;
			cerr << "aAng1 = " << aAng1 << "rad = " << aAng1 * 180 / M_PI << "deg" << endl;
			cerr << "aAng2 = " << aAng2 << "rad = " << aAng2 * 180 / M_PI << "deg" << endl;

			_a = aAng1;
			_b = aAng2 - aAng1;

			//cerr << "_a = " << _a << endl;
			//cerr << "_b = " << _b << endl;
			_circ = abs(aAng2 - aAng1) * _r;
			//cerr << "_circ = " << _circ << endl;
		}
		double angFromT(const double t) { return _a + _b * t; }
		Point pFromT(const double t) { return pFromAng(angFromT(t)); }
		double tFromCirc(const double iCirc) { return iCirc / _circ; }
		Point pFromCirc(const double iCirc) { return pFromT(tFromCirc(iCirc)); }
		PCircle internal(const double& newRad)
		{
			PCircle aTemp(newRad, _c);
			aTemp._a = _a;
			aTemp._b = _b;
			aTemp._circ = abs(angFromT(1) - angFromT(0)) * aTemp._r;
			return aTemp;
		}
	};
}

namespace racing {
	using namespace trigonometry;
	//Thrust constants
	static int max_trhust = 100;

	//Distance constants
	static int min_dist_max_speed = 5000;
	static double max_speed_reduction = 0.5;
	static double dist_const = -1 * max_speed_reduction / min_dist_max_speed;

	//Angle constants
	static const double ang_const_a = 2.103186e-17;
	static const double ang_const_b = 19.69333;
	static const double ang_const_c = 89.44275;
	static const double ang_const_d = 1.000001;
	static const CurveFit ang_red(ang_const_a, ang_const_b, ang_const_c, ang_const_d);

	static const double dist_const_a = 0.1527513;
	static const double dist_const_b = 0.4343583;
	static const double dist_const_c = 253942899999.99997;
	static const double dist_const_d = 1332764;
	//y = 715.8107 + (-4.682333e-14 - 715.8107)/(1 + (x/2327.689)^2.151523)
	//y = 1332764 + (0.1527513 - 1332764)/(1 + (x/253942899999.99997)^0.4343583)
	static const CurveFit dist_red(dist_const_a, dist_const_b, dist_const_c, dist_const_d);
	//static double max_thrust_reduction = 1;
	//static double ang_const_b_percent = 1;
	//static double ang_const_b = ang_const_b_percent * max_thrust_reduction / 180;
	//static double ang_const_a = (max_thrust_reduction / 180 - ang_const_b) / 180;
	//static double ang_const_cubic = 8 * 90 / pow(max_thrust_reduction, 3);

	struct Car {
		Point _p = Point(-1, -1);
		Point _p_prev = Point(-1, -1);
		int _thrust = 0;
		double _v = 0;
		double _v_prev = 0;
		double _dir = 0;
		double _ang = 0;
		double _d = 0;
		Car() {};
		void setNewPos(const Point& iP)
		{
			_v = Distance(iP, _p_prev);
			_p_prev = _p;
			_p = iP;
		}
	};
	
	struct Checkpoint {
		Point _p = Point(0,0);
		double _ang = 0;
		double _d = -1;
		typedef shared_ptr<Checkpoint> Ptr;
		static Ptr Create() { return make_shared<Checkpoint>(); }
		static Ptr Create(const Checkpoint& iCheck) { return make_shared<Checkpoint>(iCheck); }

		Checkpoint() {};
		Checkpoint(const int x, const int y) : _p(x,y) {};
		Checkpoint(const Checkpoint& iCheck) : _p(iCheck._p), _ang(iCheck._ang), _d(iCheck._ang) {};
		Checkpoint(Checkpoint&& iCheck) :_p(iCheck._p), _ang(iCheck._ang), _d(iCheck._ang)
		{
			iCheck._p = Point(0, 0);
			iCheck._ang = 0;
			iCheck._d = -1; 
		};
		bool operator== (const Checkpoint& b) { return Distance(this->_p, b._p) < 600; }
		friend bool operator< (const Checkpoint& a, const Checkpoint& b) { 
			return (a._p < b._p); 
		}
		bool operator< (const Checkpoint& b) { return (_p < b._p); }
		bool operator<< (const Checkpoint& b) { return (_p < b._p); }
		friend ostream& operator<<(ostream& os, const Checkpoint& iC)
		{
			os << iC._p;
			return os;
		}

		void recalculateInfo(Car& iCar) {
			Pair aDist = _p - iCar._p;
			cerr << "Distance to point: X= " << aDist.x << " Y= " << aDist.y << endl;

			_d = Distance(iCar._p, _p);
			double aAng = atan2(aDist.y, aDist.x) * 180 / M_PI;
			iCar._d = _d;
			iCar._ang = _ang - aAng;
		}
	};

	struct Map
	{
	private:
		map<int, Checkpoint> _posCheckMap;
		map<Checkpoint, int> _checkPosMap;
		Checkpoint::Ptr _currentCheck;
		bool _complete;
		int _currentCheckPos;
		int _totalChecks;
	public:
		Map() :_currentCheckPos(-1), _totalChecks(0), _complete(false) {}
		bool addPoint(const Checkpoint& iCheckpoint)
		{
			if (_checkPosMap.find(iCheckpoint) == _checkPosMap.end())
			{
				++_currentCheckPos;
				++_totalChecks;
				cerr << "Adding checkpoint: " << iCheckpoint << " at possition" << _currentCheckPos << endl;
				_posCheckMap.insert(make_pair(_currentCheckPos,iCheckpoint));
				_checkPosMap[_posCheckMap[_currentCheckPos]] = _currentCheckPos;
				return true;
			}
			else
			{
				if (_currentCheckPos != _checkPosMap[iCheckpoint]) _complete = true;
				_currentCheckPos = _checkPosMap[iCheckpoint];
				cerr << "current possition: "<< _currentCheckPos << endl;
			}
			return false;
		}
		size_t size() { return _totalChecks; }
		bool complete() { return _complete; }
		Checkpoint getCurrentCheck() { return _posCheckMap[_currentCheckPos]; }
		Checkpoint getNext() { return getCheck(1); }
		Checkpoint getCheck(const int i) 
		{
			int aNextPos = (_currentCheckPos + i) % _totalChecks;
			return _posCheckMap[aNextPos];
		}
		friend ostream& operator<<(ostream& os, const Map& iM)
		{
			os << "Checkpoints: position - coords" << endl;
			for (auto check_pair : iM._posCheckMap)
			{
				os << "\t" << check_pair.first << " - " << check_pair.second << endl;
			}
			return os;
		}
	};
	
	static double getAngReduction(const Checkpoint& iCheck)
	{
		return ang_red.y(iCheck._ang);
	}

	void Play()
	{
		cerr << "Playing race" << endl;
		PCircle aPCircle(Point(6,2), Point(5,-1), Point(4,-2));
		aPCircle.setParams(Point(5,-1),Point(4,-2),-1);

		/*cerr << aPCircle.pFromT(2) << endl;
		PCircle aPCircle2(Point(10, 7), Point(4, 1), Point(12, 5));
		aPCircle2.setParams(Point(4, 1), Point(10, 7), -1);
		PCircle aIntPCircle = aPCircle2.internal(0.5*aPCircle2._r);*/
		/*Checkpoint c1(0, 0);
		Checkpoint c2(100, 0);
		Checkpoint c3(100, 100);
		Checkpoint c4(0, 100);
		Map aMap;
		aMap.addPoint(c1);
		cerr << "Complete : " << aMap.complete() << endl;
		aMap.addPoint(c2);
		cerr << "Complete : " << aMap.complete() << endl;
		aMap.addPoint(c2);
		cerr << "Complete : " << aMap.complete() << endl;
		aMap.addPoint(c3);
		cerr << "Complete : " << aMap.complete() << endl;
		aMap.addPoint(c4);
		cerr << "Complete : " << aMap.complete() << endl;
		aMap.addPoint(c1);
		cerr << "Complete : " << aMap.complete() << " - this should be the frist 1" << endl;
		aMap.addPoint(c1);
		cerr << "Complete : " << aMap.complete() << endl;
		aMap.addPoint(c2);
		cerr << "Complete : " << aMap.complete() << endl;
		aMap.addPoint(c3);
		cerr << "Complete : " << aMap.complete() << endl;
		aMap.addPoint(c3);
		cerr << "Complete : " << aMap.complete() << endl;
		cerr << "Size: " << aMap.size() << endl;
		cerr << "A map: " << endl << aMap;
		cerr << "Current " << aMap.getCurrentCheck() << endl;
		cerr << "Next " << aMap.getNext() << endl;
		cerr << "Jump 2 " << aMap.getCheck(2) << endl;*/
	}
}

using namespace racing;
using namespace trigonometry;

void play_race()
{
	Car aMainCar;
	Car aBossCar;
	Map aMap;
	std::set<Checkpoint> aCheckpointsSet;
	std::vector<Checkpoint> aCheckpointsVector;
	bool boostUsed = false;
	// game loop
	while (1) {

		//int nextCheckpointX; // x position of the next check point
		//int nextCheckpointY; // y position of the next check point
		int nextCheckpointDist; // distance to the next checkpoint
								//int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
		Checkpoint aCheck;
		Point aCarP;
		cin >> aCarP.x >> aCarP.y >> aCheck._p.x >> aCheck._p.y >> nextCheckpointDist >> aCheck._ang; cin.ignore();
		cin >> aBossCar._p.x >> aBossCar._p.y; cin.ignore();
		aMainCar.setNewPos(aCarP);
		cerr << "speed: " << aMainCar._v;


		aCheck.recalculateInfo(aMainCar);
		aMap.addPoint(aCheck);
		//If different x and y than prev checkpoint we have a newone
		//cerr << "Car: X= " << aMainCar._p.x << " Y= " << aMainCar._p.y << endl;
		//cerr << "Input: Dist= " << nextCheckpointDist << " Angle= " << aCheck._ang << endl;
		//cerr << "Calc: Dist= " << aCheck._d << " Angle= " << aCheck._ang << endl;
		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;


		// You have to output the target position
		// followed by the power (0 <= thrust <= 100)
		// i.e.: "x y thrust"		

		//cerr << "ang red: " << ang_red << " dist red: " << dist_red << endl;
		int thrust = (int)floor(max_trhust * (1 - ang_red.y(aCheck._ang)) * (1 - dist_red.y(aCheck._d)));
		cerr << "thrust: " << thrust << endl;

		Point aNextP = aCheck._p;
		if (aMap.complete())
		{
			int dir = Atan(aMap.getCurrentCheck()._p - aMainCar._p) - Atan(aMap.getNext()._p - aMap.getCurrentCheck()._p);
			PCircle aPCircle(aMainCar._p, aMap.getCurrentCheck()._p, aMap.getNext()._p);
			cerr << "direction: " << dir << endl;
			aPCircle.setParams(aMap.getCurrentCheck()._p, aMainCar._p, sgn(dir));
			PCircle aInteriorPCircle = aPCircle.internal(aPCircle._r - ((600 + aMainCar._v) * exp(-1 * nextCheckpointDist)));
			aNextP = aInteriorPCircle.pFromCirc(nextCheckpointDist*0.4);
		}

		if (aCheck._ang < 10 && thrust == 100 && aCheck._d > 10000 && !boostUsed)
		{
			cout << (int)aNextP.x << " " << (int)aNextP.y << " " << "BOOST" << endl;
			boostUsed = true;
		}
		else cout << (int)aNextP.x << " " << (int)aNextP.y << " " << (int)thrust << endl;
	}
}

void debug_race()
{
	Car aMainCar;
	Car aBossCar;
	Map aMap;
	std::set<Checkpoint> aCheckpointsSet;
	std::vector<Checkpoint> aCheckpointsVector;
	bool boostUsed = false;
	// game loop
	//Go to start
	while (1) {
		Point destination(1000,1000);
		int nextCheckpointDist; 
		Checkpoint aCheck;
		Point aCarP;
		cin >> aCarP.x >> aCarP.y >> aCheck._p.x >> aCheck._p.y >> nextCheckpointDist >> aCheck._ang; cin.ignore();
		cin >> aBossCar._p.x >> aBossCar._p.y; cin.ignore();
		aMainCar.setNewPos(aCarP);
		double dist = Distance(destination, aMainCar._p);
		cerr << "Current speed = " << aMainCar._v << endl;
		cerr << "Desired speed = " << dist_red.y(dist) << endl;
		double thrust = (dist_red.y(dist) - aMainCar._v) * 1;
		if (thrust < 0) thrust = 0;
		if (thrust > 100) thrust = 100;
		cout << (int)destination.x << " " << (int)destination.y << " " << (int)thrust << endl;
		if (Distance(aMainCar._p, destination) < 200) break;
	}
	//Turn
	int count = 0;
	while (1)
	{
		Point destination(15000, 1000);
		int nextCheckpointDist; 
		Checkpoint aCheck;
		Point aCarP;
		cin >> aCarP.x >> aCarP.y >> aCheck._p.x >> aCheck._p.y >> nextCheckpointDist >> aCheck._ang; cin.ignore();
		cin >> aBossCar._p.x >> aBossCar._p.y; cin.ignore();
		aMainCar.setNewPos(aCarP);
		cerr << "speed: " << aMainCar._v;
		aCheck.recalculateInfo(aMainCar);
		aMap.addPoint(aCheck);
		cout << (int)destination.x << " " << (int)destination.y << " " << 0 << endl;
		if (abs(aMainCar._ang) < 5) ++count;
		if (count >= 10) break;
	}
	cerr << "Jumping to light" << endl;
	while (1)
	{
		Point destination(15000, 1000);
		int nextCheckpointDist;
		Checkpoint aCheck;
		Point aCarP;
		cin >> aCarP.x >> aCarP.y >> aCheck._p.x >> aCheck._p.y >> nextCheckpointDist >> aCheck._ang; cin.ignore();
		cin >> aBossCar._p.x >> aBossCar._p.y; cin.ignore();
		aMainCar.setNewPos(aCarP);
		cerr << "speed: " << aMainCar._v;
		aCheck.recalculateInfo(aMainCar);
		aMap.addPoint(aCheck);
		cout << (int)destination.x << " " << (int)destination.y << " " << 100 << endl;
	}
}

int main()
{
	debug_race();
	
	
}