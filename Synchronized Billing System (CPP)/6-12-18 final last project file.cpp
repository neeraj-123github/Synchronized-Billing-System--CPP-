#include <fstream>
#include<bits/stdc++.h>
#define CUSTOMER "cus.dat"  //customer detail
#define ORDER "order.dat"
#define MENU "menu.dat"
#define ITEM "item.dat"
#define STATIC "variable.txt"
#define BILL "bill_payment.dat"
using namespace std;

int disMenuItem();
void displayItemfile(int );
void item_map( unordered_map<int, pair<string,double>> &);
int searchInFile(double);

class address{   //all address detail and friend class customer
	private:
	int plot_no;
	char street[100];
	char city[100];
	char country[100];
	public:
		address(){
			plot_no = 0;
					}
		void read_add(){
			cout<<"ENTER ADDRESS DETAILS\n";
			cout<<"PLOT_NO :";
			cin>>plot_no;
			cin.ignore(1);
			cout<<"ENTER STREET NAME :";
			cin.getline(street,100);
			cout<<"ENTER CITY :";
			cin.getline(city,100);
			cout<<"ENTER COUNTRY :";
			cin.getline(country,100);
		}

		void dis_add(){
		//	cout<<" \nADDRESS DETAILS\n\n";
		//	cout<<"PLOT_NO \t STREET NAME \t CITY \t COUNTRY \n";
			cout<<"\t\t"<<plot_no<<"\t"<<street<<"\t"<<city<<"\t"<<country;
		}
		friend class customer;
};
class contact{   //all contact detail and friend class customer
	double mob_no;
	char email[50];
	public:
		contact(){}
		void read_con(){
			cout<<"ENTER CONTACT DETAILS \n";
			cout<<"MOBILE_NO :";
			cin>>mob_no;
			cin.ignore(1);
			cout<<"ENTER EMAIL :";
			cin.getline(email,100);
		}
		void dis_con(){
			//cout<<" \nCONTACT DETAILS\n\n";
			//cout<<"MOBILE_NO \t email \n";
			cout<<"\t"<<fixed<<mob_no<<"\t"<<email;
		}
		friend class customer;
};

class person { // person name with class address and contact object
	protected:
	char name[100];
	char gender[100];
	address A;
	contact C;
	public:
		void getDetail();
		void showDetail();
};

//class customer declaration
class admin : public person{  //admin detail and **inherit** person class for all detail of admin
	private:
	int admin_id;
	public:
		admin(){ }
		void get_details(){
			cout<<"Enter Admin id :";
			cin>>admin_id;
			person::getDetail();
		}
		void show_details(){
			cout<<"Admin ID: "<<admin_id<<endl;
			person::showDetail();
		}
};

class customer : public person{ //customer detail and **inherit** person class for all detail of customer and cusid as static
	private:
	int cus_id;
	public:
		static int cusId;
		customer(){ }
		customer(int i){
			cusId++;
			cus_id = cusId;
		}

	bool checkMob(double M){
		if(C.mob_no == M)
		return 1;
		return 0;
	}

	void get_details(){
		cout<<"--- CUSTOMER DETAILS ---"<<endl;
		person :: getDetail();
	}
	void show_details(){
			person::showDetail();
	}

		friend int searchInFile(double);
		friend void StaticVarWrite();
		friend void staticVarRed();
};
int customer :: cusId;  //static variable definition

class cook : public person{  //cook detail and **inherit** person class for all detail of person
	private:
	int cook_id;
	public:
		cook(){ }
		void get_details(){
			cout<<"Enter Cook id :";
			cin>>cook_id;
			person::getDetail();
		}
		void show_details(){
			cout<<"Cook ID: "<<cook_id<<endl;
			person::showDetail();
		}

};

//function to read customer details
void person :: getDetail(){

		cin.ignore();
		cout<<"ENTER  NAME : ";
		cin.getline(name,100);
		cout<<"ENTER GENDER: ";
		cin.getline(gender,10);
		A.read_add();  //for read address of a person
		C.read_con();  //for read contact of a person
}
//function to display customer details
void  person :: showDetail(){
	cout <<"\n\n"<<name<<"\t\t"<<gender;
	 A.dis_add();  //to display address of a person
	 C.dis_con();   //to display contact of a person
}

