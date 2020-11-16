#ifndef TEXT_H
#define TEXT_H
#include <string>

using namespace std;

class text
{
public:
    text(string text,size_t pozition, string type);
    text(const text& i);
    text();

    const string& get_text();
    int get_pozition() const;
    const string get_type();

    void set_text(string value);
    void set_pozition(size_t value);
    void set_type(string value);

private:
    string str;
    size_t pozition;
    bool type;
};

#endif // TEXT_H
