#include "strmsrv.h"
#include <fstream>
#include <iostream>
#include <unordered_map>

// To do - Complete this function
StreamService::StreamService(): users_{{}}, content_{{}}, cUser_{nullptr} {}

// To do - Complete this function
StreamService::~StreamService() {
    for (User *u: users_) {
        delete u;
    }
    for (Content *c: content_) {
        delete c;
    }
}

// Complete - Do not alter
void StreamService::readAndParseData(std::istream &is, Parser &p) {
    p.parse(is, content_, users_);
    std::cout << "Read " << content_.size() << " content items." << std::endl;
    std::cout << "Read " << users_.size() << " users." << std::endl;
}

// To do - Complete this function
void StreamService::userLogin(const std::string &uname) {
    if (cUser_ != nullptr) throw std::runtime_error("Another user is already logged in");
    for (User *u: users_) {
        std::string un = u->uname;
        if (un == uname) {
            cUser_ = u;
            return;
        }
    }
    throw std::invalid_argument("The username is not valid");
}

// To do - Complete this function
void StreamService::userLogout() {
    cUser_ = nullptr;
}

// To do - Complete this function
std::vector<CID_T>
StreamService::searchContent(const std::string &partial) const {
    std::vector<CID_T> results;
    for (size_t i = 0; i < content_.size(); i++) {
        // TO DO - modify this to also push back when the string 'partial'
        //  is contained in the name of the current content. Lookup the string
        //  class documentation to find an appropriate function that can be used
        //  to do this simply.
        if (partial == "*" || content_[i]->name().find(partial) != std::string::npos) {
            results.push_back(i);
        }
    }
    return results;
}

// Complete - Do not alter
std::vector<CID_T> StreamService::getUserHistory() const {
    throwIfNoCurrentUser();
    return cUser_->history;
}

// To do - Complete this function
void StreamService::watch(CID_T contentID) {
    throwIfNoCurrentUser();
    if (!isValidContentID(contentID)) throw ReviewRangeError("The content ID is not valid");
    if (content_[contentID]->rating() > cUser_->ratingLimit) throw RatingLimitError("The rating of this content is too high");
    cUser_->addToHistory(contentID);
    content_[contentID]->addViewer(cUser_->uname);
}

// To do - Complete this function
void StreamService::reviewShow(CID_T contentID, int numStars) {
    throwIfNoCurrentUser();
    if (!isValidContentID(contentID)) throw ReviewRangeError("The content ID is not valid");
    if (numStars > 5 || numStars < 0) throw ReviewRangeError("The number of stars must be between 0 and 5");
    content_[contentID]->review(numStars);
}

// To do - Complete this function
CID_T StreamService::suggestBestSimilarContent(CID_T contentID) const {
    throwIfNoCurrentUser();
    if (!isValidContentID(contentID)) throw ReviewRangeError("The content ID is not valid");
    std::vector<User *> alsoWatched = {};
    for (User *u : users_) {
        if (u->uname == cUser_->uname) continue;
        if (u->haveWatched(contentID)) alsoWatched.push_back(u);
    }
    CID_T largest = -1;
    std::unordered_map<CID_T, int> numWatched {};
    for (User *u : alsoWatched) {
        for (CID_T id: u->history) {
            if (id == contentID) continue;
            if (cUser_->haveWatched(id)) continue;
            if (numWatched.find(id) == numWatched.end()) {
                numWatched[id] = 1;
            } else {
                numWatched[id] += 1;
            }
            if (largest == -1 || numWatched[id] > numWatched[largest]) largest = id;
        }
    }
    return largest;
}

// To do - Complete this function
void StreamService::displayContentInfo(CID_T contentID) const {
    // Do not alter this
    if (!isValidContentID(contentID)) {
        throw std::invalid_argument("Watch: invalid contentID");
    }

    // Call the display abitlity of the appropriate content object
}

// Complete - Do not alter
bool StreamService::isValidContentID(CID_T contentID) const {
    return (contentID >= 0) && (contentID < (int)content_.size());
}

// Complete - Do not alter
void StreamService::throwIfNoCurrentUser() const {
    if (cUser_ == NULL) {
        throw UserNotLoggedInError("No user is logged in");
    }
}

// Complete - Do not alter
int StreamService::getUserIndexByName(const std::string &uname) const {
    for (size_t i = 0; i < users_.size(); i++) {
        if (uname == users_[i]->uname) {
            return (int)i;
        }
    }
    return -1;
}