// function to write customer details in file
template <typename T>
void filewrite(T obj){
	fstream file;
	file.open(CUSTOMER,ios::out|ios::binary|ios::app);
	if(!file){
		cout<<"Error in creating file...\n";
		return ;
	}
	obj.get_details();
	file.write((char*)&obj,sizeof(obj));
	file.close();
	cout<<"Data saved into file the file.\n";
}

// function to display customer details from file
template <typename T>
 void displayfile(){
 	T cus;
 	fstream file;
 	file.open(CUSTOMER,ios::in|ios::binary);
	if(!file){
		cout<<"Error in opening file...\n";
		return ;
	}
	file.read((char*)&cus,sizeof(cus));
	cout<<"\nname\t\t gender \tplot_no\t street_name\t city\t country\t mobile \t email \n";
	while(!file.eof()){
		//	cout<<endl<<endl;
		//	cout<<"Data extracted from file..\n";
			//print the object
			cus.show_details();
			file.read((char*)&cus,sizeof(cus));
	}
	file.close();
 }

class menu{
	char category[50];
	int m_id; //category id;
	public:
		static int menu_id;
		menu(){ }
		menu(int i){
			menu_id++;
			m_id = menu_id;
		}

		void get_menu();
		void show_menu();
		friend int disMenuItem();
		friend void StaticVarWrite();
		friend void staticVarRed();
};
int menu::menu_id;

class item{
	int item_id;
	int menu_id;
	char name[50];
	double price;
	char desc[100];
	public:
		static int itemId;
		item(){	}
		item(int i){
				itemId++;
			}
		void get_details(int);
		void show_item();
		void update();
		friend void displayItemfile(int);
		friend void updateCategory();
		friend class menu;
		friend void StaticVarWrite();
		friend void staticVarRed();
		friend void item_map(unordered_map<int, pair<string,double> > &);
};

int item :: itemId;
// display the menu category
void menu ::show_menu(){
	cout<<left<<setw(5)<<m_id<<setw(15)<<category<<endl;
}

// update price of existing item
void item::update(){
	cout<<"\nEnter updated Price :";
	cin>>price;
}

// get menu one category and items of that category
void menu::get_menu(){
	int k=1;
	cin.ignore(1);
	cout<<"ENTER THE NAME OF CATEGORY :";
	cin.getline(category,50);
	fstream file;
	file.open(ITEM,ios::out | ios :: app |ios::binary);
	cout<<"ADD ITEM IN "<<category<<" ENTER 0 for EXIT\n";
	cin>>k;
	while(k){

		item I(1);
		I.get_details(m_id); //implementation is below
		file.write((char*)&I,sizeof(I));
		cin>>k;
	}
	file.close();
}

// update items in existing category or any changes in items
void updateCategory(){
	cout<<"Update \n";

	fstream file;
//	cout<<"In Which Category U want to Update\n";
	int ch,c;
	ch=	disMenuItem();
	cout<<"\n1. For Insert\n2. For Changes\n";
	cin>>c;
	if(c==1){
		file.open(ITEM,ios::app|ios::out|ios::binary);
		item I(1);
		I.get_details(ch);
		file.write((char*)&I,sizeof(I));
	}
	else if(c==2){
		item I;
		file.open(ITEM,ios::in|ios::binary);
		file.read((char*)&I,sizeof(I));
		displayItemfile(ch);
		file.close();
		file.open(ITEM,ios::in|ios::binary|ios::out);
		int k;
		cout<<"Which item Price U want To change\nitem id =";
		cin>>k;
		file.read((char*)&I,sizeof(I));
		while(!file.eof()){
			if( I.item_id == k)
				break;
			file.read((char*)&I,sizeof(I));
		}
		file.seekp(-sizeof(I),ios::cur);
		I.update();
		file.write((char*)&I,sizeof(I));
	}
	file.close();
}

