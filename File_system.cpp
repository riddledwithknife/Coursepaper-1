#include "models.cpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <list>
#include <cctype>

using namespace std;    
class variants : models{
    friend class menu;
    friend class FileSystem;
public:
        int selected_session = 0;
        variants(){
            cout  << "Выполнение варианта\n";
        }
        ~variants(){
            cout  << "Конец выполнения варианта 8\n";
        }
        int count_marks(person_model student){
            int cnt = 0;
               for(int session = 0; session < 9; session++){
                        for (int subj = 0; subj < 10; subj++){
                                if(student.sessions[session].subj[subj].mark != -1)
                                    cnt++;
                        }
               }
            return cnt;
        }
        double calc_middle(person_model student, int session){
                double result = 0.0;
                int summ = 0;
                int cnt = 0;
                        for (int subj = 0; subj < 10; subj++){
                                if(student.sessions[session].subj[subj].mark != -1){
                                    cnt++;
                                    summ = summ + student.sessions[session].subj[subj].mark;
                                }
                        }
            if(cnt == 0){
                //cout << "Не заполнены предметы у человека\n";
                return 0;
            }
            return double(summ)/cnt;  
        }
       
       // bool compare_nocase (const person_model& first, const person_model& second)
        //{
         //   return calc_middle(first, 0) > calc_middle(second, 0);
        //}      
            
        void do_sort(std::list<person_model> students_buff, char StudyGroup_to_Select[20], int session_to_Select, int min_year, int max_year){
                int flag_one_serched = 0;
                selected_session = session_to_Select;
                std::list<person_model> Students_sorted_by_group;
                std::list<person_model> Students_sorted_by_marks;

                for(person_model student : students_buff){
                        if(strcmp(student.inst.StudyGroup, StudyGroup_to_Select) == 0 && student.Date_birth.year <=max_year && student.Date_birth.year >= min_year){
                                flag_one_serched = 1;
                                Students_sorted_by_group.push_back(student);
                        }
                }
                Students_sorted_by_group.sort([this](const person_model& first, const person_model& second) {return this->calc_middle(first, this->selected_session) > this->calc_middle(second, this->selected_session);});
                
                cout << "\n";
                int counter_sudents = 0;
                for(person_model student_to_out : Students_sorted_by_group){
                            counter_sudents++;
                            EchoStudent_not_full(counter_sudents, student_to_out);
                            cout << 1.0*calc_middle(student_to_out, selected_session) << "\n";
                }

        }
        void variant_81(std::list<person_model> students_buff){

            char StudyGroup_to_Select[20];
            int session_to_Select = 0;
            int flag_need_sort_all = 0;
qwerrrd:    cout <<  "Введите группу где делать сортировку >> ";
            cin >> StudyGroup_to_Select;
            cout << "Введите сессию где делать сортировку -1 для сортировки по всем >> ";
            cin >> session_to_Select;
            int year_birth_min = 0;
            int year_birth_max = 0;
            cout << "Введите нижнюю границу года рождения >> ";
            cin  >> year_birth_min;
            cout << "Введите вернхнюю границу года рождения >> ";
            cin  >> year_birth_max;

            if(year_birth_min > year_birth_max){
                cout << "Ошибка ввода повторите\n";
                goto qwerrrd;
            }
            
            if(session_to_Select == -1){
                    flag_need_sort_all = 1;
                    goto asde;
            }
            if(session_to_Select < 1 | session_to_Select > 9){
                cout << "Ошибка ввода повторите\n";
                goto qwerrrd;
            }
asde:       if(flag_need_sort_all){
                cout << "Выбран режим режим сортировки всех сессий для группы " << StudyGroup_to_Select <<"\n";
                for(int i = 0; i < 9; i++){
                    cout << "+==========================================================+\n";
                    cout << "|Сессия " << i+1 << "|\n";
                    do_sort(students_buff, StudyGroup_to_Select, i, year_birth_min, year_birth_max);
                    cout << "+----------------------------------------------------------+\n";
                }
            }else{
                cout << "Выбран режим режим сортировки " << session_to_Select<< " сессий для группы " << StudyGroup_to_Select <<"\n";
                do_sort(students_buff, StudyGroup_to_Select, session_to_Select - 1, year_birth_min,year_birth_max);
            }
        }

};    



