#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

double sum=0.00;
HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cPosition;

void login_by_admin();
void login_by_user();
void FrontPage();
void search_data();
void bill_id();
void bill_name();
void display_bill();

void gotoXY(int x, int y){
	cPosition.X = x;
	cPosition.Y = y;
	SetConsoleCursorPosition(Console,cPosition);
}
void logo(){
	gotoXY(45,5);
	cout << "=============================================" ;
	gotoXY(45,6);
	cout << "|                 XYZ STORE                 |" ;
	gotoXY(45,7);
	cout << "|                 _________                 |" ;
	gotoXY(45,8);
	cout << "=============================================" ;
}
class products{
	private:
		int ProductId, quantity;
		char ProductName[80];
		double price;
	public:
		void create_product() {
            cout << "Enter the Product Name: ";
            cin.getline(ProductName, 50);
            cout << "\nEnter the Product Id: ";
            cin >> ProductId;
            cout << "\nEnter the Price: ";
            cin >> price;
            cout << "\nQuantity: ";
            cin >> quantity;
            cout<<"\n";
        }

        void show_product() {
            cout << "Product Name: " << ProductName << endl;
            cout << "Product Id: " << ProductId << endl;
            cout << "Price: " << "Rs." << price << endl;
            cout << "Quantity: " << quantity << endl;
        }

    	inline int return_id(){
    		return ProductId;
		}
		inline string return_name(){
			return ProductName;
		}
		inline double return_price(){
            return price;
		}
		void change_quantity(int num)
		{
		    quantity = quantity-num;
		}
		void assign_qty_number(int num)
		{
		    quantity = num;
		}

};


void billing(){
	system("cls");

	bool running = true;
    char b;
    int a;

    while(running) {
        system("cls");
        logo();
        gotoXY(55,10); cout << "ADMIN MODE";
        gotoXY(55,11); cout << "----------";
        gotoXY(55,12); cout << " Billing";
        gotoXY(0,15); cout << "Enter '1' for billing by Product name  or '2' for billing by Id \n";
        gotoXY(0,16); cout << "___" << endl;
        gotoXY(0,16);cin>>a;

        if(a==1) {
           bill_name();

        } else {
            bill_id();
        }
        cout << "\nContinue Billing ? (y/n)" << endl;
        cin >> b;
        cout << "\n---------------------------------------------\n" << endl;
        if(tolower(b) == 'y') {
            running=true;
        } else {
            running=false;
        }
    }
    display_bill();
    cout << "Total Bill : SUM = " << sum << "\n";
    cout << "------------------------ " << endl;
    remove("Bill.bin");
    cout << "\nPress any key to continue..." << endl;
    getch();
    login_by_admin();


}
void bill_id()
{
    products prObj;
    int id,num;
    cout << "\nEnter the product ID\n";
    cin >> id;
    cout << "\nEnter the quantity number\n";
    cin >> num;
    fstream inFile("Products.bin",ios::binary | ios::in | ios::out );
    ofstream outFile("Bill.bin",ios::binary | ios::app);
    while(inFile.read((char*)&prObj,sizeof(products))){
        if(!inFile.eof()) {
            if(id == prObj.return_id()){
                sum = sum + (num*prObj.return_price());
                prObj.change_quantity(num);
                int position = -1 * sizeof(products);
                inFile.seekp(position,ios::cur);
                inFile.write((char*)&prObj,sizeof(products));
                prObj.assign_qty_number(num);
                outFile.write((char*)&prObj,sizeof(products));
            }
        }
    }
    inFile.close();
    outFile.close();
}

void display_bill(){
    system("cls");
	products prObj;
    ifstream inFile("Bill.bin", ios::binary | ios::in);
    cout << "------------------------ " << endl;
    cout << "Displaying BILL: " << endl;
    cout << "------------------------ \n\n" << endl;
    while(inFile.read((char *) & prObj, sizeof(products))) {
        fflush(stdout);
        prObj.show_product();
        cout << "\n---------------------------------\n" << endl;
    }
    inFile.close();


}

