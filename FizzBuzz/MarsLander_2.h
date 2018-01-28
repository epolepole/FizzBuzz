#pragma once
// MarsLanding2.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

namespace marslanding {
	static const double g = -3.711;
	static const int MIN_ROTATION = 15;
	static const int MAX_ROTATION = 45;
	static const int  MAX_ROT_KEEP_ALT = 45;
	static const int MAX_ROT_HIGH_GROUND = 15;
	static const int SPEX_COEF = 2;
	static const int POSX_COEF = 30;

	static const int MIN_DIST_ROT_CHECK = 75;
	static const int ALTITUDE_FIX = 2000;
	static const int ALTITUDE_SLOW = 200;

	static const int MAX_X_SPEED = 100;

	using namespace std;

	struct Pair {
		Pair() : x(0), y(0) {};
		Pair(int x, int y) : x(x), y(y) {};
		Pair(const Pair& iOther) : x(iOther.x), y(iOther.y) {};
		int x;
		int y;

		friend ostream& operator<<(ostream& os, const Pair& iP)
		{
			iP.print(os);
			return os;
		}
		virtual void getDeviation(const Pair& desiredPossition, Pair & oDeviation)
		{
			oDeviation.x = desiredPossition.x - x;
			oDeviation.y = desiredPossition.y - y;
		}
		virtual Pair getDeviation(const Pair& iDesiredPossition)
		{
			return Pair(iDesiredPossition.x - x, iDesiredPossition.y - y);
		}
		virtual ~Pair() {}

	private:
		virtual void print(std::ostream& os) const
		{
			os << '(' << x << ',' << y << ')';
		}
	};

	struct Point : public Pair
	{
		Point() :Pair() {};
		Point(int x, int y) : Pair(x, y) {};
		Point(const Point& iOther) : Pair(iOther) {};
	} aLandP, aLeftLand, aRightLand;

	struct Speed : public Pair
	{
		Speed() :Pair() {};
		Speed(int x, int y) : Pair(x, y) {};
		Speed(const Speed& iOther) : Pair(iOther) {};

		virtual void getDeviation(const Speed& maxSpeed, Speed & oDeviation)
		{
			oDeviation.x = maxSpeed.x - x;
			oDeviation.y = -maxSpeed.y - y;
		}
		virtual Speed getDeviation(const Speed& maxSpeed)
		{
			return Speed(maxSpeed.x - x, -maxSpeed.y - y);
		}
	};

	struct Controlls
	{
		Controlls() {};
		Controlls(const int iFuel, const int iPower, const int iRotation) :
			fuel(iFuel), power(iPower), rotation(iRotation) {}

		int fuel;
		int power;
		int rotation;

		friend ostream& operator<<(ostream& os, const Controlls& iP)
		{
			os << "Fuel: " << iP.fuel << " Thrust: " << iP.power << " Rotation: " << iP.rotation;
			return os;
		}
		void desiredRotation(int iRot, int iMaxRotation = MAX_ROTATION)
		{
			if (iRot > iMaxRotation) iRot = iMaxRotation;
			else if (iRot < -1 * iMaxRotation) iRot = -1 * iMaxRotation;

			rotation = iRot;

			int absRot = abs(iRot);
			if (absRot >= 15) setMinPower(1);
			else if (absRot >= 30) setMinPower(2);
			else if (absRot >= 45) setMinPower(3);
			else if (absRot >= 60) setMinPower(4);
			else if (absRot >= 75) setMinPower(4);
			else if (absRot >= 90) setMinPower(4);
		}
		void setMinPower(const int iPow)
		{
			cerr << "setting min power to: " << iPow << endl;
			if (iPow > power) power = iPow;
		}

		void desiredPower(const unsigned int iPower)
		{
			if (iPower > 4) power = 4;
			power = iPower;
			cerr << "Setting power to " << power << endl;
		}
		void rotateRight()
		{
			cerr << "rotating right" << endl;
			if (rotation > -90) rotation -= 15;
		}
		void rotateLeft()
		{
			cerr << "rotating left" << endl;
			if (rotation < 90)  rotation += 15;
		}
		void send()
		{
			cerr << "sending: " << rotation << " " << power << endl;
			cout << rotation << " " << power << endl;
		}
	};

	/**
	* Auto-generated code below aims at helping you parse
	* the standard input according to the problem statement.
	**/

	void findLandPoint(const std::vector<Point>& iSurface)
	{
		Point aPreviousP = iSurface.at(0);
		for (size_t i = 1; i < iSurface.size(); ++i)
		{
			Point aCurrentP = iSurface.at(i);
			cerr << "Checking: " << aCurrentP << endl;
			if (aPreviousP.y == aCurrentP.y)
			{
				cerr << "Found: " << aCurrentP << endl;

				aLandP.y = aCurrentP.y;
				aLandP.x = (aCurrentP.x + aPreviousP.x) / 2;
				aRightLand = aCurrentP;
				aLeftLand = aPreviousP;
				break;
			}
			aPreviousP = aCurrentP;
		}
	}