class FileSystem : models  {
    
    friend class menu;
    friend class variants;

    private:
        FILE *file = NULL;
        char *FileName;
        int count_users = 0;

        FileSystem(char* file_name){
                file = fopen(file_name, "ab+");
                FileName = file_name;
                count_users = countLines();

        } 

        ~FileSystem()
	    {
            fclose(file);
        }

        int  countLines()
        {

                                FILE *file2_R = NULL;
                                file2_R = fopen(FileName, "rb");
                                if (file2_R == NULL) {
                                        printf("Файл не существует\n");
                                        return -1;
                                        };
                                
                                unsigned long position = ftell(file2_R); 
                                int count_students = 0;
                                while (1){
                                                person_model Student;
                                                
                                                fread(&Student, sizeof(person_model), 1, file2_R);
                                                if(ftell(file2_R) == position)
                                                    break;
                                                fseek(file2_R , position + sizeof(person_model), SEEK_SET );
                                                if(ftell(file2_R) == position)
                                                    break;
                                                position = ftell(file2_R);
                                                count_students++;
                                            }
                                        
                fclose(file2_R);  
                count_users = count_students;
                return count_students;       
            }
        int ScanPerson(){
                person_model Student;
                printf("Введите имя студента >> \033[32m");
                    scanf("%s", Student.FIO.Name); 
                    printf("\033[0m");
                printf("Введите Фамилию студента >> \033[32m ");
                    scanf("%s", Student.FIO.Family);
                    printf("\033[0m");                
                printf("Введите Отчество студента >>  \033[32m");
                    scanf("%s", Student.FIO.Sec_name); 
                    printf("\033[0m");
                printf("Введите день рождения студента >>  \033[32m");
                    scanf("%d",&Student.Date_birth.day); 
                    printf("\033[0m");
                printf("Введите месяц рождения студента >>  \033[32m");
                    scanf("%d",&Student.Date_birth.mounth); 
                    printf("\033[0m");
                printf("Введите год рождения студента >>  \033[32m");
                    scanf("%d",&Student.Date_birth.year);
                    printf("\033[0m");
                printf("Введите гендерную принадлежность студента >>  \033[32m");
                    scanf("%s", Student.Gender);  
                    printf("\033[0m");
                printf("Введите год поступления в учебное заведение студента >>  \033[32m");
                    scanf("%d",&Student.inst.YearAdmission); 
                    printf("\033[0m");
                printf("Введите название института студента >>  \033[32m");
                    scanf("%s", Student.inst.institut); 
                    printf("\033[0m");
                printf("Введите кафедру студента >>  \033[32m");
                    scanf("%s", Student.inst.kafedra); 
                    printf("\033[0m");
                printf("Введите учебную группу студента >>  \033[32m");
                    scanf("%s", Student.inst.StudyGroup); 
                    printf("\033[0m");
                printf("Введите номер зачетной книги студента >>  \033[32m");
                    scanf("%s", Student.inst.CreditNumber); 
                    printf("\033[0m\n");

redo_input:     cout << "Продолжить ввод оценок? y/n >> \n";
                char continue_inp;
                cin >> continue_inp;
                cout << '\n';
                if(continue_inp == 'n'){
                    cout << "Данные о студенте записаны\n";

                    fwrite(&Student, sizeof(person_model), 1, file);
                    return 0;
                }
                if(continue_inp != 'y'){
                    cout << "\033[31m Ошибка ввода повтори ввод\n\033[0m";
                    goto redo_input;
                }
                cout << "Начало ввода оценок\n";
                for(int session = 0; session < 9; session++){
                                char continue_inp;
             redo_inp_ses:      cout << "Начало ввода \033[32m"<< session + 1<<"\033[0m сессии продолжить? y/n >> ";
                                         
                                cin >> continue_inp;
                                if(continue_inp == 'n'){
                                        cout << "\033[33m Пропуск ввода сессии\n\033[0m";
                                        continue;                                    
                                }

                                if(continue_inp == 'y'){
                                    for (int subj = 0; subj < 10; subj++){
                                                
                                                cout << "Введите название \033[32m"<< subj+1 <<"\033[0m предмета >> \033[32m";
                                                cin >> Student.sessions[session].subj[subj].name;                              
                                                cout << "\033[0m";
                                                cout << "Введите оценку за предмет \033[31m "<< Student.sessions[session].subj[subj].name<<"\033[0m >> \033[32m";
                                                cin >> Student.sessions[session].subj[subj].mark;
                                                cout << "\033[0m";
                                                char cont = 0;

            redo_in:                            cout << "Продолжить ввод? y/n>> \033[32m" ;
                                                cin >> cont;
                                                if(cont == 'n'){
                                                    cout << "Колиичество предметов в \033[32m"<< session + 1 << "\033[0mсеместе : \033[32m" << subj+1 << "\033[0m\n"; 
                                                    break;
                                                }
                                                if(cont == 'y'){


                                                }
                                                else{
                                                    cout << "\033[31m Ошибка ввода повтори ввод\n\033[0m";
                                                    goto redo_in;
                                                }
                                                cout << "\033[31mКонец ввода предмета \n\033[0m";
                                        
                                            }
                                }
                                else {
                                    cout << "\033[31m Ошибка ввода повтори ввод\n\033[0m";
                                    goto redo_inp_ses;
                                }

                }



                fwrite(&Student, sizeof(person_model), 1, file);


            return 0;
        }
        int GetPersonsFromFile(){
                cout << "+--------------------------------------------------------------------------------------+" << '\n';
                
                FILE *file2_R = NULL;
                file2_R = fopen(FileName, "rb");
                if (file2_R == NULL) {
                        printf("Файл не существует\n");
                        };
                unsigned long position = ftell(file2_R);
                count_users = countLines(); 
                for (int i=0; i < count_users; i++){
                        person_model Student;

                        fread(&Student, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == position)
                            break;
                        EchoStudent(Student); 
                        fseek(file2_R , position + sizeof(person_model), SEEK_SET );
                        position = ftell(file2_R);


                }
                
                fclose(file2_R);        
            return 0;
            
        }
        int delete_person(){
                FILE *file2_R = NULL;
                file2_R = fopen(FileName, "rb");
                if (file2_R == NULL) {
                        printf("Файл не существует\n");
                        };
                unsigned long position = ftell(file2_R);
                count_users = countLines(); 
                system("clear");
               // cout << "Какого пользовтеля удалить?"
redo_act:       for (int i=0; i < count_users; i++){
                        person_model Student;

                        fread(&Student, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == position)
                            break;
                        EchoStudent_not_full(i, Student);
                        fseek(file2_R , position + sizeof(person_model), SEEK_SET );
                        position = ftell(file2_R);
                }
                cout << "Какого пользовтеля удалить? -1 - отмена >> ";
                int changer = 0;
                cin >>changer;
                if(changer == -1){
                        cout << "Выход\n";
                        return -1;
                }
                if (changer > count_users | changer < 0){
                        cout << "Повторите ввод данные некорректны\n";
                        goto redo_act;
                }

  
                
                FILE *file_edit = NULL;
                file_edit = fopen("data/data_buff.bin", "wb");
                fseek(file2_R, 0, SEEK_SET);

                unsigned long int pos_r = ftell (file2_R);
                unsigned long int pos_w = ftell(file_edit);
                for (int i=0; i < count_users; i++){
                        person_model Student;

                        fread(&Student, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == pos_r)
                            break;
                        if(i == changer){
                                 fseek(file2_R , pos_r + sizeof(person_model), SEEK_SET );
                                 pos_r = ftell(file2_R);
                                 continue;
                        }

                        fwrite(&Student, sizeof(person_model), 1, file_edit);
                        fseek(file_edit , pos_w + sizeof(person_model), SEEK_SET );
                        fseek(file2_R , pos_r + sizeof(person_model), SEEK_SET );
                        pos_r = ftell(file2_R);
                        pos_w = ftell(file_edit);


                }
                fclose(file2_R);
                fclose(file_edit);
                remove(FileName);
                rename("data/data_buff.bin", FileName );
                cout <<"успех\n";
            return 0;
        }
        int edit_record(){


               FILE *file2_R = NULL;
                file2_R = fopen(FileName, "rb");
                if (file2_R == NULL) {
                        printf("Файл не существует\n");
                        };

redo_act1:      fseek(file2_R, 0, SEEK_SET);
                unsigned long position = ftell(file2_R);
                count_users = countLines(); 
                system("clear");

                 for (int i=0; i < count_users; i++){
                        person_model Student;

                        fread(&Student, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == position)
                            break;
                        EchoStudent_not_full(i, Student);
                        fseek(file2_R , position + sizeof(person_model), SEEK_SET );
                        position = ftell(file2_R);
                }
                cout << "Какого пользовтеля изменить? \033[31m-1 - отмена \033[0m>> \033[33m";
                int changer = 0;
                cin >> changer;
                cout << "\033[0m\n";
                if(changer == -1){
                        cout << "Выход\n";
                        return -1;
                }
                if (changer > count_users){
                        cout << "Повторите ввод данные некорректны\n";
                        goto redo_act1;
                }
            
                fseek(file2_R , 0, SEEK_SET );
                unsigned long int pos_r = ftell (file2_R);
                person_model Student_to_edit;

                for (int i=0; i < count_users; i++){
                        fread(&Student_to_edit, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == pos_r)
                            break;
                        if(i == changer){
                                 fseek(file2_R , pos_r + sizeof(person_model), SEEK_SET );
                                 pos_r = ftell(file2_R);
                                 cout << "\n\033[32mВыбран студент: \033[0m\n";
                                 EchoStudent(Student_to_edit);
                                 break;
                        }

                        fseek(file2_R , pos_r + sizeof(person_model), SEEK_SET );
                        pos_r = ftell(file2_R);


                }
                char witch;
reenter_y_n:    cout << "Продолжить редактирование ? y/n>> \033[31m";
                cin >> witch;
                cout <<  "\033[0m";
                if(witch == 'n'){
                        goto redo_act1;
                }
                if(witch != 'y'){
                    cout << "Ошибка ввода повтор\n";
                    goto reenter_y_n;
                }
                cout << "Редактирование..... 0 для пропуска параметра 1 для редактирования\n";
                    int editpos;

                    printf("Имя студента >> \033[32m");
                    cin >> editpos;
                    printf("\033[0m");                

                    if(editpos == 1){
                            printf("Введите имя студента >> \033[32m");
                            scanf("%s", Student_to_edit.FIO.Name); 
                            printf("\033[0m\n");
                    }

                    printf("Фамилию студента >> \033[32m ");
                    cin >> editpos;
                    printf("\033[0m");                

                    if(editpos == 1){
                                printf("Введите Фамилию студента >> \033[32m ");
                                scanf("%s", Student_to_edit.FIO.Family);
                                printf("\033[0m\n");
                    }     
                               
                    printf("Отчество студента >>  \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите Отчество студента >>  \033[32m");
                        scanf("%s", Student_to_edit.FIO.Sec_name); 
                        printf("\033[0m\n");
                    }

