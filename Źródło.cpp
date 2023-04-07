#include<iostream>
#include<string>

using namespace std;

struct xorllist // xor linked list
{
	int value;
	xorllist* xornp; // xor z next i previous
};

void addBeg(xorllist** beg, xorllist** end, int data);
void addEnd(xorllist** beg, xorllist** end, int data);
void printForward(xorllist* beg);
void printBackward(xorllist* end);
void delBeg(xorllist** beg, xorllist** end, xorllist** front, xorllist** back);
void delEnd(xorllist** beg, xorllist** end, xorllist** front, xorllist** back);
void clearList(xorllist** beg, xorllist** end, xorllist** front, xorllist** back);
// funkcje kolejki
void pop(xorllist** beg, xorllist** end, xorllist** front, xorllist** back, bool* isEmpty);
void push(xorllist** beg, xorllist** end, xorllist** front, xorllist** back, int* listsize, int added_value, bool* isEmpty);
void printQueue(xorllist* beg, xorllist* end, xorllist* front, xorllist* back, bool isEmpty);
void garbageSoft(xorllist* beg, xorllist* end, xorllist* front, xorllist* back, bool isEmpty);
int countqueue(xorllist* beg, xorllist* end, xorllist* front, xorllist* back, bool isEmpty);
void garbageHard(xorllist** beg, xorllist** end, xorllist** front, xorllist** back, bool isEmpty);

int main()
{
	string command;
	xorllist* beg; 
	xorllist* end;
	xorllist* front; // pocz�tek kolejki
	xorllist* back; // koniec kolejki
	int listsize = 0;
	bool isEmpty = true; // czy kolejka jest pusta
	beg = nullptr; // ustawienie pocz�tkowe wszystkich wska�nik�w na nullptr
	end = nullptr;
	front = nullptr;
	back = nullptr;
	while (cin >> command) // obs�uga komend
	{
	
		if (command == "ADD_BEG")
		{
			int added_value;
			cin >> added_value;
			addBeg(&beg, &end, added_value);
			listsize++;
		}
		else if (command == "ADD_END")
		{
			int added_value;
			cin >> added_value;
			addEnd(&beg, &end, added_value);
			listsize++;

		}
		else if (command == "DEL_BEG")
		{
			delBeg(&beg, &end, &front, &back);
			if (listsize > 0)
				listsize--;
			if (front == nullptr || back == nullptr)
				isEmpty = true;
		}
		else if (command == "DEL_END")
		{
			delEnd(&beg, &end, &front,&back);
			if (listsize > 0)
				listsize--;
			if (front == nullptr || back == nullptr)
				isEmpty = true;
		}
		else if (command == "PRINT_FORWARD")
		{
			printForward(beg);
		}
		else if (command == "PRINT_BACKWARD")
		{
			printBackward(end);
		}
		// funkcjonalno�� kolejki
		else if (command == "PUSH")
		{
			int added_value;
			cin >> added_value;
			push(&beg, &end, &front, &back, &listsize, added_value, &isEmpty);
		}
		else if (command == "POP")
		{
			pop(&beg, &end, &front, &back, &isEmpty);
		}
		else if (command == "PRINT_QUEUE")
		{
			if (!isEmpty)
				printQueue(beg, end, front, back, isEmpty);
			else
				cout << "NULL" << endl;
		}
		else if (command == "COUNT")
		{
			cout << countqueue(beg, end, front, back, isEmpty) << endl;
		}
		else if (command == "GARBAGE_SOFT")
		{
			garbageSoft(beg, end, front, back, isEmpty);
		}
		else if (command == "GARBAGE_HARD")
		{
			garbageHard(&beg, &end, &front, &back, isEmpty);
			listsize = countqueue(beg, end, front, back, isEmpty);
		}
		else if (command == "SIZE")
		{
			cout << listsize << endl;
		}
	}
	clearList(&beg, &end, &front, &back); // zwalnianie pami�ci, je�li w li�cie pozosta�y jakie� elementy
	return 0;
}

