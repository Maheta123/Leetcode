class Solution {
public:

    string add_one(string &s)
{
    int i = s.length() - 1;

    while(i >= 0)
    {
        if(s[i] == '0')
        {
            s[i] = '1';
            return s;     
        }
        else
        {
            s[i] = '0';  
        }
        i--;
    }

    s = "1" + s;
    return s;
}
    int numSteps(string s) {  
        int c = 0;
        while(s!="1")
        {
            if(s[s.length()-1]=='0')
            {
                s.erase(s.length()-1,1);
            }
            else
            {
                s = add_one(s);
            }
            c++;
        }
        return c;
    }
};