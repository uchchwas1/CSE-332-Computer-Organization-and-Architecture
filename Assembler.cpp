#include <bits/stdc++.h>
#include<string>
#include<iostream>
using namespace std;




void toLower(string& instruction) // Function for converting incoming stringstream to lowercase
{
    for(int i=0; i<instruction.length(); i++)
    {
        if (instruction[i]>='A' && instruction[i]<='Z')
        {

            instruction[i]+=32;

        }
    }
}

string toBinary(int num, int noOfBits) // Function for converting decimal to binary
{
    string s="";
    for(int i=0;i<noOfBits;i++){
        if ((num & (1<<i))!=0){
            s+="1";
        }
        else {
            s+="0";
        }
    }

    reverse(s.begin(),s.end());


    return s;

}

int main()
{

    string instruction,op,rs,rt,rd,r_type,str_constant,b;
    int cont;
    map<string,string> R_type, I_type, RegValue; // maps for key-value pairing

    /*R_Type opcode and values*/
    R_type["add"] = "00000";
    R_type["sub"] = "00001";
    R_type["and"] = "00010";
    R_type["or"] =  "00011";
    R_type["xor"] = "00100";
    R_type["nor"] = "00101";
    R_type["sll"] = "00110";
    R_type["srl"] = "00111";
    /*I_Type opcode and values*/
    I_type["addi"] = "01000";
    I_type["ori"] = "01001";
    I_type["andi"] = "01010";
    I_type["lui"] = "01011";
    I_type["lw"] = "01100";
    I_type["sw"] = "01101";
    I_type["lb"] = "01110";
    I_type["sb"] = "01111";
    /*Register values*/
    RegValue["$r0"] = "001";
    RegValue["$r1"] = "010";
    RegValue["$r2"] = "011";
    string funct="00";
    ifstream inputFile("C:\\Users\\uchchwas\\Desktop\\jaf\\input.txt");
    ofstream outputFile("C:\\Users\\uchchwas\\Desktop\\jaf\\output.txt");

    while(getline(inputFile, instruction))
    {

        toLower(instruction);
        stringstream input;

        input << instruction;
        input >> op;


        if(R_type.find(op)!=R_type.end()) // R Type opcode
        {

            input >> rd;
            cout<<rd<<endl;

            if(rd=="$000") // Exception handling
            {
                cout << "Invalid: $zero can not be used" << endl;
                outputFile << "Invalid: $zero can not be used" << endl;

            }

            else if(rd[0]!='$' )
            {

                cout <<rd<< " :Invalid: '$' sign is missing before rd"  << endl;
                outputFile << "Invalid: '$' sign is missing before rd" << endl;
                continue;
            }
//            else if(rd[rd.size()-1]!=',')
//            {
//                cout << "Invalid: ',' is missing after rd" << endl;
//                outputFile << "Invalid: ',' is missing after rd" << endl;
//                continue;
//            }
            rd.erase(rd.end()-1);
            input >> rt;

            if(rt[0]!='$')
            {
                cout << "Invalid: '$' sign is missing before rs" << endl;
                outputFile << "Invalid: '$' sign is missing before rs" << endl;
                continue;
            }

            rt.erase(rt.end()-1);
            input >> rs;

            if(rs[0]!='$')
            {
                cout << "Invalid: '$' sign is missing before rt" << endl;
                outputFile << "Invalid: '$' sign is missing before rt" << endl;
                continue;
            }
            else if(rs[rs.size()-1]==',')
            {
                cout << "Invalid: invalid character after rt" << endl;
                outputFile << "Invalid: invalid character after rt" << endl;
                continue;
            } // Exception Handling

            if(R_type.find(op)!= R_type.end() && RegValue.find(rs)!= RegValue.end() && RegValue.find(rt)!= RegValue.end() && RegValue.find(rd)!= RegValue.end()) // Machine Code Write
            {

                if (op=="sll"||op=="srl")
                {
                    rs = "000";

                    cout << R_type[op] << rs << RegValue[rt] << RegValue[rd] << endl;
                    outputFile << R_type[op] << rs << RegValue[rt] << RegValue[rd] << endl;
                }

                else
                    cout << R_type[op] << RegValue[rs] << RegValue[rt] << RegValue[rd] << funct<<endl;
                outputFile << R_type[op] << RegValue[rs] << RegValue[rt] << RegValue[rd] << funct<<endl;
            }
        }

        else if(I_type.find(op)!=I_type.end()) // For i Type opcode
        {
            if(op=="lw"||op=="sw")
            {
                input >> rd >> str_constant >> rs;


                if(rs[0]!='(') // Exception handling
                {
                    cout << "Invalid: '(' is missing before rs" << endl;
                    outputFile << "Invalid: '(' is missing before rs" << endl;
                    continue;
                }
                else if(rs[rs.size()-1]!=')')
                {
                    cout << "Invalid: ')' is missing after rs" << endl;
                    outputFile << "Invalid: ')' is missing after rs" << endl;
                    continue;
                }
                else if(rs[1]!='$')
                {
                    cout << "Invalid: '$' sign is missing before rs" << endl;
                    outputFile << "Invalid: '$' sign is missing before rs" << endl;
                    continue;
                }
                rs.erase(rs.begin());
                rs.erase(rs.end()-1);
                rd.erase(rd.end()-1);
                cout<<"lw"<<rd<<endl;

                if(rt=="$zero")
                {
                    rt = "";
                    cout << "Invalid: $zero can to be used" << endl;
                    outputFile << "Invalid: $zero can to be used" << endl;
                    continue;
                }
                else if(rs=="$zero")
                {
                    rs = "";
                    cout << "Invalid: $zero can to be used" << endl;
                    outputFile << "Invalid: $zero can to be used" << endl;
                    continue;
                }
            }

            else
            {
                input >> rd >> rs >> str_constant;



                if(rs[0]!='$')
                {
                    cout << "Invalid: '$' sign is missing before rs" << endl;
                    outputFile << "Invalid: '$' sign is missing before rs" << endl;
                    continue;
                }
//                else if(rs[rs.size()-1]!=',')
//                {
//                    cout << "Invalid: ',' is missing after rs" << endl;
//                    outputFile << "Invalid: ',' is missing after rs" << endl;
//                    continue;
//                }
                rs.erase(rs.end()-1);
                rd.erase(rd.end()-1);
                if(op=="addi"||op=="andi"||op=="ori")
                {
                    if(rs=="$zero")
                    {
                        rs = "";
                        cout << "Invalid: $zero can to be used" << endl;
                        outputFile << "Invalid: $zero can to be used" << endl;
                        continue;
                    }
                }

            } // Exception handling

            string::size_type sz;

            cont = stoi(str_constant,&sz); // string to int


            b = toBinary(cont,5);



            if(op!="addi"&&op!="andi"&&op!="ori"&&cont<0)
            {
                cout << "Invalid: value can not be neg" << endl;
                outputFile << "Invalid: value can not be neg" << endl;
            }
            else if(cont>15)
            {
                cout << "Invalid: value is too large" << endl;
                outputFile << "Invalid: value is too large" << endl;
            }
            else if(cont<0)
            {
                cout << "Invalid: value is too small" << endl;
                outputFile << "Invalid: value is too small" << endl;
            }
            else
            {

                cout << I_type[op] << RegValue[rs] << RegValue[rd] << b << endl;
                continue;

            }

        }
        else
        {
            cout << "Invalid: Op code not found" << endl;
            outputFile << "Invalid: Op code not found" << endl;
        }
    }


    inputFile.close();
}

