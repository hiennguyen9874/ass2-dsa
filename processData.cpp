/*
* ==========================================================================================
* Name        : processData.cpp
* Description : student code for Assignment 2 - Data structures and Algorithms - Fall 2017
* ==========================================================================================
*/
#include <iostream>
#include <vector>
#include <functional>
#include <math.h>
#include "requestLib.h"
#include "dbLib.h"

using namespace std;

#define GPS_DISTANCE_ERROR 0.005


struct Node
{
	VM_Record *p;
	Node() {
		p = NULL;
	}
	Node(VM_Record &p) {
		this->p = &p;
	}
	Node(Node &p) {
		this->p = p.p;
	}
	Node(time_t h)
	{
		this->p = new VM_Record;
		p->timestamp = h;
	}
	void operator=(Node &b) {
		this->p = b.p;
	}
	bool operator==(Node &b) {
		return p->timestamp == b.p->timestamp;
	}
	bool operator!=(Node &b) {
		return p->timestamp != b.p->timestamp;
	}
	bool operator>(Node &b) {
		return p->timestamp > b.p->timestamp;
	}
	bool operator<(Node &b) {
		return p->timestamp < b.p->timestamp;
	}
	bool operator>=(Node &b) {
		return p->timestamp >= b.p->timestamp;
	}
	bool operator<=(Node &b) {
		return p->timestamp <= b.p->timestamp;
	}
	void destroy() {
		delete p;
	}
};

Node ptc;

struct NodeId
{
	AVLTree<Node> Node_Id;
	char id[ID_MAX_LENGTH];
	bool booler; // Xac dinh lo trinh co bi huy lo trinh hay khong.
	Node *q;
	NodeId()
	{
		strcpy(id, "");
		booler = true;
	}
	NodeId(char id[ID_MAX_LENGTH])
	{
		strcpy(this->id, id);
		booler = true;
	}
	NodeId(string id) {
		strcpy(this->id, id.data());
		booler = true;
	}
	NodeId(VM_Record *p) {
		strcpy(id, p->id);
		q = new Node(*p);
		Node_Id.insert(*q);
		booler = true;
	}
	NodeId(Node a) {
		this->Node_Id.insert(a);
		strcpy(this->id, a.p->id);
		booler = true;
	}
	NodeId(NodeId &b) {
		strcpy(id, b.id);
		q = b.q;
		Node_Id.insert(*q);
		booler = true;
	}
	void operator=(NodeId &p) {
		strcpy(id, p.id);
		q = p.q;
		Node_Id.insert(*q);
	}
	bool operator==(NodeId &b) {
		return strcmp(id, b.id) == 0;
	}
	bool operator!=(NodeId &b) {
		return strcmp(id, b.id) != 0;
	}
	bool operator<(NodeId &b) {
		return strcmp(id, b.id) < 0;
	}
	bool operator>(NodeId &b) {
		return strcmp(id, b.id) > 0;
	}
	bool operator<=(NodeId &b) {
		return strcmp(id, b.id) < 0;
	}
	bool operator>=(NodeId &b) {
		return strcmp(id, b.id) > 0;
	}
};

class Data
{
public:
	AVLTree<NodeId> data;
	bool booler;
	Data() {
		booler = false;
	}
	void Load(L1Item<VM_Record> *q);
};

NodeId *tam = NULL;
// Ham load du lieu

void Data::Load(L1Item<VM_Record> *q)
{
	while (q)
	{
		tam = new NodeId(&q->data);
		data.insert(*tam);
		q = q->pNext;
	}
}

// Kieu du lieu cho request 6
struct StructRq6
{
	string id;
	bool booler;
};

// Kieu du lieu cho request 7
struct StructRq7
{
	string id;
	double distance;
	StructRq7() {
		id = "0";
		distance = -1;
	}
	StructRq7(StructRq7 &a) {
		this->id = a.id;
		this->distance = a.distance;
	}
};

struct Global
{
	Data *dataP;	//Con tro toi vung du lieu Data
	struct tm ptime;	// Thoi gian mac dinh cua chuong trinh
	int num;
	bool booler, booler1, booler2, booler3;
	double Along, Alat;
	double R;
	time_t H1, H2;
	int M;
	L1List<StructRq6> List;
	L1List<StructRq7> Listrq7;
	double distance;
	double numrq6;
	L1List<double> rq7;