void addBeg(xorllist** beg, xorllist** end, int data)
{
	xorllist* temp = new xorllist;
	temp->value = data;
	if (*beg == nullptr) // w przypadku, gdy lista jest pusta ustawiamy wszystkie wska�niki na pierwszy element
	{
		temp->xornp = nullptr;
		*beg = temp;
		*end = temp;
	}
	else
	{
		temp->xornp = *beg; // tworzymy nowy w�ze�, kt�ry zawiera wska�nik na nast�pny (ten kt�ry wcze�niej by� pierwszy)
		(*beg)->xornp = (xorllist*)((int)(*beg)->xornp ^ (int)temp); // przypisujemy nowy xor wska�nik�w elementowi, kt�ry "przesuwamy"
		*beg = temp; // ustawiamy wska�nik na pocz�tek na nowo dodany w�ze�
	}
}

void addEnd(xorllist** beg, xorllist** end, int data)
{
	xorllist* temp = new xorllist;
	temp->value = data;
	if (*beg == nullptr) // w przypadku, gdy lista jest pusta ustawiamy wszystkie wska�niki na pierwszy element
	{
		temp->xornp = nullptr;
		*beg = temp;
		*end = temp;
	}
	else
	{
		temp->xornp = *end; // tworzymy nowy w�ze�, kt�ry zawiera wska�nik na poprzedni (ten kt�ry wcze�niej by� ostatni)
		(*end)->xornp = (xorllist*)((int)(*end)->xornp ^ (int)temp); // przypisujemy nowy xor wska�nik�w elementowi, kt�ry "przesuwamy"
		*end = temp; // ustawiamy wska�nik na koniec na nowo dodany w�ze�
	}
}

void printBackward(xorllist* end)
{
	if (end != nullptr)
	{
		xorllist* temp = end;
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wska�nika jako 0
		cout << temp->value << " ";
		while (((xorllist*)((int)prevtemp ^ (int)temp->xornp)) != nullptr)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			cout << temp->value << " ";
		}
		cout << endl;
	}
	else
		cout << "NULL" << endl;
}

void printForward(xorllist* beg)
{
	if (beg != nullptr)
	{
		xorllist* temp = beg;
		xorllist* prevtemp = nullptr;
		cout << temp->value << " ";
		while (((xorllist*)((int)prevtemp ^ (int)temp->xornp)) != nullptr) // p�ki temp nie b�dzi� wskazywa� na nullptr
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			cout << temp->value << " ";
		}
		cout << endl;
	}
	else
		cout << "NULL" << endl;
}

void delBeg(xorllist** beg, xorllist** end, xorllist** front, xorllist** back)
{
	if (*beg != nullptr)
	{
		if (*back == *beg && *back == *front)
		{
			*back = nullptr;
			*front = nullptr;
		}
		else if (*back == *beg)
		{
			*back = (*beg)->xornp;
		}
		else if (*front == *beg)
		{
			*front = *end;
		}

		xorllist* temp = (*beg);
		if (temp->xornp == nullptr) // kiedy jest tylko 1 element listy
		{
			delete temp;
			*beg = nullptr;
			*end = nullptr;
			*back = nullptr;
			*front = nullptr;
		}
		else if (temp->xornp == *end) // kiedy s� tylko 2 elementy - pocz�tek i koniec
		{
			delete temp;
			*beg = *end;
			(*end)->xornp = nullptr;
		}
		else
		{
			xorllist* tempnext = (xorllist*)((int)*beg ^ (int)temp->xornp->xornp); // adres trzeciego w�z�a (licz�c od pocz�tku)
			temp->xornp->xornp = tempnext;
			*beg = temp->xornp;
			delete temp;
		}
	}
}

