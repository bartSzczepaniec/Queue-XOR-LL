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
	xorllist* front; // pocz¹tek kolejki
	xorllist* back; // koniec kolejki
	int listsize = 0;
	bool isEmpty = true; // czy kolejka jest pusta
	beg = nullptr; // ustawienie pocz¹tkowe wszystkich wskaŸników na nullptr
	end = nullptr;
	front = nullptr;
	back = nullptr;
	while (cin >> command) // obs³uga komend
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
		// funkcjonalnoœæ kolejki
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
	clearList(&beg, &end, &front, &back); // zwalnianie pamiêci, jeœli w liœcie pozosta³y jakieœ elementy
	return 0;
}

void addBeg(xorllist** beg, xorllist** end, int data)
{
	xorllist* temp = new xorllist;
	temp->value = data;
	if (*beg == nullptr) // w przypadku, gdy lista jest pusta ustawiamy wszystkie wskaŸniki na pierwszy element
	{
		temp->xornp = nullptr;
		*beg = temp;
		*end = temp;
	}
	else
	{
		temp->xornp = *beg; // tworzymy nowy wêze³, który zawiera wskaŸnik na nastêpny (ten który wczeœniej by³ pierwszy)
		(*beg)->xornp = (xorllist*)((int)(*beg)->xornp ^ (int)temp); // przypisujemy nowy xor wskaŸników elementowi, który "przesuwamy"
		*beg = temp; // ustawiamy wskaŸnik na pocz¹tek na nowo dodany wêze³
	}
}

void addEnd(xorllist** beg, xorllist** end, int data)
{
	xorllist* temp = new xorllist;
	temp->value = data;
	if (*beg == nullptr) // w przypadku, gdy lista jest pusta ustawiamy wszystkie wskaŸniki na pierwszy element
	{
		temp->xornp = nullptr;
		*beg = temp;
		*end = temp;
	}
	else
	{
		temp->xornp = *end; // tworzymy nowy wêze³, który zawiera wskaŸnik na poprzedni (ten który wczeœniej by³ ostatni)
		(*end)->xornp = (xorllist*)((int)(*end)->xornp ^ (int)temp); // przypisujemy nowy xor wskaŸników elementowi, który "przesuwamy"
		*end = temp; // ustawiamy wskaŸnik na koniec na nowo dodany wêze³
	}
}

