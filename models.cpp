#include <iostream>
#include "structs.cpp"
using namespace std;


class models : public person_model{
    friend class FileSystem;
    friend class variants;

    private:
            int EchoStudent(person_model student){
                //if(!(student.Date_birth.day ==-1 && student.Date_birth.mounth==-1 && student.Date_birth.year == -1)){
                            int exit_code = 0;
            

                            cout << "|" << student.FIO.Family << " "<< student.FIO.Name << " "<<student.FIO.Sec_name << "|";
                            cout << student.Date_birth.day<< "." << student.Date_birth.mounth << "." <<student.Date_birth.year << "|";
                            cout << student.Gender << "|";
                            cout << student.inst.YearAdmission << "|" << student.inst.institut << "|" << student.inst.kafedra << "|";
                            cout << student.inst.StudyGroup << "|" << student.inst.CreditNumber<<"|\n";
                            cout << "+--------------------------------------------------------------------------------------+" << '\n';
                //}

                return 0;
            }    
            int EchoStudent_not_full(int counter, person_model student){
                            if(!(student.Date_birth.day ==-1 && student.Date_birth.mounth==-1 && student.Date_birth.year == -1)){
                                int exit_code = 0;
                        
                            cout << "+-------------------------------------------------+" << '\n';

                            cout << "|" << counter << ") "<< student.FIO.Family << " "<< student.FIO.Name << " "<<student.FIO.Sec_name << "|";
                            cout << student.Date_birth.day<< "." << student.Date_birth.mounth << "." <<student.Date_birth.year << "|\n";
                            cout << "+-------------------------------------------------+" << '\n';
                }
                return 0;
            }

            int echo_marks(person_model student){

                            cout << "Студент: " << student.FIO.Family << " "<< student.FIO.Name << " "<<student.FIO.Sec_name << "\n";
                            for(int session = 0; session < 9; session++){
                                cout << "+-------------------------------------------------+" << '\n';
                                cout << "|Сессия " << session +1 << '\n';
                                    for (int subj = 0; subj < 10; subj++){
                                        if(student.sessions[session].subj[subj].mark != -1){
                                            cout << "| " << student.sessions[session].subj[subj].name << " | " <<  student.sessions[session].subj[subj].mark << '\n';

                                        }

                                    }
                            }
                            cout << "+-------------------------------------------------+" << '\n';
                
                return 0;
            }
};