#include "Twitter.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;

class Tweet {
public:
    int id;
    int time;
    Tweet* next;

    Tweet(int id, int time) : id(id), time(time), next(nullptr) {}
};

class User {
public:
    int id;
    unordered_set<int> followed;
    Tweet* head;

    User(int id) {
        this->id = id;
        head = nullptr;
        follow(id); // follow self
    }

    void follow(int userId) {
        followed.insert(userId);
    }

    void unfollow(int userId) {
        if (userId != id)
            followed.erase(userId);
    }

    void post(int tweetId, int time) {
        Tweet* tweet = new Tweet(tweetId, time);
        tweet->next = head;
        head = tweet;
    }
};

// Global storage
unordered_map<int, User*> users;

User* getUser(int userId) {
    if (users.find(userId) == users.end()) {
        users[userId] = new User(userId);
    }
    return users[userId];
}

// Twitter methods

Twitter::Twitter() {
    timeStamp = 0;
}

void Twitter::postTweet(int userId, int tweetId) {
    getUser(userId)->post(tweetId, timeStamp++);
}

//  FIXED: user validation added
void Twitter::follow(int followerId, int followeeId) {
    if (users.find(followerId) == users.end()) {
        cout << "Follower user not found!\n";
        return;
    }

    if (users.find(followeeId) == users.end()) {
        cout << "Followee user not found!\n";
        return;
    }

    else
    {
    	users[followerId]->follow(followeeId);
	cout<<"Followed successfully";
    }
}

void Twitter::unfollow(int followerId, int followeeId) {
    if (users.find(followerId) == users.end()) {
        cout << "Follower user not found!\n";
        return;
    }

    if (users.find(followeeId) == users.end()) {
        cout << "Followee user not found!\n";
        return;
    }
    
    else
    {
	cout<<"Unfollowed successfully";
    	users[followerId]->unfollow(followeeId);
    }
}

vector<int> Twitter::getNewsFeed(int userId) {
    vector<int> result;

    if (users.find(userId) == users.end()) {
        cout << "User not found!\n";
        return result;
    }

    auto cmp = [](Tweet* a, Tweet* b) {
        return a->time < b->time;
    };

    priority_queue<Tweet*, vector<Tweet*>, decltype(cmp)> pq(cmp);

    for (int followeeId : users[userId]->followed) {
        Tweet* tweet = users[followeeId]->head;
        if (tweet) pq.push(tweet);
    }

    int count = 0;
    while (!pq.empty() && count < 10) {
        Tweet* tweet = pq.top();
        pq.pop();

        result.push_back(tweet->id);
        count++;

        if (tweet->next) {
            pq.push(tweet->next);
        }
    }

    return result;
}
