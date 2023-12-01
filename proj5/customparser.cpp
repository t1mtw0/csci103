// Complete me
#include "customparser.h"
#include <iostream>
#include <sstream>

const char *error_msg_1 = "Cannot read integer n";
const char *error_msg_2 = "Error in content parsing";
const char *error_msg_3 = "Error in user parsing";

void CustomFormatParser::parse(std::istream &is,
                               std::vector<Content *> &content,
                               std::vector<User *> &users) {
    // Erase any old contents
    content.clear();
    users.clear();

    int n;
    if (!(is >> n))
        throw ParserError(error_msg_1);
    for (int i = 0; i < n; ++i) {
        int id, type;
        is >> id >> type;
        is >> std::ws;
        std::string name;
        std::getline(is, name);
        int rev, stars, rat;
        is >> rev >> stars >> rat;
        int ep;
        if (type == 1) {
            is >> ep;
        }
        if (is.fail())
            throw ParserError(error_msg_2);
        Content *con;
        if (type == 0) {
            con = new Movie(id, name, rev, stars, rat);
        } else {
            con = new Series(id, name, rev, stars, rat, ep);
        }
        is >> std::ws;
        std::string views;
        std::getline(is, views);
        std::stringstream ss(views);
        std::string v;
        while (ss >> v) {
            con->addViewer(v);
        }
        content.push_back(con);
    }
    std::string u;
    while (is >> u) {
        int rl;
        is >> rl;
        if (is.fail())
            throw ParserError(error_msg_3);
        is >> std::ws;
        User *user = new User(u, rl);
        std::string c;
        std::getline(is, c);
        std::stringstream ss(c);
        CID_T v;
        while (ss >> v) {
            user->addToHistory(v);
        }
        users.push_back(user);
    }
}