void bill_name()
{
    products prObj;
    char name[50];
    cout<<"\nEnter the product name\n";
    fflush(stdin);
    cin.getline(name,50);
    cout<<"\nEnter quantity number\n";
    int num;
    cin>>num;
    fstream inFile("Products.bin",ios::binary | ios::out | ios::in);
    ofstream outFile2("Bill.bin",ios::binary | ios::app);
    while(inFile.read(((char*)&prObj),sizeof(products)))
    {if(!inFile.eof()){

       if(name==prObj.return_name()){

        sum=sum+(num*prObj.return_price());
        prObj.change_quantity(num);
        int position=-1*sizeof(products);
        inFile.seekp(position,ios::cur);
        inFile.write((char*)&prObj,sizeof(products));
        prObj.assign_qty_number(num);
        outFile2.write((char*)&prObj,sizeof(products));

       }
    }
    }
    inFile.close();
    outFile2.close();
}

void add_product(){
	products prObj;
    ofstream outFile("Products.bin", ios::binary | ios::out | ios::app);
    cout << "Add Products: " << endl;
    cout << "------------- " << endl;
    fflush(stdin);
    cout<<"How many products you want to add"<<endl;
    int n,i=1;
    cin>>n;
    for(i=1;i<=n;++i)
    {

    fflush(stdin);
    prObj.create_product();
    outFile.write((char *) &prObj, sizeof(products));
    }
    outFile.close();
    login_by_admin();
}
void edit_product(){
	products prObj;
	cout << "Edit Item: " << endl;
	cout << "------------ " << endl;
	cout<<"Enter the product name you want to edit\n";
	char newName[80];
	fflush(stdin);
	cin.getline(newName,80);
	fstream file("Products.bin", ios::in | ios::out);
	while(file.read((char *) &prObj, sizeof(prObj))){
		if(newName == prObj.return_name()) {
			cout << "Enter New Details: " << endl;
			cout << "------------------ " << endl;
			prObj.create_product();
			int position = -1 * sizeof(prObj);
			file.seekp(position,ios::cur);
			file.write((char *) & prObj, sizeof(prObj));
		}
	}
	file.close();
	login_by_admin();
}
void delete_product(){
	products prObj;
	char name[80];
	cout << "Enter Product name to delete: ";
	fflush(stdin);
	cin.getline(name,80);
    ifstream inFile("Products.bin", ios::binary | ios::in);
    ofstream outFile("temp.bin", ios::binary | ios::out | ios::app);

    while(inFile.read((char *) & prObj, sizeof(products))) {
        if(name != prObj.return_name()){
        	outFile.write((char *) & prObj, sizeof(prObj));
		}
    }
    inFile.close();
    outFile.close();
    cout << "Data deleted " << endl;
    remove("Products.bin");
    rename("temp.bin","Products.bin");
    cout<<"Press any key to continue\n";
    getch();
    login_by_admin();
}
void modify(){
	system("cls");
	int n;
	logo();
	gotoXY(55,10); cout << "ADMIN MODE";
	gotoXY(55,11); cout << "----------";
	gotoXY(50,12); cout << "1.Add Product";
	gotoXY(50,13); cout << "2.Edit Product";
	gotoXY(50,14); cout << "3.Delete Product";
	gotoXY(50,16); cout << "->";
	gotoXY(53,16); cout << "___";
	gotoXY(53,16); cin >> n;
	switch(n){
		case 1:
			add_product();
			break;
		case 2:
			edit_product();
			break;
		case 3:
			delete_product();
		default:
			break;
	}
}
void display(){
    system("cls");
	products prObj;
    ifstream inFile("Products.bin", ios::binary | ios::in);
    cout << "Displaying All Products: " << endl;
    cout << "------------------------ " << endl;
    while(inFile.read((char *) & prObj, sizeof(products))) {
        fflush(stdout);
        prObj.show_product();
        cout << "\n---------------------------------\n" << endl;
    }
    inFile.close();
    cout<<"Press any key to continue:\n";
    getch();
    login_by_admin();
}
void search_by_id(){
	system("cls");
	products prObj;
	int num;
	gotoXY(0,10); cout << "Enter product id: "; cin >> num;
    ifstream inFile("Products.bin", ios::binary | ios::in);
    cout << "Displaying All Products: " << endl;
    cout << "------------------------ " << endl;
    while(inFile.read((char *) & prObj, sizeof(products))) {
        fflush(stdout);
        if(num == prObj.return_id()){
        	fflush(stdout);
        	prObj.show_product();
        	cout << "\n---------------------------------\n" << endl;
		}
	}
	inFile.close();
	char c;
	cout<<"Do you want to search further??(y/n)\n";
	cin>>c;
	if(tolower(c)=='y')
    {
    search_data();
    }
    else
	login_by_admin();
}
void search_by_name(){
	system("cls");
	products prObj;
	char name[80];
	gotoXY(0,10); cout << "Enter product name: ";
	fflush(stdin);
	cin.getline(name,80);
    ifstream inFile("Products.bin", ios::binary | ios::in);
    cout << "Displaying All Products: " << endl;
    cout << "------------------------ " << endl;
    while(inFile.read((char *) & prObj, sizeof(products))) {
        fflush(stdout);
        if(name == prObj.return_name()){
        	fflush(stdout);
        	prObj.show_product();
        	cout << "\n---------------------------------\n" << endl;
		}
	}
	inFile.close();
	char c;
	cout<<"Do you want to search further??(y/n)\n";
	cin>>c;
	if(tolower(c)=='y')
    {
    search_data();
    }
    else
	login_by_admin();
}
void search_data(){
	system("cls");
	int n;
	logo();
	gotoXY(55,10); cout << "ADMIN MODE";
	gotoXY(55,11); cout << "----------";
	gotoXY(50,12); cout << "1.Search By Id";
	gotoXY(50,13); cout << "2.Search By Name";
	gotoXY(50,14); cout<<"3.Return To Admin Mode Menu";
	gotoXY(50,15); cout << "->";
	gotoXY(53,15); cout << "___";
	gotoXY(53,15); cin >> n;
	switch(n){
		case 1:
			search_by_id();
			break;
		case 2:
			search_by_name();
			break;
		case 3:
            login_by_admin();
            break;
		default:
			break;
	}
}
void credits(){
	system("cls");
	gotoXY(47,5); cout << "A BIG THANKS TO";
	gotoXY(47,6); cout << "---------------" << endl;
	gotoXY(47,7); cout << "Adhikari Bishal";
	gotoXY(47,8); cout << "Kunwar Saroj";
	gotoXY(47,9); cout << "Poudel Rupesh";
	gotoXY(47,10); cout <<"Rai Dipesh";
	gotoXY(47,11); cout <<"Thapa Bipul Bikram";
	char c;
	gotoXY(43,14);cout<<"Press 'Esc' Key To GO BACK";
	c=getch();
	if(int(c)==27)
        login_by_admin();

}
void login_by_admin(){
	system("cls");
	int n;
	logo();
	gotoXY(55,10); cout << "ADMIN MODE";
	gotoXY(55,11); cout << "----------";
	gotoXY(50,12); cout << "1.Billing";
	gotoXY(50,13); cout << "2.Modify Product";
	gotoXY(50,14); cout << "3.Display Products";
	gotoXY(50,15); cout << "4.Search Product";
	gotoXY(50,16); cout << "5.Credits";
	gotoXY(50,17); cout << "6.Logout";
	gotoXY(50,18); cout << "->";
	gotoXY(53,18); cout << "___";
	gotoXY(53,18); cin >> n;
	switch(n){
		case 1:
			billing();
			break;
		case 2:
			modify();
			break;
		case 3:
			display();
			break;
		case 4:
			search_data();
			break;
		case 5:
			credits();
			break;
		case 6:
            FrontPage();
		default:
			break;
	}

}
void login_by_user(){
  system("cls");
	int n;
	logo();
	gotoXY(55,10); cout << "USER MODE";
	gotoXY(55,11); cout << "----------";
	gotoXY(50,12); cout << "1.Billing";
	gotoXY(50,13); cout << "2.Modify Product";
	gotoXY(50,14); cout << "3.Display Products";
	gotoXY(50,15); cout << "4.Search Product";
	gotoXY(50,16); cout << "5.Credits";
	gotoXY(50,17); cout << "6.Logout";
	gotoXY(50,18); cout << "->";
	gotoXY(53,18); cout << "___";
	gotoXY(53,18); cin >> n;
	switch(n){
		case 1:
			billing();
			break;
		case 2:
			modify();
			break;
		case 3:
			display();
			break;
		case 4:
			search_data();
			break;
		case 5:
			credits();
			break;
		case 6:
            FrontPage();
		default:
			break;
	}

}
void loading(int number) {

	if(number == 1) {
		login_by_admin();
	}
	if(number == 2) {
		login_by_user();
	}
}
void admin_mode(){
	system("cls");
	char correctPass[50] = "xyzstore";
	string username;
    char temp[50];
    char x;
    int i = 0;
	logo();
	gotoXY(40,10); cout << "Login(Admin Mode):";
	gotoXY(58,11); cout << "Username:";
	gotoXY(58,12); cout << "Password:";
	gotoXY(69,11); cin >> username;
	gotoXY(69,12);
	fflush(stdin);
	int z=68;
    while(true) {
        x = getch();

        if(x != '\r') {
        if((x!='\b'))
        {
        cout << "*";
        z++;
        }
        else{

         gotoXY(z,12);cout<<'\0';
           gotoXY(z,12);
           if(z>69)
           --z;
           --i;
           continue;
		}
		}
		 else {
			break;
		}
		temp[i] = x;
		i++;

    }

	if(username.length() < 6) {
		gotoXY(45,15); cout << "Username must be six characters long!";
	} else {
		if(username == "xyzstore") {
			if(!strcmp(temp, correctPass)) {
        		gotoXY(45,15); cout << "Correct Password!";
        		Sleep(100);
        		loading(1);
    		} else {
        		gotoXY(45,15);cout << "Incorrect Password!";
    		}
		} else {
			gotoXY(45,15);cout << "Incorrect Username!";
		}

	}

}
void user_mode(){
	system("cls");
	char correctPass[20] = "xyzstore";
	string username;
    char temp[20];
    char x;
    int i = 0;
	gotoXY(45,5);
	cout << "=============================================" ;
	gotoXY(45,6);
	cout << "|                 XYZ STORE                 |" ;
	gotoXY(45,7);
	cout << "|                 _________                 |" ;
	gotoXY(45,8);
	cout << "=============================================" ;
	gotoXY(40,10); cout << "Login(User Mode):";
	gotoXY(58,11); cout << "Username:";
	gotoXY(58,12); cout << "Password:";

	gotoXY(69,11); cin >> username;
	gotoXY(69,12);
	int p=68;
    while(true) {
        x = getch();
        if(x != '\r') {
              if(x!='\b')
            {cout<<"*";
            ++p;}
        else{
            gotoXY(p,12);cout<<'\0';
            --i;
            gotoXY(p,12);
            --p;
            continue;
        }
        }
        else
        {break;}
        temp[i] = x;
        i++;
    }
    temp[i] = '\0';
	if(username.length() < 6) {
		gotoXY(45,15); cout << "Username must be six characters long!";
	} else {
		if(username == "xyzstore") {
			if(!strcmp(temp, correctPass)) {
        		gotoXY(45,15); cout << "Correct Password!";
        		Sleep(100);
        		loading(2);
    		} else {
        		gotoXY(45,15);cout << "Incorrect Password!";
    		}
		} else {
			gotoXY(45,15);cout << "Incorrect Username!";
		}

	}
}
void FrontPage()
{
    system("cls");
    bool running = true;
	int a = 47, b = 12;
	logo();
	gotoXY(a,b);cout << "-->";
	gotoXY(50,10); cout << "CHOOSE MODE:";
	gotoXY(50,12); cout << "Admin  Mode";
	gotoXY(50,13); cout << "User Mode";
	while(running){
		system("pause>nul");
		if(GetAsyncKeyState(VK_DOWN) && b!=13){
			gotoXY(a,b); cout << "   ";
			b++;
			gotoXY(a,b); cout << "-->";
		}
		if(GetAsyncKeyState(VK_UP) && b!=12){
			gotoXY(a,b); cout << "   ";
			b--;
			gotoXY(a,b); cout << "-->";
		}
		if(GetAsyncKeyState(VK_RETURN)){
			if(a==47 && b==12){
				admin_mode();
			}
			if(a==47 && b==13){
				user_mode();
			}
		}
	}
}

int main(){
FrontPage();
}