	void solveSecondOrderEq(const double a, const double b, const double c, double & s1, double & s2)
	{
		s1 = (-1. * b + sqrt(b*b - 4.*a*c)) / a;
		s2 = (-1. * b - sqrt(b*b - 4.*a*c)) / a;
	}

	struct Ship {
		Ship() {};
		Controlls controlls;
		Speed speed;
		Point possition;

		friend ostream& operator<<(ostream& os, const Ship& iP)
		{
			os << "Possition: " << iP.possition << " Speed: " << iP.speed << " Controlls: [" << iP.controlls << "]";
			return os;
		}

		void goToLanding()
		{
			//MAX_ROT_HIGH_GROUND
			//We are in the landing zone.
			int speed_x = (aLandP.x - possition.x) / POSX_COEF;
			bool force_alt = false;
			if ((possition.y - aLandP.y) < ALTITUDE_FIX)
			{
				cerr << "Forcing altitude fix" << endl;
				force_alt = true;
			}
			if (possition.x > aLeftLand.x and possition.x < aRightLand.x)
			{
				if (abs(speed.x) > 20)
				{
					keepSpeed(Speed(speed_x, -2), force_alt);
				}
				else {
					if ((possition.y - aLandP.y) < ALTITUDE_SLOW)
					{
						cerr << "Initiate landing" << endl;
						keepSpeed(Speed(speed_x, -5));
					}
					else keepSpeed(Speed(speed_x, -30));
				}
			}
			else keepSpeed(Speed(speed_x, 0), force_alt);
		}

		void keepSpeed(const Speed& iSpeed, bool enforce_altitude = false)
		{
			if (speed.y < iSpeed.y) controlls.desiredPower(4);
			else if (speed.y > iSpeed.y) controlls.desiredPower(0);
			int aRot = MIN_ROTATION * (int)floor((speed.x - min(MAX_X_SPEED, iSpeed.x)) / SPEX_COEF);
			if (iSpeed.y == 0)
			{
				cerr << "speed y = 0. Desired rotation: " << aRot << endl;
				int max_rotation = enforce_altitude ? MAX_ROT_HIGH_GROUND : MAX_ROT_KEEP_ALT;
				controlls.desiredRotation(aRot, max_rotation);
			}
			else
			{
				cerr << "desired rotation: " << aRot << endl;
				controlls.desiredRotation(aRot);
			}


		}
		void sendState()
		{
			altitudeRotationCheck();
			controlls.send();
		}
		void retrieveState()
		{
			cin >> possition.x >> possition.y >> speed.x >> speed.y >> controlls.fuel >> controlls.rotation >> controlls.power; cin.ignore();
		}
		Speed landingSpeedNoThrust()
		{
			double vl1, vl2;
			double c_a = 1;
			double c_b = speed.y;
			double c_c = 2 * g * (possition.y - aLandP.y);
			solveSecondOrderEq(c_a, c_b, c_c, vl1, vl2);
			cerr << vl1 << " | " << vl2 << endl;
			return Speed(speed.x, (int)floor(min(vl1, vl2)));
		}
	private:
		void altitudeRotationCheck()
		{
			if (possition.y < aLandP.y + MIN_DIST_ROT_CHECK) controlls.desiredRotation(0);
		}
	};

	class MarsLander_2
	{
	public:
		static int Play()
		{
			int surfaceN; // the number of points used to draw the surface of Mars.
			cin >> surfaceN; cin.ignore();
			vector<Point> aSurface;
			for (int i = 0; i < surfaceN; i++) {
				int landX; // X coordinate of a surface point. (0 to 6999)
				int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
				cin >> landX >> landY; cin.ignore();
				aSurface.push_back(Point(landX, landY));
			}
			Speed aMaxSpeed{ 20, 40 };
			findLandPoint(aSurface);
			cerr << aLandP << endl;

			Ship aShip;
			// game loop
			while (1) {
				aShip.retrieveState();

				cerr << aShip << endl;
				cerr << "Land deviation: " << aShip.possition.getDeviation(aLandP) << endl;
				cerr << "Speed deviation: " << aShip.speed.getDeviation(aMaxSpeed) << endl;
				// Write an action using cout. DON'T FORGET THE "<< endl"
				// To debug: cerr << "Debug messages..." << endl;

				// rotate power. rotate is the desired rotation angle. power is the desired thrust power.
				//aShip.keepSpeed(Speed(15, 0));
				//aShip.moveHorizontaly(aLandP.x);
				aShip.goToLanding();
				//aShip.landingSpeedNoThrust();
				aShip.sendState();
			}
		}
	};
}