void delEnd(xorllist** beg, xorllist** end, xorllist** front, xorllist** back)
{
	if (*beg != nullptr)
	{
		if (*back == *end && *back == *front)
		{
			*back = nullptr;
			*front = nullptr;
		}
		else if (*back == *end)
		{
			*back = *beg;
		}
		else if (*front == *end)
		{
			*front = (*end)->xornp;
		}
		xorllist* temp = (*end);
		if (temp->xornp == nullptr) // kiedy jest tylko 1 element listy
		{
			delete temp;
			*beg = nullptr;
			*end = nullptr;
			*back = nullptr;
			*front = nullptr;
		}
		else if (temp->xornp == *beg) // kiedy s� tylko 2 elementy - pocz�tek i koniec
		{
			delete temp;
			*end = *beg;
			(*beg)->xornp = nullptr;
		}
		else
		{
			xorllist* tempnext = (xorllist*)((int)*end ^ (int)temp->xornp->xornp); // adres trzeciego w�z�a (licz�c od ko�ca)
			temp->xornp->xornp = tempnext;
			*end = temp->xornp;
			delete temp;
		}
	}
}

// funkcje do kolejki

void push(xorllist** beg, xorllist** end, xorllist** front, xorllist** back, int* listsize, int added_value, bool* isEmpty)
{
	if (countqueue(*beg, *end, *front, *back, *isEmpty)==0) // sytuacja, kiedy kolejka jest pusta
	{
		*isEmpty = false;
		if (*listsize > 0) // je�li lista nie jest pusta, to albo dodajemy tam, gdzie wcze�niej by� wska�nik na back, w przeciwnym wypadku "tworzymy" kolejke na koncu listy
		{
			if (*front == nullptr || *back==nullptr)
			{
				*front = *end;
				*back = *end;
			}
			(*front)->value = added_value;
		}
		else // je�li lista jest pusta, dodajemy do niej element, a nast�pnie ustawiane s� na niego wska�niki z kolejki
		{
			addBeg(beg, end, added_value);
			*front = *beg;
			*back = *beg;
			*listsize = *listsize + 1;
		}
	}
	else // kiedy kolejka nie jest pusta
	{
		if (*listsize == countqueue(*beg, *end, *front, *back, *isEmpty)) // je�li d�ugo�� kolejki == d�ugo�� listy, to dodajemy nowy element do listy
		{
			if (*back == *beg)
			{
				addBeg(beg, end, added_value);
				*back = *beg;
			}
			else
			{	// tak jak poprzednio z actualem dodawanie
				xorllist* temp = new xorllist; // temp to dodawany w�ze�
				temp->value = added_value;
				xorllist* temp2 = *end; // temp2 b�dzie wskazywa� na miejsce, przed kt�re doda� nasz w�ze� (licz�c od pocz�tku listy)
				xorllist* prevtemp = nullptr;
				while (temp2 != *back)
				{
					xorllist* prev = prevtemp;
					prevtemp = temp2; // poprzednik aktualnego (licz�c od ko�ca)
					temp2 = (xorllist*)((int)prev ^ (int)temp2->xornp); // docelowy aktualny
				}
				xorllist* next = (xorllist*)((int)temp2->xornp ^ (int)prevtemp); // adres nast�pnika backa (od ko�ca)
				temp->xornp = (xorllist*)((int)temp2 ^ (int)next); // nowy element znajduje si� mi�dzy backiem, a poprzednim poprzednikiem (licz�c od ko�ca)
				temp2->xornp = (xorllist*)((int)prevtemp ^ (int)temp); // xor nast�pnika backa i nowego poprzednika
				xorllist* nextnext = (xorllist*)((int)next->xornp ^ (int)temp2); // nast�pnik nast�pnika backa
				next->xornp = (xorllist*)((int)nextnext ^ (int)temp);
				*back = temp;
			}
			*listsize = *listsize + 1;
		}
		else // je�li s� wolne elementy w li�cie, przypisujemy warto�� nast�pnikowi wska�nika back (licz�c od ko�ca)
		{
			if (*back == *beg)
			{
				(*end)->value = added_value;
				*back = *end;
			}
			else
			{
				xorllist* temp = *end; // temp2 b�dzie wskazywa� na miejsce, przed kt�re doda� nasz w�ze�
				xorllist* prevtemp = nullptr;
				while (temp != *back)
				{
					xorllist* prev = prevtemp;
					prevtemp = temp; // poprzednik backa (licz�c od ko�ca)
					temp = (xorllist*)((int)prev ^ (int)temp->xornp); // docelowy wska�nik na koniec kolejki
				}
				xorllist* next = (xorllist*)((int)temp->xornp ^ (int)prevtemp); // adres nast�pnika backa (od ko�ca)
				next->value = added_value;
				*back = next;
			}
		}
	}
	
}

