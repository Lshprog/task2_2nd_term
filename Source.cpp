#include <iostream>
#include "Header.h"
#include <fstream>

std::ifstream F;
char FILE_IN_NAME[] = "mytfiles\\matrix_here.txt";

void startprog() 
{
	int matrix[15][15];
	bool finish = false;
	bool no_way = false;
	int temp_m_x, temp_m_y;
	labirint::AWayOut list = labirint::AWayOut();
	labirint::Point temp_p = labirint::Point(0, 0);
	temp_p = list.read_from_file(matrix);

	temp_m_x = temp_p.x; temp_m_y = temp_p.y;
	temp_p.y = 0; temp_p.x = 0;
	

	while (!no_way || !finish) {
		if (list.check_square(matrix,&temp_p,1,0,temp_m_x,temp_m_y)) {
			finish = list.check_and_add(temp_p.x, temp_p.y, temp_m_x, temp_m_y);
		}
		else if (list.check_square(matrix, &temp_p, 0, 1, temp_m_x, temp_m_y)) {
			finish = list.check_and_add(temp_p.x, temp_p.y, temp_m_x, temp_m_y);
		}
		else if (list.check_square(matrix, &temp_p, -1, 0, temp_m_x, temp_m_y)) {
			finish = list.check_and_add(temp_p.x, temp_p.y, temp_m_x, temp_m_y);
		}
		else if (list.check_square(matrix, &temp_p, 0, -1, temp_m_x, temp_m_y)) {
			finish = list.check_and_add(temp_p.x, temp_p.y, temp_m_x, temp_m_y);
		}
		else {
			
			matrix[temp_p.x][temp_p.y] = 2;
			no_way = list.delete_last_node(&temp_p);
		}

		if (finish) {
			list.print_awayout();
			return;
		}
		else if (no_way) {
			return;
		}
	}
	return;
}


bool labirint::AWayOut::check_square(int(&matrix)[15][15],labirint::Point* point, int dx, int dy,int temp_m_x,int temp_m_y) {
	 if ((-1<point->y + dy < temp_m_y) &&(-1 < point->x + dx < temp_m_x)&& (matrix[point->x+dx][point->y + dy] == 1)) {
			matrix[point->x][point->y] = 2;
			point->x = point->x+dx;
			point->y = point->y + dy;
			return true;
		}
	 return false;
}

labirint::Point labirint::AWayOut::read_from_file(int (&matrix)[15][15]) {
	F.open(FILE_IN_NAME,std::ios::in);
	int x, y;
	F >> x;
	F >> y;
	
	for (int i = 0; i < x; i++) {
		for (int t = 0; t < y; t++) {
			F >> matrix[i][t];
		}
	}
	F.close();
	Point point = Point(x, y);
	return point;
}

bool labirint::AWayOut::check_and_add(int x,int y,int temp_m_x,int temp_m_y)
{
	Point* point = new Point(x, y);
	Node* node = new Node(point);
	if ((head == nullptr) && (tail == nullptr)) {
		head = node;
		tail = node;
	}
	else {
		tail->next = node;
		node->prev = tail;
		tail = node;
	}

	if ((x == temp_m_x-1) && (y == temp_m_y-1))
		return true;
	else
		return false;
}

bool labirint::AWayOut::delete_last_node(labirint::Point* point) {

	if ((head == nullptr) && (tail == nullptr)) {
		std::cout << "No way \n";
		return true;
	}
	Node* temp = tail;
	if (head == tail) {
		delete temp;
		point->x = 0;
		point->y = 0;
		head = nullptr;
		tail = nullptr;
		return false;
	}
	else {
		point->x = tail->prev->data->x;
		point->y = tail->prev->data->y;
		(temp->prev)->next = nullptr;
		tail = temp->prev;
		delete temp;
		return false;
	}
}

void labirint::AWayOut::print_awayout() {
	Node* iter = head;
	while (true) {
		std::cout<<" ( " << iter->data->x<<" ; "<< iter->data->y<<" ) \n";
		if (iter == tail)
			return;
		iter = iter->next;
	}
}

labirint::AWayOut::Node::Node(Point* data) {
	this->data = data;
}

labirint::Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}