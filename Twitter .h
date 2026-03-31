#ifndef TWITTER_H
#define TWITTER_H

#include <vector>
using namespace std;

class Twitter {
public:
    Twitter();

    void postTweet(int userId, int tweetId);

    vector<int> getNewsFeed(int userId);

    void follow(int followerId, int followeeId);

    void unfollow(int followerId, int followeeId);

private:
    int timeStamp;
};

#endif