	void request2() {
		num = 0;
		booler = true;
		Along = 0;
	}

	void request3() {
		num = 0;
		booler = true;
		Alat = 0;
	}

	void request4() {
		Along = 0;
		Alat = 0;
		H1 = H2 = mktime(&ptime);
		R = 0;
		num = 0;
		booler1 = true;
	}

	void requset5()
	{
		Along = 0;
		Alat = 0;
		R = 0;
		booler = booler1 = true;
		num = 0;
	}

	void request6()
	{
		Along = Alat = 0;
		H1 = H2 = mktime(&ptime);
		booler1 = booler2 = booler3 = true;
		numrq6 = 0;
		M = 0;
		List.clean();
	}

	void request7()
	{
		Along = Alat = 0;
		R = 0;
		H1 = H2 = mktime(&ptime);
		booler = booler1 = booler2 = booler3 = true;
		numrq6 = 0;
		distance = 0;
		M = 0;
		Listrq7.clean();
		rq7.clean();
	}

	void request8_9()
	{
		Along = Alat = 0;
		H1 = H2 = mktime(&ptime);
		R = 0;
		booler = true;
		num = 0;
	}
};

Global tc;	// Tao bien toan cuc

bool initVMGlobalData(void** pGData) {
	// TODO: allocate and initialize global data
	// return false if failed
	*pGData = new Data();
	return true;
}

void releaseVMGlobalData(void* pGData) {
	// TODO: do your cleanup, left this empty if you don't have any dynamically allocated data
	delete (Data*)pGData;
	return;
}


// Ham doi char thanh thoi gian
time_t charTohour(char *str, int mm, int ss)
{
	string chh = { str[0],str[1] };
	struct tm ptime = tc.ptime;
	int a = stoi(chh);
	if (a > 23)
		ptime.tm_mday += a / 24;
	a = a % 24;
	ptime.tm_hour = a;
	ptime.tm_min = mm;
	ptime.tm_sec = ss;
	return mktime(&ptime);
}
time_t charTomin(char *str, int ss)
{
	if (strlen(str) >= 3)
	{
		string chh = { str[0],str[1] };
		string cmm = { str[2],str[3] };
		struct tm ptime = tc.ptime;
		int a = stoi(chh);
		int b = stoi(cmm);
		if (b > 59)
		{

			a += 1;
			b = b - 60;
		}
		if (a > 23)
			ptime.tm_mday += a / 24;
		a = a % 24;
		ptime.tm_hour = a;
		ptime.tm_min = b;
		ptime.tm_sec = ss;
		return mktime(&ptime);
	}
	else if (strlen(str) >= 1)
		return charTohour(str, 0, ss);
}
time_t charTosec(char *str)
{
	if (strlen(str) >= 5)
	{
		string chh = { str[0],str[1] };
		string cmm = { str[2],str[3] };
		string css = { str[4],str[5] };
		struct tm ptime = tc.ptime;

		int a = stoi(chh);
		int b = stoi(cmm);
		int c = stoi(css);
		if (c > 59) {
			b += 1;
			c = c - 60;
		}
		if (b > 59) {
			a += 1;
			b = b - 60;
		}
		if (a > 23)
			ptime.tm_mday += a / 24;
		a = a % 24;
		ptime.tm_hour = stoi(chh);
		ptime.tm_min = stoi(cmm);
		ptime.tm_sec = stoi(css);
		return mktime(&ptime);
	}
	else if (strlen(str) >= 3)
		return charTomin(str, 0);
	else if (strlen(str) >= 1)
		return charTohour(str, 0, 0);
}

// Chuyen char thanh so nguyen
int charToInt(char *str)
{
	int Int = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			Int = Int * 10 + str[i] - '0';
		}
	}
	return Int;
}