void printBackward(xorllist* end)
{
	if (end != nullptr)
	{
		xorllist* temp = end;
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wskaŸnika jako 0
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
		while (((xorllist*)((int)prevtemp ^ (int)temp->xornp)) != nullptr) // póki temp nie bêdziê wskazywa³ na nullptr
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
		else if (temp->xornp == *end) // kiedy s¹ tylko 2 elementy - pocz¹tek i koniec
		{
			delete temp;
			*beg = *end;
			(*end)->xornp = nullptr;
		}
		else
		{
			xorllist* tempnext = (xorllist*)((int)*beg ^ (int)temp->xornp->xornp); // adres trzeciego wêz³a (licz¹c od pocz¹tku)
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
		else if (temp->xornp == *beg) // kiedy s¹ tylko 2 elementy - pocz¹tek i koniec
		{
			delete temp;
			*end = *beg;
			(*beg)->xornp = nullptr;
		}
		else
		{
			xorllist* tempnext = (xorllist*)((int)*end ^ (int)temp->xornp->xornp); // adres trzeciego wêz³a (licz¹c od koñca)
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
		if (*listsize > 0) // jeœli lista nie jest pusta, to albo dodajemy tam, gdzie wczeœniej by³ wskaŸnik na back, w przeciwnym wypadku "tworzymy" kolejke na koncu listy
		{
			if (*front == nullptr || *back==nullptr)
			{
				*front = *end;
				*back = *end;
			}
			(*front)->value = added_value;
		}
		else // jeœli lista jest pusta, dodajemy do niej element, a nastêpnie ustawiane s¹ na niego wskaŸniki z kolejki
		{
			addBeg(beg, end, added_value);
			*front = *beg;
			*back = *beg;
			*listsize = *listsize + 1;
		}
	}
	else // kiedy kolejka nie jest pusta
	{
		if (*listsize == countqueue(*beg, *end, *front, *back, *isEmpty)) // jeœli d³ugoœæ kolejki == d³ugoœæ listy, to dodajemy nowy element do listy
		{
			if (*back == *beg)
			{
				addBeg(beg, end, added_value);
				*back = *beg;
			}
			else
			{	// tak jak poprzednio z actualem dodawanie
				xorllist* temp = new xorllist; // temp to dodawany wêze³
				temp->value = added_value;
				xorllist* temp2 = *end; // temp2 bêdzie wskazywa³ na miejsce, przed które dodaæ nasz wêze³ (licz¹c od pocz¹tku listy)
				xorllist* prevtemp = nullptr;
				while (temp2 != *back)
				{
					xorllist* prev = prevtemp;
					prevtemp = temp2; // poprzednik aktualnego (licz¹c od koñca)
					temp2 = (xorllist*)((int)prev ^ (int)temp2->xornp); // docelowy aktualny
				}
				xorllist* next = (xorllist*)((int)temp2->xornp ^ (int)prevtemp); // adres nastêpnika backa (od koñca)
				temp->xornp = (xorllist*)((int)temp2 ^ (int)next); // nowy element znajduje siê miêdzy backiem, a poprzednim poprzednikiem (licz¹c od koñca)
				temp2->xornp = (xorllist*)((int)prevtemp ^ (int)temp); // xor nastêpnika backa i nowego poprzednika
				xorllist* nextnext = (xorllist*)((int)next->xornp ^ (int)temp2); // nastêpnik nastêpnika backa
				next->xornp = (xorllist*)((int)nextnext ^ (int)temp);
				*back = temp;
			}
			*listsize = *listsize + 1;
		}
		else // jeœli s¹ wolne elementy w liœcie, przypisujemy wartoœæ nastêpnikowi wskaŸnika back (licz¹c od koñca)
		{
			if (*back == *beg)
			{
				(*end)->value = added_value;
				*back = *end;
			}
			else
			{
				xorllist* temp = *end; // temp2 bêdzie wskazywa³ na miejsce, przed które dodaæ nasz wêze³
				xorllist* prevtemp = nullptr;
				while (temp != *back)
				{
					xorllist* prev = prevtemp;
					prevtemp = temp; // poprzednik backa (licz¹c od koñca)
					temp = (xorllist*)((int)prev ^ (int)temp->xornp); // docelowy wskaŸnik na koniec kolejki
				}
				xorllist* next = (xorllist*)((int)temp->xornp ^ (int)prevtemp); // adres nastêpnika backa (od koñca)
				next->value = added_value;
				*back = next;
			}
		}
	}
	
}

void pop(xorllist** beg, xorllist** end, xorllist** front, xorllist** back, bool* isEmpty)
{
	if (*isEmpty) // jeœli kolejka jest pusta, to nic nie usuwamy
	{
		cout << "NULL" << endl;
		return;
	}
	else 
	{
		cout << (*front)->value << endl;
		if (countqueue(*beg,*end,*front,*back,*isEmpty) == 1) // jeœli jest tylko jeden element, to zaznaczamy, ¿e kolejka jest pusta
		{													  // zostawiaj¹c wskaŸnik w tym samym miejscu
			*isEmpty = true;
			return;
		}
		else // kiedy jest wiêcej ni¿ jeden element, to przesuwamy wskaŸnik na pocz¹tek kolejki (front)
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
				xorllist* next = (xorllist*)((int)temp->xornp ^ (int)prevtemp); // adres nastêpnika fronta (od koñca)
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
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wskaŸnika jako 0
		while (temp != front) // dojscie do pocz¹tku kolejki
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
		}
		cout << temp->value << " "; // po dojœciu do pocz¹tku kolejki, cofamy siê w liœcie, a¿ natrafi siê wskaŸnik na koniec kolejki
		while (temp != back)
		{
			if (temp == beg) // kiedy dojdziemy do pocz¹tku listy, wracamy spowrotem na koniec
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
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wskaŸnika jako 0
		bool isfrontfirst;
		while (temp != front && temp != back)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
		}
		if (temp == front) // sprawdzenie czy front jest przez backiem licz¹c od ty³u
			isfrontfirst = true;
		else
			isfrontfirst = false;

		if (isfrontfirst) // kiedy pocz¹tek kolejki jest bli¿ej koñca listy, to zerowane s¹ elementy od *end do *front i od *back do *beg
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
				if (temp == front) // sprawdzenie, czy wyzerowaæ dany element
					isOutofqueue = false;
				else if (temp == back)
					isOutofqueue = true;
				else if (isOutofqueue)
					temp->value = 0;
				if (temp == back && temp == front)
					isOutofqueue = true;
			}
		}
		else // kiedy koniec kolejki jest bli¿szy koñcowi listy, to zerowane s¹ elementy pomiêdzy *front, a *back
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
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wskaŸnika jako 0
		bool isfrontfirst;
		while (temp != *front && temp != *back)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
		}
		if (temp == *front) // sprawdzenie czy front jest przez backiem licz¹c od ty³u
			isfrontfirst = true;
		else
			isfrontfirst = false;
		if (isfrontfirst) // jeœli pocz¹tek kolejki jest pierwszy (lub kiedy pocz¹tek i koniec s¹ tym samym elementem)
		{                 // usuwamy wszystkie elementy od *end do *front i od *back do *beg (na brzegach listy)
			while (*front != *end)
				delEnd(beg, end, front, back);
			while (*back != *beg)
				delBeg(beg, end, front, back);
		}
		else // jeœli koniec kolejki jest pierwszy to elementy do usuniêcia s¹ miêdzy pocz¹tkiem kolejki, a koñcem (wzglêdem listy)
		{
			temp = *end;
			prevtemp = nullptr;
			xorllist* prev = nullptr;
			while (temp != *back) // szukanie nastêpnika backa (od koñca)
			{
				prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			}
			prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			while(temp != *front) // usuwanie elementów, a¿ nie dojdziemy do pocz¹tku kolejki
			{
					xorllist* next = (xorllist*)((int)temp->xornp ^ (int)prevtemp); // adres nastêpnika usuwanego wêz³a (od koñca)
					xorllist* nextnext = (xorllist*)((int)next->xornp ^ (int)temp); // nastêpnik nastêpnika usuwanego wêz³a
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
	else if (end != nullptr && front != nullptr && back != nullptr) // kiedy kolejka ma wiêcej ni¿ jeden element
	{
		//sprawdzenie czy pierwszy od koñca listy jest koniec kolejki, czy pocz¹tek
		xorllist* temp = end;
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wskaŸnika jako 0
		while (temp != front && temp != back)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
		}
		if (temp == front) // jeœli pierwszy (od koñca) jest pocz¹tek kolejki, to cofaj¹c siê do koñca kolejki zwiêkszamy size
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
		else // jeœli koniec jest pierwszy, to size kolejki jest równy sumie elementów od *end do *back i od *front do *beg (w³¹cznie)
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

void clearList(xorllist** beg, xorllist** end, xorllist** front, xorllist** back) // zwalnianie pamiêci na koñcu dzia³ania programu
{
	while (*beg != nullptr)
		delBeg(beg, end, front, back);
}