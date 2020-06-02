#include <iostream>

struct List
{
	int numeric = NULL;
	List* next = nullptr;

	void add(int value)
	{
		if (numeric == NULL)
		{
			numeric = value;
		}
		else if (!next)
		{
			next = new List();
			next->numeric = value;
		}
		else
		{
			List* skip;
			skip = next;
			while (skip->next)
			{
				skip = skip->next;
			}
			skip->next = new List();
			skip->next->numeric = value;
		}
	}

	void show()
	{
		if (numeric != NULL)
		{
			std::cout << numeric << " ";
			if (next)
			{
				List* skip;
				skip = next;
				std::cout << skip->numeric << " ";
				while (skip->next)
				{
					skip = skip->next;
					std::cout << skip->numeric << " ";
				}
			}
			std::cout << std::endl;
		}
		else std::cout << "NULL" << std::endl;
	}

	void remove(int value = NULL)
	{
		if (value == NULL)
		{
			if (numeric == value)
			{
				if (!next)
					numeric = NULL;
				else
				{
					numeric = next->numeric;
					List* save = nullptr;
					if (next->next)
						save = next->next;
					delete next;
					next = save;
				}
			}
			else if (next)
			{
				if (next->numeric == value)
				{
					if (next->next)
					{
						List* save = next->next;
						delete next;
						next = save;
					}
					else
					{
						delete next;
						next = nullptr;
					}
				}
				else
				{
					List* skip = next;
					while (skip->next)
					{
						if (skip->next->numeric == value)
						{
							if (skip->next->next)
							{
								List* save = skip->next->next;
								delete skip->next;
								skip->next = save;
							}
							else
							{
								delete skip->next;
								skip->next = nullptr;
							}
						}
						else skip = skip->next;
					}
				}
			}
		}
		else
		{
			if (!next)
				numeric = NULL;
			else
			{
				if (!next->next)
				{
					delete next;
					next = nullptr;
				}
				else
				{
					List* skip = next;
					while (skip->next->next)
					{
						skip = skip->next;
					}
					delete skip->next;
					skip->next = nullptr;
				}
			}
		}
	}

	void remove_at(size_t number)
	{
		if (number == 0)
		{
			if (!next)
				numeric = NULL;
			else
			{
				List* save = next->next;
				numeric = next->numeric;
				delete next;
				next = save;
			}
		}
		else if (number == 1)
		{
			if (next->next)
			{
				List* save = next->next;
				delete next;
				next = save;
			}
			else
			{
				delete next;
				next = nullptr;
			}
		}
		else if (next->next)
		{
			List* skip = next->next, * save = next;
			for (size_t i = 2; i < number; i++)
			{
				save = skip;
				skip = skip->next;
			}
			if (skip->next)
			{
				save->next = skip->next;
				delete skip;
			}
			else
			{
				delete skip;
				save->next = nullptr;
			}
		}
	}

	List* get_element(size_t number)
	{
		List* skip = nullptr;
		if (number == 0)
		{
			if (numeric != NULL)
			{
				skip = new List();
				skip->numeric = numeric;
				skip->next = next;
			}
			return skip;
		}
		else
		{
			skip = next;
			for (size_t i = 1; i < number; i++)
			{
				if (skip->next)
					skip = skip->next;
				else
				{
					skip = nullptr; break;
				}
			}
		}
		return skip;
	}
};

void lowLevel()
{
	List list;
	list.add(10);
	list.add(11);
	list.add(10);
	list.show();
	list.remove(10);
	list.show();
}

void mediumLevel()
{
	List list;
	list.add(1);
	list.add(1);
	list.add(2);
	list.add(6);
	list.add(1);
	list.show();
	int i = 0;
	while (list.get_element(i))
	{
		if (list.get_element(i)->numeric % 2 == 0 && i % 2 != 0)
		{
			std::cout << "i - " << i << std::endl;
			list.remove_at(i);
			break;
		}
		i++;
	}

	list.show();
}

struct Node
{
	int value = 0;
	Node* next = nullptr, * prev = nullptr;
};

struct DoubleConnectedList
{
	Node* head = nullptr, * tail = nullptr;
	size_t count = 0;

	void add(int value)
	{
		if (!head)
		{
			head = new Node();
			head->value = value;
		}
		else if (!tail)
		{
			tail = new Node();
			tail->value = value;
			head->next = tail;
			tail->prev = head;
		}
		else
		{
			tail->next = new Node();
			tail->next->value = value;
			tail->next->prev = tail;
			tail = tail->next;
		}
		count++;
	}

	void insert(int value, size_t num)
	{
		if (num < count && num >= 0)
		{
			Node* skip, * insert = new Node();
			insert->value = value;

			if (num <= count - num - 1) //-1
			{
				skip = head;
				for (size_t i = 0; i < num; i++)
				{
					skip = skip->next;
				}
			}
			else
			{
				skip = tail;
				for (size_t i = count - 1; i > num; i--)
				{
					skip = skip->prev;
				}
			}
			insert->next = skip;
			insert->prev = skip->prev;
			if (skip->prev)
				skip->prev->next = insert;
			else head = insert;
			skip->prev = insert;
			if (!tail)
			{
				tail = skip;
			}
			count++;
		}
		else if (num == count)
			add(value);
	}

	Node* get_element(size_t num)
	{
		if (num >= 0 && num < count)
		{
			Node* skip;
			if (num < count && num >= 0)
			{
				skip = head;
				for (size_t i = 0; i < num; i++)
				{
					skip = skip->next;
				}
			}
			else
			{
				skip = tail;
				for (size_t i = count - 1; i > num; i--)
				{
					skip = skip->prev;
				}
			}
			return skip;
		}
		return nullptr;
	} 

	void show()
	{
		if (head)
		{
			Node* skip = head;
			for (size_t i = 0; i < count; i++)
			{
				std::cout << skip->value << " ";
				if (skip->next)
					skip = skip->next;
			}
			std::cout << std::endl;
		}
		else std::cout << "NULL" << std::endl;
	}
};

void highLevel()
{
	DoubleConnectedList list;
	list.add(1);
	list.add(2);
	list.add(2);
	list.add(1);
	list.add(1);
	list.show();
	for (size_t i = 0; i < list.count; i++)
	{
		if (list.get_element(i)->value % 2 != 0)
		{
			list.insert(list.get_element(i)->value, i + 1);
			i++;
		}
	}
	list.show();
	std::cout << "Tail: " << list.tail;
}

int main()
{
	//lowLevel();
	//mediumLevel();
	highLevel();
}