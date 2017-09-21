#include <iostream>

typedef struct Position
{
	int x;
	int y;

	void print()
	{
		std::cout << x << y << std::endl;
	}
}Coordinates;

enum WarHead { EXPLOSIVE, NUCLEAR };

typedef struct Enemy {
	Coordinates coordinates;
}Target;

struct Missile {
	WarHead payload;
	Coordinates coordinates;
	Target target;

	bool missileFired;
	int launchCode = 1234;
	int range = 20;
	
	void arm()
	{
		if (missileFired != true)
		{
			missileFired = false;
		}
	}

	void defaultPayloadType()
	{
		payload = EXPLOSIVE;
	}

	void update()
	{
		if (missileFired == true)
		{
			for (int index = 0; index < range; index++)
			{
				coordinates.x += 1;
				coordinates.y += 2;
				if (coordinates.x == target.coordinates.x && coordinates.y == target.coordinates.y)
				{
					std::cout << "Target hit" << std::endl;
					break;
				}
			}
			if (coordinates.x != target.coordinates.x || coordinates.y != target.coordinates.y)
			{
				std::cout << "Target Missed" << std::endl;
			}

		}
	}
};

int main()
{
	Missile missile;
	int missileType = 0;
	int enteredCode = 0;

	missile.coordinates.x = 0;
	missile.coordinates.y = 0;

	missile.target.coordinates.x = 0;
	missile.target.coordinates.y = 0;

	std::cout << "Which payload type do you desire to launch: (1)Explosive or (2)Nuclear." << std::endl;
	std::cin >> missileType;

	if (missileType == 1)
	{
		missile.payload = EXPLOSIVE;
	}

	if (missileType == 2)
	{
		missile.payload = NUCLEAR;
	}

	std::cout << "Now enter the X Coordinates of your target." << std::endl;
	std::cin >> missile.target.coordinates.x;

	std::cout << "Now enter the Y Coordinates of your target." << std::endl;
	std::cin >> missile.target.coordinates.y;

	std::cout << "Finally enter the Launch Code" << std::endl;
	std::cin >> enteredCode;

	while (enteredCode != missile.launchCode)
	{
		std::cout << "ERROR:Please enter correct Launch Code." << std::endl;
		std::cin >> enteredCode;
	}

	if (enteredCode == missile.launchCode)
	{
		missile.missileFired = true;
	}

	missile.update();

	system("PAUSE");
}