// get details of menu category
void item::get_details(int menuId){
	menu_id = menuId;
	item_id  =menuId*100+itemId;
	cin.ignore(1);
	cout<<"Enter Name :";
	cin.getline(name,50);
	cout<<"Enter price :";
	cin>>price;
	cout<<"Enter description :";
	cin.ignore(1);
	cin.getline(desc,100);
}

// show particular item
void item::show_item(){
;	cout<<"\n"<<left<<setw(10)<<item_id<<setw(20)<<name<<setw(10)<<price<<setw(20)<<desc<<endl;
}

// write menu category in file
void fileMenuwrite(menu &M){
	fstream file;
	file.open(MENU,ios::out|ios::binary|ios::app);
	if(!file){
		cout<<"Error in creating file...\n";
		return ;
	}
	M.get_menu();
//	M.show_menu();
	file.write((char*)&M,sizeof(M));
	file.close();
	cout<<"Data saved .\n";
}

// function to display menu category from file
void displayMenufile(){
 	menu M;
 	fstream file;
 	file.open(MENU,ios::in|ios::binary);
	if(!file){
		cout<<"Error in opening file...\n";
		return ;
	}
	file.read((char*)&M,sizeof(M));
	cout<<"\nid\tCategory\n"<<endl;
	while(!file.eof()){
			M.show_menu();
			file.read((char*)&M,sizeof(M));
	}
	file.close();
 }

// Put all items into map from file ITEM
void item_map(unordered_map<int, pair<string,double> > &map){
	fstream file;
	file.open(ITEM,ios::in|ios::binary);
	if(!file){
		cout<<"Error in opening file...\n";
		return ;
	}
	item itm;
	file.read((char*)&itm,sizeof(itm));
	while(!file.eof())
	{
		//itm.show_item();
		map[itm.item_id]=make_pair(itm.name,itm.price);
		file.read((char*)&itm,sizeof(itm));
	}
	file.close();/*
	unordered_map<int, pair<string,double> >::iterator itt;

	for(itt=map.begin();itt!=map.end();++itt)
	{
		cout<<itt->first<<" "<<itt->second.first<<" "<<itt->second.second<<"\n";
		cout<<map[itt->first].first<<"   "<< map[itt->first].second<<endl;
	}*/
	return;
}

// display all items from file
void displayItemfile(int m_id){
 	item I;
 	fstream file;
 	file.open(ITEM,ios::in|ios::binary);
	if(!file){
		cout<<"Error in opening file...\n";
		return ;
	}
	file.read((char*)&I,sizeof(I));
	cout<<"\nItem id\t\tName\t\tprice\tdescription\n";
	while(!file.eof()){
		if(I.menu_id == m_id){
			//cout<<endl<<endl;
			I.show_item();
		}
		file.read((char*)&I,sizeof(I));
	}
	file.close();
 }

// display items of particular category
int disMenuItem(){
 	displayMenufile();
 	int m_id;
 	cout<<"\nWhich Category U want to display .\nEnter category id :";
 	cin>>m_id;
 	displayItemfile(m_id);
 	return m_id;
 }

class table{
	private:
	int table_no;
	int order_no;
	double cusMob;
	list< pair<int,int> > order_list;
	public:
		static int O_id;
		table(){ }
		table(double mob){
			O_id++;
			table_no=O_id*10+O_id;
			order_no = O_id;
			cusMob=mob;
		}
		bool operator== (const table &t){ return cusMob==t.cusMob;	}
		void getOrder();
	//	void updateOrder();
		void displayOrder(unordered_map<int, pair<string,double> >);
		void writeOrderFile();
		void tableDetails();
		bool billGenerate(unordered_map<int, pair<string,double> > &map,list<int>);
		bool checkTableMob(double mob_no){
			if(cusMob == mob_no)
				return 1;
			return 0;
		}
		friend void readOrderFile();
		friend void StaticVarWrite();
		friend void staticVarRed();
};

