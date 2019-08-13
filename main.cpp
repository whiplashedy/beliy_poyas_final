#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <iomanip>

using namespace std;


class Date
{
public:
    int year;
    int month;
    int day;
    int GetYear() const
    {
        return year;
    }
    int GetMonth() const
    {
        return month;
    }
    int GetDay() const
    {
        return day;
    }

};

Date StringToData(const string &s)
{
    stringstream dateholder(s);
    Date tempdata;
    dateholder >> tempdata.year;
    dateholder.ignore(1);
    dateholder >> tempdata.month;
    dateholder.ignore(1);
    dateholder >> tempdata.day;
    return tempdata;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return (lhs.GetYear()*10000 + lhs.GetMonth()*100 + lhs.GetDay() < rhs.GetYear()*10000 + rhs.GetMonth()*100 + rhs.GetDay());
}

class Database
{
public:
    map<Date, set<string>> day_events;
    void AddEvent(const Date& date, const string& event)
    {
        stringstream dateholder;
        char trash1 = 'c',trash2 = 'x';
        dateholder<<date.year<<trash1<<date.month<<trash2<<date.day;
        string dateholderchild;
        dateholderchild = dateholder.str(); //12-13-41
        day_events[StringToData(dateholderchild)].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event)
    {

        if(day_events.count(date) > 0)
        {
            if(day_events[date].count(event)>0)
            {
                day_events[date].erase(event);
                cout<<"Deleted successfully"<<endl;
                return true;
            }
            else
            {
                cout<<"Event not found"<<endl;
                return false;
            }
        }
        else
        {
                cout<<"Event not found"<<endl;
                return false;
        }
    }
    void DeleteDate(const Date& date)
    {

        if(day_events.count(date) > 0)
        {
            cout<<"Deleted "<<day_events[date].size()<<" events"<<endl;
            day_events[date].clear();
        }
        else
        {
            cout<<"Deleted 0 events"<<endl;
        }

    }

    void Find(const Date& date) const
    {
        if(day_events.count(date) > 0)
        {
            for(auto it : day_events.at(date))
            {
                cout<<it<<endl;
            }
        }
    }

    void Print() const
    {
        cout<<setfill('0');
        for(auto &d : day_events)
        {
            //cout<<"pochemu tak"<<endl;
            for(auto k : d.second)
            {
                cout<<setw(4)<<d.first.year<<'-'<<setw(2)<<setfill('0')<<d.first.month<<'-'<<setw(2)<<setfill('0')<<d.first.day;
                cout<<" "<<k<<endl;
            }
        }
    }
};


//ostream &operator <<(ostream &out, const Date &date)
//{
//    out<<setw(4)<<setfill(0)<<date.GetYear()<<'-'<<setw(2)<<setfill(0)<<date.GetMonth()<<'-'<<setw(2)<<setfill(0)<<date.GetDay();
//    return out;
//}

int main()
{
    Database db;
    Date dd;
    string command;
    while (getline(cin, command))
    {
        int y, m, d;
        string request="", dat = "", event = "";
        int i = 0;
        while (i < command.size() && command[i] != ' ')
        {
            request += command[i];
            i++;
        }
       // cout<<command.size()<<endl;
        //cout<<i<<endl;
        if (request != "" && request != "Add" && request != "Del" && request != "Find" && request != "Print")
        {
            cout << "Unknown command: " << request << endl;
            return 0;
        }
        i++;
        while (i < command.size() && command[i] != ' ')
        {
            dat += command[i];
            i++;
        }
        //cout<<"hi"<<endl;
        i++;
        while (i < command.size() && command[i] != ' ')
        {
            event += command[i];
            i++;
        }
        //cout<<"hi"<<endl;
        stringstream dateholder;
        char trash1 = '-',trash2 = '-';
        if (dat != "") {
            dateholder << dat;
            if (dateholder >> y >> trash1 >> m >> trash2 >> d) {
                if (trash1 != '-' || trash2 != '-') {
                    cout << "Wrong date format: " << dat;
                    return 0;
                }
                else if (dateholder.peek() != EOF) {
                    cout << "Wrong date format: " << dat << endl;
                    return 0;
                }
                else if (m < 1 || m > 12) {
                    cout << "Month value is invalid: " << m;
                    return 0;
                }
                else if (d < 1 || d > 31) {
                    cout << "Day value is invalid: " << d;
                    return 0;
                }
            }
            else {
                cout << "Wrong date format: " << dat << endl;
                return 0;
            }
            dd.day = d;
            dd.year = y;
            dd.month = m;
        }
        if(request == "Add")
        {
            //cout<<"hihello"<<endl;
            db.AddEvent(dd, event);
        }
        else if (request == "Del" && event != "")
            db.DeleteEvent(dd, event);
        else if (request == "Del" && event == "")
            db.DeleteDate(dd);
        else if (request == "Find")
            db.Find(dd);
        else if (request == "Print")
            db.Print();
        // —читайте команды с потока ввода и обработайте каждую
    }

    return 0;
}
/*
Add 0-1-2 event1
Add 1-2-3 event2
Find 0-1-2

Del 0-1-2
Print
Del 1-2-3 event2
Del 1-2-3 event2
*/