void pop(xorllist** beg, xorllist** end, xorllist** front, xorllist** back, bool* isEmpty)
{
	if (*isEmpty) // je�li kolejka jest pusta, to nic nie usuwamy
	{
		cout << "NULL" << endl;
		return;
	}
	else 
	{
		cout << (*front)->value << endl;
		if (countqueue(*beg,*end,*front,*back,*isEmpty) == 1) // je�li jest tylko jeden element, to zaznaczamy, �e kolejka jest pusta
		{													  // zostawiaj�c wska�nik w tym samym miejscu
			*isEmpty = true;
			return;
		}
		else // kiedy jest wi�cej ni� jeden element, to przesuwamy wska�nik na pocz�tek kolejki (front)
		{
			if (*front == *beg)
				*front = *end;
			else
			{
				xorllist* temp = *end;
				xorllist* prevtemp = nullptr;
				while (temp != *front)
				{
					xorllist* prev = prevtemp;
					prevtemp = temp;
					temp = (xorllist*)((int)prev ^ (int)temp->xornp); // docelowy front
				}
				xorllist* next = (xorllist*)((int)temp->xornp ^ (int)prevtemp); // adres nast�pnika fronta (od ko�ca)
				*front = next;
			}
		}
	}

}
void printQueue(xorllist* beg, xorllist* end, xorllist* front, xorllist* back, bool isEmpty)
{
	if (isEmpty)
		return;
	else
	{
		xorllist* temp = end;
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wska�nika jako 0
		while (temp != front) // dojscie do pocz�tku kolejki
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
		}
		cout << temp->value << " "; // po doj�ciu do pocz�tku kolejki, cofamy si� w li�cie, a� natrafi si� wska�nik na koniec kolejki
		while (temp != back)
		{
			if (temp == beg) // kiedy dojdziemy do pocz�tku listy, wracamy spowrotem na koniec
			{
				temp = end;
				prevtemp = nullptr;
				cout << temp->value << " ";
			}
			else
			{
				xorllist* prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
				cout << temp->value << " ";
			}

		}
		cout << endl;
	}
}

void garbageSoft(xorllist* beg, xorllist* end, xorllist* front, xorllist* back, bool isEmpty)
{
	if (isEmpty) // kiedy kolejka jest pusta, to zerujemy wszystkie elementy listy
	{
		xorllist* temp = end;
		xorllist* prevtemp = nullptr;
		temp->value = 0;
		while (temp != beg)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			temp->value = 0;
		}
	}
	else
	{
		xorllist* temp = end;
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wska�nika jako 0
		bool isfrontfirst;
		while (temp != front && temp != back)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
		}
		if (temp == front) // sprawdzenie czy front jest przez backiem licz�c od ty�u
			isfrontfirst = true;
		else
			isfrontfirst = false;

		if (isfrontfirst) // kiedy pocz�tek kolejki jest bli�ej ko�ca listy, to zerowane s� elementy od *end do *front i od *back do *beg
		{
			bool isOutofqueue = true;
			temp = end;
			prevtemp = nullptr;
			if (temp != front)
				temp->value = 0;
			else
				isOutofqueue = false;
			while (temp != beg)
			{
				xorllist* prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
				if (temp == front) // sprawdzenie, czy wyzerowa� dany element
					isOutofqueue = false;
				else if (temp == back)
					isOutofqueue = true;
				else if (isOutofqueue)
					temp->value = 0;
				if (temp == back && temp == front)
					isOutofqueue = true;
			}
		}
		else // kiedy koniec kolejki jest bli�szy ko�cowi listy, to zerowane s� elementy pomi�dzy *front, a *back
		{
			bool isOutofqueue = false;
			temp = end;
			prevtemp = nullptr;
			if (temp == back)
				isOutofqueue = true;
			while (temp != front)
			{
				xorllist* prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
				if (temp == back)
					isOutofqueue = true;
				else if (temp == front)
					isOutofqueue = false;
				else if (isOutofqueue)
					temp->value = 0;
			}
		}
	}
}

