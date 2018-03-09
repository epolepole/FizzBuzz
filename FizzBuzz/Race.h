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
		virtual bool operator==(const Pair& b) const { return x == b.x and y == b.y; }
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
			cerr << "creating circle with " << endl;
			cerr << "\tP1: " << iP1 << " P2: " << iP2 << " P3: " << iP3 << endl;
			double ma = (iP2.y - iP1.y) / (iP2.x - iP1.x);
			double mb = (iP3.y - iP2.y) / (iP3.x - iP2.x);
			//cerr << "ma = " << ma << endl;
			//cerr << "mb = " << mb << endl;
			_c.x = (ma * mb*(iP1.y - iP3.y) + mb * (iP1.x + iP2.x) - ma * (iP2.x + iP3.x)) / (2. * (mb - ma));
			//cerr << "_c.x = " << _c.x << endl;
			_c.y = -1. / ma * (_c.x - (iP1.x + iP2.x) / 2.) + (iP1.y + iP2.y) / 2.;
			//cerr << "_c.y = " << _c.y << endl;
			_r = Distance(_c, iP1);
			cerr << "created circle with center: " << _c << " and radius: " << _r << endl;
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
			if (not contains(iP1)){cerr << "Point 1: " << iP1 << " not in circunference with center: " << _c << " and radius: " << _r << endl;}
			if (not contains(iP2)){cerr << "Point 2: " << iP2 << " not in circunference with center: " << _c << " and radius: " << _r << endl;}
			double aAng1 = atan2(iP1.y - _c.y, iP1.x - _c.x);
			double aAng2 = atan2(iP2.y - _c.y, iP2.x - _c.x);
			if (aAng1 < 0) aAng1 += 2 * M_PI;
			if (aAng2 < 0) aAng2 += 2 * M_PI;
			if (iDirection >= 0 and aAng2<aAng1) aAng2 += 2 * M_PI;
			else if (iDirection < 0 and aAng2>aAng1) aAng2 -= 2*M_PI;
			cerr << "aAng1 = " << aAng1 << endl;
			cerr << "aAng2 = " << aAng2 << endl;

			_a = aAng1;
			_b = aAng2 - aAng1;

			cerr << "_a = " << _a << endl;
			cerr << "_b = " << _b << endl;
			_circ = abs(aAng2 - aAng1) * _r;
			cerr << "_circ = " << _circ << endl;
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
	static int min_dist_max_speed = 500;
	static double max_speed_reduction = 1;
	static double dist_const = -1 * max_speed_reduction / min_dist_max_speed;

	//Angle constants
	static double max_thrust_reduction = 1;
	static double ang_const_b_percent = 1;
	static double ang_const_b = ang_const_b_percent * max_thrust_reduction / 180;
	static double ang_const_a = (max_thrust_reduction / 180 - ang_const_b) / 180;
	static double ang_const_cubic = 8 * 90 / pow(max_thrust_reduction, 3);

	struct Car {
		Point _p = Point(-1, -1);
		int _thrust = 0;
		double _v = 0;
		double _v_prev = 0;
		double _dir = 0;
		double _ang = 0;
		double _d = 0;
		Car() {};
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
	void Play()
	{
		cerr << "Playing race" << endl;
		PCircle aPCircle(Point(0, 1), Point(1, 0), Point(2, 1));
		aPCircle.setParams(Point(1,0),Point(2,1),-1);
		cerr << aPCircle.pFromT(2) << endl;

		PCircle aPCircle2(Point(10, 7), Point(4, 1), Point(12, 5));
		aPCircle2.setParams(Point(4, 1), Point(10, 7), -1);
		cerr << aPCircle2.pFromT(0) << endl;
		cerr << aPCircle2.pFromT(0.5) << endl;
		cerr << aPCircle2.pFromT(1) << endl;
		cerr << aPCircle2.pFromT(2) << endl;
		PCircle aIntPCircle = aPCircle2.internal(0.5*aPCircle2._r);
		cerr << aIntPCircle.pFromT(0) << endl;
		cerr << aIntPCircle.pFromT(0.5) << endl;
		cerr << aIntPCircle.pFromT(1) << endl;
		cerr << aIntPCircle.pFromT(2) << endl;
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

int main_()
{
	Car aMainCar;
	Car aBossCar;
	Map aMap;
	std::set<Checkpoint> aCheckpointsSet;
	std::vector<Checkpoint> aCheckpointsVector;
	bool boostUsed = false;
	// game loop
	while (1) {

		int nextCheckpointX; // x position of the next check point
		int nextCheckpointY; // y position of the next check point
		int nextCheckpointDist; // distance to the next checkpoint
		int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
		Checkpoint aCheck;

		cin >> aMainCar._p.x >> aMainCar._p.y >> aCheck._p.x >> aCheck._p.y >> nextCheckpointDist >> aCheck._ang; cin.ignore();
		cin >> aBossCar._p.x >> aBossCar._p.y; cin.ignore();
		aCheck.recalculateInfo(aMainCar);
		//If different x and y than prev checkpoint we have a newone
		//cerr << "Car: X= " << aMainCar._p.x << " Y= " << aMainCar._p.y << endl;
		//cerr << "Input: Dist= " << nextCheckpointDist << " Angle= " << aCheck._ang << endl;
		//cerr << "Calc: Dist= " << aCheck._d << " Angle= " << aCheck._ang << endl;
		aMap.addPoint(aCheck);
		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;


		// You have to output the target position
		// followed by the power (0 <= thrust <= 100)
		// i.e.: "x y thrust"


		//Angle deviation reduction
		// double ang_red = abs(aCheck.ang) * (ang_const_a * abs(aCheck.ang) + ang_const_b);
		// double ang_red =cbrt((abs(aCheck.ang) - 90)/ang_const_cubic ) + max_thrust_reduction/2.;
		double ang_red = 0;
		if (abs(aCheck._ang) > 80)  ang_red = 1;
		//Distance speed reduction
		double dist_red = 0;
		if (aCheck._d < min_dist_max_speed)
			dist_red = max_speed_reduction + dist_const * aCheck._d;

		//cerr << "dist_red =  max_spd_red + dist_const * aCheck.d" << endl;
		//cerr << dist_red << "=" << max_speed_reduction << "+ " << dist_const << "*" << aCheck._d << endl;

		//cerr << "ang red: " << ang_red << " dist red: " << dist_red << endl;
		int thrust = max_trhust * (1 - ang_red) * (1 - dist_red);
		//cerr << "thrust: " << thrust << endl;

		Point aNextP = aCheck._p;
		if (aMap.complete())
		{
			int dir = sgn(Atan(aMap.getCurrentCheck()._p - aMainCar._p) - Atan(aMap.getNext()._p - aMap.getCurrentCheck()._p));
			PCircle aPCircle(aMainCar._p, aMap.getCurrentCheck()._p, aMap.getNext()._p);
			aPCircle.setParams(aMap.getCurrentCheck()._p, aMainCar._p, dir);
			PCircle aInteriorPCircle = aPCircle.internal(aPCircle._r - 800);
			aNextP = aInteriorPCircle.pFromCirc(nextCheckpointDist*0.3);
		}

		if (aCheck._ang < 10 and thrust == 100 && aCheck._d > 10000 and not boostUsed)
		{
			cout << aNextP.x << " " << aNextP.y << " " << "BOOST" << endl;
			boostUsed = true;
		}
		else cout << (int)aNextP.x << " " << (int)aNextP.y << " " << (int)thrust << endl;
	}
}
