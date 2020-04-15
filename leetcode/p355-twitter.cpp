#include "../common/utils.hpp"

class Twitter {
public:
    struct Tweet {
        int sn;
        int id;
        struct Tweet* next;
    };

    struct Twist {
        int id;
        Tweet head;  
        unordered_set<int> follows;   
        Twist(int _id) {
            id=_id;
            head.next=&head;
            head.sn=-1;
        }   

        void post(int sn, int tweetId) {
            Tweet* t=new Tweet;
            t->sn=sn;
            t->id=tweetId;
            t->next=head.next;
            head.next=t;         
        }
    };

    /** Initialize your data structure here. */
    Twitter() {
        sn=0;
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        forceTwist(userId)->post(++sn, tweetId);
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        Twist* tist=getTwist(userId);
        if (!tist) return {};

        vector<Tweet*> cands(tist->follows.size()+1);
        int i=0;
        for(int followeeId: tist->follows) {
            Twist* followee=getTwist(followeeId);
            if (followee && followee->head.next!=&followee->head) 
                cands[i++]=followee->head.next;
        }
        if (tist->head.next!=&tist->head)
            cands[i++]=tist->head.next;
        if (i==0) return {};
        std::make_heap(cands.begin(), cands.begin() + i, [](Tweet* a, Tweet* b) { return a->sn<b->sn; });
        int n=0;
        vector<int> ans;
        ans.reserve(10);
        while (n<10 && i>0 && cands[0]->sn>0) {
            ans.push_back(cands[0]->id);
            std::pop_heap(cands.begin(), cands.begin() + i);
            cands[i-1]=cands[i-1]->next;
            if (cands[i-1]->sn>0) 
                std::push_heap(cands.begin(), cands.begin() + i, [](Tweet* a, Tweet* b) { return a->sn<b->sn; });
            else 
                --i;
            ++n;
        }
        return ans;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId!=followeeId)
            forceTwist(followerId)->follows.insert(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        Twist* tist=getTwist(followerId);
        if (tist)
            tist->follows.erase(followeeId);
    }
private:
    inline Twist* getTwist(int userId) {
        auto it=users.find(userId);
        return it==users.end()?nullptr:it->second;
    }

    Twist* forceTwist(int userId) {
        auto it=users.find(userId);
        if (it!=users.end()) return it->second;
        Twist* ans=new Twist(userId);
        users.insert({userId,ans});
        return ans;
    }
    int sn;
    unordered_map<int, Twist*> users;
};


int main() {
    Twitter* obj = new Twitter();
    obj->postTweet(1,5);
    cout << obj->getNewsFeed(1) << endl;
    obj->follow(1,2);
    obj->postTweet(2,6);
    cout << obj->getNewsFeed(1) << endl;   
    obj->unfollow(1,2);
    cout << obj->getNewsFeed(1) << endl;   
    return 0;
}