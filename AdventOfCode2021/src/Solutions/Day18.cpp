#include "Day18.h"

#include <math.h>

class Pair
{
public:
	Pair(int numLeft, int numRight, Pair* parent)
		:numberLeft(numLeft), numberRight(numRight), parent(parent), pairLeft(nullptr), pairRight(nullptr)
	{

	}

	Pair(Pair* pairLeft, Pair* pairRight, Pair* parent)
		:pairLeft(pairLeft), pairRight(pairRight), parent(parent), numberLeft(-1), numberRight(-1)
	{

	}

	Pair()
		:pairLeft(nullptr), pairRight(nullptr), parent(parent), numberLeft(-1), numberRight(-1)
	{

	}

	Pair(const std::string& str, Pair* parent)
		:parent(parent)
	{
		int counter = 0;
		size_t i;
		for (i = 1; i < str.size(); i++)
		{
			char c = str[i];
			if (c == '[')
				counter++;
			else if (c == ']')
				counter--;

			if (counter == 0)
				break;
		}

		std::string leftPart = str.substr(1, i);
		std::string rightPart = str.substr(i + 2, str.size() - (i + 3));

		//Left
		if (leftPart[0] == '[')
		{
			pairLeft = new Pair(leftPart, this);
			numberLeft = -1;
		}
		else
		{
			pairLeft = nullptr;
			numberLeft = std::atoi(leftPart.c_str());
		}

		if (rightPart[0] == '[')
		{
			pairRight = new Pair(rightPart, this);
			numberRight= -1;
		}
		else
		{
			pairRight = nullptr;
			numberRight = std::atoi(rightPart.c_str());
		}
	}

	~Pair()
	{
		if (pairLeft != nullptr)
			delete pairLeft;
	
		if (pairRight != nullptr)
			delete pairRight;
	}

	bool explode()
	{
		return explodeInternal(0);
	}

	bool split()
	{
		bool splitted = false;
		if (pairLeft != nullptr)
		{
			splitted = pairLeft->split();
		}
		else
		{
			if (numberLeft >= 10)
			{
				int leftNum = (int)floor(numberLeft / 2.0);
				int rightNum = (int)ceil(numberLeft / 2.0);
				numberLeft = -1;
				pairLeft = new Pair(leftNum, rightNum, this);
				return true;
			}
		}
		
		if (!splitted)
		{
			if (pairRight != nullptr)
			{
				splitted = pairRight->split();
			}
			else
			{
				if (numberRight >= 10)
				{
					int leftNum = (int)floor(numberRight / 2.0);
					int rightNum = (int)ceil(numberRight / 2.0);
					numberRight = -1;
					pairRight = new Pair(leftNum, rightNum, this);
					return true;
				}
			}
		}
		

		return splitted;
	}

	Pair* add(Pair* other)
	{
		Pair* newPair = new Pair(this, other, nullptr);
		parent = newPair;
		other->parent = newPair;

		newPair->reduce();
		return newPair;
	}

	uint64_t magnitude()
	{
		uint64_t magLeft, magRight;
		if (pairLeft != nullptr)
			magLeft = pairLeft->magnitude();
		else
			magLeft = numberLeft;

		if (pairRight != nullptr)
			magRight = pairRight->magnitude();
		else
			magRight = numberRight;

		return 3 * magLeft + 2 * magRight;
	}

	std::string toString()
	{
		std::string result = "[";
		if (pairLeft != nullptr)
		{
			result += pairLeft->toString();
		}
		else
		{
			result += std::to_string(numberLeft);
		}

		result += ",";

		if (pairRight != nullptr)
		{
			result += pairRight->toString();
		}
		else
		{
			result += std::to_string(numberRight);
		}

		result += "]";

		return result;
	}