void garbageHard(xorllist** beg, xorllist** end, xorllist** front, xorllist** back, bool isEmpty)
{
	if (countqueue(*beg,*end,*front,*back,isEmpty)==0) // kiedy kolejka jest pusta, to usuwamy wszystkie elementy kolejki
	{
		while (*beg != nullptr)
		{
			delBeg(beg, end, front, back);
		}
		return;
	}
	else
	{
		xorllist* temp = *end;
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wska�nika jako 0
		bool isfrontfirst;
		while (temp != *front && temp != *back)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
		}
		if (temp == *front) // sprawdzenie czy front jest przez backiem licz�c od ty�u
			isfrontfirst = true;
		else
			isfrontfirst = false;
		if (isfrontfirst) // je�li pocz�tek kolejki jest pierwszy (lub kiedy pocz�tek i koniec s� tym samym elementem)
		{                 // usuwamy wszystkie elementy od *end do *front i od *back do *beg (na brzegach listy)
			while (*front != *end)
				delEnd(beg, end, front, back);
			while (*back != *beg)
				delBeg(beg, end, front, back);
		}
		else // je�li koniec kolejki jest pierwszy to elementy do usuni�cia s� mi�dzy pocz�tkiem kolejki, a ko�cem (wzgl�dem listy)
		{
			temp = *end;
			prevtemp = nullptr;
			xorllist* prev = nullptr;
			while (temp != *back) // szukanie nast�pnika backa (od ko�ca)
			{
				prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			}
			prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			while(temp != *front) // usuwanie element�w, a� nie dojdziemy do pocz�tku kolejki
			{
					xorllist* next = (xorllist*)((int)temp->xornp ^ (int)prevtemp); // adres nast�pnika usuwanego w�z�a (od ko�ca)
					xorllist* nextnext = (xorllist*)((int)next->xornp ^ (int)temp); // nast�pnik nast�pnika usuwanego w�z�a
					next->xornp = (xorllist*)((int)nextnext ^ (int)prevtemp);
					prevtemp->xornp = (xorllist*)((int)prev ^ (int)next);
					delete temp;
					temp = next;
			}
		}
	}
}

int countqueue(xorllist* beg, xorllist* end, xorllist* front, xorllist* back, bool isEmpty)
{
	if ((front && back == nullptr) || isEmpty)
		return 0;
	else if (front == back)
		return 1;
	else if (end != nullptr && front != nullptr && back != nullptr) // kiedy kolejka ma wi�cej ni� jeden element
	{
		//sprawdzenie czy pierwszy od ko�ca listy jest koniec kolejki, czy pocz�tek
		xorllist* temp = end;
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wska�nika jako 0
		while (temp != front && temp != back)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
		}
		if (temp == front) // je�li pierwszy (od ko�ca) jest pocz�tek kolejki, to cofaj�c si� do ko�ca kolejki zwi�kszamy size
		{
			int size = 1;
			while (temp != back)
			{
				xorllist* prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
				size++;
			}
			return size;
		}
		else // je�li koniec jest pierwszy, to size kolejki jest r�wny sumie element�w od *end do *back i od *front do *beg (w��cznie)
		{
			temp = end;
			prevtemp = nullptr;
			bool add = true;
			int size = 1;
			if (temp == back)
				add = false;
			while (temp != beg)
			{
				xorllist* prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
				if (temp == front)
					add = true;
				if (add)
					size++;
				if (temp == back)
					add = false;
			}
			return size;
		}
	}
	else
		return 0;
}

void clearList(xorllist** beg, xorllist** end, xorllist** front, xorllist** back) // zwalnianie pami�ci na ko�cu dzia�ania programu
{
	while (*beg != nullptr)
		delBeg(beg, end, front, back);
}