int table::O_id;
 // For generating bill
bool table :: billGenerate(unordered_map<int, pair<string,double> > &map,list<int> lst){
	double amount=0,pric=0;
	tuple<int,double,double> t,t2;
	string name;
	list< pair<int,int> >::iterator ls;
	for(ls=order_list.begin();ls!=order_list.end();++ls)
	{
		name=map[ls->first].first;
		pric=map[ls->first].second;

		cout<<"\n"<<name<<"\t"<<pric<<"   *   "<<ls->second<<"  =  "<<ls->second*pric;
		amount+=ls->second*pric;
	}
	cout<<"\n\n\t\t TOTAL AMOUNT   =  "<<amount<<endl;

	if(find(lst.begin(),lst.end(),order_no)==lst.end())
	{
			cout<<"\nwait for some time while ur order is completed \n";
				return 0;
	}
	fstream file;
	file.open(BILL,ios::out|ios::binary|ios::app);
	t=make_tuple(order_no,cusMob,amount);
	file.write((char*)&t,sizeof(t));
	file.close();
	return 1;

}

void bill_Display(){
	tuple<int,double,double> t;   //tuple
	fstream file;
	file.open(BILL,ios::in|ios::binary);
	if(!file)
	{
		cout<<"Error in opening file...\n";
		return;
	}
	file.read((char*)&t,sizeof(t));
	while(!file.eof())
	{
		cout <<get<0>(t)<<" "<<get<1>(t)<<" "<<get<2>(t)<<endl;
		file.read((char*)&t,sizeof(t));
	}
	file.close();
}

// For taking order from the customer
void table::getOrder(){
	int i_id,cnt,k=1;
	while(k){
		cout<<"Enter item id and count :";
		cin>>i_id>>cnt;
		order_list.push_back(make_pair(i_id,cnt));
		cin>>k;
	}
}
// Display order of the particular customer
void table ::displayOrder(	unordered_map< int , pair<string,double> > map){
		cout<<"\n\n\torder no : "<<order_no<<endl;
		list< pair<int,int> > ::iterator it;
		for(it = order_list.begin();it!=order_list.end(); ++it)
			cout<<map[(*it).first].first<<" "<<(*it).second<<endl;
}

void Dis_all_order(	unordered_map< int , pair<string,double> > map,list <table> E_c_l){
	list <table>::iterator itt;
	for(itt=E_c_l.begin();itt!=E_c_l.end();itt++ )
	{
		(*itt).displayOrder(map);
	}
}

void completed_order(list<int> &lst){
	int ord_no,c=1;
	while(c){
		cout<<"Enter which order completed :";
		cin>>ord_no;
		lst.push_back(ord_no);
		cout<<"Any other order completed than press 1 , 0 for exit ";
		cin>>c;
	}
}

// for storing value of static variable
void StaticVarWrite(){
	fstream file;
	file.open(STATIC,ios::out|ios::trunc);
	file.write((char*)&item::itemId,sizeof(item::itemId));
	file.write((char*)&menu::menu_id,sizeof(menu::menu_id));
	file.write((char*)&customer::cusId,sizeof(customer::cusId));
	file.write((char*)&table::O_id,sizeof(table::O_id));
	file.close();
}
// for reading static var value before any update
void staticVarRed(){
	fstream file;
	file.open(STATIC,ios::in);
	if(!file){
		cout<<"Error in opening file...\n";
		customer::cusId=0;
		table::O_id=0;
		item::itemId=0;
		menu::menu_id=0;
	}
	else{

		file.read((char*)&item::itemId,sizeof(item::itemId));
		file.read((char*)&menu::menu_id,sizeof(menu::menu_id));
		file.read((char*)&customer::cusId,sizeof(customer::cusId));
		file.read((char*)&table::O_id,sizeof(table::O_id));
		file.close();
	}
//	cout<<"\n"<<customer::cusId<<" "<<table::O_id<<" "<<item::itemId<<" "<<menu::menu_id<<endl;
		return;
}
// main display greetings
void dis(){
	cout<<"-------------- WELCOME TO SHREE -----------------\n";
	cout<<"\n 1. Customer\n 2. Admin\n 3. Cook\n\n";
}