                    printf("день рождения студента >>  \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите день рождения студента >>  \033[32m");
                        scanf("%d",&Student_to_edit.Date_birth.day); 
                        printf("\033[0m\n");
                    }

                    printf("месяц рождения студента >>  \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите Омесяц рождения студента >> \033[32m");
                        scanf("%d",&Student_to_edit.Date_birth.mounth); 
                        printf("\033[0m\n");
                    }

                    printf("год рождения студента >> \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите год рождения студента >>  \033[32m");
                        scanf("%d",&Student_to_edit.Date_birth.year);
                        printf("\033[0m\n");
                    }


                    printf("гендерную принадлежность студента >>  \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите гендерную принадлежность студента >>  \033[32m");
                        scanf("%s", Student_to_edit.Gender);  
                        printf("\033[0m\n");
                    }

                    printf("год поступления в учебное заведение студента >> \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите год поступления в учебное заведение студента >>  \033[32m");
                        scanf("%d",&Student_to_edit.inst.YearAdmission);
                        printf("\033[0m\n");
                    }


                    printf("название института студента >> \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите название института студента >>  \033[32m");
                        scanf("%s", Student_to_edit.inst.institut); 
                        printf("\033[0m\n");
                    }

                    printf("кафедру студента >> \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите кафедру студента >> \033[32m");
                        scanf("%s", Student_to_edit.inst.kafedra);
                        printf("\033[0m\n");
                    }

                    printf("учебную группу студента >> \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите название института студента >>  \033[32m");
                        scanf("%s", Student_to_edit.inst.StudyGroup);
                        printf("\033[0m\n");
                    }

                    printf("номер зачетной книги студента >> \033[32m");
                    cin >> editpos;
                    printf("\033[0m");  
                    if(editpos == 1){
                        printf("Введите номер зачетной книги студента >>  \033[32m");
                        scanf("%s", Student_to_edit.inst.CreditNumber);
                        printf("\033[0m\n");
                    }
                    char continue_inputs;

