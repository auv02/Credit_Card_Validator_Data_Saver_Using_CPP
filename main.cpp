//
//  main.cpp
//  credit_card_validator_and _data_saver.cpp
//
//  Created by Amritanshu Dash on 17/01/22.
//

#include<bits/stdc++.h>
#include<chrono>
using namespace std;

struct credit_card_details{

    string credit_card_holder_name;
    string credit_card_validity_date;
    string CVV_number;
    string credit_card_company_name;
    
    long long int credit_card_number;
    
    bool is_credit_card_valid;

};

class credit_card{

    struct credit_card_details credit_card_details;

    int len;
    int even_sum = 0;
    int odd_sum = 0;
    int total_sum = 0;
    string str_card_no;
    string rev_str_card_no;
    vector<int> int_card_no;
    vector<int> rev_int_card_no;
    
    
    
    void validity(){
        
        // implemented luhn algorithm here
        
        for(int i = 0; i<len; i++){
            
            if(i % 2 == 0){
                even_sum = even_sum + rev_int_card_no[i];
            }
            
            else if(i % 2 != 0){
                
                if( (rev_int_card_no[i] * 2) > 9){
                    int temp = rev_int_card_no[i] * 2;
                    int n, s = 0;
                    while(temp != 0){
                        
                        n = temp % 10;
                        temp = temp / 10;
                        s = s + n;
                    }
                    odd_sum = odd_sum + s;
                }
                
                else if( (rev_int_card_no[i] * 2) < 9){
                    odd_sum = odd_sum + (rev_int_card_no[i] * 2);
                }
            }
        }

        total_sum = even_sum + odd_sum;
        
        if(total_sum % 10 == 0){
            assign();
        }

        else if(total_sum % 10 != 0){
            cout<<"Details can't be saved as the credit card number is invalid!! "<<endl;
        }
    }
    
    
    
    void assign(){
        
        cout<<"Enter the expiry date of your Credit Card: ";
        cin>>credit_card_details.credit_card_validity_date;
        
        time(credit_card_details.credit_card_validity_date);
        
        if(credit_card_details . is_credit_card_valid){
            
            long long int assign_credit_card_number = 0;
            
            for(int i = 0; i<len; i++){
                assign_credit_card_number = (assign_credit_card_number * 10) + int_card_no[i];
            }
            
            credit_card_details . credit_card_number = assign_credit_card_number;
            
            cout<<"Enter Credit Card holder's name: ";
            cin>>credit_card_details.credit_card_holder_name;
            
            cout<<"Enter CVV: ";
            cin>>credit_card_details.CVV_number;
            
            while(credit_card_details.CVV_number.length() != 3){
                cout<<"Invalid CVV number, Please enter correct one: ";
                cin>>credit_card_details.CVV_number;
            }
            
            int check_no = (int_card_no[0]*10) + int_card_no[1], count = 0;
            
            if( (check_no == 34 || check_no == 37) && str_card_no.length() == 15){
                credit_card_details.credit_card_company_name = "American Express";
                count++;
            }
            
            else if( (check_no == 51 || check_no == 52 || check_no == 53 || check_no == 54 || check_no == 55) && str_card_no.length() == 16){
                credit_card_details.credit_card_company_name = "Master Card";
                count++;
            }
            
            else if( (check_no == 04) && (str_card_no.length() == 13 || str_card_no.length() == 16) ){
                credit_card_details.credit_card_company_name = "Visa";
                count++;
            }
            
            if(count == 0){
                cout<<"Details can't be saved as their was some error!! "<<endl;
            }
            
            else if(count != 0){
                
                //creating a text file
                create_and_save_text_file();
            }
        }
        else{
            cout<<"Details can't be saved as the credit card got expired!! "<<endl;
        }
    }
    
    void create_and_save_text_file(){
        
        ofstream txt_file;
        
        txt_file.open("Credit_Card_details_text_file.txt");
        
        txt_file << "Name of Credit Card holder: " << credit_card_details.credit_card_holder_name << "\nCredit Card number: " << credit_card_details.credit_card_number << "\nCVV of the Credit Card: " << credit_card_details.CVV_number << "\nCard issuer name: " << credit_card_details.credit_card_company_name;
        
        txt_file.close();
    }
    
    void time(string s){
        
        string str = s;
        int credit_card_month = 0, credit_card_year = 0;
        
        if(str.length() == 5 && str[2] == '/'){
            
            credit_card_month = ( (str[0] - 48) * 10 ) + ( ( str[1] - 48) );
            credit_card_year = ( (str[3] - 48) * 10 ) + ( ( str[4] - 48) );
        }
        
        time_t t = std::time(0);   // get time now
        tm* now = std::localtime(&t);
        
        int current_year = (now->tm_year + 1900) % 100;
        int current_month = now->tm_mon + 1;
        
        
        if(current_year > credit_card_year){
                credit_card_details . is_credit_card_valid = false;
        }
        
        else if(current_year == credit_card_year){
            
            if(current_month > credit_card_month){
               credit_card_details . is_credit_card_valid = false;
            }
            
            else if(current_month < credit_card_month){
               credit_card_details . is_credit_card_valid = true;
            }
        }
        
        else if(current_year < credit_card_year){
            credit_card_details . is_credit_card_valid = true;
        }
    }
    
    
    
    public:

    void input(string card_no){

        str_card_no = card_no;
        rev_str_card_no = card_no;

        len = card_no.length();

        reverse(rev_str_card_no.begin(), rev_str_card_no.end());

        for(int i = 0; i<len; i++){
            rev_int_card_no.push_back(rev_str_card_no[i] - 48);
        }
        
        for(int i = 0; i<len; i++){
            int_card_no.push_back(str_card_no[i] - 48);
        }
        
        validity();
    }
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    credit_card cc;
    cc.input("5256111204109818");
    
//    cc.input("256111204109818");
//    cc.validity();
    
    return 0;
}
