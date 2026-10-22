/*Problem-2:
I used sweep line algo to calculate minimum number of meeting rooms required. The question boils down to no of rooms needed at any moment = no of meeting taking place simulatenously.
Approach : 
We define an event which is either start or end of a meeting. For each event we create +1 value signifying start of meeting and -1 signifying end of a meeting. and then sort the unique meetings with ascending order of time. 
So we make a vector of pair elements where each pair contains (timestamp, +1/-1) value.
So we have a mixture of events i.e start/end of meetings
We maintain the counter which would keep track of max no of meeting at any instant.
While traversing we see if a meeting starts we increase the counter because start event value is +1 and vice versa for end of meeting.
If a case arises that two meetings  overlap with same timestamp I keep end meeting prior to start meeting becuase ques says we can reuse the same room at collisions of time of start of one meeting  and end of another meeting.
So for each instant we keep track of maximum no of rooms needed and return that maximum value at the end

Can_Attend_ALL_function():
I sorted meetings by their start time and compare each meeting's start before previous one ends there is an overlap and our func returns a false and stops further checking 
At the end of the loop if no false was returned that means it is safe to attend all meetings hence return true;

Time Space Complexity:
sweep line algo : sorting takes : O(2nlog2n) time where n denotes number of time stamps + O(n) traversal
Overall time O(nlogn) and space = O(n) to store in a vector for each event/Timestamp entries which stores pair of (timestamp, +1/-1) value.

Can_Attend_ALL_function: Takes O(nlogn) for sorting and a space of O(1) becuase no additional space was taken.
*/
Code : 
class Solution {
  public:
    bool Can_Attend_ALL_function(vector<pair<int,int>> &events)
    {
        sort(events.begin(), events.end());
        for (int i = 1; i < events.size(); ++i)
        {
            if (events[i].first < events[i-1].second)
            {
                return false;
            }
        }
        return true;
    }
    int minMeetingRooms(vector<pair<int,int>>meetings) {
        int n = meetings.size();
        
        vector<pair<int,int>> events;
        for(int i = 0; i < n; i++) {
            int startPoint = meetings[i].first;
            int endPoint   = meetings[i].second;
            
            events.push_back(make_pair(startPoint, 1));
            events.push_back(make_pair(endPoint, -1));
        }
        sort (events.begin(), events.end(), 
    [](const pair<int,int>&a, const pair<int,int>&b){
        if (a.first == b.first)
        {
            return a.second < b.second;
        }
        else
        {
            return a.first < b.first;
        }
    });
    
        int ctr = 0;
        int maxi = 0;
        for(auto& p : events){
            int pts = p.second;
            ctr += pts;
            maxi = max (maxi, ctr);
        }
        return maxi;
    }
};