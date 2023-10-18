#include "main.h"
class imp_res : public Restaurant
{
public:
    class Queue {
    public:
		customer* head;
		customer* tail;
		int count;
		Queue() {
		    head=nullptr;
		    tail=nullptr;
		    count=0;
		}
		bool full_wait(){
		    if(count == MAXSIZE) return true;
		    return false;
		}
		void Waiting(customer* cus) {
		    if(full_wait()==false){
		        if (head == NULL) {
		            head = tail = cus;
				    count++;
			    }
			    else {
				    tail->next = cus;
				    cus->prev = tail;
				    tail = cus;
				    count++;
			    }
		    }
		}
		void deleteHead() {
			if (head == NULL) {
				return;
			}
            customer *temp = head;
			head = head->next;
			if (head != NULL) {
				head->prev = NULL;
			}
			delete temp;
		}
    };
    class DoublyLinkedList {
    public:
		customer* current;
		int count;
		DoublyLinkedList() {
			current = nullptr;
			count = 0;
		}
		bool full_eat(){
		    if(count==MAXSIZE) return true;
		    return false;
		}
		void anywhere(customer* cus) {
			current = cus;
			count++;
		}
		void sit_at_right(customer* cus) {
		    if(full_eat()==false){
		        if (count == 1) {
		            current->next = cus;
				    current->prev = cus;
				    current = cus;
				    count++;
			    }else{
				    current->next->prev = cus;
				    cus->next = current->next;
				    cus->prev = current;
				    current->next = cus;
				    current = cus;
				    count++;
			    }
		    }
		}
		void sit_at_left(customer* cus) {
		    if(full_eat()==false){
		        if (count == 1) {
		            current->next = cus;
				    current->prev = cus;
				    current = cus;
				    count++;
			    }else{
				    current->prev->next = cus;
				    cus->prev = current->prev;
				    cus->next = current;
	                current->prev = cus;
				    current = cus;
				    count++;
			    }
		    }
		}
		void clear() {
			while (current != NULL) {
				customer* head = current;
				head = head->next;
				delete head;
			}
			current = NULL;
			count = 0;
		}
		void deleteFormHead(int n) {
			while (n != 0) {
				customer* head = current;
				head = head->next;
				current = head;
				count--;
				n--;
				delete head;
			}
		}
       
    };
public:
        DoublyLinkedList list;
        Queue que;
        imp_res() {};
		int number = MAXSIZE;
        void RED(string name, int energy)
		{
			if (energy == 0) {
				return;
			}
			customer* curr = list.current;
			customer* wait = que.head;
			if(list.count > 0){
			    for(int i=0; i<list.count; i++){
			        if(curr->name == name) return;
			        curr=curr->next;
			    }
			}
			if(que.count > 0){
			    for(int i=0; i<que.count; i++){
			        if(wait->name == name) return;
			        wait = wait->next;
			    }
			}
			customer *cus = new customer (name, energy, nullptr, nullptr);
			if (list.count == 0) {
			    number--;
				list.anywhere(cus);
			}
			else if (list.count >= number / 2 && list.count <= number) {
				customer* curr = list.current;
				customer* ans = list.current;
				int RES = 0;
				for (int i = 0; i < list.count; i++) {
					if(RES<abs(energy - curr->energy)) RES = abs(energy - curr->energy);
					curr = curr->next;
				}
				for (int i = 0; i < list.count; i++) {
					if (RES == abs(energy - ans->energy)) {
						list.current = ans;
						break;
					}
					ans = ans->next;
				}
				RES = energy - ans->energy;
				//Nếu chênh lệch sức mạnh nhiều nhất là số dương thì ngồi phải
				if (RES > 0) {
				    number--;
					list.sit_at_right(cus);
				}
				//Ngược lại
				else {
				    number--;
					list.sit_at_left(cus);
				}
			}
			else if (list.count < number / 2 && list.count > 0) {
				if (list.count == 0) {
				    number--;
					list.anywhere(cus);
				}
				else {
					//Nếu energy của khách mới lớn hơn hoặc bằng thì ngồi bên phải người vào trước đó
					if (energy >= list.current->energy) {
					    number--;
						list.sit_at_right(cus);
					}
					//Và ngược lại
					else {
					    number--;
						list.sit_at_left(cus);
					}
				}
			}
			else {
				if (que.count < number) {
					que.Waiting(cus);
				}
			}
        }
		void BLUE(int num)
		{
			if (num >= list.count || num > number) {
				list.clear();
			}
			else {
				list.deleteFormHead(num);
			}
			do {
				if (list.count == 0 || que.count == 0) break;
				customer* cus = que.head;
				RED(cus->name, cus->energy);
				que.deleteHead();
				num--;
			}while (num != 0);
        }
		void PURPLE()
		{
			
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			if (num == 0) {
				customer* kq = que.head;
				int a = que.count;
				do {
					cout << kq->name << "-" << kq->energy << endl;
					a--;
					kq = kq->next;
				}while (a != 0);
			}
			else if (num > 0) {
				customer* kq = list.current;
				int a = list.count;
				do {
					cout << kq->name << "-" << kq->energy << endl;
					a--;
					kq = kq->next;
				}while (a != 0);
			}
			else {
				customer* kq = list.current;
				int a = list.count;
				do{
					cout << kq->name << "-" << kq->energy << endl;
					a--;
					kq = kq->prev;
				}while (a != 0);
			}
		}
};
