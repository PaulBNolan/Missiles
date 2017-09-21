#include <iostream>


//This is a structure that gives the missile and target their position
typedef struct Position
{
	int x;
	int y;

	void print()
	{
		std::cout << x << y << std::endl;
	}
}Coordinates;

//This is a enum class that designates the missile type
enum WarHead { EXPLOSIVE, NUCLEAR };

typedef struct Enemy {
	Coordinates coordinates;
}Target;

struct Missile {
	WarHead payload;
	Coordinates coordinates;
	Target target;

	bool missileFired;
	//The int values used to start and end the missiles journey
	int launchCode = 1234;
	int missileRange = 60;
	//The int values that helps determines the missiles radius and whether it launches at all
	int missileType = 0;
	int enteredCode = 0;
	//The int values for the possible radiuses of the missiles
	int warheadRadius = 0;
	int nuclearRadius = 20;
	int explosiveRadius = 10;
	//Bool values that determine whether or not a collision occurs and if the player whats another go
	bool collision = false;
	bool systemActive = true;
	int replay;

	//Set
	void arm()
	{
		if (missileFired != true)
		{
			missileFired = false;
		}
	}
	//Sets the base payload type
	void defaultPayloadType()
	{
		payload = EXPLOSIVE;
	}

	//This function is used to move the missile
	void update()
	{
		coordinates.x += 1;
		coordinates.y += 2;

		collisionDetection();

		missileRange--;

		if (missileRange == 0 || collision == true)
		{
			if (collision == true)
			{
				std::cout << "Target Hit" << std::endl;
			}

			else if (collision == false)
			{
				std::cout << "Target Missed" << std::endl;
			}

			std::cout << "Do you want another attempt to hit the target? Yes(1) or No(2)" << std::endl;
			std::cin >> replay;

			while (replay < 1 || replay > 2)
			{
				std::cout << "Error:Enter a valid answer." << std::endl;
				std::cin >> replay;
			}

			if (replay == 1)
			{
				systemActive = true;
			}

			else
			{
				systemActive = false;
			}
			missileFired = false;
		}
	}

	//This function is used to determine warhead type
	void warheadType(int type)
	{
		if (type == 1)
		{
			payload = EXPLOSIVE;
			warheadRadius = explosiveRadius;
		}

		if (type == 2)
		{
			payload = NUCLEAR;
			warheadRadius = nuclearRadius;
		}

		std::cout << "The Warhead now has a radius of effect of " << warheadRadius << std::endl;
	}

	//This function helps to determine whether or not the missile strikes the target
	void collisionDetection()
	{
		if (coordinates.x - warheadRadius <= target.coordinates.x && coordinates.x + warheadRadius >= target.coordinates.x
			&&
			coordinates.y - warheadRadius <= target.coordinates.y && coordinates.y + warheadRadius >= target.coordinates.y)
		{
			collision = true;
		}
		else
		{
			collision = false;
		}
	}

	//This function is where the player inputs his values
	void inputValues()
	{
		std::cout << "Which payload type do you desire to launch: (1)Explosive or (2)Nuclear." << std::endl;
		std::cin >> missileType;
		warheadType(missileType);

		while (missileType < 1 || missileType > 2)
		{
			std::cout << "ERROR:Please enter a valid missile type." << std::endl;
			std::cin >> missileType;
		}

		std::cout << "Please Note: We will have no effect on the missiles path after launching." << std::endl;
		std::cout << "For reference the missile moves twice the speed vertically as it does horizontally." << std::endl;
		std::cout << "i.e It has a X speed of 1 and a Y speed of 2" << std::endl;

		std::cout << "Now enter the X Coordinates of your target." << std::endl;
		std::cin >> target.coordinates.x;

		std::cout << "Now enter the Y Coordinates of your target." << std::endl;
		std::cin >> target.coordinates.y;

		std::cout << "Finally enter the Launch Code" << std::endl;
		std::cin >> enteredCode;

		while (enteredCode != launchCode)
		{
			std::cout << "ERROR:Please enter correct Launch Code." << std::endl;
			std::cin >> enteredCode;
		}

		armWarhead();

	}

	//Missile used for arming the missile. If not armed the radius values do not apply
	void armWarhead()
	{
		int armingMissile = 0;
		std::cout << "Do you seek to arm the missile? Yes(1) or No(2)" << std::endl;
		std::cin >> armingMissile;

		while (armingMissile < 0 || armingMissile > 2)
		{
			std::cout << "Error:Please give a valid option." << std::endl;
		}

		if (armingMissile == 1)
		{
			std::cout << "Missile Armed" << std::endl;
		}
		else
		{
			std::cout << "Missile not armed payload disabled." << std::endl;
			std::cout << "Only a direct hit will have any effect." << std::endl;
			warheadRadius = 0;
		}
	}
	//This helps to set and reset the values of the coordinates to zero
	void setValues()
	{
		coordinates.x = 0;
		coordinates.y = 0;

		target.coordinates.x = 0;
		target.coordinates.y = 0;

		warheadRadius = 0;
	}
};

int main()
{
	Missile missile;

	while (missile.systemActive == true)
	{
		missile.defaultPayloadType();
		missile.setValues();

		missile.inputValues();

		if (missile.enteredCode == missile.launchCode)
		{
			missile.missileFired = true;
		}

		while (missile.missileFired == true)
		{
			missile.update();
		}
	}

	system("PAUSE");
}