input_continue111:  cout << "Продолжить редактирование оценок? y/n >> ";
                    cin >> continue_inputs;
                    if(continue_inputs == 'n'){
                        goto editor;
                        cout << "Готово!";

                    }
                    if(continue_inputs == 'y'){

                            
                            for(int session = 0; session < 9; session++){   
                                    char continue_req;
        edit_con_label:             cout << "Начало редактирования оценок " << session + 1 << " сессии продолжить? y/n/a >> ";
                                    cin >>  continue_req; 
                                    if(continue_req == 'n')
                                            continue;
                                    if(continue_req == 'a'){
                                        int flag = 0;
                                        cout << "Режим добавления экзамена к сессии\n";
                                         for (int subj = 0; subj < 10; subj++){
                                            if(Student_to_edit.sessions[session].subj[subj].mark == -1){
                                                cout << "Какой предмет добавить? >> "; 
                                                cin >> Student_to_edit.sessions[session].subj[subj].name;
                                                cout << "Введите оценку по предмету \033[33m" << Student_to_edit.sessions[session].subj[subj].name << "\033[0m >> ";
                                                cin >> Student_to_edit.sessions[session].subj[subj].mark;
                                                flag = 1;
                                                break;
                                            }
                                        }
                                        if(flag == 0){
                                            cout << "Невозможно добавить предмет к сессии\n";
                                            continue;
                                        }

                                    }   
                                    if(continue_req != 'y' && continue_req != 'a'){
                                        cout << "Ошибка ввода повторите\n";
                                        goto edit_con_label;
                                    }                                 
                                    for (int subj = 0; subj < 10; subj++){
                                            if(Student_to_edit.sessions[session].subj[subj].mark != -1){
                                              char need_to_continue;
                  redo_act2:                  cout << "Редактирование оценки по предмету: \033[33m" << Student_to_edit.sessions[session].subj[subj].name << "\033[0m\n";
                                              cout << "Продолжить редактирование? y/n >> ";
                                              cin >> need_to_continue;
                                              if(need_to_continue == 'n'){
                                                  continue;
                                              }
                                              if(need_to_continue == 'y'){
                                                    int mark_to_write =0;
                                                    cout << "Введите новую оценку по предмету \033[33m" << Student_to_edit.sessions[session].subj[subj].name << "\033[0m >>" ;
                                                    cin >> mark_to_write;
                                                    Student_to_edit.sessions[session].subj[subj].mark = mark_to_write;
                                              }
                                              else{
                                                    cout << "Ошибка ввода повторите \n";
                                                    goto redo_act2;

                                              }
                                
                                            }
                                    }
                            }
                    }else{
                        cout << "Ошибка ввода повторите \n";
                        goto input_continue111;
                    }
