#pragma once

namespace labirint {

	struct Point {
		int x, y;
		Point(int x,int y);
	};

	struct AWayOut {
	private:
		struct Node {
			Node* next;
			Node* prev;
			Point* data;
			Node(Point* data);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
	public:
		bool check_and_add(int x,int y,int temp_m_x,int temp_m_y);
		bool delete_last_node();
		void print_awayout();
		Point read_from_file(int (&matix)[15][15]);
		bool check_square(int(&matrix)[15][15], labirint::Point* point, int dx, int dy, int temp_m_x, int temp_m_y);
	};
}
void startprog();