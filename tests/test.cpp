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