editor:             EchoStudent(Student_to_edit);

                FILE *file_edit = NULL;
                file_edit = fopen("data/data_buff.bin", "wb");
                fseek(file2_R, 0, SEEK_SET);
                fseek(file_edit, 0, SEEK_SET);
                unsigned long int pos_w = ftell(file_edit);
                pos_r = ftell (file2_R);
                pos_w = ftell (file_edit);
                for (int i=0; i < count_users; i++){
                        person_model Student;
                        fread(&Student, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == pos_r)
                            break;
                        if(i == changer)
                                 fwrite(&Student_to_edit, sizeof(person_model), 1, file_edit);
                        else
                                 fwrite(&Student, sizeof(person_model), 1, file_edit);
                        
                        fseek(file_edit , pos_w + sizeof(person_model), SEEK_SET );
                        fseek(file2_R , pos_r + sizeof(person_model), SEEK_SET );
                        pos_r = ftell(file2_R);
                        pos_w = ftell(file_edit);


                }
                fclose(file2_R);
                fclose(file_edit);
                remove(FileName);
                rename("data/data_buff.bin", FileName );            
                cout <<"успех\n";
            return 0;

        }
        int out_tabel(){
                
               

               FILE *file2_R = NULL;
                file2_R = fopen(FileName, "rb");
                if (file2_R == NULL) {
                        printf("Файл не существует\n");
                        };

redo_act11:      fseek(file2_R, 0, SEEK_SET);
                unsigned long position = ftell(file2_R);
                count_users = countLines(); 
                system("clear");

                 for (int i=0; i < count_users; i++){
                        person_model Student;

                        fread(&Student, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == position)
                            break;
                        EchoStudent_not_full(i, Student);
                        fseek(file2_R , position + sizeof(person_model), SEEK_SET );
                        position = ftell(file2_R);
                }
                cout << "Табель какого пользователя вывести? \033[31m-1 - отмена \033[0m>> \033[33m";
                int changer = 0;
                cin >> changer;
                cout << "\033[0m\n";
                if(changer == -1){
                        cout << "Выход\n";
                        return -1;
                }
                if (changer > count_users){
                        cout << "Повторите ввод данные некорректны\n";
                        goto redo_act11;
                }
            
                fseek(file2_R , 0, SEEK_SET );
                unsigned long int pos_r = ftell (file2_R);
                person_model Student_to_edit;

                for (int i=0; i < count_users; i++){
                        fread(&Student_to_edit, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == pos_r)
                            break;
                        if(i == changer){
                                 fseek(file2_R , pos_r + sizeof(person_model), SEEK_SET );
                                 pos_r = ftell(file2_R);
                                 echo_marks(Student_to_edit);
                                 break;
                        }

                        fseek(file2_R , pos_r + sizeof(person_model), SEEK_SET );
                        pos_r = ftell(file2_R);


                }
            
            return 0;
        }
        void do_sorts(){
                                
                variants *variant = new variants();
                FILE *file2_R = NULL;
                std::list<person_model> data_students;
                file2_R = fopen(FileName, "rb");
                if (file2_R == NULL) {
                        printf("Файл не существует\n");
                        };
                unsigned long position = ftell(file2_R);
                count_users = countLines(); 
                for (int i=0; i < count_users; i++){
                        person_model Student;

                        fread(&Student, sizeof(person_model), 1, file2_R);
                        if(ftell(file2_R) == position)
                            break;   
                        data_students.push_back(Student);
                     
                        fseek(file2_R , position + sizeof(person_model), SEEK_SET );
                        position = ftell(file2_R);

                }
                variant->variant_81(data_students);

                fclose(file2_R);  

        }
};