	//OPERATORS
	Pair& operator=(const Pair& other)
	{
		if (other.pairLeft != nullptr)
		{
			pairLeft = new Pair();
			*pairLeft = *other.pairLeft;
			pairLeft->parent = this;
			numberLeft = -1;
		}
		else
		{
			pairLeft = nullptr;
			numberLeft = other.numberLeft;
		}

		if (other.pairRight != nullptr)
		{
			pairRight = new Pair();
			*pairRight = *other.pairRight;
			pairRight->parent = this;
			numberRight = -1;
		}
		else
		{
			pairRight = nullptr;
			numberRight = other.numberRight;
		}
		return *this;
	}


private:
	void reduce()
	{
		bool numberChanged = false;
		do
		{
			numberChanged = explode();
			if (!numberChanged)
				numberChanged = split();

		} while (numberChanged);
	}

	bool explodeInternal(int depth)
	{
		bool exploded = false;

		if (depth == 3)
		{
			int numLeft, numRight;
			if (pairLeft != nullptr)
			{
				numLeft = pairLeft->numberLeft;
				numRight = pairLeft->numberRight;
		
				addLeft(numLeft, pairLeft);
				addRight(numRight, pairLeft);

				delete pairLeft;
				pairLeft = nullptr;
				numberLeft = 0;

				return true;
			}
			else if(pairRight != nullptr)
			{
				numLeft = pairRight->numberLeft;
				numRight = pairRight->numberRight;

				
				addLeft(numLeft, pairRight);
				addRight(numRight, pairRight);

				delete pairRight;
				pairRight = nullptr;
				numberRight = 0;

				return true;
			}


			return false;
		}
		else
		{
			if (pairLeft != nullptr)
			{
				if (pairLeft->explodeInternal(depth + 1))
					exploded = true;
			}

			if (!exploded && pairRight != nullptr)
				if (pairRight->explodeInternal(depth + 1))
					exploded = true;
		}

		return exploded;
	}

	void addLeft(int number, Pair* caller)
	{
		if (caller == pairLeft)
		{
			if (parent == nullptr)
				return;
			parent->addLeft(number, this);
		}
		else
		{
			if (pairLeft == nullptr)
			{
				numberLeft += number;
			}
			else
			{
				Pair* current = pairLeft;
				while (current->pairRight != nullptr)
				{
					current = current->pairRight;
				}
				current->numberRight += number;
			}
		}
	}

	void addRight(int number, Pair* caller)
	{
		if (caller == pairRight)
		{
			if (parent == nullptr)
				return;
			parent->addRight(number, this);
		}
		else
		{
			if (pairRight == nullptr)
			{
				numberRight += number;
			}
			else
			{
				Pair* current = pairRight;
				while (current->pairLeft != nullptr)
				{
					current = current->pairLeft;
				}
				current->numberLeft += number;
			}
		}
	}

private:
	Pair* pairLeft, *pairRight;
	int numberLeft, numberRight;
	Pair* parent;
};

std::string Day18::part1()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	Pair* number = new Pair(input[0], nullptr);
	
	for (size_t i = 1; i < input.size(); i++)
	{
		number = number->add(new Pair(input[i], nullptr));
	}

	return std::to_string(number->magnitude());
}

std::string Day18::part2()
{
	std::vector<std::string> input = loadFileAsStringList(pathToInput1);

	std::vector<Pair*> numbers;

	for (size_t i = 0; i < input.size(); i++)
	{
		numbers.push_back(new Pair(input[i], nullptr));
	}

	uint64_t maxMag = 0;

	for (size_t i = 0; i < numbers.size(); i++)
	{
		for (size_t j = 0; j < numbers.size(); j++)
		{
			if (i != j)
			{
				Pair* numberLeft = new Pair();
				Pair* numberRight = new Pair();

				*numberLeft = *numbers[i];
				*numberRight = *numbers[j];
				
				Pair* sum = numberLeft->add(numberRight);
				uint64_t mag = sum->magnitude();
				if (mag > maxMag)
					maxMag = mag;

				delete sum;
			}
		}
	}

	return std::to_string(maxMag);
}