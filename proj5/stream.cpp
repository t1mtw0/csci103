#include "customparser.h"
#include "strmsrv.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include "jsonparser.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please provide a database filename." << std::endl;
        return 1;
    }
    const char *parser_except_msg = "Parser exception occurred";
    const char *no_user_except_msg = "No user logged in";
    const char *rating_limit_except_msg =
        "User not permitted to view this content";
    const char *review_range_except_msg = "Review should be between 0-5 stars";

    // Declare the parsers
    CustomFormatParser cp;
    JsonParser jp;

    // Declare the StreamService object
    StreamService strm;

        std::ifstream ifile(argv[1]);
        if (ifile.fail()) {
            std::cout << "Cannot open file: " << argv[1] << std::endl;
            return 1;
        }
    try {
        // Attempt to initialize the StreamService object
        // Wrap the following block of code in a try..catch
        // sequence.  If a ParserException is thrown, print out
        // the what() message and return 1.  For any other exception that is
        // thrown, ONLY output the string defined in `parser_except_msg` above
        // and return 1.
        std::string dbname(argv[1]);
        if(dbname.find(".json") != std::string::npos){
        strm.readAndParseData(ifile, jp);
        } else if (dbname.find(".cus") != std::string::npos) {
            strm.readAndParseData(ifile, cp);
        } else {
            std::cout << "Couldn't identify file format" << std::endl;
            return 1;
        }

    } catch (ParserError &er) {
        std::cout << er.what() << std::endl;
    } catch (...) {
        std::cout << parser_except_msg << std::endl;
    }

    // Close the file now that we are done parsing
    ifile.close();

    // Now interact with the user
    std::cout << "Menu:" << std::endl;
    std::cout << "==================================================="
              << std::endl;
    std::cout << "QUIT:              0" << std::endl;
    std::cout << "LOGIN:             1 uname" << std::endl;
    std::cout << "LOGOUT:            2" << std::endl;
    std::cout << "GET USER HISTORY:  3" << std::endl;
    std::cout << "SEARCH:            4 <* | string>" << std::endl;
    std::cout << "WATCH:             5 <content-id>" << std::endl;
    std::cout << "REVIEW:            6 <content-id> <number-of-stars>"
              << std::endl;
    std::cout << "SUGGEST SIMILAR:   7 <content-id>" << std::endl;
    std::cout << "==================================================="
              << std::endl;
    int option = -1;
    while (option != 0) {
        std::cout << "\nEnter a command: " << std::endl;
        std::cin >> option;
        try {
            if (option == 1) {
                std::string uname;
                std::cin >> uname;
                strm.userLogin(uname);
            } else if (option == 2) {
                strm.userLogout();
            } else if (option == 3) {
                std::vector<CID_T> results;
                results = strm.getUserHistory();

                // Process results
                std::cout << "Results: " << std::endl;
                for (size_t i = 0; i < results.size(); i++) {
                    strm.displayContentInfo(results[i]);
                }
            } else if (option == 4) {
                std::string search;
                while (isspace(std::cin.peek())) {
                    std::cin.get();
                }
                getline(std::cin, search);
                std::vector<CID_T> results;
                results = strm.searchContent(search);

                // Process results
                std::cout << "Results: " << std::endl;
                for (size_t i = 0; i < results.size(); i++) {
                    strm.displayContentInfo(results[i]);
                }
            } else if (option == 5) {
                CID_T cid;
                std::cin >> cid;
                // Add appropriate exception handling as described
                // in the writeup at an appropriate location of your
                // choosing. Note it is fine to add a try block here
                // (i.e. nested try blocks are legal)
                strm.watch(cid);
            } else if (option == 6) {
                CID_T cid;
                int numstars;
                std::cin >> cid >> numstars;
                // Add appropriate exception handling as described
                // in the writeup at an appropriate location of your
                // choosing. Note it is fine to add a try block here
                // (i.e. nested try blocks are legal)
                strm.reviewShow(cid, numstars);
            } else if (option == 7) {
                CID_T cid;
                std::cin >> cid;
                CID_T result = strm.suggestBestSimilarContent(cid);
                if (result == -1) {
                    std::cout << "No suggestions available." << std::endl;
                } else {
                    strm.displayContentInfo(result);
                }
            } else {
                option = 0;
            }
        }
        catch (UserNotLoggedInError &er) {
            std::cout << no_user_except_msg << std::endl;
        } catch (RatingLimitError &re) {
            std::cout << rating_limit_except_msg << std::endl;
        } catch (ReviewRangeError &rre) {
            std::cout << review_range_except_msg << std::endl;
        }
        catch (...) {
            std::cout << "Error processing command." << std::endl;
        }
    }
    return 0;
}
