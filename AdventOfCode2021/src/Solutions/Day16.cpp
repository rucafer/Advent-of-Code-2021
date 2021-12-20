#include "Day16.h"

#define LITERAL_ID 4

typedef std::vector<uint8_t>::const_iterator iter;

class Packet
{
public:
	uint8_t version;
	uint8_t type;
	bool lengthTypeId = false;

	std::vector<Packet> children;

	Packet(iter& it)
	{
		version = 0;
		for (int i = 0; i < 3; i++)
		{
			version *= 2;
			version += *it;
			it++;
		}

		type = 0;
		for (int i = 0; i < 3; i++)
		{
			type*= 2;
			type += *it;
			it++;
		}

		value = 0;

		if (type == LITERAL_ID)
		{
			bool isLastGroup = false;
			while (!isLastGroup)
			{
				isLastGroup = (*it) == 0;
				it++;

				for (int i = 0; i < 4; i++)
				{
					value *= 2;
					value += *it;
					it++;
				}
			}


		}
		else
		{
			lengthTypeId = (*it) == 1;
			it++;

			

			if (lengthTypeId)
			{
				int expectedLength = 0;
				for (int i = 0; i < 11; i++)
				{
					expectedLength *= 2;
					expectedLength += *it;
					it++;
				}

				for (int i = 0; i < expectedLength; i++)
				{
					children.push_back(Packet(it));
				}
			}
			else
			{
				int expectedLength = 0;
				for (int i = 0; i < 15; i++)
				{
					expectedLength *= 2;
					expectedLength += *it;
					it++;
				}

				int length = 0;

				while (length < expectedLength)
				{
					iter itCopy = it;
					children.push_back(Packet(it));
					length += std::distance(itCopy, it);
				}
			}

		}
	}

	uint64_t  GetValue() const {
		uint64_t  result = 0;
		switch (type)
		{
		case 4:
			return value;
		case 0:
			for (const Packet& p : children)
				result += p.GetValue();
			return result;

		case 1:
			result = 1;
			for (const Packet& p : children)
				result *= p.GetValue();
			return result;

		case 2:
			result = INT_MAX;
			for (const Packet& p : children)
			{
				uint64_t  val = p.GetValue();
				if (val < result)
					result = val;
			}

			return result;

		case 3:
			result = 0;
			for (const Packet& p : children)
			{
				uint64_t  val = p.GetValue();
				if (val > result)
					result = val;
			}

			return result;

		case 5:
		{
			uint64_t  val1 = children[0].GetValue();
			uint64_t  val2 = children[1].GetValue();


			return val1 > val2 ? 1 : 0;
		}

		case 6:
		{
			uint64_t   val1 = children[0].GetValue();
			uint64_t  val2 = children[1].GetValue();


			return val1 < val2 ? 1 : 0;
		}
		case 7:
		{
			uint64_t  val1 = children[0].GetValue();
			uint64_t  val2 = children[1].GetValue();


			return val1 == val2 ? 1 : 0;
		}

		default:
			break;
		}

		return 0;
	}

	int GetVersionSum() const
	{
		int sum = version;
		for (const Packet& p : children)
			sum += p.GetVersionSum();

		return sum;
	}

private:
	uint64_t value;

};

std::string Day16::part1()
{
	std::vector<uint8_t> bits;

	std::string input = loadFileAsString(pathToInput1);

	for (char c : input)
	{
		uint8_t number;
		if (c <= '9')
			number = c - '0';
		else
			number = c - 'A' + 10;

		for (int i = 0; i < 4; i++)
		{
			bits.push_back((number & 0x8) >> 3);
			number <<= 1;
		}
		
	}

	iter it = bits.begin();
	Packet root(it);

	return std::to_string(root.GetVersionSum());
}

std::string Day16::part2()
{
	std::vector<uint8_t> bits;

	std::string input = loadFileAsString(pathToInput1);

	for (char c : input)
	{
		uint8_t number;
		if (c <= '9')
			number = c - '0';
		else
			number = c - 'A' + 10;

		for (int i = 0; i < 4; i++)
		{
			bits.push_back((number & 0x8) >> 3);
			number <<= 1;
		}

	}

	iter it = bits.begin();
	Packet root(it);

	return std::to_string(root.GetValue());
}