// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "../include/my_json.hpp"



TEST(Json, ExampleJson)
{
    Json object = Json::parse(R"(
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
        }
    )");
    EXPECT_EQ(any_cast<std::string>(object["lastname"]), "Ivanov");
    EXPECT_EQ(any_cast<bool>(object["islegal"]), false);
    EXPECT_EQ(any_cast<double>(object["age"]), 25);

    Json marks = any_cast<Json>(object["marks"]);
    EXPECT_EQ(any_cast<double>(marks[0]), 4);
    EXPECT_EQ(any_cast<double>(marks[1]), 5);

    Json address = any_cast<Json>(object["address"]);
    EXPECT_EQ(any_cast<std::string>(address["city"]), "Moscow");
    EXPECT_EQ(any_cast<std::string>(address["street"]), "Vozdvijenka");
}

TEST(Json, EmptyJson)
{

    Json some{};
    EXPECT_EQ(some.is_object(), false);
    EXPECT_EQ(some.is_array(), false);
    EXPECT_EQ(some.is_empty(), true);
}


TEST(JsonArray, SimpleArray)
{
    Json json{ "[ 1 ]" };
    EXPECT_EQ(json.is_object(), false);
    EXPECT_EQ(json.is_array(), true);
    EXPECT_EQ(json.is_empty(), false);

    EXPECT_EQ(any_cast<double>(json[0]), 1.);
}

TEST(JsonArray, InArray)
{
    Json json{ "[1.5, \"Peter\", \"Vasya\", true]" };
    EXPECT_EQ(json.is_object(), false);
    EXPECT_EQ(json.is_array(), true);
    EXPECT_EQ(json.is_empty(), false);

    EXPECT_EQ(any_cast<double>(json[0]), 1.5);
    EXPECT_EQ(any_cast<std::string>(json[1]), "Peter");
    EXPECT_EQ(any_cast<std::string>(json[2]), "Vasya");
    EXPECT_EQ(any_cast<bool>(json[3]), true);
}
TEST(Json, OperatorArrayTypeException)
{
    Json some{};
    EXPECT_THROW(some[1], WrongJson);
}