bool processRequest(VM_Request &request, L1List<VM_Record> &recordList, void *pGData) {
	// TODO: Your code goes here
	// return false for invlaid events

	Data *data = (Data*)pGData;	// Con tro toi vung du lieu duoc tao	

	if (data->booler == false) // Ham xu ly du lieu 1 lan
	{
		data->Load(recordList.get_Head());
		tc.dataP = data;
		if (!recordList.isEmpty())
			tc.ptime = *localtime(&(recordList.get_Head()->data.timestamp));
		data->booler = true;
	}

	char requests[REQUEST_CODE_SIZE];
	strcpy(requests, request.code);
	for (int i = 0; i < strlen(requests); i++)
	{
		if (requests[i] == '_' && requests[i + 1] == '_')
		{
			int n = strlen(requests);
			for (int j = n - 1; j >= i + 1; j--)
			{
				requests[j + 1] = requests[j];
			}
			requests[i + 1] = '0';
			requests[n + 1] = '\0';
		}
	}
	char *str = strtok(requests, "_");
	if (strlen(str) != 1)
		return false;

	switch (str[0])
	{
	case '1':
		// Yeu cau 1
	{
		str = strtok(NULL, "_");
		if (str)
		{
			char idX[ID_MAX_LENGTH];
			strcpy(idX, str);
			str = strtok(NULL, "_");
			if (str)
			{
				char idY[ID_MAX_LENGTH];
				strcpy(idY, str);
				str = strtok(NULL, "_");
				if (str)
				{
					cout << "1: ";
					time_t H1 = charTosec(str);
					NodeId a(idX),
						b(idY), *a1 = NULL, *b1 = NULL;
					data->data.find(a, a1);
					if (a1 && a1->booler)
					{
						data->data.find(b, b1);
						if (b1 && b1->booler)
						{
							Node a11(H1);
							Node *tca = NULL, *tcb = NULL;
							a1->Node_Id.find(a11, tca);
							if (tca)
							{
								b1->Node_Id.find(a11, tcb);
								if (tcb)
								{
									if ((tca->p->longitude - tcb->p->longitude) >= 0)
										cout << "E";
									else
										cout << "W";
									if ((tca->p->latitude - tcb->p->latitude) >= 0)
										cout << " N";
									else
										cout << " S";
									cout << " " << distanceEarth(tca->p->latitude, tca->p->longitude, tcb->p->latitude, tcb->p->longitude) << endl;
									return true;
								}
							}
							a11.destroy();
						}
					}
					cout << "-1" << endl;
					return true;
				}
			}
		}
		return false;
	}
	case '2':
		// Yeu cau 2
	{
		str = strtok(NULL, "_");
		if (str)
		{
			tc.Along = strtod(str, NULL);
			str = strtok(NULL, "_");
			if (str)
			{
				if (str[0] == 'W')
				{
					cout << "2: ";
					data->data.traverseLNR([](NodeId &a)
					{
						if (a.booler)
						{
							tc.booler = true;
							a.Node_Id.traverseNLR([](Node &b)
							{
								if (tc.booler && b.p->longitude > tc.Along)
								{
									tc.booler = false;
									return;
								}
							});
							if (tc.booler == true)
								tc.num++;
						}
					});
					cout << tc.num << endl;
					tc.request2();
					return true;
				}
				else if (str[0] == 'E')
				{
					cout << "2: ";
					data->data.traverseLNR([](NodeId &a)
					{
						if (a.booler)
						{
							tc.booler = true;
							a.Node_Id.traverseNLR([](Node &b)
							{
								if (tc.booler && b.p->longitude < tc.Along)
								{
									tc.booler = false;
									return;
								}
							});
							if (tc.booler == true)
								tc.num++;
						}
					});
					cout << tc.num << endl;
					tc.request2();
					return true;
				}
			}
			tc.request2();
		}
		return false;
	}
	case '3':
		// Yeu cau 3
	{
		str = strtok(NULL, "_");
		if (str)
		{
			tc.request3();
			tc.Alat = strtod(str, NULL);
			str = strtok(NULL, "_");
			if (str)
			{
				if (str[0] == 'S')
				{
					cout << "3: ";
					data->data.traverseLNR([](NodeId &a)
					{
						if (a.booler)
						{
							tc.booler = true;
							a.Node_Id.traverseNLR([](Node &b)
							{
								if (tc.booler && b.p->latitude > tc.Alat)
								{
									tc.booler = false;
									return;
								}
							});
							if (tc.booler == true)
								tc.num++;
						}
					});
					cout << tc.num << endl;
					tc.request3();
					return true;
				}
				else if (str[0] == 'N')
				{
					cout << "3: ";
					data->data.traverseNLR([](NodeId &a)
					{
						if (a.booler)
						{
							tc.booler = true;
							a.Node_Id.traverseLNR([](Node &b)
							{
								if (tc.booler && b.p->latitude < tc.Alat)
								{
									tc.booler = false;
									return;
								}
							});
							if (tc.booler == true)
								tc.num++;
						}
					});
					cout << tc.num << endl;
					tc.request3();
					return true;
				}
			}
			tc.request3();
		}
		return false;
	}
	case '4':
		// Yeu cau 4
	{
		str = strtok(NULL, "_");
		if (str)
		{
			tc.request4();
			tc.Along = strtod(str, NULL);
			str = strtok(NULL, "_");
			if (str)
			{
				tc.Alat = strtod(str, NULL);
				str = strtok(NULL, "_");
				if (str)
				{
					tc.R = strtod(str, NULL);
					str = strtok(NULL, "_");
					if (str)
					{
						tc.H1 = charTohour(str, 0, 0);
						str = strtok(NULL, "_");
						if (str)
						{
							tc.H2 = charTohour(str, 0, 0);
							cout << "4: ";
							data->data.traverseNLR([](NodeId &a)
							{
								if (a.booler)
								{
									tc.booler1 = true;
									Node h1(tc.H1), h2(tc.H2);
									a.Node_Id.traverseMinMaxLNR(h1, h2, [](Node &b)
									{
										if (tc.booler1)
										{
											if (distanceEarth(tc.Alat, tc.Along, b.p->latitude, b.p->longitude) <= tc.R)
											{
												tc.num++;
												tc.booler1 = false;
												return;
											}
										}
									});
									h1.destroy();
									h2.destroy();
								}
							});
							cout << tc.num << endl;
							tc.request4();
							return true;
						}

					}
				}
			}
			tc.request4();
		}
		return false;
	}
	case '5':
		// Yeu cau 5
	{
		str = strtok(NULL, "_");
		if (str)
		{
			char idX[ID_MAX_LENGTH];
			strcpy(idX, str);
			str = strtok(NULL, "_");
			if (str)
			{
				tc.requset5();
				tc.Along = strtod(str, NULL);
				str = strtok(NULL, "_");
				if (str)
				{
					tc.Alat = strtod(str, NULL);
					str = strtok(NULL, "_");
					if (str)
					{
						cout << "5: ";
						tc.R = strtod(str, NULL);
						NodeId a(idX), *X = NULL;
						data->data.find(a, X);
						if (X && X->booler)
						{
							tc.booler1 = false;
							X->Node_Id.traverseLNR([](Node &x)
							{
								if (distanceEarth(tc.Alat, tc.Along, x.p->latitude, x.p->longitude) <= tc.R)
								{
									tc.booler = true;
								}
								else
								{
									tc.booler = false;
								}
								if (tc.booler1 == false && tc.booler == true)
									tc.num++;
								tc.booler1 = tc.booler;
							});
							cout << tc.num << endl;
						}
						else
						{
							cout << "-1" << endl;
						}
						tc.requset5();
						return true;
					}
				}
				tc.requset5();
			}
		}
		return false;
	}
	case '6':
		// Yeu cau 6
	{
		str = strtok(NULL, "_");
		if (str)
		{
			tc.request6();
			tc.Along = strtod(str, NULL);
			str = strtok(NULL, "_");
			if (str)
			{
				tc.Alat = strtod(str, NULL);
				str = strtok(NULL, "_");
				if (str)
				{
					tc.M = charToInt(str);
					if (tc.M < 0)
						tc.M = 0;
					str = strtok(NULL, "_");
					if (str)
					{
						cout << "6:";
						tc.H2 = charTomin(str, 0);
						tc.H1 = tc.H2 - 15 * 60;
						data->data.traverseLNR([](NodeId &x)
						{
							if (x.booler)
							{
								tc.booler1 = true;
								tc.booler2 = true;
								tc.booler3 = true;
								Node a(tc.H1), b(tc.H2);
								x.Node_Id.traverseMinMaxLNR(a, b, [](Node &ax)
								{
									double distance = distanceEarth(ax.p->latitude, ax.p->longitude, tc.Alat, tc.Along);
									if (tc.booler1 && distance < 2)
										tc.booler1 = false;
									if (tc.booler2 && distance < 0.5)
										tc.booler2 = false;
									if (tc.booler3 && distance < 0.3)
									{
										tc.numrq6++;
										tc.booler3 = false;
									}
								});
								if (tc.booler1 == false)
								{
									string id(x.id);
									StructRq6 a;
									a.id = id;
									if (tc.booler2 == false)
										a.booler = true;
									else
										a.booler = false;
									tc.List.push_back(a);
								}
								a.destroy();
								b.destroy();
							}
						});
						if (tc.List.getSize() < tc.M)
						{
							// Toan bo duoc vao tram
							L1Item<StructRq6> *p = tc.List.get_Head();
							while (p)
							{
								cout << " " << p->data.id;
								p = p->pNext;
							}
							cout << " - -1";
						}
						else
						{
							if (tc.numrq6 > 0.75*tc.M)
							{
								// Toan bo khong duoc vao tram
								cout << " -1 -";
								L1Item<StructRq6> *p = tc.List.get_Head();
								while (p)
								{
									cout << " " << p->data.id;
									p = p->pNext;
								}
							}
							else
							{
								// Duoi 500m duoc vao tram
								L1Item<StructRq6> *p = tc.List.get_Head();
								while (p)
								{
									if (p->data.booler == true)
										cout << " " << p->data.id;
									p = p->pNext;
								}
								cout << " -";
								p = tc.List.get_Head();
								int num = 0;
								while (p)
								{
									if (p->data.booler == false)
									{
										num++;
										cout << " " << p->data.id;
									}
									p = p->pNext;
								}
								if (num == 0)
									cout << " ";
							}
						}
						cout << endl;
						tc.request6();
						return true;
					}
				}
			}
			tc.request6();
		}
		return false;
	}
	case '7':
		// Yeu cau 7
	{
		str = strtok(NULL, "_");
		if (str)
		{
			tc.request7();
			tc.Along = strtod(str, NULL);
			str = strtok(NULL, "_");
			if (str)
			{
				tc.Alat = strtod(str, NULL);
				str = strtok(NULL, "_");
				if (str)
				{
					tc.M = charToInt(str);
					str = strtok(NULL, "_");
					if (str)
					{
						tc.R = strtod(str, NULL);
						str = strtok(NULL, "_");
						if (str)
						{
							cout << "7:";
							tc.H1 = charTomin(str, 0);
							tc.H2 = tc.H1 + 30 * 60;
							data->data.traverseLNR([](NodeId &x)
							{
								if (x.booler)
								{
									tc.booler1 = true;
									tc.booler2 = true;
									tc.booler3 = true;
									tc.booler = true;
									tc.distance = 0;
									Node a(tc.H1), b(tc.H2);
									x.Node_Id.traverseMinMaxLNR(a, b, [](Node &ax)
									{
										double distance = distanceEarth(tc.Alat, tc.Along, ax.p->latitude, ax.p->longitude);
										if (tc.booler1 && distance <= 0.5)
										{
											tc.numrq6++;
											tc.booler1 = false;
										}
										if (tc.booler && distance <= 1.0)
										{
											tc.distance = distance;
											tc.booler = false;
										}
										if (tc.booler && distance > 1.0 && distance < 2.0)
										{
											if (tc.distance < distance)
												tc.distance = distance;
											if (tc.booler2)
												tc.booler2 = false;
										}
										if (tc.booler3 && distance < 2.0)
										{
											tc.booler3 = false;
										}
									});
									if (tc.booler3 == false)
									{
										string id(x.id);
										StructRq7 arq7;
										arq7.id = id;
										if (tc.booler == false)
											arq7.distance = -1;
										else if (tc.booler2 == false)
										{
											tc.rq7.push_back(tc.distance);
											arq7.distance = tc.distance;
										}
										tc.Listrq7.push_back(arq7);
									}
									a.destroy();
									b.destroy();
								}
							});

							if (tc.numrq6 < 0.7*tc.M)
							{
								// Khong un tac
								// In het List
								cout << " -1 -";
								int num = 0;
								L1Item<StructRq7> *p = tc.Listrq7.get_Head();
								while (p)
								{
									cout << " " << p->data.id;
									num++;
									p = p->pNext;
								}
								if (num == 0)
									cout << " -1";
							}
							else
							{
								// Un tac
								tc.rq7.quickSort();
								double dis = tc.rq7[tc.rq7.getSize() / 4];
								L1Item<StructRq7> *p = tc.Listrq7.get_Head();
								while (p)
								{
									if (p->data.distance == -1 || p->data.distance < dis)
										cout << " " << p->data.id;
									if (p->data.distance == dis && tc.rq7.getSize() % 4 != 0)
										cout << " " << p->data.id;
									p = p->pNext;
								}
								cout << " -";
								p = tc.Listrq7.get_Head();
								while (p)
								{
									if (p->data.distance > dis)
										cout << " " << p->data.id;
									if (p->data.distance == dis && tc.rq7.getSize() % 4 == 0)
										cout << " " << p->data.id;
									p = p->pNext;
								}
							}
							cout << endl;
						}
					}
				}
			}
			tc.request7();
			return true;
		}
		return false;
	}
	case '8':
		// Yeu cau 8
	{
		str = strtok(NULL, "_");
		if (str)
		{
			tc.request8_9();
			tc.Along = strtod(str, NULL);
			str = strtok(NULL, "_");
			if (str)
			{
				tc.Alat = strtod(str, NULL);
				str = strtok(NULL, "_");
				if (str)
				{
					tc.R = strtod(str, NULL);
					str = strtok(NULL, "_");
					if (str)
					{
						cout << "8:";
						tc.H1 = charTomin(str, 0);
						tc.H2 = tc.H1 + 59;
						data->data.traverseLNR([](NodeId &x)
						{
							if (x.booler)
							{
								tc.booler = true;
								Node a(tc.H1), b(tc.H2);
								x.Node_Id.traverseMinMaxLNR(a, b, [](Node &ax)
								{
									if (tc.booler && distanceEarth(tc.Alat, tc.Along, ax.p->latitude, ax.p->longitude) <= tc.R)
									{
										tc.booler = false;
										return;
									}
								});
								if (tc.booler == false)
								{
									cout << " " << x.id;
									x.booler = false;
									tc.num++;
								}
								a.destroy();
								b.destroy();
							}
						});
						if (tc.num == 0)
							cout << " 0";
						cout << endl;
						tc.request8_9();
						return true;
					}
				}
			}
			tc.request8_9();
		}
		return false;
	}
	case '9':
		// Yeu cau 9
	{
		str = strtok(NULL, "_");
		if (str)
		{
			tc.request8_9();
			tc.Along = strtod(str, NULL);
			str = strtok(NULL, "_");
			if (str)
			{
				tc.Alat = strtod(str, NULL);
				str = strtok(NULL, "_");
				if (str)
				{
					tc.R = strtod(str, NULL);
					str = strtok(NULL, "_");
					if (str)
					{
						cout << "9:";
						tc.H1 = charTomin(str, 0);
						tc.H2 = tc.H1 + 59;
						data->data.traverseLNR([](NodeId &x)
						{
							if (x.booler == false)
							{
								tc.booler = true;
								Node a(tc.H1), b(tc.H2);
								x.Node_Id.traverseMinMaxLNR(a, b, [](Node &ax)
								{
									if (tc.booler && distanceEarth(tc.Alat, tc.Along, ax.p->latitude, ax.p->longitude) <= tc.R)
									{
										tc.booler = false;
										return;
									}
								});
								if (tc.booler == false)
								{
									cout << " " << x.id;
									x.booler = true;
									tc.num++;
								}
								a.destroy();
								b.destroy();
							}
						});
						if (tc.num == 0)
							cout << " 0";
						cout << endl;
						tc.request8_9();
						return true;
					}
				}
			}
			tc.request8_9();
		}
		return false;
	}
	default:
		// Cac truong hop khac
		return false;
	}
}