#include<iostream>
#include<string>
using namespace std;
string version1(const string & s1, const string & s2);
const string & version2(string & s1, const string & s2);


int main()
{
    string input = "My fault";
    string result;
    result = version1(input, "###");
    cout << "1st" << input << "\n" << result << endl;
    result = version2(input, "###");
    cout << "2nd" << input << "\n" << result << endl;
    cout << "3rd" << input << "\n" << result << endl;
    return 0;
}

string version1(const string & s1, const string & s2)
{
    string temp;

    temp = s2 + s1 + s2;
    return temp;
}

const string & version2(string & s1, const string & s2)
{
    s1 = s2 + s1 + s2;
    return s1;
}

