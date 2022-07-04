#include <bits/stdc++.h>
using namespace std;

#define ii pair<int, int>
#define mp make_pair

class dashboard
{
private:
    int sum_elements, count_elements;
    multiset<int> leftset, rightset;
    set<ii> frequency_element;
    map<int, int> elements;

public:
    dashboard()
    {
        sum_elements = count_elements = 0;
    }
    void adjustsize()
    {
        if (leftset.size() > rightset.size() + 1)
        {
            int temp = *leftset.rbegin();
            leftset.erase(leftset.find(temp));
            rightset.insert(temp);
        }
        else if (leftset.size() < rightset.size())
        {
            int temp = *rightset.begin();
            rightset.erase(rightset.find(temp));
            leftset.insert(temp);
        }
    }
    void insert(int element)
    {
        elements[element]++;

        sum_elements += element;
        count_elements++;

        if (leftset.empty() || element <= *leftset.rbegin())
            leftset.insert(element);
        else
            rightset.insert(element);
        adjustsize();

        int fre = elements[element];
        if (fre != 1)
        {
            frequency_element.erase(mp(fre - 1, element));
        }
        frequency_element.insert(mp(fre, element));
    }
    void remove(int element)
    {
        if (elements[element] == 0)
            return;
        elements[element]--;

        sum_elements -= element;
        count_elements--;

        if (leftset.find(element) != leftset.end())
            leftset.erase(leftset.find(element));
        else
            rightset.erase(rightset.find(element));
        adjustsize();

        int fre = elements[element];
        frequency_element.erase(mp(fre + 1, element));
        frequency_element.insert(mp(fre, element));
    }
    void getMean()
    {
        if (count_elements == 0)
        {
            cout << "No elements found!" << endl;
            return;
        }
        cout << "Mean of elements: " << fixed << setprecision(6) << double(sum_elements) / double(count_elements) << endl;
    }
    void getMedian()
    {
        if (count_elements == 0)
        {
            cout << "No elements found!" << endl;
            return;
        }
        cout << "Median of elements: ";
        if (leftset.size() == rightset.size())
        {
            cout << double(*leftset.rbegin() + *rightset.begin()) / (2.0) << endl;
        }
        else
        {
            cout << *leftset.rbegin() << endl;
        }
    }
    void getMode()
    {
        if (count_elements == 0)
        {
            cout << "No elements found!" << endl;
            return;
        }
        cout << "Mode of elements: " << (frequency_element.rbegin())->second << endl;
    }
};
int main()
{
    dashboard board;
    cout << "----------------Instructions---------------" << endl;
    cout << "Enter \"insert\" to insert number into data set" << endl;
    cout << "Enter \"remove\" to remove number from data set" << endl;
    cout << "Enter \"median\" to get median of exisiting data set " << endl;
    cout << "Enter  \"mean\"  to get mean   of exisiting data set " << endl;
    cout << "Enter  \"mode\"  to get mode   of exisiting data set " << endl;
    cout << "Enter  \"exit\"  to exit " << endl
         << endl;
    int num;
    string str;
    do
    {
        cout << "Enter string command: ";
        cin >> str;
        if (str == "insert")
        {
            cout << "Enter the number to be inserted: ";
            cin >> num;
            board.insert(num);
        }
        else if (str == "remove")
        {
            cout << "Enter the number to be removed: ";
            cin >> num;
            board.remove(num);
        }
        else if (str == "median")
            board.getMedian();
        else if (str == "mode")
            board.getMode();
        else if (str == "mean")
            board.getMean();

    } while (str != "exit");
}