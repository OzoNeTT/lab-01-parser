#include <iostream>

#include <my_json.hpp>

using namespace std;

const char * const json_data = R"(
{
    "lastname" : "Ivanov",
    "firstname" : "Ivan",
    "age" : 25,
    "islegal" : false,
    "marks" : [
    	4,5,5,5,2,3
    ],
    "address" : {
    	"city" : "Moscow",
        "street" : "Vozdvijenka"
    }
})";

template <typename T, typename R>
void EXPECT_EQ(T left, R right, string name = "")
{
    if (left != right)
        cout << name + " is FAILED" << endl;
    else
        cout << name + " is PASSED" << endl;
}

int main() {
    Json object = Json::parse(json_data);
    EXPECT_EQ(any_cast<std::string>(object["lastname"]), "Ivanov");
    EXPECT_EQ(any_cast<bool>(object["islegal"]), false);
    EXPECT_EQ(any_cast<double>(object["age"]), 25);

    auto marks = any_cast<Json>(object["marks"]);
    EXPECT_EQ(any_cast<double>(marks[0]), 4);
    EXPECT_EQ(any_cast<double>(marks[1]), 5);

    auto address = any_cast<Json>(object["address"]);
    EXPECT_EQ(any_cast<std::string>(address["city"]), "Moscow");
    EXPECT_EQ(any_cast<std::string>(address["street"]), "Vozdvijenka");
    return 0;
}