// For checking customer mob no. exist or not
int searchInFile(double m_b){
	fstream file;
	file.open(CUSTOMER,ios::in|ios::binary);
	customer cus;
	file.read((char*)&cus, sizeof(cus));
	while(!file.eof())
    {
		if(cus.checkMob(m_b))
		return cus.cus_id;
		file.read((char*)&cus, sizeof(cus));
	}
	return 0;
}

// main
int main(){
	list <table>Exist_cus_list;  //doubly linked list
	list<int> cmpltOrder;
	unordered_map< int , pair<string,double> > ItemMap;
	item_map(ItemMap);
	int c=1;
	staticVarRed();
	while(c){
		dis();
		cin>>c;
		switch(c){
			case 1:{
				int ch,flag = 0;
				table *tab;
				double mob_no;
					cout<<"\n 1. new Customer\n 2. Existing Customer\n";
						cin>>ch;
						if(ch == 1){
							enter_details:
								//object of Customer class
								customer cus(1);
								//write into the file
								filewrite<customer>(cus);
							//	displayfile<customer>();
						}
						cout<<"\nEnter ur mobile_no : ";
						cin>>mob_no;
						if(!searchInFile(mob_no)){
							cout<<"U R not Existing customer so Enter ur details\n";
							goto enter_details;
						}
						list <table> ::iterator it;
						/*for(it = Exist_cus_list.begin();it!=Exist_cus_list.end();it++)
                            {
							if((*it).checkTableMob(mob_no)){
								tab = &(*it);
								cout<<"\ntable mob_no match\n";
								tab->displayOrder(ItemMap);//dont know
								flag = 1;
							}
							cout<<"\nmob_no matching in table list \n" ;
						}*/
						if(flag)
						{
							//if already given the order
							int k;
							cout<<"1. Update\n 2. Bill Generate\n ";
							cin>>k;
							if(k == 1){
								cout<<"\nupdate Order\n";
								tab->displayOrder(ItemMap);
								disMenuItem();
								tab->getOrder();
							}
							else{
								cout<<"\ngenrate bill\n";
								int  ck=tab->billGenerate(ItemMap,cmpltOrder);
								if(ck){
									Exist_cus_list.remove(*tab); // delete object from list
								}
							}
							goto end;
						}
						else{
							//if new order genrate
							int k;
							table t(mob_no);
							disMenuItem();
							t.getOrder();
							Exist_cus_list.push_back(t);
							cout<<"U wnat to give more Or 0 For exit.. ";
							cin>>k;
							if(k){
									Exist_cus_list.remove(t);
									cout<<"\n update order \n";
									disMenuItem();
									t.getOrder();
									Exist_cus_list.push_back(t);

														}
							else
								goto end;
						}

				}
				break;

			case 2:{
					int id ,chk_id;
					double A_mob;
				//	admin Ad;
				//	filewrite<admin>(Ad);
					cout<<"Enter id and password\n";
					cin>>id>>A_mob;
					chk_id=searchInFile(A_mob);
					if(chk_id!=id){
						cout<<"U R not Admin\n";
						goto end;
					}
					int ch=1;
					while(ch){
						cout<<"\n1. Add menu in File\n2. Display menu\n3. Update in Existing menu\n4. Show Bill\n\n";
						cin>>ch;
						if(ch == 1){
							menu M(1);
				 			fileMenuwrite(M);
				 		}
			 			else if(ch == 2){
			 				disMenuItem();
			 			}
			 			else if(ch == 3){
			 				updateCategory();
						}
						else if(ch==4){
							bill_Display();

						}
						else
							break;
					}


				}
				break;

			case 3:
			{
				cout<<"\n1.Display Order list";
				Dis_all_order(ItemMap,Exist_cus_list);
				completed_order(cmpltOrder);
			}
			break;
		}
		end:;


	}//while end

	StaticVarWrite();
	return 0;
}
