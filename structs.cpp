
struct Date_birth{
    int day = -1;
    int mounth = -1;
    int year =-1;
};

struct inst{
    char institut[10];
    char kafedra[10];
    int YearAdmission = 0;
    char StudyGroup[20];
    char CreditNumber[7];
};
struct subject{
    char name[25];
    int mark = -1;
};
struct sessions{
    struct subject subj[10];
};
struct FIO{
        char Name[20];
        char Family[20];
        char Sec_name[20];
};
struct person_model{
        struct FIO FIO;
        struct Date_birth Date_birth;
        struct inst inst;
        char Gender[8];
        struct sessions sessions[9];
};